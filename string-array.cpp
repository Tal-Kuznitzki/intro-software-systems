#include "string-array.h"

// using std::vector;

StringArray::StringArray() = default;

int StringArray::get_size(){
    return this->str_arr.size();
}

//add string, resize if needed
void StringArray::add_str(GenericString* str){
    this->str_arr.push_back(str);
}

//can access specific string using []
GenericString* StringArray::operator[](int index) {
    return this->str_arr[index];
}


StringArray::~StringArray() {};


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