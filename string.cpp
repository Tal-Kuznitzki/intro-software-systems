#include "string.h"
// #include "generic-string.h"
// #include <string>
#include <cstring>

using std::string;

String::String(char *str){this->internal_str = str;}
String::String(const char *str){this->internal_str = str;}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * @param delemiters A set of characters. For example, when delimieters=" ,"
 * this should be split according to spaces and commas.
 * @returns A "StringArray" object. See HW spec for more info.
 */
StringArray String::split(const char *delimiters) const {
    StringArray arr;
    char *copy = strdup(this->internal_str.c_str());
    char *substr = strtok(copy, delimiters) ;
    while(substr){
        arr.add_str(make_string(substr));
        substr = strtok(NULL, delimiters);
        delete make_string(substr); //TODO TEST !
    }
    delete copy;
    return arr;
}

/**
 * @brief Sets the contents of this to be a copy of "str".
 * @returns A reference to this.
 */
GenericString& String::operator=(const char *str){
        this->internal_str = str; //std::string is the best :) Memmory handling and copy
        return *this;
}

/**
 * @brief Remove any leading or trailing white-spaces from this.
 * @returns A reference to this.
 */
GenericString& String::trim(){
    //trim end
    size_t last = this->internal_str.find_last_not_of(" ");
    this->internal_str.erase(last + 1);
    //trim eginnning
    size_t first = this->internal_str.find_first_not_of(" ");
    this->internal_str.erase(0, first);
    
    return *this;
}

/**
 * @brief Returns true iff the contents of this == the contents of other.
 */
bool String::operator==(const GenericString &other) const {       ///////////////////// CHECK WHEN FINISH CLASS
    const String *temp = dynamic_cast<const String*>(&other);
    return !(this->internal_str.compare(temp->internal_str)) ? true : false ;
}
bool String::operator==(const char *other) const {                ///////////////////// CHECK WHEN FINISH CLASS
    return !(this->internal_str.compare(other)) ? true : false ;
}

/**
 * @brief Returns an integer representation of the contents of this.
 * In case this cannot be represented as integer, returns 0.
 * @note You can use the "atol" function in the "cstring" library.
 */
int String::to_integer() const{
    //atoi returns 0 if fails
    int num = std::atoi(this->internal_str.c_str());
    return num;
}

/**
 * @brief Returns a reference to this as "String" instead of "GenericString"
 */
String& String::as_string(){                                ///////////////////// CHECK WHEN FINISH CLASS
    // return dynamic_cast<String*>(this);
    return *this;
}
const String& String::as_string() const{                    ///////////////////// CHECK WHEN FINISH CLASS
    // return dynamic_cast<String*>(this);
    return *this;
}

String::~String() {}

/**
 * @brief Global method. Creates a GenericString representation of "str".
 * Should allocate memory. The user is responsible of freeing the returned
 * object.
 */
GenericString* make_string(const char *str){
    String *temp =  new String;
    *temp = str;
    return temp;

}
