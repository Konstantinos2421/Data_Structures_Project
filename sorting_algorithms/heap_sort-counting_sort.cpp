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
    Data *heap = new Data[length+1];  //Creation of new dynamic table which is used as a heap

    //Table elements are imported into the heap and after each import the heap structure is restored
    for(int i=1; i<=length; i++){
        heap[i] = table[i-1];  //Each element of the table is inserted at the end of the heap 
        int j = i;
        while(heap[j].phosphate > heap[j/2].phosphate && j > 1){ // If the phosphate value of the father is lower than that of the son, i.e. the element that was just inserted,
            Data temp = heap[j];                                 // then the two elements are swapped. The check is done until the first element is reached.
            heap[j] = heap[j/2];
            heap[j/2] = temp;
            j = j/2;
        }
    }

    return heap;
}


void Heap_Sort(Data *table, int length){I store in each position of the table the
    Data *heap = Heapify_Array(table, length); //The table is converted into heap form
    int heap_length = length;

    for(int i=length-1; i>=0; i--){  //Starting from the end of the table, in each of its cells is stored the
        table[i] = heap[1];          //first element of the heap which is the element with the highest phosphate value
        Data temp = heap[1];         //First and last element of the heap are swapped
        heap[1] = heap[heap_length];
        heap[heap_length] = temp;
        heap_length--;               //The size of the heap is reduced by 1 to extract the element with the highest phosphate value
        
        //The structure of the heap is then restored after the first and last elements have been swaped
        int j = 1;
        while(2*j < heap_length){ //Starting from the root, as long as the father has two children, the following procedure is carried out
            if(heap[j].phosphate < heap[2*j].phosphate || heap[j].phosphate < heap[2*j+1].phosphate){ //If the phosphate value of the father is lower than that of at least one of his two sons the following procedure is performed
                if(heap[2*j].phosphate > heap[2*j+1].phosphate){ //If the phosphate value of the right son is higher than that of the left son
                    Data temp = heap[j];                         //the father is swapped with his right son
                    heap[j] = heap[2*j];
                    heap[2*j] = temp;
                    j = 2*j;            //j is changed to go to the right son
                }else if(heap[2*j].phosphate < heap[2*j+1].phosphate){ //If the phosphate value of the left son is higher than that of the right son
                    Data temp = heap[j];                               //the father is swapped with his left son
                    heap[j] = heap[2*j+1];
                    heap[2*j+1] = temp;
                    j = 2*j + 1;          //j is changed to go to the left son
                }else{                    //Otherwise, if the phosphate values of the right and left sons are equal
                    Data temp = heap[j];  //there is a random switching of the father with his right son
                    heap[j] = heap[2*j];
                    heap[2*j] = temp;
                    j = 2*j;              //j is changed to go to the right son
                }
            }else break; //If the phosphate value of the father is greater than the phosphate values of both his sons then the iteration stops after the heap structure has been restored
        }

        if(2*j == heap_length && heap[j].phosphate < heap[2*j].phosphate){ //I check the case where the father has only one son
            Data temp = heap[j];                                           //If his son has a higher phosphate value then the elements are swapped
            heap[j] = heap[2*j];
            heap[2*j] = temp;
        }
    }
}


void Counting_Sort(Data *table, int length, int wide){
    Data *tableB = new Data[length]; //Creation of an auxiliary tableB in which objects of type Data are stored
    int *tableC = new int[wide+1];   //Creation of an auxiliary tableC in which integers are stored

    for(int i=0; i<wide+1; i++)  //Initializion of all positions of tableC with 0
        tableC[i] = 0;

    for(int i=0; i<length; i++)                //For each element of the table the phosphate value is multiplied by 100 to be converted into an integer
        tableC[int(table[i].phosphate*100)]++; //and the corresponding counter in tableC is incremented by 1

    for(int i=1; i<wide+1; i++)   //In each position of tableC we store the sum of the contents of that position and the
        tableC[i] += tableC[i-1]; //contents of its previous position, starting from position 1 of the table

    for(int i=length-1; i>=0; i--){              //For each element of the table we find its correct insertion position in the sorted tableB as determined
        int index = int(table[i].phosphate*100); //by tableC and copy the element to tableB by decreasing the corresponding counter in tableC by 1
        tableB[tableC[index]-1] = table[i];
        tableC[index]--;
    }

    for(int i=0; i<length; i++) //The sorted data of tableB are stored in the table
        table[i] = tableB[i];
}


//Print data of the table elements in the file "sorted_data.doc"
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
