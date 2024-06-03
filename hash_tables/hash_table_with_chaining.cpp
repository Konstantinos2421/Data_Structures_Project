#include <iostream>
#include <fstream>
#include <sstream>
#define N 1405

using namespace std;

class Node{

    public:
        string date;
        float temperature;
        Node *prev;
        Node *next;


    Node(string date, float temperature){
        this->date = date;
        this->temperature = temperature;
    }

};


class List{

    public:
        Node *head;
        Node *tail;

    List(){
        this->head = nullptr;
        this->tail = nullptr;
    }


    void insertNode(Node *node);

    Node* searchNode(string date);

    bool deleteNode(string date);

};


class HashTableWithChains{

    public:
        int buckets;
        List **lists = new List*[buckets];

    HashTableWithChains(int buckets){
        this->buckets = buckets;
        for(int i=0; i<buckets; i++)
            lists[i] = new List();
    }


    int Hash(string date);

    void Insert(ifstream &fin);

    Node* Search(string date);

    bool Delete(string date);

    void displayMenu();

};


void List::insertNode(Node *new_node){
    if(this->head == nullptr){
        this->head = new_node;
        this->tail = new_node;
        new_node->next = nullptr;
        new_node->prev = nullptr;
    }else{
        tail->next = new_node;
        new_node->prev = tail;
        tail = tail->next;
        new_node->next = nullptr;
    }
}


Node* List::searchNode(string date){
    Node *scan = this->head;
    bool found = false;

    while(scan!=nullptr && !found){
        if(scan->date == date)
            found = true;
        else scan = scan->next;;
    }

    if(found)
        return scan;
    else
        return nullptr;

}


bool List::deleteNode(string date){
    Node *scan = this->head;
    bool deleted = false;

    while(scan!=nullptr && !deleted){
        if(scan->date == date){
            if(scan == this->head){
                scan->next->prev = nullptr;
                this->head = scan->next;
                (*scan).~Node();
            }else if(scan == this->tail){
                scan->prev->next = nullptr;
                this->tail = scan->prev;
                (*scan).~Node();
            }else{
                scan->prev->next = scan->next;
                scan->next->prev = scan->prev;
                (*scan).~Node();
            }
            deleted = true;
        }else scan = scan->next;
    }


    if(deleted)
        return true;
    else
        return false;

}


int HashTableWithChains::Hash(string date){
    int sum = 0;
    for(int i=0; i<date.length(); i++)
        sum += int(date[i]);
    int index = sum % this->buckets;
    return index;
}


void HashTableWithChains::Insert(ifstream &fin){
    string temp_string, date ,temperature;

    if(fin.is_open()){
        getline(fin, temp_string);
        while(getline(fin, temp_string)){
            stringstream row(temp_string);
            getline(row, date, ',');
            getline(row, temperature, ',');
            Node *new_node = new Node(date, stof(temperature));

            int index = Hash(new_node->date);
            lists[index]->insertNode(new_node);
        }
    }else{
        cout << "Error in reading file";
        exit(0);
    }
}


Node* HashTableWithChains::Search(string date){
    int index = Hash(date);
    Node *v = lists[index]->searchNode(date);
    return v;
}


bool HashTableWithChains::Delete(string date){
    int index = Hash(date);
    bool deleted = lists[index]->deleteNode(date);
    return deleted;
}


void HashTableWithChains::displayMenu(){
    int option;

    cout << endl << "---------------------------------" << endl;
    cout << "1. Search temperature for a date" << endl;
    cout << "2. Modify temperature for a date" << endl;
    cout << "3. Delete element" << endl;
    cout << "4. Exit" << endl;
    cout << "---------------------------------" << endl;

    cin >> option;

    switch(option){
        case 1:
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
                if(v != nullptr){
                    cout << endl <<"Date: " << v->date << endl;
                    cout << "Temperature: " << v->temperature << endl;
                }else{
                    cout << endl << "Requested element not found" << endl;
                }
                displayMenu();
                break;
            }

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
                if(v != nullptr){
                    string temperature;
                    cout << endl << "Insert the new temperature: ";
                    cin >> temperature;

                    try{
                        v->temperature = stof(temperature);
                        cout << endl << "Temperature is changed" << endl;
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

                bool deleted = Delete(input);
                if(deleted)
                    cout << endl << "Element was successfully deleted" << endl;
                else
                    cout << endl << "Requested element not found" << endl;

                displayMenu();
                break;
            }

        case 4:
            exit(0);
            break;
        default:
            cout << endl << "You inserted invalid option" << endl;
            displayMenu();
    }
}


int main(){

    ifstream fin("ocean.csv");
    HashTableWithChains hash_table(21);
    hash_table.Insert(fin);
    hash_table.displayMenu();

}
