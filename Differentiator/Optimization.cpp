//=============================================================================
#include "Optimization.hpp"
//=============================================================================
void Simplify(MyNode<DData> *n)
{
  if (n == nullptr) return;

  Simplify(n->leftChild_ );
  Simplify(n->rightChild_);

  if (n->data_->type_ != OP)
  {
    return;
  }
  switch ((int)n->data_->value_)
  {
    case '+':
      SimplifyAdd(n);
      return;
    case '-':
      SimplifySub(n);
      return;
    case '*':
      SimplifyMul(n);
      return;
    case '^':
      SimplifyPow(n);
      return;
    case '/':
      SimplifyDiv(n);
      return;
  }
}
//=============================================================================
void SimplifyEquate(MyNode<DData> *a, MyNode<DData> *b)
{
  a->data_       = b->data_;
  a->leftChild_  = b->leftChild_;
  a->rightChild_ = b->rightChild_;
}
// 0+x=x+0=x a+b
void SimplifyAdd(MyNode<DData> *n)
{
  if (n->leftChild_ ->data_->type_ == CNST && n->leftChild_ ->data_->value_ == 0)
  {
    MyNode<DData> *child = n->rightChild_;
    SimplifyEquate(n, child);
    return;
  }
  if (n->rightChild_->data_->type_ == CNST && n->rightChild_->data_->value_ == 0)
  {
    MyNode<DData> *child = n->leftChild_;
    SimplifyEquate(n, child);
    return;
  }
  if (n->leftChild_->data_->type_ == CNST && n->rightChild_->data_->type_ == CNST)
  {
    n->data_ = DDataCreate(CNST, 255, n->leftChild_->data_->value_ + n->rightChild_->data_->value_);
    n->KillChildren();
    return;
  }
}
// x-0=x x-x=0 a-b
void SimplifySub(MyNode<DData> *n)
{
  if (n->rightChild_->data_->type_ == CNST && n->rightChild_->data_->value_ == 0)
  {
    MyNode<DData> *child = n->leftChild_;
    SimplifyEquate(n, child);
    return;
  }
  if (n->leftChild_->data_->type_ == CNST && n->rightChild_->data_->type_ == CNST)
  {
    n->data_ = DDataCreate(CNST, 255, n->leftChild_->data_->value_ - n->rightChild_->data_->value_);
    n->KillChildren();
    return;
  }
}
// 1*x=x x*1=x 0*x=0 x*0=0 a*b
void SimplifyMul(MyNode<DData> *n)
{
  if (n->leftChild_ ->data_->type_ == CNST && n->leftChild_ ->data_->value_ == 1)
  {
    MyNode<DData> *child = n->rightChild_;
    SimplifyEquate(n, child);
    return;
  }
  if (n->rightChild_->data_->type_ == CNST && n->rightChild_->data_->value_ == 1)
  {
    MyNode<DData> *child = n->leftChild_;
    SimplifyEquate(n, child);
    return;
  }
  if (n->leftChild_ ->data_->type_ == CNST && n->leftChild_ ->data_->value_ == 0)
  {
    n->data_ = DDataCreate(CNST, 255, 0);
    n->KillChildren();
    return;
  }
  if (n->rightChild_->data_->type_ == CNST && n->rightChild_->data_->value_ == 0)
  {
    n->data_ = DDataCreate(CNST, 255, 0);
    n->KillChildren();
    return;
  }
  if (n->leftChild_->data_->type_ == CNST && n->rightChild_->data_->type_ == CNST)
  {
    n->data_ = DDataCreate(CNST, 255, n->leftChild_->data_->value_ * n->rightChild_->data_->value_);
    n->KillChildren();
    return;
  }
}
// 1^x=1 x^1=x 0^x=0 x^0=1 a^b
void SimplifyPow(MyNode<DData> *n)
{
  if (n->leftChild_ ->data_->type_ == CNST && n->leftChild_ ->data_->value_ == 1)
  {
    n->data_ = DDataCreate(CNST, 255, 1);
    n->KillChildren();
    return;
  }
  if (n->rightChild_->data_->type_ == CNST && n->rightChild_->data_->value_ == 1)
  {
    MyNode<DData> *child = n->leftChild_;
    SimplifyEquate(n, child);
    return;
  }
  if (n->leftChild_ ->data_->type_ == CNST && n->leftChild_ ->data_->value_ == 0)
  {
    n->data_ = DDataCreate(CNST, 255, 0);
    n->KillChildren();
    return;
  }
  if (n->rightChild_->data_->type_ == CNST && n->rightChild_->data_->value_ == 0)
  {
    n->data_ = DDataCreate(CNST, 255, 1);
    n->KillChildren();
    return;
  }
  if (n->leftChild_->data_->type_ == CNST && n->rightChild_->data_->type_ == CNST)
  {
    n->data_ = DDataCreate(CNST, 255, std::pow(n->leftChild_->data_->value_,n->rightChild_->data_->value_));
    n->KillChildren();
    return;
  }
}
// x/1=x 0/x=0 a/b
void SimplifyDiv(MyNode<DData> *n)
{
  if (n->rightChild_->data_->type_ == CNST && n->rightChild_->data_->value_ == 1)
  {
    MyNode<DData> *child = n->leftChild_;
    SimplifyEquate(n, child);
    return;
  }
  if (n->leftChild_ ->data_->type_ == CNST && n->leftChild_ ->data_->value_ == 0)
  {
    n->data_ = DDataCreate(CNST, 255, 0);
    n->KillChildren();
    return;
  }
  if (n->leftChild_->data_->type_ == CNST && n->rightChild_->data_->type_ == CNST)
  {
    n->data_ = DDataCreate(CNST, 255, n->leftChild_->data_->value_ / n->rightChild_->data_->value_);
    n->KillChildren();
    return;
  }

}
//=============================================================================
