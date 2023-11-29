#define ASSERT(condition)                                                      \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "Assertion failed: (%s), file %s, line %d\n",            \
              #condition, __FILE__, __LINE__);                                 \
      abort();                                                                 \
    }                                                                          \
  } while (0)


