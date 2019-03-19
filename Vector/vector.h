//---------------------------------------------------------------------------*/
#undef private
//---------------------------------------------------------------------------*/
#include <iostream>
#include <ctime>
//---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------------*/
#define NEW new(__FILE__, __func__, __LINE__)
#define DELETE(p)                                                             \
{                                                                             \
  PRINT_LOGS_MEM ("%8d freed     %s %s %d", p, __FILE__, __func__, __LINE__); \
  delete p;                                                                   \
}
//---------------------------------------------------------------------------*/
#ifdef DEBUG
  #define PRINT_LOGS_VTR(s, ...) \
    fprintf(log_file_vector, "%s # " s "\n", __TIME__, ##__VA_ARGS__)
  #define PRINT_LOGS_MEM(s, ...) \
    fprintf(log_file_memory, "%s # " s "\n", __TIME__, ##__VA_ARGS__)
#else
  #define PRINT_LOGS_VTR(s)
  #define PRINT_LOGS_MEM(s, lhs)
#endif
//---------------------------------------------------------------------------*/
const char *log_file_vector_name = "vector_log.txt";
const char *log_file_memory_name = "memory_log.txt";

FILE *log_file_vector = fopen (log_file_vector_name, "w");
FILE *log_file_memory = fopen (log_file_memory_name, "w");
//---------------------------------------------------------------------------*/
template <typename data>
class vector
{
  private:
    data  *data_;
    data   poison_;
    size_t size_;

  public:
    explicit vector  ();
    vector  (vector &&that);
    vector  (const vector& that);
    vector  (size_t size);
    ~vector ();

    char swap   (vector &that);
    char print  ();
    char clear  (data content = 0);
    char resize (size_t count);

    const data &at   (size_t index) const;
    data &operator[] (size_t index);

    const vector &operator= (const vector& that);
    const vector &operator= (vector&&      that);

    const size_t size () const;

  friend std::istream &operator>> (std::istream& in,  const vector& lhs);
};
//---------------------------------------------------------------------------*/
template <typename data>
std::ostream &operator<< (std::ostream& out, const vector<data>& lhs);

template <typename data>
char operator== (const vector<data>& lhs, const vector<data>& rhs);
template <typename data>
char operator!= (const vector<data>& lhs, const vector<data>& rhs);

template <typename data>
vector<data> operator+ (const vector<data>& lhs, const vector<data>& rhs);
template <typename data>
vector<data> operator+ (const vector<data>& lhs, const data& rhs);
template <typename data>
vector<data> operator+ (const data& lhs, const vector<data>& rhs);

template <typename data>
vector<data> operator- (const vector<data>& lhs, const vector<data>& rhs);
template <typename data>
vector<data> operator- (const vector<data>& lhs, const data& rhs);

template <typename data>
vector<data> operator* (const data& lhs, const vector<data>& rhs);
template <typename data>
vector<data> operator* (const vector<data>& lhs, const data& rhs);
template <typename data>
data operator* (const vector<data>& lhs, const vector<data>& rhs);

template <typename data>
vector<data> operator/ (const vector<data>& lhs, const data& rhs);

inline void *operator new   (size_t size, const char* file, \
                             const char *fun, int line);
inline void *operator new[] (size_t size, const char* file, \
                             const char *fun, int line);

inline void operator delete   (void *p) noexcept;
inline void operator delete[] (void *p) noexcept;
//---------------------------------------------------------------------------*/
