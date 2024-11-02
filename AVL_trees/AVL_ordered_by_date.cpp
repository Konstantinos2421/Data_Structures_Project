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


    Node* Search(string date);

    void Delete(string date);

    void Insert(ifstream &fin);

    void displayTreeData(Node *v);

    void leftRotation(Node *v);

    void rightRotation(Node *v);

    void balanceTree(Node *v);

    void fixNodesHeight(Node *v);

    void displayMenu();

};


char compare_dates(string date1, string date2){
    string month, day, year;
    stringstream data1(date1);
    getline(data1, month, '/');
    getline(data1, day, '/');
    getline(data1, year, '/');
    int m1 = stoi(month);
    int d1 = stoi(day);
    int y1 = stoi(year);

    stringstream data2(date2);
    getline(data2, month, '/');
    getline(data2, day, '/');
    getline(data2, year, '/');
    int m2 = stoi(month);
    int d2 = stoi(day);
    int y2 = stoi(year);

    if(y1 > y2)
        return '>';
    else if(y1 < y2)
        return '<';
    else if(y1 == y2)
        if(m1 > m2)
            return '>';
        else if(m1 < m2)
            return '<';
        else if(m1 == m2)
            if(d1 > d2)
                return '>';
            else if(d1 < d2)
                return '<';
            else if(d1 == d2)
                return '=';
}


Node* AVL_Tree::Search(string date){
    Node *v = root;

    while(v->left_son!=nullptr && v->right_son!=nullptr){
        if(compare_dates(date, v->date) != '>')
            v = v->left_son;
        else if(compare_dates(date, v->date) == '>')
            v = v->right_son;
    }
    return v;
}


