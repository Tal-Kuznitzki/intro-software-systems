#include "string-array.h"
#include "string.h"
#include <vector>
#include <iostream>

using std::vector;


class StringArray{
        
        vector<GenericString*> str_arr;

    public:

        StringArray() = default;

        int get_size(){
            return str_arr.size();
        }

        //add string, resize if needed
        void add_str(GenericString* str){
            str_arr.push_back(str);
        }

        //can access specific string using []
        GenericString* operator[](int index) {
        if (index < str_arr.size()) {
            return str_arr[index];
        }
        //false statement handle needed?
    }


        ~StringArray() = default;
};

/* //small test
int main() {
    StringArray arr; // Reserve initial capacity for 10 strings

    arr.add_str("Hello");
    arr.add_str("World");
    

    std::cout << "Size: " << arr.get_size() << std::endl;

    // Access elements using []
    std::cout << "Element at index 0: " << arr[0] << std::endl;
    std::cout << "Element at index 1: " << arr[1] << std::endl;

    arr.add_str("added");
    std::cout << "Element at index 2: " << arr[2] << std::endl;
    std::cout << "Element at index 3: " << arr[3] << std::endl;  //WHY NO ERROR?
    std::cout << "Size: " << arr.get_size() << std::endl;
    arr.add_str("");
    std::cout << "Size: " << arr.get_size() << std::endl;
    std::cout << "Element at index 3: " << arr[3] << std::endl;


    return 0;
}
*/