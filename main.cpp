#include "headers /headers.h"

#ifdef _WIN32
    #define WIN 1
#else
    #define WIN 0
#endif

using namespace std;

struct student* createStudent(const string& record,int line) {
    stringstream ss(record);
    auto* st = (student*) malloc(sizeof(struct student));
    string name,number,email,credits,gpa;
    getline(ss,name,',');
    getline(ss,number,',');
    getline(ss,email,',');
    getline(ss,credits,',');
    getline(ss,gpa,',');

    //When we get to here, we know that our Record is valid.
    st->name=name;
    st->number=number;
    st->email=email;
    st->credits=stoi(credits);
    st->gpa=stod(gpa);
    st->parsedAtLine=line;
    return st;
}

void processInputFile(struct student hashTable[], string filename) {
    cout << endl << endl;

    ifstream iss(filename);
    string s;
    int lineNum=0;

    cout << setw(28) << std::left << "Placed At: " << std::left << setw(30) << "Action: " << endl
    << setw(28) << "-------------------------" << setw(50) << "------------------------------------------" << endl;
    while(getline(iss,s)){
        lineNum++;

        //Test Record for Carriage Returns if running on Unix.
        if(!WIN && s.find('\r')!=string::npos) { displayError(carriageReturn,"",lineNum); exit(0); }
        if(s.size()>=3 && s.size()<35) { displayError(shortRecord,s,lineNum); continue; }
        if(s.empty()) { displayError(blankRecord,"",lineNum); continue; }
        if(std::count(s.begin(),s.end(),',')!=4) { displayError(corruptRecord,s,lineNum); continue; }

        student* st = createStudent(s,lineNum);
        if (testStudentData(hashTable,*st)) {
            insertStudent(hashTable, st);
        } else { continue; }
    }
    displayHashTable(hashTable);
    cout << "-----------------------------------------------------------------------" << endl;
}
void processSearchFile(struct student hashTable[], string filename) {
    cout << endl << "Do Search Stuff Here" << endl;
}

int main(int argc, char* argv[]) {

    if(argc<2) { displayError(missingArgs,"No File Provided",-1); }

    cout << "Using Data From File: "+string(argv[1]) << endl;
    auto* table = (student*) calloc(TABLE_SIZE,sizeof(struct student));
    processInputFile(table,argv[1]);

    if(argc>2) {
        cout << endl << "Using Search File: "+string(argv[2]) << endl;
        processSearchFile(table,argv[2]);
    }
    return 0;
}