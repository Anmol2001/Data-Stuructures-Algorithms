//group 5
#include <iostream>
using namespace std;
// this is a modified code from normal red black tree
// which uses sum of children at every node as extra field for augmentation
// creating structure for a node in the tree
struct Node {
    int data; // holds the key
    Node *parent; // pointer to the parent
    Node *left; // pointer to left child
    Node *right; // pointer to right child
    int color; //  1-> Red, 0 -> Black
    int size_subT;  //  size of the subtree(node included)
    int value;  // value of element stored in node
    int sum;   // sum of values of subtree(node included)
};
typedef Node *Pointer;
// class redBlackTree implements the operations in Red Black Tree
struct redBlackTree {
public:
    Pointer root;
    Pointer TNULL;
    // initializes the nodes
    // all the pointers are set to be NULL
    void initialize(Pointer node, Pointer parent) {
        node->data = 0;
        node->parent = parent;
        node->left = NULL;
        node->right = NULL;
        node->color = 0;
        node->size_subT = 0;
        node->sum = 0;
        node->value = 0;
    }




   // selecting the node by rank by checking rank=size of left child +1
   // and moving left or right at each step accordingly
    Node* Select(Node* root , int i){
        int position = root->left->size_subT + 1;
    Pointer y = root;
    for (int cj=1; cj>0; cj++) {
        if (y == NULL || position == i){break;}
        else{
        if (i < position)
            y = y->left;
        else {
            i = i - position;
            y = y->right;
        }
        if (y == NULL)
            return NULL;
        position = y->left->size_subT + 1;
        }
    }
    return y;
    }
    int Sum(Node* root,int i){
        int sum = 0;
      int position = root->left->size_subT + 1;
    Pointer y = root;
    for (int cj=1; cj>0; cj++) {
        if (y == NULL || position == i){break;}
        else{
        if (i < position)
            y = y->left;
        else {
            i = i - position;
            sum += y->left->sum + y->value;
            y = y->right;
        }
        if (y == NULL)
            return 0;
        position = y->left->size_subT + 1;}
    }
    return sum + y->value + y->left->sum;
    }

    // fix the rb tree modified by the delete operation
    void deletefixing(Pointer x) {
        Pointer s;
        for (int cj=1; cj>0; cj++) {
            if (x == root || x->color != 0){break;}
            else{
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        // case 3.3
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        // case 3.3
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
            }
        }
        x->color = 0;
    }


