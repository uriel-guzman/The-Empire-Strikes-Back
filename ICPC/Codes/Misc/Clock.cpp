struct Clock {
  clock_t start;

  Clock() : start(clock()) {}

  unsigned now() {
    return (clock() - start) * (int)1e3 / CLOCKS_PER_SEC;
  }
};