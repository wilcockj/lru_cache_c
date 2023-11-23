#include "lru.h"
int fib(int n) {
  if (n < 2)
    return n;
  return fib(n - 1) + fib(n - 2);
}

int main() {

  char *test = "asdasdasdasdasdas";
  create_lru(2, 3, 34123123, 123, 123, 123, 12, 312, 312, 312, 3, 13, 1, 2, 3,
             4, 5);
  return 0;
}
