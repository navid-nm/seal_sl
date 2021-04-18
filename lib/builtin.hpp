#include <iostream>
#include <string>

enum type {INT, STR, SWITCH};

class builtin {
  public:
    void say(std::string text);
    void sleep(int time);
};

class var {
  public:
    void gettype();
    void set(std::string val);
};