/**
 * struct - VERIFY
 * course destroy
 * grades_calc_avg
 * grades_add_grade
 * grades_print_student
*/
#include <stdlib.h>
#include "linked-list.h"
#include <string.h>
#include "grades.h"
#include <stdbool.h>
//#include "liblinked-list.so"

//course is a linkedList that will
//inside student we have a linked list of courses
struct Course{
    int score;
    char* name;
};
/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades{
    struct list *students;
};
struct Student{
    char* name;
    int id;
    struct list *courses;// = list_init(student_clone, student_destroy);
};

struct grades* grades_init(){
    struct grades *grades = (struct grades*)malloc(sizeof(struct grades));
    grades->students = list_init(student_clone, student_destroy);
    return *grades;
}
/**
 * @brief Destroys "grades", de-allocate all memory!
 */

void grades_destroy(struct grades *grades);
int student_clone(struct Student *student, struct Student *new_stu);
void student_destroy(struct Student *student);
struct Course* course_init( const char *name,  const int grade);
int course_clone(struct Course *course, struct Course *new_course );
struct Course* course_destroy(struct Course *course);
        

void grades_destroy(struct grades *grades){
    if(grades){
        list_destroy(grades->students);
        free(grades);
    }
}
int student_clone(struct Student *student, struct Student *new_stu){
    //checks
    if(!student){
        new_stu = NULL;
        return 1;
    }

    //initiate and copy non-list types
    new_stu = (struct Student*)malloc(sizeof(struct Student));
    new_stu->name = (char*)malloc(strlen(student->name));
    strcpy(new_stu->name,student->name);
    new_stu->id = student->id;
    new_stu->courses = list_init(course_clone, course_destroy);

    //copy courses
    struct iterator* idx = list_begin(student->courses);
    struct Course *temp_course;
    while(idx != NULL){
        course_clone(list_get(idx), temp_course);
        list_push_back(new_stu->courses, temp_course);
        list_next(idx);
    }
    free(idx);

    return 0;
}
void student_destroy(struct Student *student){
    if(student){
        if(student->name){
            free(student->name);
        }
        list_destroy(student->courses);
        free(student);
    }
}
/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
struct Course* course_init( const char *name,  const int grade){
       struct Course *course=(struct *course)malloc(sizeof(struct Course));
       course->name=(char*)malloc(sizeof(name));
       strcpy(name,course->name);
       course->score=grade;
    return course;
}
int course_clone(struct Course *course, struct Course *new_course ) {
    if (!course) {
        new_course = NULL;
        return 1;
    }
    new_course = (struct Course*)malloc(sizeof(struct Course));
    new_course->name = (char*)malloc(strlen(course->name));
    strcpy(course->name,new_course->name);
    new_course->score = course->score;
    return 0;


}
struct Course* course_destroy(struct Course *course) {
if (course){
    if(course->name){
        free(course->name);
    }
    free(course);
}
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

    if (grade>100 || grade<0)
    {
        return 1;
    }

    //go over all the students, find student with id "id"  and add a course with the needed data
    struct iterator* current_student_iterator = list_begin(grades->students);
    struct student* current_student_element=list_get(current_student_iterator); //TODO perhaps replace with void* ?
    while(current_student_iterator && grades!=NULL){
        if ( current_student_element->id == id){
            struct iterator* current_course_iterator = list_begin(current_student_element->courses);
            while (current_course_iterator!=NULL){

                if ( !strcmp(list_get(current_course_iterator)->name,name) )
                    return 1;
                current_course_iterator = list_next(current_course_iterator);
            }

            struct Course* new_course = course_init(name,grade);
            list_insert(current_student_element->courses,
                        list_end(current_student_element->courses),
                        new_course
            );//TODO check for segfault
            return 0;
        }
        current_student_iterator = list_next(current_student_iterator);
        current_student_element = list_get(current_student_iterator);
    }
    return 1;
}


/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
    //check: is gardes valid, and does id already exists
    if(!grades) return 1;
    struct iterator *idx = list_begin(grades->students);
    struct Student *temp_stu;
    while(idx != NULL){
        temp_stu = list_get(idx);
        if(temp_stu->id == id) return 1;
        idx = list_next(idx);
    }

    //initiate
    struct Student *student = (struct Student*)malloc(sizeof(struct Student));
    student->name = (char*)malloc(strlen(student->name));
    strcpy(name,student->name);
    student->id = id;
    student->courses = list_init(course_clone, course_destroy);

    //add to grades:
    list_push_back(grades->students, student);

    return 0;
}


float grades_calc_avg(struct grades *grades, int id, char **out){

    //go over all the students, find student with id "id"  and calc avg
    float avg=0.0;
    out=NULL;
    if (!grades) return -1;
    struct iterator* current_student_iterator = list_begin(grades->students);
    struct student* current_student_element = list_next(current_course_iterator);
    while(current_student_iterator){
        if ( current_student_element->id == id){

            float num_of_courses = (float)list_size(current_student_element->courses);
            struct iterator* current_course_iterator = list_begin(current_student_element->courses);
            while(current_course_iterator){
                avg += (float)list_get(current_course_iterator)->score;//  TODO error in conversation?
                current_course_iterator = list_next(current_course_iterator);
            }
            out=(char*)malloc(strlen(current_student_element->name));
            strcpy(current_student_element->name,out);
            return avg/num_of_courses;

        }
        current_student_iterator = list_next(current_student_iterator);
        current_student_element = list_get(current_student_iterator);
    }

    return -1;
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
    if (!grades){
        return 1;
    }
    struct iterator* current_student_iterator = list_begin(grades->students);
    struct student* current_student_element=list_get(current_student_iterator);
    while(current_student_iterator){
        if ( current_student_element->id == id){
            printf("%s %d:",current_student_element->name,current_student_element->id);
            //Loop on courses:
            struct iterator* current_course_iterator = list_begin(current_student_element->courses);
            while(current_course_iterator){
                printf("%s %u",
                       list_get(current_course_iterator)->name,
                       list_get(current_course_iterator)->score);
                current_course_iterator = list_next(current_course_iterator);
            }
            printf("\n");
           return 0;
        }
        current_student_iterator = list_next(current_student_iterator);
        current_student_element = list_get(current_student_iterator);
    }
    return 1;
}

int grades_print_all(struct grades *grades){
    //checks
    if(!grades) return 1;

    struct iterator *idx = list_begin(grades->students);
    struct Student *temp;
    while(idx != NULL){
        temp = list_get(idx);
        if(!grades_print_student(grades, temp->id)) return 1;
        idx = list_next(idx);
    }

    return 0;
}
