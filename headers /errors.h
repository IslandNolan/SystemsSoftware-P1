#pragma once
#include <string>
#include <iostream>
#include <iomanip>


/**
 * Enumeration for the error type.
 * We use the ordinal values here instead of manually defining them.
 */
enum error{
    missingArgs,
    fileNotFound,
    blankRecord,
    corruptRecord,
    shortRecord,
    duplicateName,
    nameLength,
    numberLength,
    emailLength,
    emailFormat,
    creditsValue,
    gpaValue,
    carriageReturn,
    numberFormat
};

/**
 * Display an error message based on the enumeration enum.
 * @param error Type of Error.
 * @param content Dependent on the implementation- Usually the problematic field.
 * @param lineNumber The Line # of the file the error appeared on.
 */
void displayError(int error, std::string content, int lineNumber){
    std::string err = "Error: (Line: "+std::to_string(lineNumber)+")  ";
    std::cout << std::left << std::setw(28) << err;
	switch(error){
        case missingArgs:
            std::cout << content << std::endl;
            break;
        case fileNotFound:
            break;
        case blankRecord:
            std::cout << "Blank Record: ( --- )" << std::endl;
            break;
        case corruptRecord:
            std::cout << "Corrupt Record: (" << content << ")" << std::endl;
            break;
        case shortRecord:
            std::cout << "Short Record: (" << content << ")" << std::endl;
            break;
        case duplicateName:
            std::cout << "Duplicate Name: (" << content << ")" << std::endl;
            break;
        case nameLength:
            std::cout << "Name Length: (" << content << ")" << std::endl;
            break;
        case numberLength:
            std::cout << "Number Length: (" << content << ")" << std::endl;
            break;
        case emailLength:
            std::cout << "Email Length: (" << content << ")" << std::endl;
            break;
        case emailFormat:
            std::cout << "Email Format: (" << content << ")" << std::endl;
            break;
        case creditsValue:
            std::cout << "Student Credit is greater than max Allowed: (" << content << ")" << std::endl;
            break;
        case gpaValue:
            std::cout << "Student GPA Not Less Than 4.0 (" << content << ")" << std::endl;
            break;
        case carriageReturn:
            std::cout << "A Carriage Return has been detected (Line: " << lineNumber << "). " << std::setw(27) <<"You are testing on a unix-style system.\n "<< std::setw(27) <<
                      std::right << "" << "Please convert the inputted file into a unix-style format, and re-run the program.\n" << std::setw(27) << "" << " The Program will now exit, as there are known incompatibilities with carriage returns on unix." << std::endl;
            break;
        case numberFormat:
            std::cout << "Number Format: (" << content << ")" << std::endl;
            break;
        default: break;
    }
}