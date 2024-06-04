#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>
#define N 1405

using namespace std;

class Data{

    public:
        string date;
        float temperature;
        float phosphate;
};


void read_data(ifstream &fin, Data *table){
    string temp_string, temperature, phosphate;
    int i = 0;

    if(fin.is_open()){
        getline(fin, temp_string);
        while(getline(fin, temp_string)){
            stringstream row(temp_string);
            getline(row, table[i].date, ',');
            getline(row, temperature, ',');
            table[i].temperature = stof(temperature);
            getline(row, phosphate, ',');
            table[i].phosphate = stof(phosphate);
            i++;
        }
    }else{
        cout << "Error in reading file";
        exit(0);
    }
}


char compare_dates(string date1, string date2){
    string month, day, year;
    stringstream data1(date1);
    getline(data1, month, '/');
    getline(data1, day, '/');
    getline(data1, year, '/');
    int month1 = stoi(month);
    int day1 = stoi(day);
    int year1 = stoi(year);

    stringstream data2(date2);
    getline(data2, month, '/');
    getline(data2, day, '/');
    getline(data2, year, '/');
    int month2 = stoi(month);
    int day2 = stoi(day);
    int year2 = stoi(year);

    if(year1 > year2)
        return '>';
    else if(year1 < year2)
        return '<';
    else if(year1 == year2)
        if(month1 > month2)
            return '>';
        else if(month1 < month2)
            return '<';
        else if(month1 == month2)
            if(day1 > day2)
                return '>';
            else if(day1 < day2)
                return '<';
            else if(day1 == day2)
                return '=';
}


int find_next(Data *table, string requested_date, int left, int right){
    string day, month, year;

    stringstream data(requested_date);
    getline(data, month, '/');
    getline(data, day, '/');
    getline(data, year, '/');
    int x_month = stoi(month);
    int x_day = stoi(day);
    int x_year = stoi(year);

    stringstream date1(table[left].date);
    getline(date1, month, '/');
    getline(date1, day, '/');
    getline(date1, year, '/');
    int left_month = stoi(month);
    int left_day = stoi(day);
    int left_year = stoi(year);

    stringstream date2(table[right].date);
    getline(date2, month, '/');
    getline(date2, day, '/');
    getline(date2, year, '/');
    int right_month = stoi(month);
    int right_day = stoi(day);
    int right_year = stoi(year);

    if(right_year == left_year){
        if(right_month != left_month){
            int next = ((x_month-left_month)*(right-left)/(right_month-left_month)) + left;
            return next;
        }else{
            int next = ((x_day-left_day)*(right-left)/(right_day-left_day)) + left;
            return next;
        }
    }else{
        int next = ((x_year-left_year)*(right-left)/(right_year-left_year)) + left;
        return next;
    }

}