    void redblackReplace(Pointer u, Pointer v){
        if (u->parent == NULL) {
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeTool(Pointer node, int key) {
        // find the node containing key
        Pointer z = TNULL;
        Pointer x, y;
        z = Select(root,key);
        if (z == TNULL) {
            cout<<"Couldn't find key in the tree"<<endl;
            return;
        }
        if (z != node) {
        Pointer tmp = z->parent;
        for (int cj=1; cj>0; cj++) {
            if (tmp == NULL){break;}
            else{
            tmp->size_subT--;
            tmp->sum -= z->value;
            tmp = tmp->parent;
            }
        }

    }
        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            redblackReplace(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            redblackReplace(z, z->left);
        } else {
            y = min(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                redblackReplace(y, y->right);
                y->right = z->right;
                y->right->parent = y;
                    Pointer tmp = x->parent;
                 for (int cj=1; cj>0; cj++) {
                     if (tmp == y){break;}
                     else{
                tmp->sum -= z->value;
                tmp->size_subT--;
                tmp = tmp->parent;
                     }
            }
            y->size_subT = y->left->size_subT + 1;
            y->sum = y->left->sum + y->value;
            }

            redblackReplace(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        //delete z;
        y->size_subT = y->left->size_subT + y->right->size_subT + 1;
        y->sum = y->left->sum + y->right->sum + y->value;
        if (y_original_color == 0){
            deletefixing(x);
        }
    }

    // fix the red-black tree
    void After_insert(Pointer k){
        Pointer u;
        for (int cj=1; cj>0; cj++) {
            if (k->parent->color != 1){break;}
            else{
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == 1) {
                    // case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle

                if (u->color == 1) {
                    // mirror case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
            }
        }
        root->color = 0;
    }



public:
    redBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = NULL;
        TNULL->right = NULL;
        root = TNULL;
        TNULL->size_subT = 0;
        TNULL->value = 0;
        TNULL->sum = 0;
    }



    // find the node with the min key
    Pointer min(Pointer node) {
        for (int cj=1; cj>0; cj++) {
            if (node->left == TNULL){break;}
            else{
            node = node->left;
            }
        }
        return node;
    }

    // find the node with the maximum key
    Pointer maximum(Pointer node) {
        for (int cj=1; cj>0; cj++) {
            if (node->right == TNULL){break;}
            else{
            node = node->right;
            }
        }
        return node;
    }

    // rotate right at a node and updating size accordingly
    void rightRotate(Pointer x) {
        Pointer y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
        x->size_subT = y->size_subT;
        y->size_subT = y->left->size_subT + y->right->size_subT + 1;
        x->sum = y->sum;
        y->sum = y->left->sum + y->right->sum + y->value;
        // updating the size after rotation as the root at point of rotation changes
        // and so the value of sum needs to be updated
    }

     // rotate left at a node and updating size accordingly
    void leftRotate(Pointer x) {
        Pointer y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        y->size_subT = x->size_subT;
        y->sum = x->sum;
        x->size_subT = x->left->size_subT + x->right->size_subT +1;
        x->sum = x->left->sum + x->right->sum + x->value;

    }

    // insert the key to the tree in its appropriate position
    // and fix the tree
    void insert(int key,int value) {
        // Ordinary Binary Search Insertion
        Pointer node = new Node;
        node->parent = NULL;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; // new node must be red
        node->size_subT = 1;
        node->value = value;
        node->sum = value;

        Pointer y = NULL;
        Pointer x = this->root;

        for (int cj=1; cj>0; cj++) {
            if (x == TNULL){break;}
            else{
            y = x;
            y->size_subT++;
            y->sum += value;
            if (node->data > x->data) {
                x = x->right;
            } else {
                x = x->left;
            }
            }
        }

        // y is parent of x
        node->parent = y;
        if (y == NULL) {
            root = node;
        } else if (node->data <= y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        // if new node is a root node then return
        if (node->parent == NULL){
            root = node;
            node->color = 0;
            return;
        }

        // if the grandparent is null then return
        if (node->parent->parent == NULL) {
            return;
        }

        // Fix the tree
        After_insert(node);
    }

    // deleting the node
    void deleteNode(int data) {
        deleteNodeTool(this->root, data);
    }

};

int main() {
    redBlackTree bst;
    int e;
    int index,value,position,l,r;
    double s1;
    Node* searched;
    int Q;
   cout<<"Enter the number of operations you want to perform\n"<<"\n";
    cin>>Q;
    while(Q--){
        cout<<"Choose e according to the operation you need to perform\n";
    cin>>e;
         // e==1: insert needs index and value
         // 2: delete needs index
         // 3: search needs to index;
         // 4: find average between range l to r
    if (e==1){
        cout<<"Index and Value of the element you want to insert\n";
        cin>>index>>value;
        bst.insert(index,value);}
    else if (e==2){
        cout<<"Index of the element you want to delete\n";
        cin>>index;
        bst.deleteNode(index);}

    else if (e==3){
        cout<<"Index of the element you want to search\n";
        cin>>position;
        searched  = bst.Select(bst.root,position);
        cout<<searched->value<<"\n";}
    else if (e==4){   // its for part b
        cout<<"Pick l and r\n";
        cin>>l>>r;
        s1 = float(bst.Sum(bst.root,r));
        if(l>1){
             s1 -= float(bst.Sum(bst.root,l-1));
        }
        float length = float(r-l+1);
        s1 /= length;
        cout<<s1<<"\n";}
}

    return 0;
}
