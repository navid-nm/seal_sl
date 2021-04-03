#include <iostream>
#include <cstdio>
#include "StatusManager.hpp"

using namespace std;

void StatusManager::error(int code) {
  printf("Error: ");
  if (code == 1) {
    puts("The input is empty.");
  }
  exit(1);
}