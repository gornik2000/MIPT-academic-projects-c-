//-----------------------------------------------------------------------------
///
/// Words that can be used:
///   x  y  z
///   pi  e  phi  ls
///   +  -  /  *  ^
///   sin  cos  tan  cot
///   arcsin  arccos  arctan  arccot
///   ln  ()
///
//-----------------------------------------------------------------------------
/* if you need optimization, add to optimization node function */
/* name - value_ - type_ - priority - arg number - derivative function*/
//-----------------------------------------------------------------------------
#define D(n)        CreateDerivative(n)
#define C(n)        Copy(n)
#define NC(k, l, r) MyNodeCreate(k, l, r)
#define DC(t, p, v) DDataCreate (t, p, v)
//-----------------------------------------------------------------------------
/* variables  */
DEF_DIFF ("x", 'x', VAR, 255, 0,
          {
            dN = NC(DC(CNST, 255, 1),
                    (MyNode<DData> *)nullptr,
                    (MyNode<DData> *)nullptr
                    );
          })
DEF_DIFF ("y", 'y', VAR, 255, 0,
          {
            dN = NC(DC(CNST, 255, 1),
                    (MyNode<DData> *)nullptr,
                    (MyNode<DData> *)nullptr
                    );
          })

DEF_DIFF ("z", 'z', VAR, 255, 0,
          {
            dN = NC(DC(CNST, 255, 1),
                    (MyNode<DData> *)nullptr,
                    (MyNode<DData> *)nullptr
                    );
          })
//-----------------------------------------------------------------------------
/* operations */
DEF_DIFF ("+",      '+', OP, 30, 2,
          {
            /* node - +, right Child_ - diff(right), left Child_ - diff(left),
            right left Child_ - -1, right right Child_ - cos(copy) */
            dN = NC(DC(OP, 30, '+'),
                    D(n->leftChild_),
                    D(n->rightChild_)
                    );
          })
DEF_DIFF ("-",      '-', OP, 30, 2,
          {
            /* node - -, right Child_ - diff(right), left Child_ - diff(left),
            right left Child_ - -1, right right Child_ - cos(copy) */
            dN = NC(DC(OP, 30, '-'),
                    D(n->leftChild_),
                    D(n->rightChild_)
                    );
          })
DEF_DIFF ("*",      '*', OP, 20, 2,
          {
            dN = NC(DC(OP, 30, '+'),
                    NC(DC(OP, 20, '*'),
                       D(n->leftChild_),
                       C(n->rightChild_)
                       ),
                    NC(DC(OP, 20, '*'),
                       C(n->leftChild_),
                       D(n->rightChild_)
                       )
                    );
          })
DEF_DIFF ("/",      '/', OP, 20, 2,
          {
            dN = NC(DC(OP, 20, '/'),
                    NC(DC(OP, 30, '-'),
                       NC(DC(OP, 20, '*'),
                          D(n->leftChild_),
                          C(n->rightChild_)
                          ),
                       NC(DC(OP, 20, '*'),
                          C(n->leftChild_),
                          D(n->rightChild_)
                          )
                       ),
                    NC(DC(OP, 20, '*'),
                       C(n->rightChild_),
                       C(n->rightChild_)
                       )
                    );
          })
DEF_DIFF ("^",      '^', OP, 15, 2,
          {
            if (n->rightChild_->data_->type_ == CNST)
            {
              dN = NC(DC(OP, 20, '*'),
                      NC(DC(OP, 20, '*'),
                         C(n->rightChild_),
                         NC(DC(OP, 15, '^'),
                            C(n->leftChild_),
                            NC(DC(CNST, 255, n->rightChild_->data_->value_ - 1),
                               (MyNode<DData> *)nullptr,
                               (MyNode<DData> *)nullptr
                              )
                           )
                         ),
                      D(n->leftChild_)
                      );
            }
            else
            {
              dN = NC(DC(OP, 20, '*'),
                      NC(DC(OP, 15, '^'),
                         C(n->leftChild_),
                         C(n->rightChild_)
                         ),
                      NC(DC(OP, 30, '+'),
                         NC(DC(OP, 20, '*'),
                            D(n->rightChild_),
                            NC(DC(OP, 10, 'l'),
                               C(n->leftChild_),
                               (MyNode<DData> *)nullptr
                               )
                            ),
                         NC(DC(OP, 20, '*'),
                            D(n->leftChild_),
                            NC(DC(OP, 20, '/'),
                               C(n->rightChild_),
                               C(n->leftChild_)
                               )
                            )
                         )
                      );
            }
          })

DEF_DIFF ("ln",     'l', OP, 10, 1,
          {
            dN = NC(DC(OP, 20, '*'),
                    D(n->leftChild_),
                    NC(DC(OP, 20, '/'),
                       NC(DC(CNST, 255, 1),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          ),
                       C(n->leftChild_)
                       )
                    );
          })

