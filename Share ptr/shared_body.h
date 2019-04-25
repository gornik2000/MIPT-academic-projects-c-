//---------------------------------------------------------------------------*/
//                            Shared_body                                    //
//---------------------------------------------------------------------------*/
template <typename data>
class Shared_body
{
  private:
    data *data_;
    int   count_;

  public:
    Shared_body  (data *object);
    ~Shared_body ();

    const int  count () const;
    const data *get  () const;

    void count_inc ();
    void count_dec ();
};
//---------------------------------------------------------------------------*/
#include "shared_body.cpp"
//---------------------------------------------------------------------------*/
//                 © Gorbachev Nikita, April 2019                            //
//---------------------------------------------------------------------------*/
