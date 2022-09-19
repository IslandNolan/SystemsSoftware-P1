#pragma once

/*
 * NOTES: You can input true sizes for string length requirements
 *       in my version of this project. An offset of 1 is no longer
 *       needed because we do not need to account for \r.
 *       The program will refuse to run if a \r is detected.
 *
 */

#define EMAIL_SIZE 17
#define NAME_SIZE_MAX 20
#define NAME_SIZE_MIN 5
#define NUMBER_SIZE 9

#define TABLE_SIZE 35

/**
 * struct student.
 *
 * This struct contains two additional fields
 *   1. parsedAtLine: Which line the record was read from in the file
 *   2. isChained: Is the element linked to another element
 *
 * The rest functions as originally intended.
 */
struct student {
    struct student* next = nullptr;
    std::string name;
    std::string number;
    std::string email;
    int credits;
    double gpa;
    int parsedAtLine;
    bool isChained = false;
};

/** Simple Hash Function- No AES512 today.. :( */
int computerHash(std::string input) {
    int sum=0;
    for(char c : input){ sum+=c; }
    return sum%TABLE_SIZE;
}

/**
 * Prints a Singular Record via a struct pointer to the HashTable.
 * this does not include the 'chained' records, or the records that follow.
 *
 * @param st element that is printed. Does not include chained elements.
 * @param index position in hashtable
 */
void printRecord(struct student st, int index){
    bool emptyRecord = st.name.empty();
    std::cout << std::setw(5) << std::right << ((st.isChained || index==-1) ? "|" : std::to_string(index))
              << "  " << std::setw(20) << std::left << (emptyRecord? "-": st.name)
              << "  " << std::setw(9) << std::left << (emptyRecord? "-": st.number)
              << "  " << std::setw(17) << std::left << (emptyRecord? "-": st.email)
              << "  " << std::setw(7) << std::right << (emptyRecord? "-":std::to_string(st.credits));
    if(emptyRecord){
        std::cout << std::setw(5) << std::right << "-" << std::endl;
    } else{ std::cout << "  " << st.gpa << std::endl; }

}

/**
 * Prints a Singular Record, including all chained values
 *
 * @param index Index of the element we want to display
 * @param st Element that we want to display
 * */
void displayRecord(struct student st, int index) {

    printRecord(st, index);
    struct student* pt = st.next;
    while(pt!=nullptr){
        printRecord(*pt, index);
        pt = pt->next;
    }
}

/**
 * Display the entire HashTable.
 * Lines that begin with ' | ' are chained to the last printed Index Value.
 */
void displayHashTable(struct student hashTable[]) {
    std::cout << "\n"
                 "Index  Name                  Number     Email Address      Credits  GPA\n"
                 "-----  --------------------  ---------  -----------------  -------  ---"
              << std::endl;
    for(int i=0;i<TABLE_SIZE;i++){
        displayRecord(hashTable[i],i);
    }
}

/**
 * Insert a student to the proper hashed index.
 * If the space is already taken by another element,
 * the element will be appended to the end of the already existent element Via a pointer
 */
void insertStudent(struct student hashTable[], struct student* st) {
    int expectedHash = computerHash(st->name), linkNumber=1;
    struct student* pt = &hashTable[expectedHash];

    //If the space is not taken, then insert into the table without a link.
    if(hashTable[expectedHash].name.empty()){
        hashTable[expectedHash]=*st;
        std::cout << std::left << std::setw(28) << "Hash: "+std::to_string(expectedHash)
                  << std::right << std::setw(25) << "Added Student to Table: \"" + st->name + "\""
                  << std::endl;
        return;
    }
    else {
        //If the space is already taken, then append a link to the end of the table index
        while(pt->next!=nullptr) {
            linkNumber++;
            pt = pt->next;
        }
        pt->next=st;
        pt->next->isChained=true;
    }

    /*Prints the action to the HashTable Log in the pattern
      HASH: X, LINK# 1          Added Student to Table: "xx"

      Link Value is 1-indexed.
     */
    std::cout << std::left << std::setw(10) << "Hash: "+std::to_string(expectedHash)
              << std::left << std::setw(18) << ((linkNumber==0) ? "" : "Link #"+std::to_string(linkNumber))
              << std::right << std::setw(31) << "Added Student to Table: \"" + st->name + "\""
              << std::endl;
}


/**
 * Checks the Number for validity.
 * The Record must conform to the length and format requirements set in Canvas.
 *
 * @param st Student to Check
 * @return T/F, Valid/Invalid
 */
bool testNumberFormat(struct student st) {
    if (st.number.size() != NUMBER_SIZE) { displayError(numberLength, st.number, st.parsedAtLine); return false; }
    else if (st.number[0] != 'u' || (st.number.substr(1, st.number.size()).find_first_not_of("0123456789") != std::string::npos)) {
        //This mess checks the first digit for 'u', and all the following digits to see if they are between 0-9. If not, then kick error.
        displayError(numberFormat, st.number, st.parsedAtLine);
        return false;
    }
    else return true;
}


/**
 * Check Student Email for validity.
 * The Record must conform to the length and format requirements set in Canvas.
 *
 * @param st Student to Check
 * @return T/F, Valid/Invalid
 */
bool testEmailFormat(struct student st) {
    if(st.email.size() != EMAIL_SIZE) { displayError(emailLength, st.email, st.parsedAtLine); return false; }
    else if((st.email[0] != 'u') || st.email.substr(st.email.size() - 8, st.email.size()) != "@ufb.edu") { displayError(emailFormat, st.email, st.parsedAtLine); return false; }
    else return true;
}

/**
 * Checks all student data for validity.
 * If this method reutrns false, the student will not be inserted, and the record will be ignored.
 * The Following Chekcs are executed here:
 *  1. Name Length
 *  2. Duplicate Name
 *  3. Number Length+Format
 *  4. Email Length+Format
 *  5. Credits constraint to 0 < credits < 150
 *  6. Gpa constraint to 0 < gpa < 4.0
 *
 * @param hashTable
 * @param st
 * @return
 */
bool testStudentData(struct student hashTable[],struct student st) {

    if(st.name.size() < NAME_SIZE_MIN || st.name.size() > NAME_SIZE_MAX){ displayError(nameLength, st.name, st.parsedAtLine); return false; }

    //Check duplicates
    for(int i=0;i<TABLE_SIZE;i++){
        if(st.name == hashTable[i].name){ displayError(duplicateName, st.name, st.parsedAtLine); return false; }

        struct student* pt = hashTable[i].next;
        while(pt!=nullptr){
            if(st.name == pt->name){ displayError(duplicateName, st.name, st.parsedAtLine); return false; }
            pt = pt->next;
        }
    }

    //Check email, and number formats.
    if(!testNumberFormat(st) || !testEmailFormat(st)) { return false; }

    if(st.credits > 150 || st.credits < 0) { displayError(creditsValue, st.name, st.parsedAtLine); return false; }
    if(st.gpa > 4.0 || st.gpa < 0.0) { displayError(gpaValue, st.name, st.parsedAtLine); return false; }
    return true;
}