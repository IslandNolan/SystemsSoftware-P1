#pragma once // Prevents the header file from loading multiple times

enum searchEnum {
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
    number,
    numberContains
};

/**
 * Search Object to help facilitate extra organization.
 * This was done this way in order to provide an easy way to expand
 * it's functionality at a later date (Project 2+ ?)
 */
struct search {
    searchEnum type;
    std::string text;

    bool checkStudent(struct student st) const{
        switch(type){
            case creditsEqual:
                return (stoi(text)==st.credits);
            case creditsLess:
                return (st.credits<stoi(text));
            case creditsMore:
                return (st.credits>stoi(text));
            case email:
                return (st.email==text);
            case emailPart:
                return st.email.find(text)!=std::string::npos;
            case fullName:
                return st.name==text;
            case firstName:
                return st.name.substr(0,text.size())==text;
            case lastName:
                return st.name.substr(st.name.size()-text.size())==text;
            case gpaEqual:
                return stod(std::to_string(st.gpa))==stod(text);
            case gpaLess:
                return st.gpa<stod(text);
            case gpaMore:
                return st.gpa>stod(text);
            case number:
                return st.number==text;
            case numberContains:
                return st.number.find(text)!=std::string::npos;
            default: return false;
        }
    }
};

/**
 * Construct a new Search Object
 * @param search String of Text to parse for each record.
 * @return
 */
search createSearch(std::string search){
    std::istringstream iss(search);
    std::string type, text;
    getline(iss,type,',');
    getline(iss,text,',');
    struct search search1;
    search1.text=text;
    search1.type=searchEnum(stoi(type));
    switch(stoi(type)){
        case creditsEqual:
            std::cout << "Searching for Credits == "+text << std::endl << "_____" << std::endl;
            break;
        case creditsLess:
            std::cout << "Searching for Credits < "+text << std::endl << "_____" << std::endl;
            break;
        case creditsMore:
            std::cout << "Searching for Credits > "+text << std::endl << "_____" << std::endl;
            break;
        case email:
            std::cout << "Searching for Email == "+text << std::endl << "_____" << std::endl;
            break;
        case emailPart:
            std::cout << "Searching for Email Contains "+text << std::endl << "_____" << std::endl;
            break;
        case fullName:
            std::cout << "Searching for Full Name == "+text << std::endl << "_____" << std::endl;
            break;
        case firstName:
            std::cout << "Searching for First Name == "+text << std::endl << "_____" << std::endl;
            break;
        case lastName:
            std::cout << "Searching for Last Name == "+text << std::endl << "_____" << std::endl;
            break;
        case gpaEqual:
            std::cout << "Searching for GPA == "+text << std::endl << "_____" << std::endl;
            break;
        case gpaLess:
            std::cout << "Searching for GPA < "+text << std::endl << "_____" << std::endl;
            break;
        case gpaMore:
            std::cout << "Searching for GPA > "+text << std::endl << "_____" << std::endl;
            break;
        case number:
            std::cout << "Searching for Number == "+text << std::endl << "_____" << std::endl;
            break;
        case numberContains:
            std::cout << "Searching for Number Contains "+text << std::endl << "_____" << std::endl;
            break;
    }
    return search1;
}

/**
 * Performs a particular search and checks every student for qualifying criteria.
 * If it matches, then the record is printed.
 * @param hashtable
 * @param search
 */
void performSearch(struct student hashtable[], std::string search) {
    struct search s = createSearch(search);
    for(int i=0;i<TABLE_SIZE;i++){
        struct student* st = &hashtable[i];
        struct student* pt = st->next;
        if(!st->name.empty() && s.checkStudent(*st)) { printRecord(*st,-1); }
        while(pt!=nullptr){
            if(s.checkStudent(*pt)){
                printRecord(*pt,1);
            }
            pt=pt->next;
        }
    }
    std::cout << std::endl;
}