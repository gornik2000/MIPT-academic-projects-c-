//---------------------------------------------------------------------------*/
#ifndef MY_EXCEPTION
#define MY_EXCEPTION
//---------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------------*/
char* strdup (const char* src)
{
  size_t len   = strlen (src);
  char* result = (char *)malloc (len + 1);

  if (result == NULL)
  {
    return NULL;
  }

  memcpy (result, src, len + 1);
  return result;
}
//---------------------------------------------------------------------------*/
class my_exception
{
  public:
    enum exc_code
    {
       UNTITLED            = 0,
       DIV_BY_ZERO         = 1,
       CANT_OPEN_FILE      = 2,
       CANT_CLOSE_FILE     = 3,
       ARRAY_OUT_OF_RANGE  = 4,
       NULL_POINTER        = 5,
       NOT_ENOUGH_MEMORY   = 6,
    };

    my_exception  (const char* filename, const char* func,
                   const long int line, const char* message,
                   exc_code code);
    my_exception  (const my_exception& except);
    my_exception  (my_exception&&      except);
    ~my_exception (void);

    void where (std::ostream& os);
    void what  (std::ostream& os);
    void code  (std::ostream& os);

  private:
    char*    message_;
    exc_code code_;
    char*    file_name_;
    char*    function_;
    long int line_;

};
//---------------------------------------------------------------------------*/
#include "exception.cpp"
//---------------------------------------------------------------------------*/
#endif
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
