#include "generic-string.h"
// #include <string>

#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H


class StringArray{
    public:

        StringArray();
        int get_size();
        void add_str(GenericString* str);
        GenericString* operator[](int index);
        ~StringArray();
};

#endif