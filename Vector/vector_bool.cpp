//---------------------------------------------------------------------------*/
//                           Boolean vector                                  //
//---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------*/
//                           Class Reference                                 //
//---------------------------------------------------------------------------*/
vector<bool>::reference::reference ():
  arr_ (NULL),
  num_ (0)
  {
  }
//---------------------------------------------------------------------------*/
vector<bool>::reference::~reference ()
{
}
//---------------------------------------------------------------------------*/
vector<bool>::reference::operator bool () const
{
  return *arr_ & (1 << num_);
}
//---------------------------------------------------------------------------*/
vector<bool>::reference& vector<bool>::reference::operator= (bool b)
{
  if (b == true)
  {
    *arr_ = *arr_ | (1 << num_);
    return *this;
  }
  *arr_ = *arr_ & ~(1 << num_);
  return *this;
}
//---------------------------------------------------------------------------*/
vector<bool>::reference& vector<bool>::reference::operator= (const vector<bool>::reference&  that)
{
  if (bool (that) == true)
  {
    *arr_ = *arr_ | (1 << num_);
    arr_ = that.arr_;
    num_ = that.num_;

    return *this;
  }
  *arr_ = *arr_ & ~(1 << num_);
  arr_ = that.arr_;
  num_ = that.num_;

  return *this;
}
//---------------------------------------------------------------------------*/
//                    Constructor - Destructor                               //
//---------------------------------------------------------------------------*/
vector<bool>::vector ():
  data_   (NULL),
  size_   (0)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with zero size", this, 0);
  }
//---------------------------------------------------------------------------*/
vector<bool>::vector (vector<bool>&& that):
  data_   (NULL),
  size_   (0)
  {
    swap (that);
    PRINT_LOGS_VTR ("Vector %8d [%8d] was moved", this, data_);
  }
//---------------------------------------------------------------------------*/
vector<bool>::vector (const vector<bool>& that):
  data_   (NEW bool_t [that.memsize()]),
  size_   (that.size_)
  {
    memcpy (data_, that.data_, memsize() * sizeof (bool_t));
    PRINT_LOGS_VTR ("Vector %8d [%8d] was copied to %8d [%8d]", \
                    that, that.data_, this, data_);
  }
//---------------------------------------------------------------------------*/
vector<bool>::vector (size_t size):
  data_   (NEW bool_t [size / BOOL_CELL + 1]),
  size_   (size)
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] was created with %d size", \
                    this, data_, size);
  }
//---------------------------------------------------------------------------*/
vector<bool>::~vector ()
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
const size_t vector<bool>::size () const
{
  return size_;
}
//---------------------------------------------------------------------------*/
const size_t vector<bool>::memsize () const
{
  /* real given data_ size in bool_t */
  return size_ / BOOL_CELL + 1;
}
//---------------------------------------------------------------------------*/
const char vector<bool>::poison () const
{
  return VECTOR_POISON_BOOL;
}
//---------------------------------------------------------------------------*/
void vector<bool>::clear ()
{
  memset (data_, poison(), memsize() * sizeof (bool_t));

  PRINT_LOGS_VTR ("Vector %8d [%8d] was cleared with %d", \
                  this, data_, poison());
}
//---------------------------------------------------------------------------*/
char vector<bool>::resize (size_t count)
{
  size_t memcount = count / BOOL_CELL + 1;
  if (memcount == memsize())
  {
    PRINT_LOGS_VTR ("Vector %8d [%8d] size wasn't changed", \
                    this, data_);
    return 1;
  }

  size_t memcapacity = (memsize () < memcount)? memsize ():memcount;

  bool_t *new_data = NEW bool_t [memcount];
  memcpy (new_data, data_, memcount * sizeof (bool_t));
  clear  ();
  DELETE (data_);

  data_ = new_data;
  size_ = count;

  PRINT_LOGS_VTR ("Vector %8d [%8d] size was changed to %d", \
                  this, data_, count);
  return 0;
}
//---------------------------------------------------------------------------*/
void vector<bool>::swap (vector<bool> &that)
{
  std::swap (size_, that.size_);
  std::swap (data_, that.data_);
}
//---------------------------------------------------------------------------*/
//                            Public Operators                               //
//---------------------------------------------------------------------------*/
vector<bool>::reference vector<bool>::at (size_t index)
{
  if (index >= size_)
  {
    PRINT_LOGS_VTR ("ERROR index %d out of range", index);
  }
  vector<bool>::reference a;
  a.arr_ = data_ + index / BOOL_CELL;
  a.num_ = index % BOOL_CELL;

  return a;
}
//---------------------------------------------------------------------------*/
vector<bool>::reference vector<bool>::operator[] (size_t index)
{
  vector<bool>::reference a;
  a.arr_ = data_ + index / BOOL_CELL;
  a.num_ = index % BOOL_CELL;

  return a;
}
//---------------------------------------------------------------------------*/
const vector<bool>::reference vector<bool>::at (size_t index) const
{
  if (index >= size_)
  {
    PRINT_LOGS_VTR ("ERROR index %d out of range", index);
  }
  vector<bool>::reference a;
  a.arr_ = data_ + index / BOOL_CELL;
  a.num_ = index % BOOL_CELL;

  return a;
}
//---------------------------------------------------------------------------*/
const vector<bool>::reference vector<bool>::operator[] (size_t index) const
{
  vector<bool>::reference a;
  a.arr_ = data_ + index / BOOL_CELL;
  a.num_ = index % BOOL_CELL;

  return a;
}
//---------------------------------------------------------------------------*/
const vector<bool> &vector<bool>::operator= (const vector<bool>& that)
{
  vector copy = that;
  swap (copy);

  PRINT_LOGS_VTR (" # Vector %8d [%8d] was set from %8d [%8d]\n", \
                  this, data_, that, that.data_);
  return *this;
}
//---------------------------------------------------------------------------*/
const vector<bool> &vector<bool>::operator= (vector<bool>&& that)
{
  swap (that);

  PRINT_LOGS_VTR (" # Vector %8d [%8d] was moved from %8d [%8d]\n", \
                  this, data_, that, that.data_);
  return *this;
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
