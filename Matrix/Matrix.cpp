#include "Matrix.hpp"
//===========================================================================*/
template <typename T>
Matrix<T>::Matrix()
{
  n_ = 0;
  m_ = 0;
  data_ = nullptr;
}

template <typename T>
Matrix<T>::Matrix(Matrix &&that)
{
  Swap(that);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& that)
{
  data_ = new T[that.n_ * that.m_];
  n_ = that.n_;
  m_ = that.m_;

  for (int64_t x = 0; x < n_; ++x)
  for (int64_t y = 0; y < m_; ++y)
  {
    data_[x][y] = that.data_[x][y];
  }
}

template <typename T>
Matrix<T>::Matrix(int64_t m, int64_t n)
{
  data_ = new T[n * m]{0};
  n_ = n;
  m_ = m;
}

template <typename T>
Matrix<T>::~Matrix()
{
  delete(data_);
  data_ = nullptr;
  n_ = 0;
  m_ = 0;
}
//===========================================================================*/
template <typename T>
const int64_t Matrix<T>::Get_n() const
{
  return n_;
}

template <typename T>
const int64_t Matrix<T>::Get_m() const
{
  return m_;
}
//===========================================================================*/
template <typename T>
void Matrix<T>::Swap(Matrix &that)
{
  std::swap(data_, that.data_);
  std::swap(n_, that.n_);
  std::swap(m_, that.m_);
}

template <typename T>
void Matrix<T>::Resize(int64_t m, int64_t n)
{
  if (n == n_ && m_ == m) return;
  int64_t capacity = (n_ * m_ < n * m) ? n_ * m_ : n * m;
  T* new_data = new T[n * m]{0};

  memcpy(new_data, data_, sizeof(T) * capacity);
  Clear();
  delete(data_);

  data_ = new_data;
  n_ = n;
  m_ = m;
}

template <typename T>
void Matrix<T>::Clear()
{
  for (int64_t x = 0; x < n_; ++x)
  for (int64_t y = 0; y < m_; ++y)
  {
    data_[x][y] = 0;
  }
}
//===========================================================================*/
template <typename T>
T& Matrix<T>::At(int64_t x, int64_t y)
{
  // check
  return data_[x + y * n_];
}

template <typename T>
T& Matrix<T>::operator()(int64_t x, int64_t y)
{
  return data_[x + y * n_];
}

template <typename T>
const T& Matrix<T>::At(int64_t x, int64_t y) const
{
  // check
  return data_[x + y * n_];
}

template <typename T>
const T& Matrix<T>::operator()(int64_t x, int64_t y) const
{
  return data_[x + y * n_];
}
//===========================================================================*/
template <typename T>
const Matrix<T>& Matrix<T>::operator=(const Matrix<T>& that)
{
  Matrix copy = that;
  swap(copy);

  return *this;
}

template <typename T>
const Matrix<T>& Matrix<T>::operator=(Matrix<T>&& that)
{
  swap(that);

  return *this;
}
//===========================================================================*/
template <typename T>
std::istream &operator>>(std::istream& in, Matrix<T>& lhs)
{
  int64_t m = lhs.Get_m();
  int64_t n = lhs.Get_n();
  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    in >> lhs.at(x, y);
  }

  return in;
}

template <typename T>
std::ostream &operator<<(std::ostream& out, const Matrix<T>& lhs)
{
  int64_t m = lhs.Get_m();
  int64_t n = lhs.Get_n();
  for (int64_t y = 0; y < m; ++y) {
  for (int64_t x = 0; x < n; ++x) {
    out << lhs.At(x, y) << " ";
  }
  out << "\n";
  }

  return out;
}
//===========================================================================*/
template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
  // check?
  if (lhs.get_n() != rhs.Get_n()) return false;
  if (lhs.get_m() != rhs.Get_m()) return false;

  int64_t m = lhs.get_m();
  int64_t n = lhs.get_n();
  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    if (lhs(x, y) != rhs(x, y)) return false;
  }

  return true;
}

