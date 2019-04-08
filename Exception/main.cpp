//---------------------------------------------------------------------------*/
#include "exception.h"
#define MY_EXCEPTION(message, exc_code) my_exception(__FILE__, __func__, \
                                                     __LINE__, message, exc_code)
//---------------------------------------------------------------------------*/
void goo (void)
{
  try
  {
    if (0 == 0)
    {
      throw (MY_EXCEPTION("Testing", my_exception::DIV_BY_ZERO));
    }
  }
  catch (my_exception& except)
  {
    throw;
  }
}
//---------------------------------------------------------------------------*/
void foo (void)
{
  goo ();
}
//---------------------------------------------------------------------------*/
int main (int argc, char const *argv[])
{
  try
  {
    foo ();
  }
  catch (my_exception& except)
  {
    except.where (std::cout);
    except.what  (std::cout);
    except.code  (std::cout);
  }
  return 0;
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
