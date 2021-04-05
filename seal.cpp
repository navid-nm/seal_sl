#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include "lib/StatusManager.hpp"

using namespace std;
StatusManager sm;

void processcommand(string command) {
  const regex say("^(?:say\())");
  auto wrdbegin = sregex_iterator(command.begin(), command.end(), say);
  auto wrdend = sregex_iterator();
  int pos = command.find('(') + 1;
  if (distance(wrdbegin, wrdend) == 1) {
    string mouth = command.substr(pos, command.find(')', pos) - pos);
    printf("%s\n", mouth.c_str());
  }
}

void execflow(list<string> list) {
  for (auto i : list) {
    processcommand(i);
  }
}

int main(int argc, char* argv[]) {
  system("clear");
  list<string> instructions;
  fstream fstr;
  fstr.open(argv[1]);
  if (fstr.fail()) {
    sm.error(1);
  } else {
    string line;
    while (getline(fstr, line)) {
      instructions.push_back(line);
    }
    execflow(instructions);
  }
  return 0;
}