#include <cstdint>
#include <iostream>
#include <random>
#include <cstring>
#include <ctime>
//===========================================================================*/
// matrix m x n
template <typename T>
class Matrix
{
  private:
    int64_t n_;
    int64_t m_;
    T*  data_;

  public:
    explicit Matrix();
    Matrix(Matrix &&that);
    Matrix(const Matrix& that);
    Matrix(int64_t m, int64_t n);
    ~Matrix();

    const int64_t Get_n() const;
    const int64_t Get_m() const;

    void Swap(Matrix &that);
    void Resize(int64_t m, int64_t n);
    void Clear();

    T& At(int64_t x, int64_t y);
    T& operator()(int64_t x, int64_t y);

    const T& At(int64_t x, int64_t y) const;
    const T& operator()(int64_t x, int64_t y) const;

    const Matrix& operator=(const Matrix& that);
    const Matrix& operator=(Matrix&&      that);

    T              Det();                                         // using Row_echelon_form
    Matrix<double> Row_echelon_form();                            // Gaussian elimination method
    Matrix<double> Row_echelon_form(char& sign);                  // Sign for swap changes
    char           Swap_rows(int64_t row_num1, int64_t row_num2);
    void           Random(double min = -10, double max = 10);     // fills matrix with random values from min to max
};
//===========================================================================*/
template <typename T>
std::istream &operator>>(std::istream& in, Matrix<T>& lhs);

template <typename T>
std::ostream &operator<<(std::ostream& out, const Matrix<T>& lhs);
//===========================================================================*/
template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs);
//===========================================================================*/
template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs);
//===========================================================================*/
template <typename T>
Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs);

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs);
//===========================================================================*/
template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs);

template <typename T>
const Matrix<T>& operator+(const Matrix<T>& lhs);
//===========================================================================*/