void AVL_Tree::Delete(string date){
    Node *x = Search(date);

    if(compare_dates(date, x->date) == '='){
        Node *v = x->father;
        Node *y;
        if(x == v->left_son)
            y = v->right_son;
        else if(x == v->right_son)
            y = v->left_son;


        if(v->father->left_son == v)
            v->father->left_son = y;
        else if(v->father->right_son == v)
            v->father->right_son = y;

        y->father = v->father;

        (*x).~Node();
        (*v).~Node();


        if(y->left_son==nullptr && y->right_son==nullptr){
            fixNodesHeight(y->father);
            balanceTree(y);
        }else{
            fixNodesHeight(y);
            balanceTree(y);
        }
    }
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
                Node *v = Search(date);
                if(compare_dates(date, v->date) != '='){
                    Node *new_node = new Node(date, stof(temperature), nullptr, nullptr, nullptr);
                    if(compare_dates(new_node->date, v->date) == '>'){
                        v->left_son = new Node(v->date, v->temperature, v, nullptr, nullptr);
                        v->right_son = new_node;
                        new_node->father = v;
                        fixNodesHeight(v);
                    }else if(compare_dates(new_node->date, v->date) == '<'){
                        if(v->father->left_son == v){
                            v->father->left_son = new_node;
                        }else if(v->father->right_son == v){
                            v->father->right_son = new_node;
                        }

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


ofstream fout("tree_data.doc");
void AVL_Tree::displayTreeData(Node *v){
    if(v==nullptr)
        return;

    displayTreeData(v->left_son);

    if(v->left_son==nullptr && v->right_son==nullptr){
        fout << "Date: " << v->date << endl;
        fout << "Temperature: " << v->temperature << endl;
        fout << "----------------------" << endl;
    }

    displayTreeData(v->right_son);
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
    string date = v->date;

    while(v!=root){
        v = v->father;
        int balance = v->right_son->height - v->left_son->height;
        if(balance > 1){
            if(compare_dates(date, v->right_son->date) == '>'){
                leftRotation(v);
                break;
            }else if(compare_dates(date, v->right_son->date) != '>'){
                rightRotation(v->right_son);
                leftRotation(v);
                break;
            }
        }else if(balance < -1){
            if(compare_dates(date, v->left_son->date) != '>'){
                rightRotation(v);
                break;
            }else if(compare_dates(date, v->left_son->date) == '>'){
                leftRotation(v->left_son);
                rightRotation(v);
                break;
            }
        }else continue;
    }
}


int recursive_call_number = 0;
void AVL_Tree::fixNodesHeight(Node *v){
    recursive_call_number++;

    if(v==nullptr){
        recursive_call_number--;
        return;
    }

    fixNodesHeight(v->left_son);

    fixNodesHeight(v->right_son);

    if(v->left_son==nullptr && v->right_son==nullptr){
        v->height = 1;
    }else{
        if(v->left_son->height > v->right_son->height)
            v->height = v->left_son->height + 1;
        else if(v->left_son->height < v->right_son->height)
            v->height = v->right_son->height + 1;
        else if(v->left_son->height == v->right_son->height)
            v->height = v->left_son->height + 1;
    }
    recursive_call_number--;

    if(recursive_call_number == 0){
        Node *scan = v->father;
        while(scan!=nullptr){
            if(scan->left_son->height > scan->right_son->height)
                scan->height = scan->left_son->height + 1;
            else if(scan->left_son->height < scan->right_son->height)
                scan->height = scan->right_son->height + 1;
            else if(scan->left_son->height == scan->right_son->height)
                scan->height = scan->left_son->height + 1;

            scan = scan->father;
        }
    }
}


void AVL_Tree::displayMenu(){
    int option;

    cout << endl << "---------------------------------" << endl;
    cout << "1. Display AVL tree" << endl;
    cout << "2. Search temperature for a date" << endl;
    cout << "3. Modify temperature for a date" << endl;
    cout << "4. Delete element" << endl;
    cout << "5. Exit" << endl;
    cout << "---------------------------------" << endl;

    cin >> option;

    switch(option){
        case 1:
            displayTreeData(this->root);
            cout << endl << "Tree data were printed in the file \"tree_data.doc\"" << endl;
            displayMenu();
            break;
        case 2:
            {
                string input, month, day, year;
                int m, d, y;
                cout << endl << "Insert date(MM/DD/YYYY): " ;
                cin >> input;
                stringstream date(input);
                getline(date, month, '/');
                getline(date, day, '/');
                getline(date, year, '/');
                try{
                    m = stoi(month);
                    d = stoi(day);
                    y = stoi(year);
                }catch(std::invalid_argument){
                    cout << endl << "Invalid Date Format" << endl;
                    displayMenu();
                }

                Node *v = Search(input);
                if(compare_dates(input, v->date) == '='){
                    cout << endl <<"Date: " << v->date << endl;
                    cout << "Temperature: " << v->temperature << endl;
                }else{
                    cout << endl << "Requested element not found" << endl;
                }

                displayMenu();
                break;
            }

        case 3:
            {
                string input, month, day, year;
                int m, d, y;
                cout << endl << "Insert date(MM/DD/YYYY): " ;
                cin >> input;
                stringstream date(input);
                getline(date, month, '/');
                getline(date, day, '/');
                getline(date, year, '/');
                try{
                    m = stoi(month);
                    d = stoi(day);
                    y = stoi(year);
                }catch(std::invalid_argument){
                    cout << endl << "Invalid Date Format" << endl;
                    displayMenu();
                }

                Node *v = Search(input);
                if(compare_dates(input, v->date) == '='){
                    string temperature;
                    cout << endl << "Insert the new temperature: ";
                    cin >> temperature;

                    try{
                        v->temperature = stof(temperature);
                        cout << endl << "Temperature is changed";
                    }catch(std::invalid_argument){
                        cout << endl << "You inserted invalid temperature" << endl;
                        displayMenu();
                    }
                }else{
                    cout << endl << "Requested element not found" << endl;
                }

                displayMenu();
                break;
            }

        case 4:
            {
                string input, month, day, year;
                int m, d, y;
                cout << endl << "Insert date(MM/DD/YYYY): " ;
                cin >> input;
                stringstream date(input);
                getline(date, month, '/');
                getline(date, day, '/');
                getline(date, year, '/');
                try{
                    m = stoi(month);
                    d = stoi(day);
                    y = stoi(year);
                }catch(std::invalid_argument){
                    cout << endl << "Invalid Date Format" << endl;
                    displayMenu();
                }

                Node *v = Search(input);
                if(compare_dates(input, v->date) == '='){
                    Delete(input);
                    cout << endl << "Element was successfully deleted" << endl;
                }else{
                    cout << endl << "Requested element not found" << endl;
                }
                displayMenu();
                break;
            }
        case 5:
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
