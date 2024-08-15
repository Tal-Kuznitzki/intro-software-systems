#ifndef STRING_H
#define STRING_H


#include "generic-string.h"
#include "string-array.h"
#include <string>

using std::string;

class String: public GenericString{
    string internal_str;

    public:
    String() = default;
    String(char *str);
    String(const char *str);

    StringArray split(const char *delimiters) const;
    GenericString& operator=(const char *str);
    GenericString& trim();
    bool operator==(const GenericString &other) const;
    bool operator==(const char *other) const;
    int to_integer() const;
    String& as_string();
    const String& as_string() const;
    ~String();
};

GenericString* make_string(const char *str);

#endif