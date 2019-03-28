//---------------------------------------------------------------------------*/
//                        Class vector <bool>                                //
//---------------------------------------------------------------------------*/
template <>
class vector<bool>
{
  private:
    bool_t *data_;
    size_t  size_;
    class reference
    {
      private:
        friend class vector;
        bool_t *arr_;
        size_t  num_;
        explicit reference();
      public:
        ~reference();
        operator bool() const;
        reference& operator=(bool b);
        reference& operator=(const reference& that);
    };
  public:
    explicit vector  ();
    vector  (vector &&that);
    vector  (const vector& that);
    vector  (size_t size);
    ~vector ();

    const size_t memsize () const;
    const size_t size    () const;
    const char   poison  () const;

    void swap   (vector &that);
    char resize (size_t count);
    void clear  ();

    reference at (size_t index);
    reference operator[] (size_t index);

    const reference at (size_t index) const;
    const reference operator[] (size_t index) const;

    const vector &operator= (const vector& that);
    const vector &operator= (vector&&      that);
};
//---------------------------------------------------------------------------*/
#include "vector_bool.cpp"
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
