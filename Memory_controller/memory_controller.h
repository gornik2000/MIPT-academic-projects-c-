//---------------------------------------------------------------------------*/
#ifdef DEBUG
  #define PRINT_LOGS_MEM(s, ...) \
    fprintf(log_file_memory, "%s " s "\n", __TIME__, ##__VA_ARGS__)
#else
  #define PRINT_LOGS_MEM(s, ...)
#endif
//---------------------------------------------------------------------------*/
#define NEW new(__FILE__, __func__, __LINE__)
#define DELETE(p)                                                             \
{                                                                             \
  PRINT_LOGS_MEM ("%8d freed     %s %s %d", p, __FILE__, __func__, __LINE__); \
  delete p;                                                                   \
}
//---------------------------------------------------------------------------*/
const char *log_file_memory_name = "memory_log.txt";
FILE       *log_file_memory      = fopen (log_file_memory_name, "w");
//---------------------------------------------------------------------------*/
inline void *operator new   (size_t size, const char* file, \
                             const char *fun, int line);

inline void *operator new[] (size_t size, const char* file, \
                             const char *fun, int line);
//---------------------------------------------------------------------------*/
#include "scan.h"
//---------------------------------------------------------------------------*/
//                       Memory Operators                                    //
//---------------------------------------------------------------------------*/
inline void *operator new (size_t size, const char* file, \
                           const char *fun, int line)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS_MEM ("ERROR memory was not allocated %s %s %d", file, fun, line);
    return p;
  }

  PRINT_LOGS_MEM ("%8d allocated %s %s %d", p, file, fun, line);
  return p;
}
//---------------------------------------------------------------------------*/
inline void *operator new[] (size_t size, const char* file, \
                             const char *fun, int line)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS_MEM ("ERROR memory was not allocated %s %s %d", file, fun, line);
    return p;
  }

  PRINT_LOGS_MEM ("%8d allocated %s %s %d", p, file, fun, line);
  return p;
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
