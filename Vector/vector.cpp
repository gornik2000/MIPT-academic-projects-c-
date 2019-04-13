//---------------------------------------------------------------------------*/
//                    Constructor - Destructor                               //
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::vector ():
  data_   (NULL),
  size_   (0)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with zero size", this, 0);
  }
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::vector (vector<data>&& that):
  data_   (NULL),
  size_   (0)
  {
    swap (that);
    PRINT_LOGS_VTR ("Vector %8d [%8d] was moved", this, data_);
  }
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::vector (const vector<data>& that):
  data_   (NEW data[that.size_]),
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
  data_   (NEW data [size]),
  size_   (size)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with %d size", \
                    this, data_, size);
  }
//---------------------------------------------------------------------------*/
template <typename data>
vector<data>::~vector ()
{
  clear ();
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
const data vector<data>::poison () const
{
  return 0;
}
//---------------------------------------------------------------------------*/
template <>
const char vector<char>::poison () const
{
  return VECTOR_POISON_CHAR;
}
//---------------------------------------------------------------------------*/
template <>
const int vector<int>::poison () const
{
  return VECTOR_POISON_INT;
}
//---------------------------------------------------------------------------*/
template <>
const float vector<float>::poison () const
{
  return VECTOR_POISON_FLOAT;
}
//---------------------------------------------------------------------------*/
template <>
const double vector<double>::poison () const
{
  return VECTOR_POISON_DOUBLE;
}
//---------------------------------------------------------------------------*/
template <>
const long long vector<long long>::poison () const
{
  return VECTOR_POISON_LONG_LONG;
}
//---------------------------------------------------------------------------*/
template <typename data>
void vector<data>::clear ()
{
  data content = poison ();
  for (int i = 0; i < size_; ++i)
  {
    data_[i] = content;
  }

  PRINT_LOGS_VTR ("Vector %8d [%8d] was cleared with %d", \
                  this, data_, content);
}
//---------------------------------------------------------------------------*/
template <typename data>
char vector<data>::resize (size_t count)
{
  if (count == size_)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] size wasn't changed", \
                    this, data_);
    return 1;
  }

  size_t capacity = (size_ < count)? size_:count;

  data *new_data = NEW data [count]{0};
  for (int i = 0; i < capacity; ++i)
  {
    new_data[i] = data_[i];
  }
  clear ();
  DELETE  (data_);

  data_ = new_data;
  size_ = count;

  PRINT_LOGS_VTR ("Vector %8d [%8d] size was changed to %d", \
                  this, data_, count);
  return 0;
}
//---------------------------------------------------------------------------*/
template <typename data>
void vector<data>::swap (vector<data> &that)
{
  std::swap (size_, that.size_);
  std::swap (data_, that.data_);
}
//---------------------------------------------------------------------------*/
//                            Public Operators                               //
//---------------------------------------------------------------------------*/
template <typename data>
data &vector<data>::at (size_t index)
{
  if (index >= size_ || index < 0)
  {
    PRINT_LOGS_VTR ("ERROR index %d out of range", index);
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
const data &vector<data>::at (size_t index) const
{
  if (index >= size_ || index < 0)
  {
    PRINT_LOGS_VTR ("ERROR index %d out of range", index);
  }
  return data_[index];
}
//---------------------------------------------------------------------------*/
template <typename data>
const data &vector<data>::operator[] (size_t index) const
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
//                          Other Operators                                  //
//---------------------------------------------------------------------------*/
template <typename data>
std::istream &operator>> (std::istream& in, vector<data>& lhs)
{
  for (int i = 0; i < lhs.size(); ++i)
  {
    in >> lhs.at(i);
  }

  return in;
}
//---------------------------------------------------------------------------*/
template <typename data>
std::ostream &operator<< (std::ostream& out, const vector<data>& lhs)
{
  for (int i = 0; i < lhs.size(); ++i)
  {
    out << lhs[i] << " ";
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
    if (lhs[i] != rhs[i]) return 0;
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
    result[i] = lhs[i] + rhs[i];
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
    result[i] = num + rhs[i];
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
    result[i] = num + lhs[i];
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
    result[i] = lhs[i] - rhs[i];
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
    result[i] = lhs[i] - num;
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
    result[i] = num * rhs[i];
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
    result[i] = lhs[i] * num;
  }

  return result;
}
//---------------------------------------------------------------------------*/
//#undef DEBUG
//#undef NEW
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
