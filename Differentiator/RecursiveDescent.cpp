//=============================================================================
#include "Tree.cpp"
#include <ctype.h>
#include <iostream>
#include <string.h>
//-----------------------------------------------------------------------------
///   G::=E'\0'
///   E::=T{[+-]T}*
///   T::=D{[*/]D}*
///   D::=P{^P}*
///   P::=(E)|N|S
///
///   N::=double number
///   S::=string from base
//-----------------------------------------------------------------------------
const int   MAX_COMMAND_LENGTH    = 15;
const char *TREE_STRING_FOR_INPUT = NULL;
#define s TREE_STRING_FOR_INPUT

MyTree<DData> GetTreeFromStr(std::string& str);
MyNode<DData> *getE(void);
MyNode<DData> *getT(void);
MyNode<DData> *getD(void);
MyNode<DData> *getP(void);
MyNode<DData> *getN(void);
MyNode<DData> *getS(void);
//-----------------------------------------------------------------------------
MyTree<DData> GetTreeFromStr(std::string& str)
{
  s = str.data();
  MyTree<DData> t;

  if (*s == '\0')
  {
    std::cout << " # ERROR! Empty inputted data\n";
    return t;
  }

  t.rootNode_ = getE();

  if (*s != '\0')
  {
    std::cout << s << " # ERROR! Incorrect data, 0 was not found in the end\n";
    return t;
  }

  return t;
}
//-----------------------------------------------------------------------------
MyNode<DData> *getE(void)
{
  std::cout << "GetE\n";
  MyNode<DData> *nLeft = getT();

  while (*s == '+' || *s == '-')
  {
    int op = *s;
    s++;

    MyNode<DData> *nRight = getT();
    if (op == '+')
    {
      nLeft = MyNodeCreate<DData>(DDataCreate(OP, 30, '+'),
                                  nLeft,
                                  nRight
                                  );
    }
    else
    {
      nLeft = MyNodeCreate<DData>(DDataCreate(OP, 30, '-'),
                                  nLeft,
                                  nRight
                                  );
    }
  }

  return nLeft;
}
//-----------------------------------------------------------------------------
MyNode<DData> *getT(void)
{
  std::cout << "GetT\n";
  MyNode<DData> *nLeft = getD();

  while (*s == '*' || *s == '/')
  {
    int op = *s;
    s++;

    MyNode<DData> *nRight = getD();
    if (op == '*')
    {
      nLeft = MyNodeCreate<DData>(DDataCreate(OP, 20, '*'),
                                  nLeft,
                                  nRight
                                  );
    }
    else
    {
      nLeft = MyNodeCreate<DData>(DDataCreate(OP, 20, '/'),
                                  nLeft,
                                  nRight
                                  );
    }
  }

  return nLeft;
}
//-----------------------------------------------------------------------------
MyNode<DData> *getD(void)
{
  std::cout << "GetD\n";
  MyNode<DData> *nLeft = getP();

  while (*s == '^')
  {
    s++;

    MyNode<DData> *nRight = getP();
    nLeft = MyNodeCreate<DData>(DDataCreate(OP, 15, '^'),
                                nLeft,
                                nRight
                                );
  }

  return nLeft;
}
//-----------------------------------------------------------------------------
MyNode<DData> *getP(void)
{
  std::cout << "GetP\n";
  if (*s == '(')
  {
    s++;
    MyNode<DData> *n = getE();
    if (*s != ')')
    {
      std::cout << " ERROR! ) was not found\n";
      return n;
    }
    s++;
    return n;
  }
  if (isdigit (*(s)))
  {
    /* think about it */
    return getN();
  }
  if (isalpha (*(s)))
  {
    /* think about it */
    return getS();
  }

  std::cout << " # ERROR. Got not digit and not alpha\n";
}
//-----------------------------------------------------------------------------
MyNode<DData> *getN(void)
{
  std::cout << "GetN\n";
  char number[MAX_COMMAND_LENGTH] = {0};
  int i = 0;

  while (isdigit(*s) || *s == '.')
  {
    number[i] = *s;
    s++;
    i++;
  }
  std::cout << atof(number);
  return MyNodeCreate<DData>(DDataCreate(CNST, 255, atof(number)),
                             (MyNode<DData> *)nullptr,
                             (MyNode<DData> *)nullptr
                             );
}
//-----------------------------------------------------------------------------
#define DEF_DIFF(name, val, tp, pt, arg, funD)                                \
{                                                                             \
  if (strcmp(name, buf) == 0)                                                 \
  {                                                                           \
    switch(arg)                                                               \
    {                                                                         \
      case 0:                                                                 \
        return MyNodeCreate<DData>(DDataCreate(tp, pt, val),                  \
                                   (MyNode<DData> *)nullptr,                  \
                                   (MyNode<DData> *)nullptr                   \
                                   );                                         \
      case 1:                                                                 \
        return MyNodeCreate<DData>(DDataCreate(tp, pt, val),                  \
                                   getP(),                                    \
                                   (MyNode<DData> *)nullptr                   \
                                   );                                         \
      default:                                                                \
        std::cout << " # ERROR. Arg for constant was not inputted";           \
    }                                                                         \
  }                                                                           \
}
MyNode<DData> *getS(void)
{
  std::cout << "GetS\n";
  char buf[MAX_COMMAND_LENGTH] = {0};
  int i = 0;

  while (i < MAX_COMMAND_LENGTH)
  {
    buf[i] = *s;
    s++;
    i++;
    #include "operations.h"
  }

  std::cout << " # Command has not been read\n";
  return NULL;
}
#undef DEF_DIFF
//-----------------------------------------------------------------------------
