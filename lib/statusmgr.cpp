#include <iostream>
#include <cstdio>
#include "statusmgr.hpp"

using namespace std;

void statusmgr::error(int code) {
  printf("Error: ");
  if (code == 1) {
    puts("The input is empty.");
  }
  exit(1);
}