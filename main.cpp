#include "headers /headers.h"

/*
 * Pre-Processor Directive to Identify a windows operating environment.
 * This is important because a check for carriage returns relies on it.
 */
#ifdef _WIN32
    #define WIN 1
#else
    #define WIN 0
#endif

//C++ Trick, I don't want to type std:: before everything.
using namespace std;

/**
 * Creates, and allocates memory for a new struct student.
 *
 * @param record The String which is parsed from the text file.
 * @param line The Current Line Number that was parsed.
 * @return A pointer to the space in memory for this instance of student.
 */
struct student* createStudent(const string& record,int line) {
    stringstream ss(record);
    auto* st = (student*) malloc(sizeof(struct student));
    string name,number,email,credits,gpa;
    getline(ss,name,',');
    getline(ss,number,',');
    getline(ss,email,',');
    getline(ss,credits,',');
    getline(ss,gpa,',');

    //When we get to here, we know that our record format is valid.
    st->name=name;
    st->number=number;
    st->email=email;
    st->credits=stoi(credits);
    st->gpa=stod(gpa);
    st->parsedAtLine=line;
    return st;
}

/**
 * Process the search file, and execute pre-checks for each record.
 * @param hashTable Table to place values into.
 * @param fileName Name of the file to parse.
 */
void processInputFile(struct student hashTable[], string fileName) {
    cout << endl << endl;

    ifstream iss(fileName);
    string s;
    int lineNum=0;

    cout << setw(28) << std::left << "Placed At: " << std::left << setw(30) << "Action: " << endl
    << setw(28) << "-------------------------" << setw(50) << "------------------------------------------" << endl;
    while(getline(iss,s)){
        lineNum++;

        //Test Record for Carriage Returns if running on Unix.
        if(!WIN && s.find('\r')!=string::npos) { displayError(carriageReturn,"",lineNum); exit(1); }

        //Check Record Validity and Format, then construct student. If record is not valid, then skip and continue.
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

/**
 * Entry Point for the Program. Expects at a Minimum 2 arguments.
 *
 * Minimum Expectations: ./P1 ../data.txt
 *
 * @param argc Argument Count
 * @param argv Array of Arguments to use.
 * @return exit code
 */
int main(int argc, char* argv[]) {

    if(argc<2) { displayError(missingArgs,"No File Provided",-1); }

    cout << "Using Data From File: "+string(argv[1]) << endl;

    //calloc the array here instead of initializing to NULL.
    auto* table = (student*) calloc(TABLE_SIZE,sizeof(struct student));
    processInputFile(table,argv[1]);

    if(argc>2) {
        cout << endl << "Using Search File: "+string(argv[2]) << endl;
        processSearchFile(table,argv[2]);
    }
    return 0;
}