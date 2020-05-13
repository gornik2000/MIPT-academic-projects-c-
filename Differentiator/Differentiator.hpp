//=============================================================================
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
//=============================================================================
enum DIFF_VAR_TYPES
{
  CNST = 1, /* const can't be used */
  OP   = 2,
  VAR  = 3,
};
const char   MAX_COMMAND_SIZE = 20;
//=============================================================================
class DData
{
  public:
    char   type_;
    char   priority_;
    double value_;

    DData();
    DData(char type, char priority, double value);
    ~DData();
};

DData *DDataCreate(char type, char priority, double value);
//=============================================================================
#include "RecursiveDescent.cpp"
#include "Optimization.cpp"
//=============================================================================
void Differentiate(const std::string &fileInName,
                   const std::string &fileOutName, int diffNumber);

MyNode<DData> *CreateDerivative(MyNode<DData> *n);
MyNode<DData> *Copy(MyNode<DData> *n);

void SubTreeToFile(MyNode<DData> *n, std::ofstream& fileOut);
void TexOpening(std::ofstream& fileOut);
void TexEnding (std::ofstream& fileOut);

std::string CreateStrFromFile(const std::string& fileName);
//=============================================================================
