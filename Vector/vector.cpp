//*/-------------------------------------------------------------------------//
//                             Header                                        //
//*/-------------------------------------------------------------------------//
#include "vector.h"
//*/-------------------------------------------------------------------------//
//                    Constructor - Destructor                               //
//*/-------------------------------------------------------------------------//
vector::vector ():
  data_ (NULL),
  size_ (0)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with zero size", this, 0);
  }
//*/---------------------------------------------------------------------------
vector::vector (const vector& that):
  data_ (NEW vector_data[that.size_]),
  size_ (that.size_)
  {
    for (int i = 0; i < size_; i++)
    {
      data_[i] = that.data_[i];
    }
    PRINT_LOGS_VTR ("Vector %8d [%8d] was copied to %8d [%8d]",
                          that, that.data_,       this, data_);
  }
//*/---------------------------------------------------------------------------
vector::vector (vector_pars size):
  data_ (NEW vector_data [size]{}),
  size_ (size)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with %d size",
                          this, data_,                    size);
  }
//*/---------------------------------------------------------------------------
vector::~vector ()
{
  clear (VECTOR_POISON);
  delete[] data_;

  size_ = -1;
  PRINT_LOGS_VTR ("Vector %8d [%8d] was destroyed", this, data_);
  data_ = NULL;
}
//*/-------------------------------------------------------------------------//
//                             Public                                        //
//*/-------------------------------------------------------------------------//
const vector_pars vector::size () const
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

  PRINT_LOGS_VTR ("Vector %8d [%8d] was cleared with %d",
                        this, data_,            content);
  return 0;
}
//*/---------------------------------------------------------------------------
char vector::resize (vector_pars count)
{
  if (size_ <  count)
  {
    vector_data *new_data = NEW vector_data [count]{0};
    for (int i = 0; i < size_; i++)
    {
      new_data[i] = data_[i];
    }
    clear (VECTOR_POISON);
    delete[] data_;

    data_     = new_data;
    size_ = count;

    PRINT_LOGS_VTR ("Vector %8d [%8d] size was changed to %d",
                          this, data_,                 count);
    return 0;
  }
  if (size_ >  count)
  {
    vector_data *new_data = NEW vector_data [count]{0};
    for (int i = 0; i < count; i++)
    {
      new_data[i] = data_[i];
    }
    clear (VECTOR_POISON);
    delete[] data_;

    data_     = new_data;
    size_ = count;

    PRINT_LOGS_VTR ("Vector %8d [%8d] size was changed to %d",
                          this, data_,                 count);
    return 0;
  }
  PRINT_LOGS_VTR ("Vector %8d [%8d] size wasn't changed", this, data_);
  return 0;
}
//*/---------------------------------------------------------------------------
char vector::swap (vector &that)
{
  std::swap (size_, that.size_);
  std::swap (data_, that.data_);

  return 0;
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
const vector_data &vector::at (vector_pars index) const
{
  if (index >= size_)
  {
    PRINT_LOGS_VTR ("ERROR index %d out of range", index);
    return VECTOR_POISON;
  }
  return data_[index];
}
//*/---------------------------------------------------------------------------
vector_data &vector::operator[] (vector_pars index)
{
  return data_[index];
}
//*/---------------------------------------------------------------------------
const vector &vector::operator= (const vector& that)
{
  vector copy = that;
  swap (copy);

  PRINT_LOGS_VTR (" # Vector %8d [%8d] was set %8d [%8d]\n",
                           this, data_,      that, that.data_);
  return *this;
}
//*/---------------------------------------------------------------------------
//                       Memory Operators
//*/---------------------------------------------------------------------------
inline void *operator new (size_t size, const char *fun, int line)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS_MEM ("ERROR memory was not allocated");
    return p;
  }

  PRINT_LOGS_MEM ("%8d allocated", p);
  return p;
}
//*/---------------------------------------------------------------------------
inline void *operator new[] (size_t size, const char *fun, int line)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS_MEM ("ERROR memory was not allocated");
    return p;
  }

  PRINT_LOGS_MEM ("%8d allocated", p);
  return p;
}
//*/---------------------------------------------------------------------------
inline void operator delete (void *p) noexcept
{
  PRINT_LOGS_MEM ("%8d freed    ", p);

  free (p);
}
//*/---------------------------------------------------------------------------
inline void operator delete[] (void *p) noexcept
{
  PRINT_LOGS_MEM ("%8d freed    ", p);

  free (p);
}
//*/-------------------------------------------------------------------------//
//                          Friend Operators                                 //
//*/-------------------------------------------------------------------------//
std::istream &operator>> (std::istream& in, const vector& a)
{
  for (int i = 0; i < a.size_; i++)
  {
    in >> a.data_[i];
  }

  return in;
}
//*/-------------------------------------------------------------------------//
//                          Other Operators                                  //
//*/-------------------------------------------------------------------------//
std::ostream &operator<< (std::ostream& out, const vector& a)
{
  for (int i = 0; i < a.size(); i++)
  {
    out << a.at(i) << " ";
  }

  return out;
}
//*/---------------------------------------------------------------------------
char operator== (const vector& a, const vector& b)
{
  if (a.size() != b.size()) return 0;
  for (int i = 0; i < a.size(); i++)
  {
    if (a.at(i) != b.at(i)) return 0;
  }

  return 1;
}
//*/---------------------------------------------------------------------------
char operator!= (const vector& a, const vector& b)
{
  return !(a == b);
}
//*/---------------------------------------------------------------------------
vector operator+ (const vector& a, const vector& b)
{
  vector result (b.size());

  for (int i = 0; i < b.size(); i++)
  {
    result[i] = a.at(i) + b.at(i);
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator+ (const vector_data& a, const vector& b)
{
  vector result (b.size());

  for (int i = 0; i < b.size(); i++)
  {
    result[i] = a + b.at(i);
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator+ (const vector& a, const vector_data& b)
{
  vector result (a.size());

  for (int i = 0; i < a.size(); i++)
  {
    result[i] = b + a.at(i);
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator- (const vector& a, const vector& b)
{
  vector result (a.size());

  for (int i = 0; i < a.size(); i++)
  {
    result[i] = a.at(i) - b.at(i);
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator- (const vector& a, const vector_data& b)
{
  vector result (a.size());

  for (int i = 0; i < a.size(); i++)
  {
    result[i] = a.at(i) - b;
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator* (const vector_data& a, const vector& b)
{
  vector result (b.size());

  for (int i = 0; i < b.size(); i++)
  {
    result[i] = a * b.at(i);
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector  operator* (const vector& a, const vector_data& b)
{
  vector result (a.size());

  for (int i = 0; i < a.size(); i++)
  {
    result[i] = a.at(i) * b;
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector_data  operator* (const vector& a, const vector& b)
{
  vector_data result (0);

  for (int i = 0; i < b.size(); i++)
  {
    result  = result + a.at(i) * b.at(i);
  }

  return result;
}
//*/---------------------------------------------------------------------------
vector operator/ (const vector& a, const vector_data& b)
{
  vector result (a.size());

  for (int i = 0; i < a.size(); i++)
  {
    result[i] = a.at(i) / b;
  }

  return result;
}
//*/---------------------------------------------------------------------------
#undef DEBUG
#undef PRINT_LOGS_VTR
#undef PRINT_LOGS_MEM
#undef NEW
//*/---------------------------------------------------------------------------
