//---------------------------------------------------------------------------*/
//                             Header                                        //
//---------------------------------------------------------------------------*/
#include "vector.h"
//---------------------------------------------------------------------------*/
//                    Constructor - Destructor                               //
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::vector ():
  data_   (NULL),
  poison_ (0),
  size_   (0)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with zero size", this, 0);
  }
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::vector (vector<data>&& that):
  data_   (NULL),
  poison_ (0),
  size_   (0)
  {
    swap (that);
    PRINT_LOGS_VTR ("Vector %8d [%8d] was moved", this, data_);
  }
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::vector (const vector<data>& that):
  data_   (NEW data[that.size_]),
  poison_ (0),
  size_   (that.size_)
  {
    for (int i = 0; i < size_; ++i)
    {
      data_[i] = that.data_[i];
    }
    PRINT_LOGS_VTR ("Vector %8d [%8d] was copied to %8d [%8d]", \
                    that, that.data_, this, data_);
  }
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::vector (size_t size):
  data_   (NEW data [size]{}),
  poison_ (0),
  size_   (size)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with %d size", \
                    this, data_, size);
  }
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::~vector ()
{
  clear (poison_);
  DELETE  (data_);

  size_ = -1;
  PRINT_LOGS_VTR ("Vector %8d [%8d] was destroyed", \
                  this, data_);
  data_ = NULL;
}
//---------------------------------------------------------------------------*/
//                             Public                                        //
//---------------------------------------------------------------------------*/
template <typename data>
const size_t vector<data>::size () const
{
  return size_;
}
//---------------------------------------------------------------------------*/
template <typename data>
char vector<data>::clear (data content)
{
  for (int i = 0; i < size_; ++i)
  {
    data_[i] = content;
  }

  PRINT_LOGS_VTR ("Vector %8d [%8d] was cleared with %d", \
                  this, data_, content);
  return 0;
}
//---------------------------------------------------------------------------*/
template <typename data>
char vector<data>::resize (size_t count)
{
  if (size_ <  count)
  {
    data *new_data = NEW data [count]{0};
    for (int i = 0; i < size_; ++i)
    {
      new_data[i] = data_[i];
    }
    clear (poison_);
    DELETE  (data_);

    data_ = new_data;
    size_ = count;

    PRINT_LOGS_VTR ("Vector %8d [%8d] size was changed to %d", \
                    this, data_, count);
    return 0;
  }
  if (size_ > count)
  {
    data *new_data = NEW data [count]{0};
    for (int i = 0; i < count; ++i)
    {
      new_data[i] = data_[i];
    }
    clear (poison_);
    DELETE  (data_);

    data_ = new_data;
    size_ = count;

    PRINT_LOGS_VTR ("Vector %8d [%8d] size was changed to %d", \
                    this, data_, count);
    return 0;
  }
  PRINT_LOGS_VTR ("Vector %8d [%8d] size wasn't changed", \
                  this, data_);
  return 0;
}
//---------------------------------------------------------------------------*/
template <typename data>
char vector<data>::swap (vector<data> &that)
{
  std::swap (size_, that.size_);
  std::swap (data_, that.data_);

  return 0;
}
//---------------------------------------------------------------------------*/
template <typename data>
char vector<data>::print ()
{
  for (int i = 0; i < size_; ++i)
  {
    std::cout << data_[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
//---------------------------------------------------------------------------*/
//                            Public Operators                               //
//---------------------------------------------------------------------------*/
template <typename data>
const data &vector<data>::at (size_t index) const
{
  if (index >= size_)
  {
    PRINT_LOGS_VTR ("ERROR index %d out of range", index);
    return poison_;
  }
  return data_[index];
}
//---------------------------------------------------------------------------*/
template <typename data>
data &vector<data>::operator[] (size_t index)
{
  return data_[index];
}
//---------------------------------------------------------------------------*/
template <typename data>
const vector<data> &vector<data>::operator= (const vector<data>& that)
{
  vector copy = that;
  swap (copy);

  PRINT_LOGS_VTR (" # Vector %8d [%8d] was set from %8d [%8d]\n", \
                  this, data_, that, that.data_);
  return *this;
}
//---------------------------------------------------------------------------*/
template <typename data>
const vector<data> &vector<data>::operator= (vector<data>&& that)
{
  swap (that);

  PRINT_LOGS_VTR (" # Vector %8d [%8d] was moved from %8d [%8d]\n", \
                  this, data_, that, that.data_);
  return *this;
}
//---------------------------------------------------------------------------*/
//                          Friend Operators                                 //
//---------------------------------------------------------------------------*/
template <typename data>
std::istream &operator>> (std::istream& in, const vector<data>& lhs)
{
  for (int i = 0; i < lhs.size_; ++i)
  {
    in >> lhs.data_[i];
  }

  return in;
}
//---------------------------------------------------------------------------*/
//                          Other Operators                                  //
//---------------------------------------------------------------------------*/
template <typename data>
std::ostream &operator<< (std::ostream& out, const vector<data>& lhs)
{
  for (int i = 0; i < lhs.size(); ++i)
  {
    out << lhs.at(i) << " ";
  }

  return out;
}
//---------------------------------------------------------------------------*/
template <typename data>
char operator== (const vector<data>& lhs, const vector<data>& rhs)
{
  if (lhs.size() != rhs.size()) return 0;
  for (int i = 0; i < lhs.size(); ++i)
  {
    if (lhs.at(i) != rhs.at(i)) return 0;
  }

  return 1;
}
//---------------------------------------------------------------------------*/
template <typename data>
char operator!= (const vector<data>& lhs, const vector<data>& rhs)
{
  return !(lhs == rhs);
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator+ (const vector<data>& lhs, const vector<data>& rhs)
{
  vector<data> result (rhs.size());

  for (int i = 0; i < rhs.size(); ++i)
  {
    result[i] = lhs.at(i) + rhs.at(i);
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>  operator+ (const data& num, const vector<data>& rhs)
{
  vector<data> result (rhs.size());

  for (int i = 0; i < rhs.size(); ++i)
  {
    result[i] = num + rhs.at(i);
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator+ (const vector<data>& lhs, const data& num)
{
  vector<data> result (lhs.size());

  for (int i = 0; i < lhs.size(); ++i)
  {
    result[i] = num + lhs.at(i);
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator- (const vector<data>& lhs, const vector<data>& rhs)
{
  vector<data> result (lhs.size());

  for (int i = 0; i < lhs.size(); ++i)
  {
    result[i] = lhs.at(i) - rhs.at(i);
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator- (const vector<data>& lhs, const data& num)
{
  vector<data> result (lhs.size());

  for (int i = 0; i < lhs.size(); ++i)
  {
    result[i] = lhs.at(i) - num;
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator* (const data& num, const vector<data>& rhs)
{
  vector<data> result (rhs.size());

  for (int i = 0; i < rhs.size(); ++i)
  {
    result[i] = num * rhs.at(i);
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator* (const vector<data>& lhs, const data& num)
{
  vector<data> result (lhs.size());

  for (int i = 0; i < lhs.size(); ++i)
  {
    result[i] = lhs.at(i) * num;
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
data  operator* (const vector<data>& lhs, const vector<data>& rhs)
{
  data result (0);

  for (int i = 0; i < rhs.size(); ++i)
  {
    result  = result + lhs.at(i) * rhs.at(i);
  }

  return result;
}
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator/ (const vector<data>& lhs, const data& num)
{
  vector<data> result (lhs.size());

  for (int i = 0; i < lhs.size(); ++i)
  {
    result[i] = lhs.at(i) / num;
  }

  return result;
}
//---------------------------------------------------------------------------*/
//                       Memory Operators                                    //
//---------------------------------------------------------------------------*/
template <typename data>
inline void *operator new (size_t size, const char* file, \
                           const char *fun, int line)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS_MEM ("ERROR memory was not allocated %s %s %d", file, fun, line);
    return p;
  }

  PRINT_LOGS_MEM ("%8d allocated %s %s %d", p, file, fun, line);
  return p;
}
//---------------------------------------------------------------------------*/
inline void *operator new[] (size_t size, const char* file, \
                             const char *fun, int line)
{
  void *p = calloc (1, size);

  if (p == NULL)
  {
    PRINT_LOGS_MEM ("ERROR memory was not allocated %s %s %d", file, fun, line);
    return p;
  }

  PRINT_LOGS_MEM ("%8d allocated %s %s %d", p, file, fun, line);
  return p;
}
//---------------------------------------------------------------------------*/
inline void operator delete (void *p) noexcept
{
  free (p);
}
//---------------------------------------------------------------------------*/
inline void operator delete[] (void *p) noexcept
{
  free (p);
}
//---------------------------------------------------------------------------*/
#undef DEBUG
#undef PRINT_LOGS_VTR
#undef PRINT_LOGS_MEM
#undef NEW
//---------------------------------------------------------------------------*/
