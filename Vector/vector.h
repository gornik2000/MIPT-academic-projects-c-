//*/---------------------------------------------------------------------------
#undef private
//*/---------------------------------------------------------------------------
#include <iostream>
#include <ctime>
//*/---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
//*/---------------------------------------------------------------------------
#define NEW new(__func__, __LINE__)
//*/---------------------------------------------------------------------------
#ifdef DEBUG
  #define PRINT_LOGS_VTR(s, ...) \
    fprintf(log_file_vector, "%s # " s "\n", __TIME__, ##__VA_ARGS__)
  #define PRINT_LOGS_MEM(s, ...) \
    fprintf(log_file_memory, "%s # " s "\n", __TIME__, ##__VA_ARGS__)
#else
  #define PRINT_LOGS_VTR(s)
  #define PRINT_LOGS_MEM(s, a)
#endif
//*/---------------------------------------------------------------------------
typedef size_t vector_data;
typedef int    vector_pars;
//*/---------------------------------------------------------------------------
const vector_data VECTOR_POISON  = 0;

const char *log_file_vector_name = "vector_log.txt";
const char *log_file_memory_name = "memory_log.txt";

FILE  *log_file_vector = fopen (log_file_vector_name, "w");
FILE *log_file_memory  = fopen (log_file_memory_name, "w");
//*/---------------------------------------------------------------------------
class vector
{
  private:
    vector_data *data_;
    vector_pars size_;

  public:
    vector  ();
    vector  (const vector& that);
    vector  (vector_pars size);
    ~vector ();

    char swap   (vector &that);
    char print  ();
    char clear  (vector_data content = 0);
    char resize (vector_pars count);

    const vector_data  &at   (vector_pars index) const;

    vector_data  &operator[] (vector_pars index);
    const vector &operator=  (const vector& that);

    const vector_pars size () const;

  friend std::istream &operator>> (std::istream& in,  const vector& a);
};
//*/---------------------------------------------------------------------------
std::ostream &operator<< (std::ostream& out, const vector& a);

char operator== (const vector& a, const vector& b);
char operator!= (const vector& a, const vector& b);

vector operator+ (const vector& a,      const vector& b);
vector operator+ (const vector_data& a, const vector& b);
vector operator+ (const vector& a,      const vector_data& b);

vector operator- (const vector& a, const vector& b);
vector operator- (const vector& a, const vector_data& b);

vector      operator* (const vector_data& a, const vector& b);
vector      operator* (const vector& a,      const vector_data& b);
vector_data operator* (const vector& a,      const vector& b);

vector operator/ (const vector& a, const vector_data& b);

inline void *operator new   (size_t size, const char *fun, int line);
inline void *operator new[] (size_t size, const char *fun, int line);

inline void operator delete   (void *p) noexcept;
inline void operator delete[] (void *p) noexcept;
