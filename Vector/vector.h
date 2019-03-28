//---------------------------------------------------------------------------*/
//                             Header                                        //
//---------------------------------------------------------------------------*/
#undef private
//---------------------------------------------------------------------------*/
#include <iostream>
#include <ctime>
//---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//---------------------------------------------------------------------------*/
#ifdef DEBUG
  #define PRINT_LOGS_VTR(s, ...) \
    fprintf(log_file_vector, "%s " s "\n", __TIME__, ##__VA_ARGS__)
#else
  #define PRINT_LOGS_VTR(s, ...)
#endif
//---------------------------------------------------------------------------*/
#include "..\Memory_controller\memory_controller.h"
//---------------------------------------------------------------------------*/
enum vector_poison
{
  VECTOR_POISON_CHAR      = 1,
  VECTOR_POISON_INT       = 2,
  VECTOR_POISON_FLOAT     = 3,
  VECTOR_POISON_DOUBLE    = 4,
  VECTOR_POISON_LONG_LONG = 5,
  VECTOR_POISON_BOOL      = 6,
};
//---------------------------------------------------------------------------*/
typedef size_t bool_t;
size_t bool_cell = sizeof (bool_t) * 8;
//---------------------------------------------------------------------------*/
const char *log_file_vector_name = "vector_log.txt";
FILE       *log_file_vector      = fopen (log_file_vector_name, "w");
//---------------------------------------------------------------------------*/
//                        Class vector <data>                                //
//---------------------------------------------------------------------------*/
template <typename data>
class vector
{
  private:
    data  *data_;
    size_t size_;

  public:
    explicit vector  ();
    vector  (vector &&that);
    vector  (const vector& that);
    vector  (size_t size);
    ~vector ();

    const size_t size   () const;
    const data   poison () const;

    void swap   (vector &that);
    char resize (size_t count);
    void clear  ();

    data &at (size_t index);
    data &operator[] (size_t index);

    const data &at (size_t index) const;
    const data &operator[] (size_t index) const;

    const vector &operator= (const vector& that);
    const vector &operator= (vector&&      that);
};
//---------------------------------------------------------------------------*/
//                        Class vector <bool>                                //
//---------------------------------------------------------------------------*/
#include "vector_bool.h"
//---------------------------------------------------------------------------*/
template <typename data>
std::istream &operator>> (std::istream& in, vector<data>& lhs);

template <typename data>
std::ostream &operator<< (std::ostream& out, const vector<data>& lhs);
//---------------------------------------------------------------------------*/
template <typename data>
char operator== (const vector<data>& lhs, const vector<data>& rhs);

template <typename data>
char operator!= (const vector<data>& lhs, const vector<data>& rhs);
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator+ (const vector<data>& lhs, const vector<data>& rhs);

template <typename data>
vector<data> operator+ (const vector<data>& lhs, const data& rhs);

template <typename data>
vector<data> operator+ (const data& lhs, const vector<data>& rhs);
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator- (const vector<data>& lhs, const vector<data>& rhs);

template <typename data>
vector<data> operator- (const vector<data>& lhs, const data& rhs);
//---------------------------------------------------------------------------*/
template <typename data>
vector<data> operator* (const data& lhs, const vector<data>& rhs);

template <typename data>
vector<data> operator* (const vector<data>& lhs, const data& rhs);
//---------------------------------------------------------------------------*/
#include "vector.cpp"
//---------------------------------------------------------------------------*/
//#undef PRINT_LOGS_VTR
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
