
#include "encryptor_openssl.h"

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <boost/ptr_container/ptr_vector.hpp>

#include <muduo/base/Logging.h>
#include <muduo/base/CurrentThread.h>

#include "utils/string_utils.h"

namespace crypto {

bool SupportedCipher(muduo::StringPiece cipher_name) {
  static const char* supported_ciphers[] = {
      "aes-128-cfb", "aes-192-cfb", "aes-256-cfb", NULL,
  };

  for (int i = 0; supported_ciphers[i] != NULL; ++i) {
    if (cipher_name == supported_ciphers[i]) {
      return true;
    }
  }

  return false;
}

size_t GetCipherIvLength(muduo::StringPiece cipher_name) {
  EnsureOpenSSLInit();

  const EVP_CIPHER* cipher = EVP_get_cipherbyname(cipher_name.data());
  if (cipher == NULL) {
    return 0;
  }

  return EVP_CIPHER_iv_length(cipher);
}

Encryptor::Encryptor() {}

Encryptor::~Encryptor() {}

bool Encryptor::Init(muduo::StringPiece cipher_name_val,
                     muduo::StringPiece passwd_val, muduo::StringPiece iv_val,
                     bool do_encrypt) {
  EnsureOpenSSLInit();

  std::string gen_key;
  uint8_t* key_ptr = reinterpret_cast<uint8_t*>(
      utils::WriteInto(&gen_key, EVP_MAX_KEY_LENGTH + 1));

  const EVP_CIPHER* cipher = EVP_get_cipherbyname(cipher_name_val.data());
  if (cipher == NULL) return false;

  size_t key_len =
      EVP_BytesToKey(cipher, EVP_md5(), NULL,
                     reinterpret_cast<const unsigned char*>(passwd_val.data()),
                     passwd_val.size(), 1, key_ptr, NULL);

  gen_key.resize(key_len);

  assert(EVP_CIPHER_iv_length(cipher) == static_cast<int>(iv_val.size()));
  assert(EVP_CIPHER_key_length(cipher) == static_cast<int>(gen_key.size()));

  ScopedCipherCTXPtr ctx(new ScopedCipherCTX);
  if (!EVP_CipherInit_ex(ctx->get(), cipher, NULL,
                         reinterpret_cast<const uint8_t*>(gen_key.data()),
                         reinterpret_cast<const uint8_t*>(iv_val.data()),
                         do_encrypt)) {
    return false;
  }

  cipher_name_val.CopyToStdString(&cipher_name_);
  iv_val.CopyToStdString(&iv_);
  passwd_val.CopyToStdString(&passwd_);

  key_.swap(gen_key);
  ctx_.swap(ctx);
  do_encrypt_ = do_encrypt;

  return true;
}

bool Encryptor::Update(muduo::StringPiece plaintext, std::string* ciphertext) {
  assert(!plaintext.empty() && ciphertext != NULL);
  return Crypt(plaintext, ciphertext);
}

bool Encryptor::Update(const char* plaintext, int text_size,
                       std::string* ciphertext) {
  assert(plaintext != NULL && text_size > 0 && ciphertext != NULL);
  return Update(muduo::StringPiece(plaintext, text_size), ciphertext);
}

bool Encryptor::Update(muduo::StringPiece plaintext,
                       muduo::net::Buffer* ciphertext) {
  assert(!plaintext.empty() && ciphertext != NULL);
  return Crypt(plaintext, ciphertext);
}

bool Encryptor::Update(const muduo::net::Buffer* plaintext,
                       muduo::net::Buffer* ciphertext) {
  assert(plaintext != NULL && ciphertext != NULL);
  return Update(
      muduo::StringPiece(plaintext->peek(),
                         static_cast<int>(plaintext->readableBytes())),
      ciphertext);
}

bool Encryptor::Update(const char* plaintext, int text_size,
                       muduo::net::Buffer* ciphertext) {
  assert(plaintext != NULL && text_size > 0 && ciphertext != NULL);
  return Update(muduo::StringPiece(plaintext, text_size), ciphertext);
}

bool Encryptor::Crypt(muduo::StringPiece input, muduo::net::Buffer* output) {
  assert(ctx_);
  assert(output != NULL);

  std::string result;
  if (!DoCrypt(input, &result)) {
    return false;
  }

  output->append(result);
  return true;
}

bool Encryptor::Crypt(muduo::StringPiece input, std::string* output) {
  assert(ctx_);
  assert(output != NULL);

  std::string result;
  if (!DoCrypt(input, &result)) {
    return false;
  }

  output->swap(result);
  return true;
}

bool Encryptor::DoCrypt(muduo::StringPiece input, std::string* output) {
  assert(ctx_);
  assert(output != NULL);
  output->clear();

  const int output_size =
      input.size() + (do_encrypt_ ? static_cast<int>(iv_.size()) : 0);
  assert(output_size > 0);
  assert(output_size + 1 > input.size());

  uint8_t* out_ptr =
      reinterpret_cast<uint8_t*>(utils::WriteInto(output, output_size + 1));
  int out_len;
  if (!EVP_CipherUpdate(ctx_->get(), out_ptr, &out_len,
                        reinterpret_cast<const uint8_t*>(input.data()),
                        input.size())) {
    return false;
  }

  int tail_len;
  if (!EVP_CipherFinal_ex(ctx_->get(), out_ptr + out_len, &tail_len)) {
    return false;
  }

  out_len += tail_len;
  assert(out_len <= static_cast<int>(output_size));
  output->resize(out_len);

  return true;
}
}
