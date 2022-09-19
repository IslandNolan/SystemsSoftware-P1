#include "headers /headers.h"

/*
 * Pre-Processor Directive to Identify a Windows operating environment.
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
void processInputFile(struct student hashTable[], const string& fileName) {
    cout << endl << endl;

    ifstream ifs(fileName);
    if(!ifs.is_open()) { displayError(fileNotFound,fileName,stoi("0")); exit(1); }
    cout << "Using Data From File: "+string(fileName) << endl;
    string s;
    int lineNum=0;

    cout << setw(28) << std::left << "Result/Location: " << std::left << setw(30) << "Description: " << endl
    << setw(28) << "-------------------------" << setw(50) << "------------------------------------------" << endl;
    while(getline(ifs,s)){
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

void processSearchFile(struct student hashTable[], string fileName) {
    std::cout << std::endl;
    ifstream ifs(fileName);
    if(!ifs.is_open()) { displayError(fileNotFound,fileName,stoi("0")); exit(1); }
    string currentLine;
    int lineNum=0;
    std::cout << "Processing Search File: " + fileName << std::endl;
    while(getline(ifs,currentLine)){
        if(!WIN && currentLine.find('\r')!=string::npos) { cout<<"Could not read file, Line: "+to_string(lineNum)+" contains a Carriage Return Value.. "<< endl; exit(1); }
        performSearch(hashTable,currentLine);
        lineNum++;
    }

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

    if(argc<2) { displayError(missingArgs,"No File Provided",-1); exit(0); }

    auto* table = (student*) calloc(TABLE_SIZE,sizeof(struct student));
    processInputFile(table,argv[1]);

    if(argc>2) {
        processSearchFile(table,argv[2]);
    }
    return 0;
}