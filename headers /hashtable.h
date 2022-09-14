#pragma once

#define EMAIL_SIZE 17
#define NAME_SIZE_MAX 20
#define NAME_SIZE_MIN 5
#define NUMBER_SIZE 9

#define TABLE_SIZE 35

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

int computerHash(std::string input) {
    int sum=0;
    for(char c : input){
        sum+=c;
    }
    return sum%TABLE_SIZE;
}
void printRecord(struct student temp,int index){

    bool emptyRecord = temp.name.empty();
    std::cout << std::setw(5) << std::right << ((temp.isChained) ? "|" : std::to_string(index))
              << "  " << std::setw(20) << std::left << (emptyRecord? "-":temp.name)
              << "  " << std::setw(9) << std::left << (emptyRecord? "-":temp.number)
              << "  " << std::setw(17) << std::left << (emptyRecord? "-":temp.email)
              << "  " << std::setw(7) << std::right << (emptyRecord? "-":std::to_string(temp.credits));
    if(emptyRecord){
        std::cout << std::setw(5) << std::right << "-" << std::endl;
    } else{ std::cout << "  " << temp.gpa << std::endl; }

}
void displayRecord(struct student temp,int num) {

    printRecord(temp,num);

    struct student* pt = temp.next;
    while(pt!=nullptr){
        printRecord(*pt,num);
        pt = pt->next;
    }

}
void displayHashTable(struct student hashTable[]) {
    std::cout << "\n"
                 "Index  Name                  Number     Email Address      Credits  GPA\n"
                 "-----  --------------------  ---------  -----------------  -------  ---"
              << std::endl;
    for(int i=0;i<TABLE_SIZE;i++){
        displayRecord(hashTable[i],i);
    }
}
void insertStudent(struct student hashTable[], struct student* temp) {
    int expectedHash = computerHash(temp->name), linkNumber=1;
    struct student* pt = &hashTable[expectedHash];
    if(hashTable[expectedHash].name.empty()){
        hashTable[expectedHash]=*temp;
        std::cout << std::left << std::setw(28) << "Hash: "+std::to_string(expectedHash)
                  << std::right << std::setw(25) << "Added Student to Table: \""+temp->name+"\""
                  << std::endl;
        return;
    }
    else {
        while(pt->next!=nullptr) {
            linkNumber++;
            pt = pt->next;
        }
        pt->next=temp;
        temp->isChained=true;
    }
    std::cout << std::left << std::setw(10) << "Hash: "+std::to_string(expectedHash)
              << std::left << std::setw(18) << ((linkNumber==0) ? "" : "Link #:"+std::to_string(linkNumber))
              << std::right << std::setw(31) << "Added Student to Table: \""+temp->name+"\""
              << std::endl;
}
bool testNumberFormat(struct student temp) {
    if (temp.number.size() != NUMBER_SIZE) { displayError(numberLength, temp.number,temp.parsedAtLine); return false; }
    else if (temp.number[0] != 'u' || (temp.number.substr(1, temp.number.size()).find_first_not_of("0123456789") != std::string::npos)) {
        //This mess checks the first digit for 'u', and all the following digits to see if they are between 0-9. If not, then kick error.
        displayError(numberFormat, temp.number,temp.parsedAtLine);
        return false;
    }
    else return true;
}
bool testEmailFormat(struct student temp) {
    if(temp.email.size()!=EMAIL_SIZE) { displayError(emailLength, temp.email,temp.parsedAtLine); return false; }
    else if((temp.email[0]!='u') || temp.email.substr(temp.email.size()-8,temp.email.size())!="@ufb.edu") { displayError(emailFormat,temp.email,temp.parsedAtLine); return false; }
    else return true;
}
bool testStudentData(struct student hashTable[],struct student temp) {
    if(temp.name.size()<NAME_SIZE_MIN || temp.name.size()>NAME_SIZE_MAX){ displayError(nameLength,temp.name,temp.parsedAtLine); return false; }
    for(int i=0;i<TABLE_SIZE;i++){
        if(temp.name==hashTable[i].name){
            displayError(duplicateName,temp.name,temp.parsedAtLine);
            return false;
        }
    }

    //Exec all checks for email, and number.
    if(!testNumberFormat(temp) || !testEmailFormat(temp)) { return false; }

    if(temp.credits>150) { displayError(creditsValue,temp.name,temp.parsedAtLine); return false; }
    if(temp.gpa>4.0) { displayError(gpaValue,temp.name,temp.parsedAtLine); return false; }
    return true;
}