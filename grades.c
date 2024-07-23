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
//TODO clone should return the cloned object IN STUDENT

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

    //TODO add return value;
    //    return *grades;
}
/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
    //why not just list_destroy(grades) ?
    if(grades){
        list_destroy(grades->students);
        free(grades);
    }
}
void student_clone(struct Student *student, struct Student *new_stu){
    //checks
    if(!student) return;

    //initiate and copy non-list types
    struct Student *student = (struct Student*)malloc(sizeof(struct Student));
    strcpy(student->name,new_stu->name);
    new_stu->id = student->id;
    new_stu->courses = list_init(course_clone, course_destroy);

    //copy courses
    struct iterator* idx = list_begin(student->courses);
    while(idx != NULL){
        list_push_back(new_stu->courses, course_clone(list_get(idx)));
        list_next(idx);
    }
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
       struct Course *course;
       course->name=(char*)malloc(sizeof(name));
       strcpy(name,course->name);
       course->score=grade;
    return course; //TODO verify
}
struct Course* course_clone(struct Course *course){
    if (!course){
        return NULL;
    }
    struct Course *new_course = course_init(course->name,course->score);
    /** EHW WAY
    struct Course *new_course = (struct Course*)malloc(sizeof(struct Course));
    new_course->name=(char*)malloc(sizeof(course->name));
    strcpy(course->name,new_course->name);
    new_course->score=course->score;
**/
    return new_course;//TODO verify
}
struct Course* course_destroy(struct Student *student ,struct Course *course) {
    list_remove(student->courses,course)
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

    //go over all the students, find student with id "id"  and add a course with the needed data
    struct iterator* current_student_iterator = list_begin(grades->students);
    struct student* current_student_element; //TODO perhaps replace with void* ?
    while(current_student_iterator){
        if ( current_student_element->id == id){
            struct Course* new_course = course_init(name,grade);
            list_insert(current_student_element->courses,
                        list_end(current_student_element->courses),
                        new_course
            );
            break;
        }
        current_student_iterator = list_next(current_student_iterator);
        current_student_element = list_get(current_student_iterator);
    }
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
    student->name = name;
    student->id = id;
    student->courses = list_init(course_clone, course_destroy);

    //add to grades:
    list_push_back(grades->students, student);

    return 0;
}


float grades_calc_avg(struct grades *grades, int id, char **out){

    //go over all the students, find student with id "id"  and calc avg
    float avg=0.0;
    struct iterator* current_student_iterator = list_begin(grades->students);
    struct student* current_student_element; //TODO perhaps replace with void* ?
    while(current_student_iterator){
        if ( current_student_element->id == id){
            size_t num_of_courses = list_size(current_student_element->courses);
            struct iterator* current_course_iterator = list_begin(current_student_element->courses);
            while(current_course_iterator){
                avg += (float)list_get(current_course_iterator)->score;//  TODO error in conversation?
                current_course_iterator = list_next(current_course_iterator);
            }
            avg/=num_of_courses;
            break;
        }
        current_student_iterator = list_next(current_student_iterator);
        current_student_element = list_get(current_student_iterator);
    }

    return avg;
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
        return NULL;
    }
    struct iterator* current_student_iterator = list_begin(grades->students);
    struct student* current_student_element; //TODO perhaps replace with void* ?
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
           return 0;
        }
        current_student_iterator = list_next(current_student_iterator);
        current_student_element = list_get(current_student_iterator);
    }
    return NULL;
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
