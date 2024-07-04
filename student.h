#include <string.h>
#include "common.h"

typedef struct {
    char *name;
    int age;
    int id;
}Student;

Student* create_student(const char* name, int age, int id);
Student* clone_student(Student *student);
void destroy_student(Student *student);
void print_student(Student *student);