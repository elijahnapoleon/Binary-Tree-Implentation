#ifndef bst_h
#define bst_h

bool isValid(string s);
int order(string s);

BET::BET()
{
    root = new BinaryNode();
}

BET::BET(const string & postfix)
{
    root = new BinaryNode();
    buildFromPostfix(postfix);
}

BET::BET(const BET& rhs)
{
    root = clone(rhs.root);
}

BET::~BET()
{
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string& postfix)
{
    stack<BinaryNode*> temp;
    stringstream ss(postfix);
    string s1, s2;
    int num1 =0,num2=0;

    if(postfix.length() == 0)
    {
        cout << "Error\n";
        root = nullptr;
        return false;
    }

    if(!empty())
    {
        makeEmpty(root);
    }
    while(ss >> s1)
    {

        BinaryNode * node = new BinaryNode(s1);

        if(isValid(s1))
        {
            temp.push(node);
            num1++;
        }
        else if(order(s1)!=0)
        {
            num2++;
            if(num1==num2)
            {
                cout << "Error\n";
                root = nullptr;
                return false;
            }
            else
            {
                node->left = temp.top();
                temp.pop();
                node->right = temp.top();
                temp.pop();
                temp.push(node);
            }
        }
        
    }
    
    if(num1!=num2)
    {
        root = temp.top();
    }

    if(temp.empty())
    {
        cout << "Error\n";
        root = nullptr;
        return false;
    }

    return true;
}

const BET & BET::operator=(const BET& rhs)
{
    makeEmpty(root);
    root = clone(rhs.root);
    return *this;
}

void BET::printInfixExpression()
{
    printInfixExpression(root);
}

void BET::printPostfixExpression()
{
    printPostfixExpression(root);
}

size_t BET::size()
{
    return size(root);
}

size_t BET::leaf_nodes()
{
    return leaf_nodes(root);
}

bool BET::empty()
{
    return(root==nullptr);
}

void BET::printInfixExpression(BinaryNode *n)
{
    bool p = false;

    if(n!=nullptr)
    {
        if(n->left==nullptr && n->right==nullptr)
        {
            cout << n->element << " ";
        }
        else
        {
            if(order(n->element) != 0 && order(n->right->element) !=0)
            {
                if(order(n->element) >= order(n->right->element))
                {
                    if(order(n->element)==2)
                    {
                        cout << "( ";
                        p=true;
                    }
                }
            }

            printInfixExpression(n->right);

        if(p){cout << ") ";}
        p=false;
        cout << n->element << " ";

        if(order(n->element) != 0 && order(n->left->element) != 0)
        {
            if(order(n->element) >= order(n->left->element))
            {
                cout << "( ";
                p=true;
            }
        }

        printInfixExpression(n->left);
        if(p){cout << ") ";}
        p=false;
        }
    }
}

void BET::makeEmpty(BinaryNode * &t)
{
    if(t!=nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

BET::BinaryNode * BET::clone(BinaryNode *t)
{
    if(t==nullptr){return t;}
    else{return new BinaryNode(t->element,clone(t->left),clone(t->right));}
    
}

void BET::printPostfixExpression(BinaryNode *n)
{
    if(size(n) == 0){return;}
    else if(root->left == nullptr && root->right==nullptr)
    {
        cout << root->element << endl;
    }
    else
    {
        printPostfixExpression(n->right);
        printPostfixExpression(n->left);
        cout << n->element << " ";
    }
    
}

size_t BET::size(BinaryNode *t)
{
    if(t == nullptr){return 0;}
    else{return (size(t->left) + size(t->right) + 1);}
}

size_t BET::leaf_nodes(BinaryNode *t)
{
    if(t == nullptr){return 0;}
    else if(t->left==nullptr&& t->right == nullptr)
    {
        return 1;
    }
    else
    {
        return (leaf_nodes(t->left)+leaf_nodes(t->right));
    }
}

int order(string s)
{
    if(s == "(" || s == ")"){return 3;}
    else if(s == "*" || s == "/"){return 2;}
    else if(s == "+" || s == "-"){return 1;}
    else{return 0;}
}

bool isValid(string s)
{
    for(int i =0;i<s.length();i++)
    {
        if(!isalnum(s[i]))
        {
            return false;
        }
    }
    return true;
}





#endif