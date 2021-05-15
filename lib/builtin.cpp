#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "builtin.hpp"

using namespace std;

void bfunc::say(string text) {
  printf("%s\n", text.c_str());
}

void bfunc::sleep(int time) {
  usleep(time * pow(10, 6));
} 

string strfrm::trim(string s) {
  string whitespace = " \n\r\t\f\v";
  size_t start = s.find_first_not_of(whitespace);
  s = (start == string::npos) ? "" : s.substr(start);
  size_t end = s.find_last_not_of(whitespace);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string strfrm::removeallwsp(string s) {
  s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
  return s;
}