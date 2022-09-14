#pragma once

#define EMAIL_SIZE 17
#define NAME_SIZE_MAX 20
#define NAME_SIZE_MIN 5
#define NUMBER_SIZE 9

#define TABLE_SIZE 35

struct student {

    std::string name;
    std::string number;
    std::string email;
    int credits;
    double gpa;
    int parsedAtLine;
};

int computerHash(std::string input) {
    int sum=0;
    for(char c : input){
        sum+=c;
    }
    return sum%TABLE_SIZE;
}
void displayRecord(struct student temp,int num) {
    std::string index=std::to_string(num)+".",name=temp.name,number=temp.number,email=temp.email,credits=std::to_string(temp.credits);
    bool empty = (temp.name.empty());
    std::cout << std::setw(5) << std::right << index
    << "  " << std::setw(20) << std::left << (empty? "-":name)
    << "  " << std::setw(9) << std::left << (empty? "-":number)
    << "  " << std::setw(17) << std::left << (empty? "-":email)
    << "  " << std::setw(7) << std::right << (empty? "-":credits);
    if(empty){
        std::cout << std::setw(5) << std::right << "-" << std::endl;
    } else{ std::cout << "  " << temp.gpa << std::endl; }
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
    int expectedHash = computerHash(temp->name);
    for(int i = expectedHash;i<(TABLE_SIZE*2);i++){
        int realHash = ((i>TABLE_SIZE-1) ? i-TABLE_SIZE : i);
        if(hashTable[realHash].name.empty()){
            hashTable[realHash]=*temp;

            std::cout << std::left << std::setw(14) << "Expected: "+std::to_string(expectedHash)+","
            << std::left << std::setw(14) << std::left << "Actual: "+std::to_string(realHash) << std::right
            << std::setw(25) << "Added Student to Table: \""+temp->name+"\"" << std::endl;

            //As long as there is space for the element, we will always have a place for it.
            return;
        }
    }
    //If we reach here, then there is no available spot for the element, throw error.
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