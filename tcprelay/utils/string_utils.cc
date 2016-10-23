

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "string_utils.h" 

namespace utils {

void GenRandString(std::string* str, int len) {
  assert(str != NULL && len > 0);
  uint8_t* ptr = reinterpret_cast<uint8_t*>(WriteInto(str, len+1));
  for (int i = 0; i < len; ++i) {
    uint8_t uch = static_cast<uint8_t>(rand() & 0xFF);
    ptr[i] = uch;
  }
  ptr[len] = '\0';
}

std::string GenRandString(int len) {
  std::string str;
  GenRandString(&str, len);
  return str;
}

void HexDump(const muduo::StringPiece& sp, std::string* result) {
  assert(result != NULL); 
  int now_len = 0;
  int len_with_null = 5 * sp.size() + 1;
  char* ptr = reinterpret_cast<char*>(WriteInto(result, len_with_null));
  for (int i = 0; i < sp.size(); ++i) {
    if (!(now_len >= 0 && now_len < len_with_null)) return;
    int nc = snprintf(ptr+now_len, len_with_null-now_len,
                      "0x%02x ", static_cast<uint8_t>(sp[i])); 
    if (nc <= 0) return;
    now_len += nc;
  }
}

std::string HexDump(const muduo::StringPiece& sp) {
  std::string result;
  HexDump(sp, &result);
  return result;
}

std::string HexDump(const void* ptr, int len) {
  assert(ptr != NULL && len > 0);
  return HexDump(muduo::StringPiece(static_cast<const char*>(ptr), len));
}

void HexDump(const void* ptr, int len, std::string* result) {
  assert(ptr != NULL && len > 0 && result != NULL);
  HexDump(muduo::StringPiece(static_cast<const char*>(ptr), len), result);
}

void Split(std::string str, char delim, std::vector<std::string>* vs) {
  assert (vs != NULL);
  int len = static_cast<int>(str.size());
  for (int i = 0; i < len; ++i) {
    if (str[i] == delim) str[i] = ' ';
  }
  std::stringstream ss(str);
  std::string x;
  while (ss >> x) {
    vs->push_back(x); 
  }
}

std::vector<std::string> Split(const std::string& str, char delim) {
  std::vector<std::string> vs;
  Split(str, delim, &vs);
  return vs;
}

void Join(const std::string& str, const std::vector<std::string>& vs, std::string* result) {
  assert(result != NULL);
  int str_len = static_cast<int>(str.size());
  int vs_len = static_cast<int>(vs.size());
  int total_len = (vs_len > 0) ? (vs_len-1)*str_len : 0; 

  assert(str_len >= 0);
  assert(vs_len >= 0);
  for (int i = 0; i < vs_len; ++i) {
    total_len += static_cast<int>(vs[i].size());
  }
  assert(total_len >= 0);

  char* ptr = reinterpret_cast<char*>(WriteInto(result, total_len+1));
  int now_len = 0;
  for (int i = 0; i < vs_len; ++i) {
    int len = static_cast<int>(vs[i].size());
    for (int j = 0; j < len; ++j) {
      ptr[now_len++] = vs[i][j];
    } 
    if (i < vs_len - 1) {
      for (int j = 0; j < str_len; ++j) {
        ptr[now_len++] = str[j];
      }
    }
  }
}

std::string Join(const std::string& str, const std::vector<std::string>& vs) {
  std::string result;
  Join(str, vs, &result);
  return result;
}

}
