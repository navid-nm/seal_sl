#include <iostream>
#include <string>
#include <cstdio>
#include "builtin.hpp"

using namespace std;

void builtin::say(string text) {
  printf("%s\n", text.c_str());
}