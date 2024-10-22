module;

#include <print>

export module Log;

export namespace Log {
  void debug (){
    std::print("hello from module!");
  }
};
