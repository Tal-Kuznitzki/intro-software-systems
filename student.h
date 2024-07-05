#ifndef STUDENT_H
#define STUDENT_H

#include <string.h>
#include "common.h"


struct student{
    char *name;
    int age;
    int id;
};

struct student* student_create(const char* name, int age, int id);
struct student* student_clone(struct student *student);
void student_destroy(struct student *student);
void student_print(struct student *student);

#endif