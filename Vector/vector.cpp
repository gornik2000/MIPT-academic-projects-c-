//*/-------------------------------------------------------------------------//
//                             Header                                        //
//*/-------------------------------------------------------------------------//
#include "vector.h"
//*/-------------------------------------------------------------------------//
//                    Constructor - Destructor                               //
//*/-------------------------------------------------------------------------//
vector::vector ():
  data_     (NULL),
  size_ (0)
  {
    PRINT_LOGS (" # Vector was created with zero size\n", 0);
  }
//*/---------------------------------------------------------------------------
vector::vector (const vector& that):
  data_     (new vector_data [that.size_]{}),
  size_ (that.size_)
  {
    for (int i = 0; i < size_; i++)
    {
      data_[i] = that.data_[i];
    }
    PRINT_LOGS (" # Vector was copied\n", 0);
  }
//*/---------------------------------------------------------------------------
vector::vector (vector_pars size):
  data_     (new vector_data [size]{}),
  size_ (size)
  {
    PRINT_LOGS (" # Vector was created with %d size\n", size);
  }
//*/---------------------------------------------------------------------------
vector::~vector ()
{
  clear (VECTOR_POISON);
  delete[] data_;

  size_ = -1;
  data_     = NULL;

  PRINT_LOGS (" # Vector was destroyed\n", 0);
}
//*/-------------------------------------------------------------------------//
//                             Public                                        //
//*/-------------------------------------------------------------------------//
vector_pars vector::size ()
{
  return size_;
}
//*/---------------------------------------------------------------------------
char vector::clear (vector_data content)
{
  for (int i = 0; i < size_; i++)
  {
    data_[i] = content;
  }

  PRINT_LOGS (" # Vector was cleared with %d\n", content);
  return 0;
}
//*/---------------------------------------------------------------------------
char vector::resize (vector_pars count)
{
  if (size_ <  count)
  {
    vector_data *new_data = new vector_data [count]{0};
    for (int i = 0; i < size_; i++)
    {
      new_data[i] = data_[i];
    }
    clear (VECTOR_POISON);
    delete[] data_;

    data_     = new_data;
    size_ = count;

    PRINT_LOGS (" # Vector size was changed to %d\n", count);
    return 0;
  }
  if (size_ >  count)
  {
    vector_data *new_data = new vector_data [count]{0};
    for (int i = 0; i < count; i++)
    {
      new_data[i] = data_[i];
    }
    clear (VECTOR_POISON);
    delete[] data_;

    data_     = new_data;
    size_ = count;

    PRINT_LOGS (" # Vector size was changed to %d\n", count);
    return 0;
  }
  PRINT_LOGS (" # Vector size wasn't changed\n", 0);
  return 0;
}
//*/---------------------------------------------------------------------------
char vector::swap (vector &that)
{
  std::swap (size_, that.size_);
  std::swap (data_, that.data_);
}
//*/---------------------------------------------------------------------------
char vector::print ()
{
  for (int i = 0; i < size_; i++)
  {
    std::cout << data_[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
//*/-------------------------------------------------------------------------//
//                            Public Operators                               //
//*/-------------------------------------------------------------------------//
vector_data &vector::operator[] (vector_pars index)
{
  return data_[index];
}
//*/---------------------------------------------------------------------------
const vector &vector::operator= (const vector& that)
{
  vector copy = that;
  swap (copy);

  PRINT_LOGS (" # Vector was assigned\n", 0);
  return *this;
}
//*/-------------------------------------------------------------------------//
//                          Friend Operators                                 //
//*/-------------------------------------------------------------------------//
vector operator+ (const vector& a, const vector& b)
{
  vector result (b.size_);

  for (int i = 0; i < b.size_; i++)
  {
    result[i] = a.data_[i] + b.data_[i];
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator+ (const vector_data& a, const vector& b)
{
  vector result (b.size_);

  for (int i = 0; i < b.size_; i++)
  {
    result[i] = a + b.data_[i];
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator+ (const vector& a, const vector_data& b)
{
  vector result (a.size_);

  for (int i = 0; i < a.size_; i++)
  {
    result[i] = b + a.data_[i];
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator- (const vector& a, const vector& b)
{
  vector result (a.size_);

  for (int i = 0; i < a.size_; i++)
  {
    result[i] = a.data_[i] - b.data_[i];
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator- (const vector& a, const vector_data& b)
{
  vector result (a.size_);

  for (int i = 0; i < a.size_; i++)
  {
    result[i] = a.data_[i] - b;
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator* (const vector_data& a, const vector& b)
{
  vector result (b.size_);

  for (int i = 0; i < b.size_; i++)
  {
    result[i] = a * b.data_[i];
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator* (const vector& a, const vector_data& b)
{
  vector result (a.size_);

  for (int i = 0; i < a.size_; i++)
  {
    result[i] = a.data_[i] * b;
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector_data  operator* (const vector& a, const vector& b)
{
  vector_data result (0);

  for (int i = 0; i < b.size_; i++)
  {
    result  = result + a.data_[i] * b.data_[i];
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector operator/ (const vector& a, const vector_data& b)
{
  vector result (a.size_);

  for (int i = 0; i < a.size_; i++)
  {
    result[i] = a.data_[i] / b;
  }

  return result;
}
//*/---------------------------------------------------------------------------
char operator== (const vector& a, const vector& b)
{
  if (a.size_ != b.size_) return 0;
  for (int i = 0; i < a.size_; i++)
  {
    if (a.data_[i] != b.data_[i]) return 0;
  }

  return 1;
}
//*/---------------------------------------------------------------------------
char operator!= (const vector& a, const vector& b)
{
  return !(a == b);
}
//*/---------------------------------------------------------------------------
std::ostream &operator<< (std::ostream& out, const vector& a)
{
  for (int i = 0; i < a.size_; i++)
  {
    out << a.data_[i] << " ";
  }

  return out;
}
//*/---------------------------------------------------------------------------
std::istream &operator>> (std::istream& in, const vector& a)
{
  for (int i = 0; i < a.size_; i++)
  {
    in >> a.data_[i];
  }

  return in;
}
//*/---------------------------------------------------------------------------
#undef DEBUG
#undef PRINT_LOGS
//*/---------------------------------------------------------------------------
