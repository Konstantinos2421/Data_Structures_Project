#include <iostream>
#include <fstream>
#include <sstream>
#define N 1405

using namespace std;

class Node{

    public:
        Node *father;
        Node *right_son;
        Node *left_son;

        string date;
        float temperature;

        int height;

    Node(string date, float temperature, Node *father, Node *left_son, Node *right_son){
        this->date = date;
        this->temperature = temperature;

        this->father = father;
        this->right_son = right_son;
        this->left_son = left_son;
    }

};


class AVL_Tree{

    public:
        Node *root;

    AVL_Tree(){
        root = nullptr;
    }


    Node* Search(float temperature);

    void Insert(ifstream &fin);

    void leftRotation(Node *v);

    void rightRotation(Node *v);

    void balanceTree(Node *v);

    void fixNodesHeight(Node *v);

    Node* findMin();

    Node* findMax();

    void displayMenu();

};


Node* AVL_Tree::Search(float temperature){
    Node *v = root;

    while(v->left_son!=nullptr && v->right_son!=nullptr){
        if(temperature <= v->temperature)
            v = v->left_son;
        else if(temperature > v->temperature)
            v = v->right_son;
    }
    return v;
}


void AVL_Tree::Insert(ifstream &fin){
    string temp_string, date ,temperature;

    if(fin.is_open()){
        getline(fin, temp_string);
        while(getline(fin, temp_string)){
            stringstream row(temp_string);
            getline(row, date, ',');
            getline(row, temperature, ',');

            if(this->root == nullptr){
                root = new Node(date, stof(temperature), nullptr, nullptr, nullptr);
            }else{
                float t = stof(temperature);
                Node *v = Search(t);
                if(t != v->temperature){
                    Node *new_node = new Node(date, t, nullptr, nullptr, nullptr);
                    if(new_node->temperature > v->temperature){
                        v->left_son = new Node(v->date, v->temperature, v, nullptr, nullptr);
                        v->right_son = new_node;
                        new_node->father = v;
                        fixNodesHeight(v);
                    }else if(new_node->temperature < v->temperature){
                        if(v->father->left_son == v)
                            v->father->left_son = new_node;
                        else if(v->father->right_son == v)
                            v->father->right_son = new_node;

                        new_node->father = v->father;
                        new_node->left_son = new Node(new_node->date, new_node->temperature, new_node, nullptr, nullptr);
                        new_node->right_son = v;
                        v->father = new_node;
                        v->left_son = nullptr;
                        v->right_son = nullptr;
                        fixNodesHeight(v->father);
                    }
                    balanceTree(v);
                }
            }
        }
    }else{
        cout << "Error in reading file";
        exit(0);
    }
}


void AVL_Tree::leftRotation(Node *x){
    Node *y = x->right_son;

    if(x != this->root){
        if(x->father->left_son == x)
            x->father->left_son = y;
        else if(x->father->right_son == x)
            x->father->right_son = y;
    }else this->root = y;

    y->father = x->father;
    x->right_son = y->left_son;
    y->left_son = x;
    x->father = y;
    x->right_son->father = x;

    fixNodesHeight(x);

}


void AVL_Tree::rightRotation(Node *x){
    Node *y = x->left_son;

    if(x != this->root){
        if(x->father->left_son == x)
            x->father->left_son = y;
        else if(x->father->right_son == x)
            x->father->right_son = y;
    }else this->root = y;

    y->father = x->father;
    x->left_son = y->right_son;
    y->right_son = x;
    x->father = y;
    x->left_son->father = x;

    fixNodesHeight(x);

}

void AVL_Tree::balanceTree(Node *v){
    float temperature = v->temperature;

    while(v!=root){
        v = v->father;
        int balance = v->right_son->height - v->left_son->height;
        if(balance > 1){
            if(temperature > v->right_son->temperature){
                leftRotation(v);
                break;
            }else if(temperature <= v->right_son->temperature){
                rightRotation(v->right_son);
                leftRotation(v);
                break;
            }
        }else if(balance < -1){
            if(temperature <= v->left_son->temperature){
                rightRotation(v);
                break;
            }else if(temperature > v->left_son->temperature){
                leftRotation(v->left_son);
                rightRotation(v);
                break;
            }
        }else continue;
    }
}


void AVL_Tree::fixNodesHeight(Node *v){
    Node *scan_left = v->left_son;
    Node *scan_right = v->right_son;

    if(scan_left->left_son!=nullptr && scan_left->right_son!=nullptr){
        fixNodesHeight(scan_left);
    }else{
        scan_left->height = 1;
        scan_right->height = 1;
        int height = 2;
        while(scan_left!=v){
            scan_left = scan_left->father;
            scan_left->height = height;
            height++;
        }
    }

    if(scan_right->left_son!=nullptr && scan_right->right_son!=nullptr){
        fixNodesHeight(scan_right);
    }else{
        scan_left->height = 1;
        scan_right->height = 1;
        int height = 2;
        while(scan_right!=v){
            scan_right = scan_right->father;
            scan_right->height = height;
            height++;
        }
    }

    if(v->left_son->height > v->right_son->height)
        v->height = v->left_son->height + 1;
    else if(v->left_son->height < v->right_son->height)
        v->height = v->right_son->height + 1;
    else if(v->left_son->height == v->right_son->height)
        v->height = v->left_son->height + 1;

    Node *scan = v;
    int height = v->height + 1;
    while(scan!=root){
        scan = scan->father;
        scan->height = height;
        height++;
    }
}


Node* AVL_Tree::findMin(){
    Node *v = this->root;

    while(v->left_son!=nullptr)
        v = v->left_son;

    return v;
}


Node* AVL_Tree::findMax(){
    Node *v = this->root;

    while(v->right_son!=nullptr)
        v = v->right_son;

    return v;
}


void AVL_Tree::displayMenu(){
    int option;

    cout << endl << "-------------------------------------------" << endl;
    cout << "1. Show dates with the lowest temperature" << endl;
    cout << "2. Show dates with the highest temperature" << endl;
    cout << "3. Exit" << endl;
    cout << "-------------------------------------------" << endl;

    cin >> option;

    switch(option){
        case 1:
            {
                Node *v = findMin();
                cout << "\nDate: " << v->date << endl;
                cout << "Temperature: " << v->temperature << endl;
                displayMenu();
                break;
            }
        case 2:
            {
                Node *v = findMax();
                cout << "\nDate: " << v->date << endl;
                cout << "Temperature: " << v->temperature << endl;
                displayMenu();
                break;
            }
        case 3:
            exit(0);
            break;
        default:
            cout << endl << "You inserted invalid option" << endl;
            displayMenu();
    }
}


int main(){

     ifstream fin("ocean.csv");
     AVL_Tree tree;
     tree.Insert(fin);
     tree.displayMenu();

}
