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

inline void *operator new   (size_t size);
inline void *operator new[] (size_t size);

inline void operator delete   (void *p) noexcept;
inline void operator delete[] (void *p) noexcept;
//*/---------------------------------------------------------------------------
inline void *operator new (size_t size)
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
inline void *operator new[] (size_t size)
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
  PRINT_LOGS (" at %d", time(NULL));
  PRINT_LOGS (" line %d\n", __LINE__);

  return p;
}
//*/---------------------------------------------------------------------------
inline void operator delete (void *p) noexcept
{
  PRINT_LOGS ("%d freed    ", p);
  PRINT_LOGS (" at %d\n", time(NULL));

  free (p);
}
//*/---------------------------------------------------------------------------
inline void operator delete[] (void *p) noexcept
{
  PRINT_LOGS ("%d freed    ", p);
  PRINT_LOGS (" at %d\n", time(NULL));

  free (p);
}
//*/---------------------------------------------------------------------------
#undef PRINT_LOGS
//*/---------------------------------------------------------------------------
