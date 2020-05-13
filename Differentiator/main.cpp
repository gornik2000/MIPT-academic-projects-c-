//====================================================================================
#include "Differentiator.cpp"
//====================================================================================
int main ()
{
  std::cout << " # Differentiator 2.0\n"                                             \
               " # This program helps to count derivatives of the inputted data \n"  \
               " # Input expression in \"data.txt\" without enter and"               \
               " with all brackets\n"                                                \
               " # Derivative can be found in \"out.pdf\". Good luck! \n\n";

  int diffNumber = 0;
  std::cout <<  " # enter Derivative number ";
  std::cin  >> diffNumber;
  std::cout << "\n";

  Differentiate("data.txt", "out.tex", diffNumber);
  system("Tex\\pdflatex.exe out.tex");
  system("cls");

  std::cout << " # Derivative was successfully counted\n"                            \
               " # Thanks for using this program\n";

  return 0;
}
//====================================================================================
