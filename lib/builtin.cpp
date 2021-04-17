#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "builtin.hpp"

using namespace std;

void builtin::say(string text) {
  printf("%s\n", text.c_str());
}

void builtin::sleep(int time) {
  usleep(time * pow(10, 6));
}