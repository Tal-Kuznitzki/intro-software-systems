#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H


#include "generic-string.h"
#include <vector>
using std::vector;

class StringArray{
    vector<GenericString*> str_arr;

    public:

        StringArray();
        int get_size();
        void add_str(GenericString* str);
        GenericString* operator[](int index);
        ~StringArray();
};

#endif