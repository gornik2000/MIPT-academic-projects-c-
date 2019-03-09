//*/---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>
//*/---------------------------------------------------------------------------
#ifdef DEBUG
  #define PRINT_LOGS(s, a)                                                    \
  {                                                                           \
    fprintf(log_file_memory, s, a);                                           \
  }
#else
  #define PRINT_LOGS(s, a);
#endif
//*/---------------------------------------------------------------------------
const char *log_file_memory_name = "memory_log.txt";
FILE *log_file_memory            = fopen (log_file_memory_name, "w");
//*/---------------------------------------------------------------------------

void *operator new   (size_t size);
void *operator new[] (size_t size);

void operator delete   (void *p) noexcept;
void operator delete[] (void *p) noexcept;
//*/---------------------------------------------------------------------------
void *operator new (size_t size)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS ("ERROR NULL memory pointer", 0);
  }
  else
  {
    PRINT_LOGS ("%d allocated", p);
  }
  PRINT_LOGS (" at %d\n", time(NULL));

  return p;
}
//*/---------------------------------------------------------------------------
void *operator new[] (size_t size)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS ("ERROR NULL memory pointer", 0);
  }
  else
  {
    PRINT_LOGS ("%d allocated", p);
  }
  PRINT_LOGS (" at %d\n", time(NULL));

  return p;
}
//*/---------------------------------------------------------------------------
void operator delete (void *p) noexcept
{
  PRINT_LOGS ("%d freed    ", p);
  PRINT_LOGS (" at %d\n", time(NULL));

  free (p);
}
//*/---------------------------------------------------------------------------
void operator delete[] (void *p, char *file_name,
                        char *fn_name, int line) noexcept
{
  PRINT_LOGS ("%d freed    ", p);
  PRINT_LOGS (" at %d\n", time(NULL));

  free (p);
}
//*/---------------------------------------------------------------------------
#undef PRINT_LOGS
//*/---------------------------------------------------------------------------
