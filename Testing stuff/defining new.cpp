#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define NEW new(__LINE__, __func__)

inline void *operator new[] (size_t size, int line, const char *fun)
{
  printf (" <new> line %d function %s\n", line, fun);
  return malloc (size);
}

inline void operator delete[] (void *p, int line) noexcept
{
  printf (" <delete> line %d\n", __LINE__);
  free (p);
}

int main()
{
  int *a = NEW int[64];
  delete[] a;

  return 0;
}
