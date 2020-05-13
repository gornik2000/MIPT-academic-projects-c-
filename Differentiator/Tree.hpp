//=============================================================================
template <typename T>
class MyNode
{
  public:
    T      *data_;

    MyNode *leftChild_;
    MyNode *parent_;
    MyNode *rightChild_;

    int     deepness_;

    MyNode();
    MyNode(T *data, MyNode& leftChild, MyNode& rightChild);
    ~MyNode();
    int Repair();
    void KillChildren();
};
//=============================================================================
template <typename T>
class MyTree:MyNode<T>
{
  public:
    MyNode<T> *rootNode_;
    int  edgeCount_;

    MyTree();
    ~MyTree();
    void Repair();
};
//=============================================================================
