#include <iostream>
#include <string>
#include <cstdio>
#include "BuiltIn.hpp"

using namespace std;

void BuiltIn::say(string text) {
  printf("%s\n", text.c_str());
}