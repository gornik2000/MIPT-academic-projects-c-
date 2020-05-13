//=============================================================================
#include "Tree.hpp"
//=============================================================================
template <typename T>
MyNode<T>::MyNode()
{
  data_ = new T;

  leftChild_  = nullptr;
  parent_     = nullptr;
  rightChild_ = nullptr;

  deepness_ = 0;
}

template <typename T>
MyNode<T>::MyNode(T *data, MyNode& leftChild, MyNode& rightChild)
{
  data_       = data;

  leftChild_  = leftChild;
  parent_     = nullptr;
  rightChild_ = rightChild;

  deepness_ = 0;
}

template <typename T>
MyNode<T>::~MyNode()
{
  delete data_;
  delete leftChild_;
  delete rightChild_;

  leftChild_  = nullptr;
  parent_     = nullptr;
  rightChild_ = nullptr;

  deepness_ = 0;
}

template <typename T>
void MyNode<T>::KillChildren()
{
  if (leftChild_ != nullptr)
  {
    delete leftChild_;
    leftChild_ = 0;
  }
  if (rightChild_ != nullptr)
  {
    delete rightChild_;
    rightChild_ = 0;
  }
}

template <typename T>
int MyNode<T>::Repair()
{
  if (leftChild_ != nullptr && rightChild_ != nullptr)
  {
    leftChild_ ->parent_   = this;
    leftChild_ ->deepness_ = deepness_ + 1;
    rightChild_->parent_   = this;
    rightChild_->deepness_ = deepness_ + 1;
    return rightChild_->Repair() +
           leftChild_->Repair()  + 2;
  }
  if (leftChild_ != nullptr)
  {
    leftChild_->parent_   = this;
    leftChild_->deepness_ = deepness_ + 1;
    return leftChild_->Repair() + 1;
  }
  if (rightChild_ != nullptr)
  {
    rightChild_->parent_   = this;
    rightChild_->deepness_ = deepness_ + 1;
    return rightChild_->Repair() + 1;
  }

  return 0;
}
//============================================================================
template <typename T>
MyNode<T> *MyNodeCreate(T *data, MyNode<T> *leftChild, MyNode<T> *rightChild)
{
  MyNode<T> *n = new MyNode<T>;
  n->data_ = data;
  n->leftChild_  = leftChild;
  n->rightChild_ = rightChild;
  return n;
}
//============================================================================
template <typename T>
MyTree<T>::MyTree()
{
  rootNode_ = new MyNode<T>;//new MyNode<T>;
  edgeCount_ = 1;
}

template <typename T>
MyTree<T>::~MyTree()
{
  edgeCount_ = -1;
  delete rootNode_;
}

template <typename T>
void MyTree<T>::Repair()
{
  rootNode_->parent_   = nullptr;
  rootNode_->deepness_ = 0;
  edgeCount_ = rootNode_->Repair();
}
//=============================================================================
