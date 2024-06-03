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
    Data *heap = new Data[length+1];  //Δημιουργία νέου δυναμικού πίνακα heap ο οποίος χρησιμοποιείται ως σωρός

    //Παρακάτω γίνεται εισαγωγή των στοιχείων του table στον heap και μετά από κάθε εισαγωγή γίνεται αποκατάστση της δομής του σωρού
    for(int i=1; i<=length; i++){
        heap[i] = table[i-1];  //Εισαγωγή κάθε στοιχείου του table στο τέλος του heap 
        int j = i;
        while(heap[j].phosphate > heap[j/2].phosphate && j > 1){ // Αν η τιμή phosphate του πατέρα είναι μικρότερη από αυτή του γιου δηλαδή του στοιχείου που εισαγάγαμε
            Data temp = heap[j];                                 // τότε γίνεται εναλλαγή των δύο στοιχείων. Ο έλεγχος γίνεται μέχρι να φτάσουμε στο πρώτο στοιχείο.
            heap[j] = heap[j/2];
            heap[j/2] = temp;
            j = j/2;
        }
    }

    return heap;
}


void Heap_Sort(Data *table, int length){
    Data *heap = Heapify_Array(table, length); //Φέρνω τον πίνακα table σε μορφή σωρού με χρήση της παραπάνω συνάρτησης
    int heap_length = length;

    for(int i=length-1; i>=0; i--){  //Ξεκινώντας από το τέλος του πίνακα table αποθηκεύω σε κάθε θέση του
        table[i] = heap[1];          //το πρώτο στοιχείο του σωρού το οποίο είναι το στοιχείο με τη μεγαλύτερη τιμή phosphate
        Data temp = heap[1];         //Εναλάσσω το πρώτο με το τελευταίο στοιχείο του σωρού
        heap[1] = heap[heap_length];
        heap[heap_length] = temp;
        heap_length--;               //Μειώνω το μέγεθος του σωρού κατά 1 ώστε να γίνει εξαγωγή του στοιχείου με τη μεγαλύτερη τιμή phosphate
        
        //Στη συνέχεια γίνεται αποκατάσταση της δομής του σωρού μετά την εναλλαγή του πρώτου και του τελευταίου στοιχείου
        int j = 1;
        while(2*j < heap_length){ //Ξεκινώντας από τη ρίζα, όσο ο πατέρας έχει δύο παιδιά εκτελείται η παρακάτω διαδικασία
            if(heap[j].phosphate < heap[2*j].phosphate || heap[j].phosphate < heap[2*j+1].phosphate){ //Αν η τιμή phosphate του πατέρα είναι μικρότερη από αυτή τουλάχιστον ενός από τους δύο γιους του εκτελείται η παρακάτω διαδικασία
                if(heap[2*j].phosphate > heap[2*j+1].phosphate){ //Αν η τιμή phosphate του δεξιού γιου είναι μεγαλύτερη από αυτή του αριστερού γιου
                    Data temp = heap[j];                         //γίνεται εναλλαγή του πατέρα με τον δεξί γιο του
                    heap[j] = heap[2*j];
                    heap[2*j] = temp;
                    j = 2*j;            //Μεταβάλλουμε το j ώστε να μεταβούμε στον δεξί γιο
                }else if(heap[2*j].phosphate < heap[2*j+1].phosphate){ //Αν η τιμή phosphate του αριστερού γιου είναι μεγαλύτερη από αυτή του δεξιού γιου
                    Data temp = heap[j];                               //γίνεται εναλλαγή του πατέρα με τον αριστερό γιο του
                    heap[j] = heap[2*j+1];
                    heap[2*j+1] = temp;
                    j = 2*j + 1;          //Μεταβάλλουμε το j ώστε να μεταβούμε στον αριστερό γιο
                }else{                    //Αλλιώς αν οι τιμές phosphate του δεξιού και του αριστερού γιου είναι ίσες
                    Data temp = heap[j];  //γίνεται τυχαία εναλλαγή του πατέρα με τον δεξί γιο του
                    heap[j] = heap[2*j];
                    heap[2*j] = temp;
                    j = 2*j;              //Μεταβάλλουμε το j ώστε να μεταβούμε στον δεξί γιο
                }
            }else break; //Αν η τιμή phosphate του πατέρα είναι μεγαλύτερη από τις τιμές phosphate και των δύο γιων του τότε σταματάει η επανάληψη αφού έχει αποκατασταθεί η δομή του σωρού
        }

        if(2*j == heap_length && heap[j].phosphate < heap[2*j].phosphate){ //Ελέγχω την περίπτωση που ο πατέρας έχει μόνο έναν γιο. Αν ο γιος του έχει μεγαλύτερη τιμή phosphate
            Data temp = heap[j];                                           //τότε γίνεται εναλλαγή των στοιχείων
            heap[j] = heap[2*j];
            heap[2*j] = temp;
        }
    }
}


void Counting_Sort(Data *table, int length, int wide){
    Data *tableB = new Data[length]; //Δημιουργία βοηθητικού πίνακα tableB στον οποίο αποθηκεύονται αντικείμενα τύπου Data 
    int *tableC = new int[wide+1];   //Δημιουργία βοηθητικού πίνακα tableC στον οποίο αποθηκεύονται ακέραιοι

    for(int i=0; i<wide+1; i++)  //Αρχικοποίηση όλων των θέσεων του πίνακα tableC με 0
        tableC[i] = 0;

    for(int i=0; i<length; i++)                //Για κάθε στοιχείο του πίνακα table πολλαπλασιάζουμε την τιμή phosphate με 100 για να μετατραπεί σε ακέραιο
        tableC[int(table[i].phosphate*100)]++; //και αυξάνουμε κατά 1 τον αντίστοιχο μετρητή στον πίνακα tableC

    for(int i=1; i<wide+1; i++)   //Σε κάθε θέση του πίνακα tableC αποθηκεύουμε το άθροισμα του περιεχομένου
        tableC[i] += tableC[i-1]; //της συγκεκριμένης θέσης και του περιεχομένου της προηγούμενής της ξεκινώντας από τη θέση 1 του πίνακα

    for(int i=length-1; i>=0; i--){              //Για κάθε στοιχείο του table
        int index = int(table[i].phosphate*100); //βρίσκουμε τη σωστή θέση εισαγωγής του στον ταξινομημένο πίνακα tableB όπως προσδιορίζεται από τον πίνακα tableC
        tableB[tableC[index]-1] = table[i];      //και αντιγράφουμε το στοιχείο στον πίνακα tableB
        tableC[index]--;                         //μειώνοντας τον αντίστοιχο μετρητή στον tableC κατά 1
    }

    for(int i=0; i<length; i++) //Αποθηκεύω τα ταξινομημένα στοιχεία του πίνακα tableB στον πίνακα table
        table[i] = tableB[i];
}


void display_data(Data *table, int length){  //Εκτύπωση των δεδομένων των στοιχείων του πίνακα table στο αρχείο "sorted_data.doc"
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
