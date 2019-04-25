//---------------------------------------------------------------------------*/
//                     Constructor - Destructor                              //
//---------------------------------------------------------------------------*/
template <typename data>
Shared_body<data>::Shared_body (data *object):
  data_       (object),
  count_      (1)
  {
    PRINT (" Create body");
  }
//---------------------------------------------------------------------------*/
template <typename data>
Shared_body<data>::~Shared_body ()
{
  PRINT (" Destructor body");

  data_  = NULL;
  count_ = 0;
}
//---------------------------------------------------------------------------*/
//                            Public functions                               //
//---------------------------------------------------------------------------*/
template <typename data>
const int Shared_body<data>::count () const
{
  PRINT (" Count %d", count_);
  return count_;
}
//---------------------------------------------------------------------------*/
template <typename data>
const data *Shared_body<data>::get () const
{
  PRINT (" Get");
  return data_;
}
//---------------------------------------------------------------------------*/
template <typename data>
void Shared_body<data>::count_inc ()
{
  PRINT (" Inc");
  ++count_;
}
//---------------------------------------------------------------------------*/
template <typename data>
void Shared_body<data>::count_dec ()
{
  PRINT (" Dec");
  --count_;
}
//---------------------------------------------------------------------------*/
//                 © Gorbachev Nikita, April 2019                            //
//---------------------------------------------------------------------------*/
