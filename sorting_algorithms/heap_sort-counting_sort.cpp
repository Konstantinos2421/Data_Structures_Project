#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#define N 1405

using namespace std;

class Data{

    public:
        string date;
        float phosphate;
};


void read_data(ifstream &fin, Data *table){
    string temp_string, phosphate;
    int i = 0;

    if(fin.is_open()){
        getline(fin, temp_string);
        while(getline(fin, temp_string)){
            stringstream row(temp_string);
            getline(row, table[i].date, ',');
            getline(row, phosphate, ',');
            getline(row, phosphate, ',');
            table[i].phosphate = stof(phosphate);
            i++;
        }
    }else{
        cout << "Error in reading file";
        exit(0);
    }
}


Data* Heapify_Array(Data *table, int length){
    Data *heap = new Data[length+1];  

    for(int i=1; i<=length; i++){
        heap[i] = table[i-1]; 
        int j = i;
        while(heap[j].phosphate > heap[j/2].phosphate && j > 1){ 
            Data temp = heap[j];                                
            heap[j] = heap[j/2];
            heap[j/2] = temp;
            j = j/2;
        }
    }

    return heap;
}


void Heap_Sort(Data *table, int length){I store in each position of the table the
    Data *heap = Heapify_Array(table, length); 
    int heap_length = length;

    for(int i=length-1; i>=0; i--){ 
        table[i] = heap[1];         
        Data temp = heap[1];        
        heap[1] = heap[heap_length];
        heap[heap_length] = temp;
        heap_length--;             
        
        int j = 1;
        while(2*j < heap_length){ 
            if(heap[j].phosphate < heap[2*j].phosphate || heap[j].phosphate < heap[2*j+1].phosphate){
                if(heap[2*j].phosphate > heap[2*j+1].phosphate){ 
                    Data temp = heap[j];                      
                    heap[j] = heap[2*j];
                    heap[2*j] = temp;
                    j = 2*j;         
                }else if(heap[2*j].phosphate < heap[2*j+1].phosphate){ 
                    Data temp = heap[j];                            
                    heap[j] = heap[2*j+1];
                    heap[2*j+1] = temp;
                    j = 2*j + 1;         
                }else{                   
                    Data temp = heap[j]; 
                    heap[j] = heap[2*j];
                    heap[2*j] = temp;
                    j = 2*j;
                }
            }else break;
        }

        if(2*j == heap_length && heap[j].phosphate < heap[2*j].phosphate){ 
            Data temp = heap[j];                                           
            heap[j] = heap[2*j];
            heap[2*j] = temp;
        }
    }
}


void Counting_Sort(Data *table, int length, int wide){
    Data *tableB = new Data[length]; 
    int *tableC = new int[wide+1];  

    for(int i=0; i<wide+1; i++)
        tableC[i] = 0;

    for(int i=0; i<length; i++)                
        tableC[int(table[i].phosphate*100)]++;

    for(int i=1; i<wide+1; i++)   
        tableC[i] += tableC[i-1]; 

    for(int i=length-1; i>=0; i--){            
        int index = int(table[i].phosphate*100);
        tableB[tableC[index]-1] = table[i];
        tableC[index]--;
    }

    for(int i=0; i<length; i++)
        table[i] = tableB[i];
}


void display_data(Data *table, int length){ 
    ofstream fout("sorted_data.doc");

    fout << "Date\t\t\tPhosphate" << endl;
    fout << "-----------------------------" << endl;
    for(int i=0; i<length; i++){
        fout << table[i].date << "\t\t   " << table[i].phosphate << endl;
        fout << "-----------------------------" << endl;
    }
}


int main(){

    ifstream fin("ocean.csv");
    Data *table = new Data[N];
    read_data(fin, table);
    clock_t start, end;

    start = clock();
    Heap_Sort(table, N);
    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Clock ticks: " << double(end - start) << endl;
    cout << "CLOCKS PER SEC: " << double(CLOCKS_PER_SEC) << endl;
    cout << "Time taken for sorting: " << fixed << time_taken << setprecision(6) << " sec" << endl;

    display_data(table, N);

}
