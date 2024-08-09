#include "string.h"
#include <iostream>
#include <string>
#include <cstring>

using std::string;

class String: public GenericString{
        
    string internal_str;

    public:

    String() = default;
    String(string str){internal_str = str;}
    String(const string str){internal_str = str;}
    String(char *str){internal_str = str;}
    String(const char *str){internal_str = str;}

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * @param delemiters A set of characters. For example, when delimieters=" ,"
     * this should be split according to spaces and commas.
     * @returns A "StringArray" object. See HW spec for more info.
     */
    StringArray split(const char *delimiters){
        StringArray arr;
        string internal_copy = internal_str;
        char *substr = strtok(&internal_copy[0], delimiters) ;
        while(substr){
            arr.add_str(make_string(substr));
            substr = strtok(NULL, delimiters);
        }
        return arr;
    }

    /**
     * @brief Sets the contents of this to be a copy of "str".
     * @returns A reference to this.
     */
    GenericString& operator=(const char *str){
            internal_str = str; //std::string is the best :) Memmory handling and copy
            return *this;
    }

   /**
     * @brief Remove any leading or trailing white-spaces from this.
     * @returns A reference to this.
     */
    GenericString& trim(){
        //trim end
        size_t last = internal_str.find_last_not_of(" ");
        internal_str.erase(last + 1);
        //trim eginnning
        size_t first = internal_str.find_first_not_of(" ");
        internal_str.erase(0, first);
        
        return *this;
    }

    /**
     * @brief Returns true iff the contents of this == the contents of other.
     */
    bool operator==(const GenericString &other) {       ///////////////////// CHECK WHEN FINISH CLASS
        String *temp = (String)other;
        return !(internal_str.compare(temp->internal_str)) ? true : false ;
    }
    bool operator==(const char *other) {                ///////////////////// CHECK WHEN FINISH CLASS
        return !(internal_str.compare(other)) ? true : false ;
    }

    /**
     * @brief Returns an integer representation of the contents of this.
     * In case this cannot be represented as integer, returns 0.
     * @note You can use the "atol" function in the "cstring" library.
     */
    int to_integer(){
        //atoi returns 0 if fails
        int num = std::atoi(internal_str.c_str());
        return num;
    }

    /**
     * @brief Returns a reference to this as "String" instead of "GenericString"
     */
    String& as_string(){
        return *dynamic_cast<String>(this);
    }
    const String& as_string() const{
        return *dynamic_cast<String>(this);
    }

    ~String() {}

};

/**
 * @brief Global method. Creates a GenericString representation of "str".
 * Should allocate memory. The user is responsible of freeing the returned
 * object.
 */
GenericString* make_string(const char *str){
    // String temp_string = str;
    // GenericString a = new String(str);
    // GenericString *temp_generic = &temp_string;
    
    // return dynamic_cast<GenericString>*(temp_string);

}
