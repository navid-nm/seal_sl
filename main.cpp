#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include "lib/statusmgr.hpp"
#include "lib/builtin.hpp"

using namespace std;

statusmgr status;
builtin self;

/*
  startend: True for start, false for end
  full:     The entire str
  es:       The ending/start of the str
*/
bool with(bool startend, string full, string es) {
  bool out = false;
  if (!startend) {
    if (full.length() >= es.length()) {
      return (0 == full.compare(full.length() - es.length(), es.length(), es));
    }
  } else {
    if (full.rfind(es, 0) == 0) {
      out = true;
    }
  }
  return out;
}

/*
  type: The type of command
  full: The users attempt at a command
*/
bool proper(string type, string full) {
  if (with(true, full, type + "(") && with(false, full, ")")) {
    return true;
  }
  return false;
}

string getcontent(string com) {
  int pos = com.find('(') + 1;
  return com.substr(pos, com.find(')', pos) - pos);
}

void processcommand(string com) {
   if (proper("say", com)) {
    self.say(getcontent(com));
   }
}

void execflow(list<string> prog) {
  for (auto i : prog) {
    processcommand(i);
  }
}

int main(int argc, char* argv[]) {
  system("clear");
  list<string> instructions;
  fstream fstr;
  fstr.open(argv[1]);
  if (fstr.fail()) {
    status.error(1);
  } else {
    string line;
    while (getline(fstr, line)) {
      instructions.push_back(line);
    }
    execflow(instructions);
  }
  return 0;
}