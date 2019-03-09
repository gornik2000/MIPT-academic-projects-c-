#define DEBUG
//*/---------------------------------------------------------------------------
#include "vector.cpp"
//*/---------------------------------------------------------------------------
int main()
{
  int size = 5;
  vector a(5);
  std::cout << a << "\n";
  for (int i = 0; i < size; i++)
  {
    a[i] = i*i;
  }
  vector b = a * 2;
  //std::cin >> b;
  std::cout << b;
  vector c = b;
  std::cout << c * 2;
  return 0;

  fclose (log_file_memory);
  fclose (log_file_vector);
}
//*/---------------------------------------------------------------------------
