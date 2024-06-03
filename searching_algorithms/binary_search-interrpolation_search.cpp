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
    stringstream data1(date1);  //Μετατροπή της χρονιάς, του μήνα και της μέρας της ημερομηνίας date1 σε ακέραιους
    getline(data1, month, '/');
    getline(data1, day, '/');
    getline(data1, year, '/');
    int month1 = stoi(month);
    int day1 = stoi(day);
    int year1 = stoi(year);

    stringstream data2(date2);  //Μετατροπή της χρονιάς, του μήνα και της μέρας της ημερομηνίας date2 σε ακέραιους
    getline(data2, month, '/');
    getline(data2, day, '/');
    getline(data2, year, '/');
    int month2 = stoi(month);
    int day2 = stoi(day);
    int year2 = stoi(year);

    if(year1 > year2)           //Εύρεση αν η date1 είναι μικρότερη, μεγαλύτερη ή ίση με τη date2
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

    stringstream data(requested_date); //Μετατροπή της χρονιάς, του μήνα και της ημέρας της ημερομηνίας requested_date σε ακέραιους
    getline(data, month, '/');
    getline(data, day, '/');
    getline(data, year, '/');
    int x_month = stoi(month);
    int x_day = stoi(day);
    int x_year = stoi(year);

    stringstream date1(table[left].date); //Μετατροπή της χρονιάς, του μήνα και της ημέρας της ημερομηνίας του στοιχείου left του πίνακα table σε ακέραιους
    getline(date1, month, '/');
    getline(date1, day, '/');
    getline(date1, year, '/');
    int left_month = stoi(month);
    int left_day = stoi(day);
    int left_year = stoi(year);

    stringstream date2(table[right].date); //Μετατροπή της χρονιάς, του μήνα και της ημέρας της ημερομηνίας του στοιχείου right του πίνακα table σε ακέραιους
    getline(date2, month, '/');
    getline(date2, day, '/');
    getline(date2, year, '/');
    int right_month = stoi(month);
    int right_day = stoi(day);
    int right_year = stoi(year);

    if(right_year == left_year){  
        if(right_month != left_month){                                                      //Αν η χρονιά των δύο ημερομηνιών των στοιχείων left και right του πίνακα table είναι ίδιες
            int next = ((x_month-left_month)*(right-left)/(right_month-left_month)) + left; //υπολογισμός του βήματος παρεμβολής με βάση τον μήνα των δύο ημερομηνιών
            return next;
        }else{                                                                      //Αν η χρονιά και ο μήνας των δύο ημερομηνιών των στοιχείων left και right του πίνακα table είναι ίδιες
            int next = ((x_day-left_day)*(right-left)/(right_day-left_day)) + left; //υπολογισμός του βήματος παρεμβολής με βάση την ημέρα των δύο ημερομηνιών
            return next;
        }
    }else{                                                                          //Αν η χρονιά των δύο ημερομηνιών των στοιχείων left και right του πίνακα table είναι διαφορετικές
        int next = ((x_year-left_year)*(right-left)/(right_year-left_year)) + left; //υπολογισμός του βήματος παρεμβολής με βάση τη χρονιά των δύο ημερομηνιών
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
    int mid = (first+last)/2;   //Υπολογισμός του μεσαίου στοιχείου του πίνακα table
    bool found = false;

    if(last>=first && !found){
        if(compare_dates(table[mid].date, requested_date) == '='){     //Αν η ημερομηνία του μεσαίου στοιχείου είναι ίση με αυτή που ψάχνουμε 
            cout << "\nDate: " << table[mid].date << endl;             //εκτυπώνονται τα δεδομένα του μεσαίου στοιχείου και η συνάρτηση τερματίζεται αφού γίνεται found=true.
            cout << "Temperature: " << table[mid].temperature << endl;
            cout << "Phosphate: " << table[mid].phosphate << endl;
            found = true;
        }else if(compare_dates(table[mid].date, requested_date) == '<'){ //Αν η ημερομηνία του μεσαίου στοιχείου είναι μικρότερη από αυτή που ψάχνουμε
            return Binary_Search(table, requested_date, mid+1, last);    //η συνάρτηση καλείται αναδρομικά για το δεύτερο μισό του πίνακα
        }else if(compare_dates(table[mid].date, requested_date) == '>'){ //Αν η ημερομηνία του μεσαίου στοιχείου είναι μεγαλύτερη από αυτή που ψάχνουμε
            return Binary_Search(table, requested_date, first, mid-1);   //η συνάρτηση καλείται αναδρομικά για το πρώτο μισό του πίνακα
        }
    }

    if(!found)                                                 //Αν το στοιχείο που ψάχνουμε δεν βρεθεί και στην τελευταία αναδρομική κλήση 
        cout << endl << "Requested element not found" << endl; //εκτυπώνεται το αντίστοιχο μήνυμα
}


void Interpolation_Search(Data *table, string requested_date, int left, int right){
    bool found = false;
    int next = find_next(table, requested_date, left, right);  //Υπολογισμός βήματος παρεμβολής

    if(compare_dates(requested_date, table[left].date)!='<' && compare_dates(requested_date, table[right].date)!='>' && !found){
        if(compare_dates(requested_date, table[next].date) == '='){     //Αν η ημερομηνία που ψάχνουμε είναι ίδια με αυτή του στοιχείου που υπολογίστηκε από το βήμα παρεμβολής
            cout << "\nDate: " << table[next].date << endl;             //εκτυπώνουμε τα δεδομένα του συγκεκριμένου στοιχείου και η συνάρτηση τερματίζεται αφού γίνεται found=true
            cout << "Temperature: " << table[next].temperature << endl;
            cout << "Phosphate: " << table[next].phosphate << endl;
            found = true;
        }else if(compare_dates(requested_date, table[next].date) == '>'){      //Αν η ημερομηνία που ψάχνουμε είναι μεγαλύτερη από αυτή του στοιχείου που υπολογίστηκε από το βήμα παρεμβολής
            return Interpolation_Search(table, requested_date, next+1, right); //καλούμε αναδρομικά τη συνάρτηση για το διάστημα [next+1, right]
        }else if(compare_dates(requested_date, table[next].date) == '<'){      //Αν η ημερομηνία που ψάχνουμε είναι μικρότερη από αυτή του στοιχείου που υπολογίστηκε από το βήμα παρεμβολής
            return Interpolation_Search(table, requested_date, left, next-1);  //καλούμε αναδρομικά τη συνάρτηση για το διάστημα [left, next-1]
        }
    }

    if(!found)                                                 //Αν το στοιχείο που ψάχνουμε δεν βρεθεί και στην τελευταία αναδρομική κλήση 
        cout << endl << "Requested element not found" << endl; //εκτυπώνεται το αντίστοιχο μήνυμα
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
    Binary_Search(table, input, 0, N-1);
    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "\nClock ticks: " << double(end - start) << endl;
    cout << "CLOCKS PER SEC: " << double(CLOCKS_PER_SEC) << endl;
    cout << "Time taken for searching: " << fixed << time_taken << setprecision(6) << " sec" << endl;

}
