//---------------------------------------------------------------------------*/
#include "exception.h"
#define MY_EXCEPTION(message, exc_code) my_exception(__FILE__, __func__, \
                                                     __LINE__, message, exc_code)
//---------------------------------------------------------------------------*/
void fun_one (void)
{
  try
  {
    if (42)
    {
      throw (MY_EXCEPTION(" Testing exception ", my_exception::ERR_UNTITLED));
    }
  }
  catch (my_exception& except)
  {
    throw;
  }
}
//---------------------------------------------------------------------------*/
void fun_two (void)
{
  fun_one ();
}
//---------------------------------------------------------------------------*/
int main (int argc, char const *argv[])
{
  try
  {
    fun_two ();
  }
  catch (my_exception& except)
  {
    except.info (std::cout);
  }
  return 0;
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