void Quick_Sort(Data *table, int left, int right){

    int i = left;
    int j = right;
    string pivot = table[i].date;
    i++;

    while(i <= j){
        if(compare_dates(table[i].date, pivot)=='>' && compare_dates(table[j].date, pivot)!='>'){
            Data temp = table[i];
            table[i] = table[j];
            table[j] = temp;
            i++;
            j--;
        }else if(compare_dates(table[i].date, pivot)=='>' && compare_dates(table[j].date, pivot)=='>'){
            j--;
        }else if(compare_dates(table[i].date, pivot)!='>' && compare_dates(table[j].date, pivot)!='>'){
            i++;
        }else if(compare_dates(table[i].date, pivot)!='>' && compare_dates(table[j].date, pivot)=='>'){
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


void Binary_Search(Data *table, string requested_date, int first, int last){
    int mid = (first+last)/2;
    bool found = false;

    if(mid+1!=last && mid-1!=first && !found){
        if(compare_dates(table[mid].date, requested_date) == '='){
            cout << "\nDate: " << table[mid].date << endl;
            cout << "Temperature: " << table[mid].temperature << endl;
            cout << "Phosphate: " << table[mid].phosphate << endl;
            found = true;
        }else if(compare_dates(table[mid].date, requested_date) == '<'){
            return Binary_Search(table, requested_date, mid-1, last);
        }else if(compare_dates(table[mid].date, requested_date) == '>'){
            return Binary_Search(table, requested_date, first, mid+1);
        }
    }

    if(!found)
        cout << endl << "Requested element not found" << endl;
}


void BIS(Data *table, string requested_date, int left, int right){
    int next = find_next(table, requested_date, left, right);
    bool found = false;

    if(compare_dates(requested_date, table[left].date)=='<' || compare_dates(requested_date, table[right].date)=='>')
        cout << endl << "Requested element not found" << endl;

    while(compare_dates(requested_date, table[left].date)!='<' && compare_dates(requested_date, table[right].date)!='>' && !found){
        int table_size = right - left + 1;    

        if(table_size <= 5){                                               
            for(int i=left; i<=right; i++){                                 
                if(compare_dates(requested_date, table[i].date) == '='){   
                    cout << "\nDate: " << table[i].date << endl;           
                    cout << "Temperature: " << table[i].temperature << endl;
                    cout << "Phosphate: " << table[i].phosphate << endl;
                    found = true;
                }
            }
            if(!found)                                                 
                cout << endl << "Requested element not found" << endl; 
            break;                                                     
        }

        int i=1;
        if(compare_dates(requested_date, table[next].date) == '='){     
            cout << "\nDate: " << table[next].date << endl;            
            cout << "Temperature: " << table[next].temperature << endl;
            cout << "Phosphate: " << table[next].phosphate << endl;
            found = true;
        }else if(compare_dates(requested_date, table[next].date) == '>'){ 
            while(compare_dates(requested_date, table[next + i*int(sqrt(table_size))].date) == '>') 
                i++;                                                                               
            left = next + (i-1)*int(sqrt(table_size)); 
            right  = next + i*int(sqrt(table_size));
        }else if(compare_dates(requested_date, table[next].date) == '<'){ 
            while(compare_dates(requested_date, table[next - i*int(sqrt(table_size))].date) == '<') 
                i++;                                                                               
            left = next - i*int(sqrt(table_size));   
            right = next - (i-1)*int(sqrt(table_size));
        }
        next = find_next(table, requested_date, left, right); 
    }

}


void BIS_Optimized(Data *table, string requested_date, int left, int right){
    int next = find_next(table, requested_date, left, right); 
    bool found = false;

    if(compare_dates(requested_date, table[left].date)=='<' || compare_dates(requested_date, table[right].date)=='>') 
        cout << endl << "Requested element not found" << endl;                                                       

    while(compare_dates(requested_date, table[left].date)!='<' && compare_dates(requested_date, table[right].date)!='>' && !found){
        int table_size = right - left + 1;  

        int i=1;
        if(compare_dates(requested_date, table[next].date) == '='){    
            cout << "\nDate: " << table[next].date << endl;            
            cout << "Temperature: " << table[next].temperature << endl;
            cout << "Phosphate: " << table[next].phosphate << endl;
            found = true;
        }else if(compare_dates(requested_date, table[next].date) == '>'){ 
            while(compare_dates(requested_date, table[next + i*int(sqrt(table_size))].date) == '>') 
                i = 2*i;                                                                            
            left = next + (i/2)*int(sqrt(table_size)); 
            right  = next + i*int(sqrt(table_size));
            return Binary_Search(table, requested_date, left, right); 
        }else if(compare_dates(requested_date, table[next].date) == '<'){ 
            while(compare_dates(requested_date, table[next - i*int(sqrt(table_size))].date) == '<') 
                i = 2*i;                                                                            
            left = next - i*int(sqrt(table_size));    
            right = next - (i/2)*int(sqrt(table_size));
            return Binary_Search(table, requested_date, left, right);
        }
    }
}


int main(){

    ifstream fin("ocean.csv");
    Data *table = new Data[N];
    read_data(fin, table);

    string input, month, day, year;
    int m, d, y;
    cout << "Insert date(MM/DD/YYYY): " ;
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
        exit(0);
    }


    Quick_Sort(table, 0, N-1);
    clock_t start, end;

    start = clock();
    BIS_Optimized(table, input, 0, N-1);
    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "\nClock ticks: " << double(end - start) << endl;
    cout << "CLOCKS PER SEC: " << double(CLOCKS_PER_SEC) << endl;
    cout << "Time taken for searching: " << fixed << time_taken << setprecision(6) << " sec" << endl;

}
