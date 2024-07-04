#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "stack.h"

typedef struct Student Struct;

struct Student* create_student();
struct Student* clone_student(Student *student);
void destroy_student(Student *student);
void print_student(Student *student);