#include "generic-string.h"
#include "string-array.h"

#ifndef STRING_H
#define STRING_H

class String: public GenericString{
    public:
    String() = default;
    String(string str);
    String(const string str);
    String(char *str);
    String(const char *str);

    StringArray split(const char *delimiters);
    GenericString& operator=(const char *str);
    GenericString& trim();
    bool operator==(const GenericString &other);
    bool operator==(const char *other);
    int to_integer();
    String& as_string();
    const String& as_string() const;
    ~String();
};

#endif