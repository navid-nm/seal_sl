#include <cstdio>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "lib/statusmgr.hpp"
#include "lib/builtin.hpp"
#include "lib/sysc.hpp"

using namespace std;

map<string, vector<string>> vars;
statusmgr status;
strfrm ptols;
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

string getins(string s, string start, string end) {
  int pos = s.find(start) + 1;
  return s.substr(pos, s.find(end, pos) - pos);
}

string resolvevar(string name) {
  if (vars.find(name) == vars.end()) {
    return "null";
  } else {
    return vars[name][1];
  }
}

void assignvar(string &s) {
  vector<string> tandv;
  string vname = getins(s, "$", "="), type = getins(s, "=", "("), val = getins(s, "(", ")");
  tandv.push_back(type); tandv.push_back(val);
  vars[vname] = tandv;
}

/*
  argss[0]: variable name
  argss[1]: increment value
*/
void incvar(string com) {
  com = getins(com, "(", ")");
  vector<string> argss; string tmp; 
  stringstream ss(com);
  while (getline(ss, tmp, ',')) { 
      argss.push_back(tmp);
  }
  argss[0].erase(argss[0].begin());
  int tempint = stoi(vars[argss[0]][1]) + stoi(argss[1]);
  vars[argss[0]][1] = to_string(tempint);
}

string tokenise(string innerc) {
  vector<string> tokens; string res;
  string tmp; 
  stringstream ss(innerc);
  while (getline(ss, tmp, ' ')) { 
      tokens.push_back(tmp);
  }
  for (int i = 0; i < tokens.size(); i++) {
    string first, toadd; first.push_back(tokens[i][0]);
    if (first == "$") {
      string vtres = tokens[i];
      vtres.erase(vtres.begin());
      toadd = resolvevar(vtres);
    } else {
      toadd = tokens[i];
    }
    res += toadd + " ";
  }
  return res;
}

string getcontent(string com) {
  int pos = com.find('(') + 1;
  string content = com.substr(pos, com.find(')', pos) - pos); //previous return val
  if (content.find('$') + 1 != string::npos) {
    content = tokenise(content);                              //found $, so tokenise
  }
  return content;
}

void processcommand(string com) {
  string first; first.push_back(com[0]);
  if (proper("say", com)) {
    self.say(getcontent(com));
  } else if (proper("sleep", com)) {
    self.sleep(stoi(getcontent(com)));
  } else if (proper("inc", com)) {
    incvar(com);
  } else if (first == "$") {
    com = ptols.removeallwsp(com);
    if (vars.find(getins(com, "$", "=")) == vars.end()) {
      assignvar(com); //not found, therefore assign
    }
  }
}

bool forever(vector<string> prog, int index) {
  bool switchp; string curinst; int offset = 0;
  while(1) {
    curinst = prog[index + offset];
    if (curinst == "<") {
      offset = 0;
    } else if (curinst == "stop") {
      switchp = false;
      break;
    }
    processcommand(curinst);
    offset++;
  }
  return switchp;
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
      instructions.push_back(ptols.trim(line));
    }
    execflow(instructions);
  }
  return 0;
}