#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <regex>
#include "lib/StatusManager.hpp"

using namespace std;
StatusManager sm;

int main(int argc, char* argv[]) {
  system("clear");
  const regex say("^(?:say\())");

  fstream fstr;
  fstr.open(argv[1]);
  if (fstr.fail()) {
    sm.error(1);
  } else {
    string line;
    while (getline(fstr, line)) {
      auto wrdbegin = sregex_iterator(line.begin(), line.end(), say);
      auto wrdend = sregex_iterator();
      auto pos = line.find('(') + 1;
      if (distance(wrdbegin, wrdend) == 1) {
        string mouth = line.substr(pos, line.find(')', pos) - pos);
        printf("%s\n", mouth.c_str());
      }
    }
  }
    
  return 0;
}