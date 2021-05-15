#include <iostream>
#include <string>

enum type {INT, STR, SWITCH};

class bfunc {
  public:
    void say(std::string text);
    void sleep(int time);
};

class strfrm {
  public:
    std::string trim(std::string text);
    std::string removeallwsp(std::string text);
};

class var {
  public:
    void gettype();
    void set(std::string val);
};