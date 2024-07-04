#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "stack.h"

typedef struct {
    char *name;
    int age;
    int id;
    }Student;


Student* create_student(const char* name, int age, int id){
    Student* student = (Student*)malloc(sizeof(Student));
    //need to set empty values to avoid trash?
    if(student != NULL){
        student->name = (char*)malloc(strlen(name) + 1);
        if(student->name != NULL){
            strcpy(student->name, name);
        }
        student->age = age;
        student->id = id;  
    }

    return student;
}

Student* clone_student(Student *student){
    if(!student->name || !student->age || !student->id){ //corrent failure?
        return NULL;
    }
    Student *new_stu = create_student(student->name, student->age, student->id);

    return new_stu;
}


void destroy_student(Student *student){
    free(student->name);
    free(student);
}


void print_student(Student *student){
    printf("student name: %s, age: %d, id: %d.\n",
        student->name,
        student->age,
        student->id);
}

/* //main - for small sacle testing
int main(int argc, char const *argv[]) {
    Student *stu = create_student("aaa", 3, 1039);
    print_student(stu);
    Student *stu2 = clone_student(stu);
    print_student(stu2);
    destroy_student(stu);
    destroy_student(stu2);
}
*/