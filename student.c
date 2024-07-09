#include "student.h"


struct student* student_create(const char* name, int age, int id){
    struct student* student = (struct student*)malloc(sizeof(struct student));
    //need to set empty values to avoid trash?
    if(student != NULL){
        student->name = (char*)malloc((strlen(name) + 1)*sizeof(char));
        if(student->name != NULL){
            strcpy(student->name, name);
        }
        student->age = age;
        student->id = id;  
    }

    return student;
}

struct student* student_clone(struct student *student){
    if(!student->name|| !student){ //corrent failure?
        return NULL;
    }
    struct student *new_stu;
    new_stu = student_create(student->name, student->age, student->id);

    return new_stu;
}


void student_destroy(struct student *student){
    if(student->name){
        free(student->name);
    }
    free(student);
}


void student_print(struct student *student){
    printf("print func");
    if(student){
        printf("student name: %s, age: %d, id: %d.\n",
        student->name,
        student->age,
        student->id);
    }
}


/* //main - for small sacle testing

int main(int argc, char const *argv[]) {
    struct student *stu = create_student("aaa", 3, 1039);
    print_student(stu);
    struct student *stu2 = clone_student(stu);
    print_student(stu2);
    destroy_student(stu);
    destroy_student(stu2);
}
*/
