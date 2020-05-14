//=============================================================================
#include "Differentiator.hpp"
//=============================================================================
DData::DData()
{
  type_     = 0;
  priority_ = 0;
  value_    = 0;
}

DData::DData(char type, char priority, double value)
{
  type_     = type;
  priority_ = priority;
  value_    = value;
}

DData::~DData()
{
  type_     = 0;
  priority_ = 0;
  value_    = 0;
}

DData *DDataCreate(char type, char priority, double value)
{
  DData *d = new DData;
  d->type_     = type;
  d->priority_ = priority;
  d->value_    = value;
  return d;
}
//=============================================================================
void Differentiate(const std::string &fileInName,
                   const std::string &fileOutName, int diffNumber)
{
  std::string dStr = CreateStrFromFile("data.txt");

  MyTree<DData> T = GetTreeFromStr(dStr);
  Simplify(T.rootNode_);
  std::ofstream fileOut(fileOutName);
  TexOpening(fileOut);
  fileOut << "\\begin{center}Morning nose to Stephen Wolfram!\n\\end{center}";

  fileOut << "\\begin{equation}\\label{eq:solv}\n f = ";
  SubTreeToFile(T.rootNode_, fileOut);
  fileOut << "\n\\end{equation}\n";

  MyTree<DData> dT;

  for (int i = 0; i < diffNumber; ++i)
  {
    dT.rootNode_ = CreateDerivative(T.rootNode_);
    T = dT;
    Simplify(dT.rootNode_);
    fileOut << "\\begin{equation}\\label{eq:solv}\n f^{(" << i + 1 << ")} = ";
    SubTreeToFile(dT.rootNode_, fileOut);
    fileOut << "\n\\end{equation}\n";
  }

  //dT.Repair();
  TexEnding(fileOut);
}
//=============================================================================
#define DEF_DIFF(name, val, tp, pt, arg, funD)                                \
{                                                                             \
  if (n->data_->type_  == tp   &&                                             \
      n->data_->type_  != CNST &&                                             \
      n->data_->value_ == val)                                                \
  {                                                                           \
    MyNode<DData> *dN = 0;                                                    \
    funD                                                                      \
    return dN;                                                                \
  }                                                                           \
}
/* derivative of n */
MyNode<DData> *CreateDerivative(MyNode<DData> *n)
{
  #include "Operations.h"

  MyNode<DData> *dN = new MyNode<DData>;
  dN->data_ = DDataCreate(CNST, 255, 0.0);
  return dN;
}
#undef DEF_DIFF
//=============================================================================
MyNode<DData> *Copy(MyNode<DData> *n)
{
  MyNode<DData> *nCopy = new MyNode<DData>;

  nCopy->data_ = DDataCreate(n->data_->type_, n->data_->priority_, n->data_->value_);
  nCopy->deepness_ = n->deepness_;
  nCopy->parent_   = n->parent_;

  if (n->leftChild_  != nullptr)
  {
    nCopy->leftChild_  = Copy(n->leftChild_);
  }
  if (n->rightChild_ != nullptr)
  {
    nCopy->rightChild_ = Copy(n->rightChild_);
  }

  return nCopy;
}
//=============================================================================
void TexOpening(std::ofstream& fileOut)
{
  fileOut << "\\documentclass[12pt,a4paper]{scrartcl}\n"                      \
             "\\usepackage[utf8]{inputenc}\n"                                 \
             "\\usepackage[english,russian]{babel}\n"                         \
             "\\usepackage{indentfirst}\n"                                    \
             "\\usepackage{misccorr}\n"                                       \
             "\\usepackage{graphicx}\n"                                       \
             "\\usepackage{amsmath}\n"                                        \
             "\\begin{document}\n";
}
//=============================================================================
void TexEnding(std::ofstream& fileOut)
{
  fileOut << "\\end{document}";
  fileOut.close();
}
//=============================================================================
#define DEF_DIFF(name, val, tp, pt, arg, funD)                                \
{                                                                             \
  if (n->data_->type_ == tp && n->data_->value_ == val)                       \
  {                                                                           \
    if (tp == VAR || tp == CNST ||                                            \
       (tp == OP && val == '^' || val == '+' || val == '-' || val == '*'))    \
    {                                                                         \
      fileOut  << name;                                                       \
    }                                                                         \
    else                                                                      \
    {                                                                         \
      fileOut << "{";                                                         \
      fileOut << '\\' <<name;                                                 \
      fileOut << "}";                                                         \
    }                                                                         \
    skip = 1;                                                                 \
  }                                                                           \
}
void SubTreeToFile(MyNode<DData> *n, std::ofstream& fileOut)
{
  if (n->data_->type_ == OP && n->data_->value_ == '/')
  {
    fileOut << "\\frac";

    fileOut << "{";
    SubTreeToFile(n->leftChild_, fileOut);
    fileOut << "}";

    fileOut << "{";
    SubTreeToFile(n->rightChild_, fileOut);
    fileOut << "}";

    return;
  }

  if (n->data_ != nullptr && n->rightChild_ == nullptr)
  {
    char skip = 0;
    #include "Operations.h"

    if (skip == 0)
    {
      fileOut << n->data_->value_;
    }
  }

  if (n->leftChild_ != nullptr)
  {
    if ((n->leftChild_->data_->priority_) > (n->data_->priority_))
    {
      fileOut << "(";
      SubTreeToFile(n->leftChild_, fileOut);
      fileOut << ")";
    }
    else
    {
      SubTreeToFile(n->leftChild_, fileOut);
    }
  }

  if (n->data_ != nullptr && n->rightChild_ != nullptr)
  {
    char skip = 0;

    #include "Operations.h"

    if (skip == 0)
    {
      fileOut << n->data_->value_;
    }
  }

  if (n->rightChild_ != nullptr)
  {
    if (n->rightChild_->data_->priority_ > n->data_->priority_)
    {
      fileOut << "(";
      SubTreeToFile(n->rightChild_, fileOut);
      fileOut << ")";
    }
    else
    {
      SubTreeToFile(n->rightChild_, fileOut);
    }
  }
}
#undef DEF_DIFF
//=============================================================================
std::string CreateStrFromFile(const std::string& fileName)
{
  std::ifstream fileIn(fileName);
  std::stringstream strFile;
  strFile << fileIn.rdbuf();
  fileIn.close();

  return strFile.str();
}
//=============================================================================
