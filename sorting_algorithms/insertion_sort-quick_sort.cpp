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
        float temperature;
};


void read_data(ifstream &fin, Data *table){
    string temp_string, temperature;
    int i = 0;

    if(fin.is_open()){
        getline(fin, temp_string);
        while(getline(fin, temp_string)){
            stringstream row(temp_string);
            getline(row, table[i].date, ',');
            getline(row, temperature, ',');
            table[i].temperature = stof(temperature);
            i++;
        }
    }else{
        cout << "Error in reading file";
        exit(0);
    }
}


void Insertion_Sort(Data *table, int left, int right){

    for(int i=left+1; i<=right; i++){ 
        for(int j=left; j<i; j++){  
            if(table[i].temperature < table[j].temperature){ 
                Data temp = table[i];                       
                for(int k=i-1; k>=j; k--)                    
                    table[k+1] = table[k];                   
                table[j] = temp;                             
            }else              
                continue;  
        }
    }
}


void Quick_Sort(Data *table, int left, int right){

    int i = left;
    int j = right;
    float pivot = table[i].temperature;
    i++;

    while(i <= j){
        if(table[i].temperature>pivot && table[j].temperature<=pivot){ 
            Data temp = table[i];                                       
            table[i] = table[j];
            table[j] = temp;
            i++;
            j--;
        }else if(table[i].temperature>pivot && table[j].temperature>pivot){ 
            j--;                                                           
        }else if(table[i].temperature<=pivot && table[j].temperature<=pivot){
            i++;                                                         
        }else if(table[i].temperature<=pivot && table[j].temperature>pivot){
            i++;                                                             
            j--;
        }
    }

    Data temp = table[left];
    table[left] = table[j];
    table[j] = temp;

    if(left < j-1)                    
        Quick_Sort(table, left, j-1);
    if(right > j+1)
        Quick_Sort(table, j+1, right);

}


void display_data(Data *table, int length){  
    ofstream fout("sorted_data.doc");

    fout << "Date\t\t\tTemperature" << endl;
    fout << "-----------------------------" << endl;
    for(int i=0; i<length; i++){
        fout << table[i].date << "\t\t   " << table[i].temperature << endl; 
        fout << "-----------------------------" << endl;
    }
}


int main(){

    ifstream fin("ocean.csv");
    Data *table = new Data[N];
    read_data(fin, table);
    clock_t start, end;

    start = clock();
    Insertion_Sort(table, 0, N-1);
    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Clock ticks: " << double(end - start) << endl;
    cout << "CLOCKS PER SEC: " << double(CLOCKS_PER_SEC) << endl;
    cout << "Time taken for sorting: " << fixed << time_taken << setprecision(6) << " sec" << endl;

    display_data(table, N);

}
