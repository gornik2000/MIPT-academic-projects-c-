//---------------------------------------------------------------------------*/
//                     Constructor - Destructor                              //
//---------------------------------------------------------------------------*/
template <typename data>
Shared_ptr<data>::Shared_ptr (data *object):
  body_ (NULL)
  {
    PRINT (" Create ptr");

    body_ = new Shared_body<data> (object);
  }
//---------------------------------------------------------------------------*/
template <typename data>
Shared_ptr<data>::Shared_ptr (const Shared_ptr<data>& that):
  body_ (that.body_)
  {
    PRINT (" Create copy");

    body_->count_inc ();
  }
//---------------------------------------------------------------------------*/
template <typename data>
Shared_ptr<data>::~Shared_ptr ()
{
  PRINT (" Destructor");

  body_->count_dec ();
  if (body_->count () == 0)
  {
    delete body_;
  }
  else
  {
    PRINT (" WARNING! DSTR while ptrs existing");
  }

  body_ = NULL;
}
//---------------------------------------------------------------------------*/
//                            Public functions                               //
//---------------------------------------------------------------------------*/
template <typename data>
void Shared_ptr<data>::swap (Shared_ptr<data>& that)
{
  PRINT (" Swap");

  std::swap (body_, that.body_);
}
//---------------------------------------------------------------------------*/
//                            Public operators                               //
//---------------------------------------------------------------------------*/
template <typename data>
const Shared_ptr<data>& Shared_ptr<data>::operator= (const Shared_ptr<data>& that)
{
  PRINT (" = set");
  if (body_ == that.body_) return *this;

  body_->count_dec ();
  body_ = that.body_;
  body_->count_inc ();

  return *this;
}
//---------------------------------------------------------------------------*/
template <typename data>
const Shared_ptr<data>& Shared_ptr<data>::operator= (data *object)
{
  PRINT (" = ptr");
  if (body_->get () == object) return *this;

  body_->count_dec ();
  body_ = new Shared_body<data> (object);

  PRINT (" = ptr");
  return *this;
}
//---------------------------------------------------------------------------*/
template <typename data>
const data Shared_ptr<data>::operator* ()
{
  PRINT (" *");

  return *(body_->get ());
}
//---------------------------------------------------------------------------*/
//                 © Gorbachev Nikita, April 2019                            //
//---------------------------------------------------------------------------*/
