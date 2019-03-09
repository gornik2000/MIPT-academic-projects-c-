//*/---------------------------------------------------------------------------
#undef private
//*/---------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//*/---------------------------------------------------------------------------
#include "C:\Users\Lenovo\Documents\GitHub\MIPT-academic-projects-cpp\Memory Controller\memory_controller.cpp"
//*/---------------------------------------------------------------------------
#ifdef DEBUG
  #define PRINT_LOGS(s, a)                                                    \
  {                                                                           \
    fprintf(log_file_vector, s, a);                                           \
  }
#else
  #define PRINT_LOGS(s);
#endif
//*/---------------------------------------------------------------------------
typedef size_t vector_data;
typedef int    vector_pars;
//*/---------------------------------------------------------------------------
const vector_data VECTOR_POISON  = 0;
const char *log_file_vector_name = "vector_log.txt";
FILE  *log_file_vector           = fopen (log_file_vector_name, "w");
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

    vector_pars size ();

    char swap   (vector &that);
    char print  ();
    char clear  (vector_data content = 0);
    char resize (vector_pars count);

    vector_data  &operator[] (vector_pars index);
    const vector &operator=  (const vector& that);

  friend vector operator+ (const vector& a,      const vector& b);
  friend vector operator+ (const vector_data& a, const vector& b);
  friend vector operator+ (const vector& a,      const vector_data& b);

  friend vector operator- (const vector& a, const vector& b);
  friend vector operator- (const vector& a, const vector_data& b);

  friend vector      operator* (const vector_data& a, const vector& b);
  friend vector      operator* (const vector& a,      const vector_data& b);
  friend vector_data operator* (const vector& a,      const vector& b);

  friend vector operator/ (const vector& a, const vector_data& b);

  friend char operator== (const vector& a, const vector& b);
  friend char operator!= (const vector& a, const vector& b);

  friend std::ostream &operator<< (std::ostream& out, const vector& a);
  friend std::istream &operator>> (std::istream& in,  const vector& a);

};
//*/---------------------------------------------------------------------------
