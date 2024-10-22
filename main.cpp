#include <print>

import Log;

int main (int argc, char** argsv){
  std::print("Hello from main!");

  Log::debug("Hello from module!");

  return 0;
}

