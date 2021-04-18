#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include "lib/statusmgr.hpp"
#include "lib/builtin.hpp"
#include "lib/sysc.hpp"

using namespace std;

statusmgr status;
bfunc self;
sysc sys;

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
  if (with(true, full, type + "(")) {
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
  } else if (proper("sleep", com)) {
    self.sleep(stoi(getcontent(com)));
  }
}
 
string trim(string s) {
  string whitespace = " \n\r\t\f\v";
  size_t start = s.find_first_not_of(whitespace);
  s = (start == string::npos) ? "" : s.substr(start);
  size_t end = s.find_last_not_of(whitespace);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

bool forever(vector<string> prog, int index) {
  bool paiddues;
  string curinst; 
  int offset = 0;
  while(1) {
    curinst = prog[index + offset];
    if (curinst == "<") {
      offset = 0;
    } else if (curinst == "stop") {
      paiddues = false;
      break;
    }
    processcommand(curinst);
    offset++;
  }
  return paiddues;
}

void execflow(vector<string> prog) {
  int index = 0;
  bool paiddues = true;
  for (auto i : prog) {
    if (i == "forever >") {
      paiddues = forever(prog, index);
    }
    if (paiddues) {
      processcommand(prog[index]);
    } else if (prog[index] == "<") {
      paiddues = true;
    }
    index++;
  }
}

int main(int argc, char* argv[]) {
  sys.clear();
  vector<string> instructions;
  fstream fstr; fstr.open(argv[1]);
  if (fstr.fail()) {
    status.error(1);
  } else {
    string line;
    while (getline(fstr, line)) {
      instructions.push_back(trim(line));
    }
    execflow(instructions);
  }
  return 0;
}