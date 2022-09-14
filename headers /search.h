#pragma once // Prevents the header file from loading multiple times

enum searchType {
    creditsEqual,
    creditsLess,
    creditsMore,
    email,
    emailPart,
    fullName,
    firstName,
    lastName,
    gpaEqual,
    gpaLess,
    gpaMore,
    number
};

void performSearch(struct student hashtable[], int searchType, std::string searchText) {
	switch(searchType){
        case creditsEqual:
            break;
        case creditsLess:
            break;
        case creditsMore:
            break;
        case email:
            break;
        case emailPart:
            break;
        case fullName:
            break;
        case firstName:
            break;
        case lastName:
            break;
        case gpaEqual:
            break;
        case gpaLess:
            break;
        case gpaMore:
            break;
        case number:
            break;
        default: break;
    }
}