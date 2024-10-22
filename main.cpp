import Log;

int main (int argc, char** argsv){
    (void) argc;
    (void) argsv;

    for (int i = 0; i < 10'000'000; i++) {
      Log::debug("{}{} {} {}\n", "Hello World", '!', 42, 3.14);
    }

    return 0;
}