template <typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
  return !(lhs == rhs);
}
//===========================================================================*/
template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
  // check
  Matrix<T> result(rhs.get_n(), rhs.get_m());

  int64_t m = lhs.Get_m();
  int64_t n = lhs.Get_n();
  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    result(x, y) = lhs(x, y) + rhs(x, y);
  }

  return result;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
  // check
  Matrix<T> result(rhs.get_n(), rhs.get_m());

  int64_t m = lhs.Get_m();
  int64_t n = lhs.Get_n();
  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    result(x, y) = lhs(x, y) - rhs(x, y);
  }

  return result;
}
//===========================================================================*/
template <typename T>
Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs)
{
  Matrix<T> result(rhs.get_n(), rhs.get_m());

  int64_t m = rhs.Get_m();
  int64_t n = rhs.Get_n();
  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    result(x, y) = lhs * rhs(x, y);
  }

  return result;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs)
{
  Matrix<T> result(lhs.get_n(), lhs.get_m());

  int64_t m = lhs.Get_m();
  int64_t n = lhs.Get_n();
  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    result(x, y) = lhs(x, y) * rhs;
  }

  return result;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
  //check n = n
  int64_t m = lhs.Get_m();
  int64_t n = rhs.Get_n();
  Matrix<T> result(m, n);

  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    T value = 0;
    for (int64_t z = 0; z < lhs.Get_n(); ++ z)
    {
      value += lhs(z, y) * rhs(x, z);
    }

    result(x, y) = value;
  }

  return result;
}
//===========================================================================*/
template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs)
{
  int64_t m = lhs.Get_m();
  int64_t n = lhs.Get_n();
  Matrix<T> result(n, m);

  for (int64_t y = 0; y < m; ++y)
  for (int64_t x = 0; x < n; ++x)
  {
    result(x, y) = -lhs(x, y);
  }
}

template <typename T>
const Matrix<T>& operator+(const Matrix<T>& lhs)
{
  return lhs;
}
//===========================================================================*/
template <typename T>
T Matrix<T>::Det()
{
  // check
  char sign = 0;
  Matrix<double> result = Row_echelon_form(sign);
  T answer = result(0, 0) * sign;

  for (int64_t step = 1; step < n_; ++step)
  {
    answer *= result(step, step);
  }

  return answer;
}
//===========================================================================*/
template <typename T>
Matrix<double> Matrix<T>::Row_echelon_form(char& sign)
{
  // make a double copy of the matrix
  sign = 1;
  Matrix<double> result(n_, m_);
  for (int64_t y = 0; y < m_; ++y)
  for (int64_t x = 0; x < n_; ++x)
  {
    result(x, y) = data_[x + y * n_];
  }

  for (int64_t step = 0; step < m_; ++step)
  {
    int64_t row = step;
    // finding first non zero in a beginning of the row

    while (result(step, row) == 0 && row < m_) ++row;
    int64_t chosen_row = row;
    ++row;

    // subtraction of the chosen row to get a zero in the beginning of the row
    for (; row < m_; ++row)
    {
      double k = result(step, row) / result(step, chosen_row);
      for (int64_t col = step; col < n_; ++col)
      {
        result(col, row) -= result(col, chosen_row) * k;
      }
    }

    sign *= result.Swap_rows(step, chosen_row);
  }

  return result;
}
//===========================================================================*/
template <typename T>
Matrix<double> Matrix<T>::Row_echelon_form()
{
  // make a double copy of the matrix
  Matrix<double> result(n_, m_);
  for (int64_t y = 0; y < m_; ++y)
  for (int64_t x = 0; x < n_; ++x)
  {
    result(x, y) = data_[x + y * n_];
  }

  for (int64_t step = 0; step < m_; ++step)
  {
    int64_t row = step;
    // finding first non zero in a beginning of the row

    while (result(step, row) == 0 && row < m_) ++row;
    int64_t chosen_row = row;
    ++row;

    // subtraction of the chosen row to get a zero in the beginning of the row
    for (; row < m_; ++row)
    {
      double k = result(step, row) / result(step, chosen_row);
      for (int64_t col = step; col < n_; ++col)
      {
        result(col, row) -= result(col, chosen_row) * k;
      }
    }

    result.Swap_rows(step, chosen_row);
  }

  return result;
}
//===========================================================================*/
template <typename T>
char Matrix<T>::Swap_rows(int64_t row_num1,int64_t row_num2)
{
  //check
  if (row_num1 == row_num2) return 1;

  int64_t size = sizeof(T) * n_;
  T* row_save = new T[n_];
  T* row1 = data_ + row_num1 * n_;
  T* row2 = data_ + row_num2 * n_;
  std::memcpy(row_save, row2,     size); //rs = r2
  std::memcpy(row2,     row1,     size); //r2 = r1
  std::memcpy(row1,     row_save, size); //r1 = rs

  return -1;
}
//===========================================================================*/
template <typename T>
void Matrix<T>::Random(double min, double max)
{
  std::mt19937 generator(time(0));
  std::uniform_real_distribution<> distribution(min, max);

  for (int64_t y = 0; y < m_; ++y)
  for (int64_t x = 0; x < n_; ++x)
  {
    data_[x + y * n_] = distribution(generator);
  }
}
//===========================================================================*/
