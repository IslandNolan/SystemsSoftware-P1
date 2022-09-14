#pragma once // Prevents the header file from loading multiple times
#include <string>
#include <iostream>
#include <iomanip>

enum error{
    missingArgs=1,
    fileNotFound=2,
    blankRecord=3,
    corruptRecord=4,
    shortRecord=5,
    duplicateName=6,
    nameLength=7,
    numberLength=8,
    emailLength=9,
    emailFormat=10,
    creditsValue=11,
    gpaValue=12,
    carriageReturn=13,
    numberFormat=14
};
void displayError(int error, std::string content, int lineNumber){
    std::string err = "Error: (Line: "+std::to_string(lineNumber)+")  ";
    std::cout << std::left << std::setw(28) << err;
	switch(error){
        case 1:
            std::cout << content << std::endl;
            break;
        case 2:
            break;
        case 3:
            std::cout << "Blank Record: ( --- )" << std::endl;
            break;
        case 4:
            std::cout << "Corrupt Record: (" << content << ")" << std::endl;
            break;
        case 5:
            std::cout << "Short Record: (" << content << ")" << std::endl;
            break;
        case 6:
            std::cout << "Duplicate Name: (" << content << ")" << std::endl;
            break;
        case 7:
            std::cout << "Name Length: (" << content << ")" << std::endl;
            break;
        case 8:
            std::cout << "Number Length: (" << content << ")" << std::endl;
            break;
        case 9:
            std::cout << "Email Length: (" << content << ")" << std::endl;
            break;
        case 10:
            std::cout << "Email Format: (" << content << ")" << std::endl;
            break;
        case 11:
            std::cout << "Student Credit is greater than max Allowed: (" << content << ")" << std::endl;
            break;
        case 12:
            std::cout << "Student GPA Not Less Than 4.0 (" << content << ")" << std::endl;
            break;
        case 13:
            std::cout << "A Carriage Return has been detected (Line: " << lineNumber << ").\n Testing is being performed on a unix-style system.\n "
                         "Please convert the inputted file into a unix-style format, and re-run the program.\n The Program will now exit, as there are known incompatibilities with carriage returns on unix." << std::endl;
            break;
        case 14:
            std::cout << "Number Format: (" << content << ")" << std::endl;
            break;
        default: break;
    }
}