#include "Matrix.cpp"

int main()
{ /*
	Matrix<double> m1(3, 3);
	m1(0,0) = 0;
  m1(0,1) = 2;
  m1(0,2) = 1;

	m1(1,0) = 4;
  m1(1,1) = 5;
  m1(1,2) = 2;

  m1(2,0) = 1;
  m1(2,1) = 3;
  m1(2,2) = 2;*/

  for (int x = 1; x < 20; ++x)
  {
    Matrix<double> m2(x * 50, x * 50);
    int time = 0;
    for (int i = 0; i < 3; ++ i)
    {
      m2.Random(0, 0.5);
	    int start = clock();
	    std::cout << x * 50 << "//" << m2.Det() << "\n";// << m2.Row_echelon_form() << "\n";
      time += clock() - start;
    }
    std::cout << time / 3 << "clocks\n";
  }
  return 0;
}
