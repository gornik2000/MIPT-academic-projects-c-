//---------------------------------------------------------------------------*/
#define DEBUG
//---------------------------------------------------------------------------*/
#include "vector.h"
//---------------------------------------------------------------------------*/
int fake_main1()
{
  int size = 10;

  vector<int> a(size);
  vector<int> d(size);

  std::cin >> d;
  std::cout << d << "\n";

  std::cout << sizeof(long long) << "\n";

  std::cout << a << "\n";

  for (int i = 0; i < size; i++)
  {
    a[i] = i*i;
  }

  std::cout << a << "\n";
  vector<int> b = a * 2;

  std::cout << b << "\n";
  vector<int> c = b;

  std::cout << c * 2 << "\n";

  return 0;
}
int fake_main2 ()
{
  int size = 10;
  vector<bool> a(size);

  std::cout << "1:" << a << "\n";

  a[1] = true;
  std::cout << "2:" << a << "\n";

  a[3] = a[2] = a[1];
  std::cout << "3:" << a << "\n";
  vector<bool> b(size);

  //std::cout << c  << "\n";
  std::cout << b << "\n";

  a[4] = 1;
  std::cout << "4:" << a << "\n";

  a[5] = 1;
  std::cout << "5:" << a << "\n";

  a[4] = 0;
  std::cout << "6:" << a << "\n";

  a[5] = a.at(4);
  std::cout << "7:" << a << "\n";
  //*/
  std::cout << 100/64;
  return 0;
}
//---------------------------------------------------------------------------*/
int main ()
{
  fake_main2();

  fclose (LOG_FILE_MEMORY);
  fclose (LOG_FILE_VECTOR);

  int step = 1000;
  memory_scan (step);

  return 0;
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
