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

    for(int i=left+1; i<=right; i++){ //i είναι μετρητής ο οποίος σε κάθε επανάληψη προσδιορίζει το στοιχείο προς ταξινόμηση
        for(int j=left; j<i; j++){    //j είναι μετρητής ο οποίος προσδιορίζει τη θέση εισαγωγής του στοιχείου i στο ταξινομημένο κομμάτι του πίνακα
            if(table[i].temperature < table[j].temperature){ //Αν η θερμοκρασία του στοιχείου στη θέση j είναι μεγαλύτερη από αυτή του στοιχείου στη θέση i
                Data temp = table[i];                        //το στοιχείο που βρίσκεται στη θέση i αποθηκεύεται στη μεταβλητή temp
                for(int k=i-1; k>=j; k--)                    
                    table[k+1] = table[k];                   //όλα τα στοιχεία από τη θέση i-1 μέχρι τη θέση j μετατοπίζονται μία θέση δεξιά
                table[j] = temp;                             //και το temp εισάγεται στη θέση j
            }else                                            //Σε κάθε άλλη περίπτωση εκτελείται η ίδια διαδικασία αυξάνοντας κάθε φορά το j κατά 1
                continue;                                    //μέχρι να βρεθεί η σωστή θέση εισαγωγής του στοιχείου i στον ταξινομημένο πίνακα
        }
    }
}


void Quick_Sort(Data *table, int left, int right){

    int i = left;
    int j = right;
    float pivot = table[i].temperature;  //Ορισμός της θερμοκρασίας του πρώτου στοιχείου ως στοιχείου διαχωρισμού
    i++;

    while(i <= j){
        if(table[i].temperature>pivot && table[j].temperature<=pivot){  //Αν και τα δύο στοιχεία είναι σε λάθος θέση
            Data temp = table[i];                                       //κάνω swap
            table[i] = table[j];
            table[j] = temp;
            i++;
            j--;
        }else if(table[i].temperature>pivot && table[j].temperature>pivot){ //Αν μόνο το table[i] είναι σε λάθος θέση
            j--;                                                            //μειώνω τον μετρητή j κατά 1
        }else if(table[i].temperature<=pivot && table[j].temperature<=pivot){ //Αν μόνο το table[j] είναι σε λάθος θέση
            i++;                                                              //αυξάνω τον μετρητή i κατά 1
        }else if(table[i].temperature<=pivot && table[j].temperature>pivot){ //Αν και τα δύο στοιχεία είναι στη σωστή θέση
            i++;                                                             //αυξάνω τον μετρητή i κατά 1
            j--;                                                             //και μειώνω τον μετρητή j κατά 1
        }
    }

    Data temp = table[left];  //Εναλλαγή του στοιχείου table[j] με το πρώτο στοιχείο του πίνακα(δηλαδή το στοιχείο διαχωρισμού)
    table[left] = table[j];
    table[j] = temp;

    if(left < j-1)                    //Ελέγχεται αν τα όρια των δύο υποπινάκων αριστερά και δεξιά του στοιχείου διαχωρισμού δεν ξεπερνούν τα όρια του αρχικού πίνακα
        Quick_Sort(table, left, j-1); //και αν ισχύουν οι συνθήκες γίνεται αναδρομική εκτέλεση της συνάρτησης για τους δύο υποπίνακες
    if(right > j+1)
        Quick_Sort(table, j+1, right);

}


void display_data(Data *table, int length){  //Εκτύπωση των δεδομένων των στοιχείων του πίνακα table στο αρχείο "sorted_data.doc"
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
