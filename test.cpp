#include <iostream>
#include <string>
#include <cstring>
#include "string.h"
#include "string-array.h"
#include "generic-string.h"

using std::string;

int foo(string& str){
    int num = std::atoi(str.c_str());
        return num;
}

int main() {
    // Create a string
    const char *base1 = "    213,456,789    ";
    const char *base2 = "213,456,789";

    std::cout << "base1 (before):/" << base1 << "/" << std::endl;
    std::cout << "base2 (before):/" << base2 << "/" << std::endl;

    
    String str1 = base1;
    String str2 = base2;

    bool a = str1==str2;
    std::cout << "compare== before trim/" << a << "/" << std::endl;
    String str3 = str1;
    str3.trim();
    a = str3==str2;
    std::cout << "compare== after trim/" << a << "/" << std::endl;

    StringArray arr = str3.split(",");
    for(int i=0; i<arr.get_size(); i++){
        std::cout << "print arr num " << i << "/" << arr[i]->to_integer() << "/" << std::endl;
    }

    for(int i=0; i<arr.get_size(); i++){
        std::cout << "print arr num " << i << " after as_string/" << arr[i]->as_string().to_integer() << "/" << std::endl;
        delete arr[i];
    }

    String *str4 = (String*)make_string("394856");
    std::cout << "print arr num " << "/" << str4->to_integer() << "/" << std::endl;
    delete str4;
    
    std::cout << "--END--" << std::endl;

    return 0;
}
