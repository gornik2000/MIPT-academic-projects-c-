#include <stdio.h>
#include <ctime>

#define rdtscll(val) __asm__ __volatile__("rdtsc" :"=A"(val))
// Type of val --- unsigned long long

int main()
{
  int iterations = 10000;
  long long a[2] = {0};
  long long b = 0;
  for (int j = 0; j < iterations; j++)
  {
    rdtscll(a[0]);
    for (int i = 0; i < 10000; i++);
    rdtscll(a[1]);
    b += a[1] - a[0];
    //printf ("%d\n", a[1] - a[0]);
  }
  printf ("%ld\n", b);
  return 0;
}
