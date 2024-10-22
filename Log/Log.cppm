module;

#include <print>

export namespace Log {
  void debug (const char * fmt){
    std::print(fmt);
  }
};
