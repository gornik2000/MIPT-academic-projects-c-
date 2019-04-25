//---------------------------------------------------------------------------*/
#include <stdio.h>
#include <iostream>
//---------------------------------------------------------------------------*/
#ifdef DEBUG
  #define PRINT(s, ...) printf(" Shared_ptr " s "\n", ##__VA_ARGS__)
#else
  #define PRINT(s, ...)
#endif
//---------------------------------------------------------------------------*/
#include "shared_body.h"
//---------------------------------------------------------------------------*/
//                              Shared_ptr                                   //
//---------------------------------------------------------------------------*/
template <typename data>
class Shared_ptr
{
  private:
    Shared_body<data> *body_;

  public:
    Shared_ptr (data *object);
    Shared_ptr (const Shared_ptr& that);
    ~Shared_ptr ();

    void  swap (Shared_ptr& that);

    const Shared_ptr& operator= (const Shared_ptr& that);
    const Shared_ptr& operator= (data *object);
    const data        operator* ();
};
//---------------------------------------------------------------------------*/
#include "shared_ptr.cpp"
//---------------------------------------------------------------------------*/
#ifdef DEBUG
  #define Shared_ptr(type) Shared_ptr<type>
#else
  #define Shared_ptr(type) type *
#endif
//---------------------------------------------------------------------------*/
#undef PRINT
//---------------------------------------------------------------------------*/
//                 © Gorbachev Nikita, April 2019                            //
//---------------------------------------------------------------------------*/
