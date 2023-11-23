#include "lru.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
want to hash as function if possible, not sure if it is, other than macro
magic
_create_lru(size_t Arg, unsigned long hash
unsigned long hash_args(size_t Arg, ...) {
  va_list sArg;
  int num_args = Arg;
  unsigned long hash = 0;
  // get first arg
  // which is just number of args
  va_start(sArg, Arg);
  while (--Arg) {
    hash = va_arg(sArg, size_t) + (hash << 6) + (hash << 16) - hash;
  }
  return hash;
}
*/

lru *_create_lru(size_t max_len, size_t Arg, ...) {
  lru *new_lru = malloc(sizeof(lru));
  new_lru->max_len = max_len;
  new_lru->len = 0;
  new_lru->head = NULL;
  new_lru->tail = NULL;
  printf("max len = %d\n", new_lru->max_len);
  va_list sArg;
  printf("number of args = %ld\n", Arg);
  int num_args = Arg;
  va_start(sArg, Arg);

  unsigned long hash = 0;
  // get first arg
  // which is just number of args
  va_start(sArg, Arg);
  while (--Arg) {
    hash = va_arg(sArg, size_t) + (hash << 6) + (hash << 16) - hash;
  }
  // make a hash table and use the hash we made as the key

  // hash is hash unique to these args
  printf("hash = %lu\n", hash);

  Arg = num_args;
  va_start(sArg, Arg);
  while (--Arg) {
    printf("%ld = %ld\n", num_args - Arg - 1, va_arg(sArg, size_t));
  }
  return new_lru;
}