DEF_DIFF ("sin",    's', OP, 10, 1,
          {
            /* node - *, left - diff(), right - cos(copy) */
            dN = NC(DC(OP, 20, '*'),
                    D(n->leftChild_),
                    NC(DC(OP, 10, 'c'),
                       C(n->leftChild_),
                       (MyNode<DData> *)nullptr
                       )
                   );
          })

DEF_DIFF ("cos",    'c', OP, 10, 1,
          {
            /* node - *, right Child_ - *, left Child_ - diff(),
            right left Child_ - -1, right right Child_ - cos(copy) */
            dN = NC(DC(OP, 20, '*'),
                    D(n->leftChild_),
                    NC(DC(OP, 30, '-'),
                       NC(DC(CNST, 255, 0),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          ),
                       NC(DC(OP, 10, 's'),
                          C(n->leftChild_),
                          (MyNode<DData> *)nullptr
                          )
                       )
                    );
          })

DEF_DIFF ("tan",    't', OP, 10, 1,
          {
            dN = NC(DC(OP, 20, '*'),
                    D(n->leftChild_),
                    NC(DC(OP, 15, '^'),
                       NC(DC(OP, 10, 'c'),
                          C(n->leftChild_),
                          (MyNode<DData> *)nullptr
                          ),
                       NC(DC(CNST, 255, -2),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          )
                       )
                    );
          })

DEF_DIFF ("cot",    '1', OP, 10, 1,
          {
            dN = NC(DC(OP, 20, '*'),
                    D(n->leftChild_),
                    NC(DC(OP, 15, '^'),
                       NC(DC(OP, 10, 's'),
                          C(n->leftChild_),
                          (MyNode<DData> *)nullptr
                          ),
                       NC(DC(CNST, 255, -2),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          )
                       )
                    );
          })

DEF_DIFF ("arcsin", '2', OP, 10, 1,
          {
            dN = NC(DC(OP, 20, '*'),
                    D(n->leftChild_),
                    NC(DC(OP, 15, '^'),
                       NC(DC(OP, 30, '-'),
                          NC(DC(CNST, 255, 1),
                             (MyNode<DData> *)nullptr,
                             (MyNode<DData> *)nullptr
                             ),
                          NC(DC(OP, 15, '^'),
                             C(n->leftChild_),
                             NC(DC(CNST, 255, 2),
                                (MyNode<DData> *)nullptr,
                                (MyNode<DData> *)nullptr
                                )
                             )
                          ),
                       NC(DC(CNST, 255, -0.5),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          )
                       )
                    );
          })

DEF_DIFF ("arccos", '3', OP, 10, 1,
          {
            dN = NC(DC(OP, 20, '*'),
                    NC(DC(OP, 30, '-'),
                       NC(DC(CNST, 255, 0),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          ),
                       D(n->leftChild_)
                       ),
                    NC(DC(OP, 15, '^'),
                       NC(DC(OP, 30, '-'),
                          NC(DC(CNST, 255, 1),
                             (MyNode<DData> *)nullptr,
                             (MyNode<DData> *)nullptr
                             ),
                          NC(DC(OP, 15, '^'),
                             C(n->leftChild_),
                             NC(DC(CNST, 255, 2),
                                (MyNode<DData> *)nullptr,
                                (MyNode<DData> *)nullptr
                                )
                             )
                          ),
                       NC(DC(CNST, 255, -0.5),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          )
                       )
                    );
          })

DEF_DIFF ("arctan", '4', OP, 10, 1,
          {
            dN = NC(DC(OP, 20, '*'),
                    D(n->leftChild_),
                    NC(DC(OP, 15, '^'),
                       NC(DC(OP, 30, '+'),
                          NC(DC(CNST, 255, 1),
                             (MyNode<DData> *)nullptr,
                             (MyNode<DData> *)nullptr
                             ),
                          NC(DC(OP, 15, '^'),
                             C(n->leftChild_),
                             NC(DC(CNST, 255, 2),
                                (MyNode<DData> *)nullptr,
                                (MyNode<DData> *)nullptr
                                )
                             )
                          ),
                       NC(DC(CNST, 255, -1),
                          (MyNode<DData> *)nullptr,
                          (MyNode<DData> *)nullptr
                          )
                       )
                     );
          })
//-----------------------------------------------------------------------------
/* constants  */
DEF_DIFF ("pi",  3.141592654, CNST, 255, 0, ;)
DEF_DIFF ("e",   2.718281828, CNST, 255, 0, ;)
DEF_DIFF ("phi", 1.618033989, CNST, 255, 0, ;)
DEF_DIFF ("lc",  299792458,   CNST, 255, 0, ;)
//-----------------------------------------------------------------------------
#undef D
#undef NCC
#undef NC
#undef DC
//-----------------------------------------------------------------------------
