//---------------------------------------------------------------------------*/
//                            Exception                                      //
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
class my_exception
{
  public:
    enum exc_code
    {
       ERR_UNTITLED           = 0,
       ERR_DIV_BY_ZERO        = 1,
       ERR_CANT_OPEN_FILE     = 2,
       ERR_CANT_CLOSE_FILE    = 3,
       ERR_BAD_INDEX          = 4,
       ERR_NULL_POINTER       = 5,
       ERR_NOT_ENOUGH_MEMORY  = 6,
    };

    my_exception  (const char*     filename, const char* func,
                   const long int  line,     const char* message,
                   exc_code        code);
    my_exception  (const my_exception&  except);
    my_exception  (      my_exception&& except);

    ~my_exception (void);

    void where (std::ostream& os);
    void what  (std::ostream& os);
    void code  (std::ostream& os);
    void info  (std::ostream& os);

  private:
    char*    message_;
    exc_code code_;
    char*    file_name_;
    char*    function_;
    long int line_;

};
//---------------------------------------------------------------------------*/
#include "exception.cpp"
#define MY_EXCEPTION(message, exc_code) my_exception(__FILE__, __func__, \
                                                     __LINE__, message, exc_code)
//---------------------------------------------------------------------------*/
#endif
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
