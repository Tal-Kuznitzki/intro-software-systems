/**
 * struct - VERIFY
 * course destroy
 * grades_calc_avg
 * grades_add_grade
 * grades_print_udent
*/

#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"
#include <string.h>
#include "grades.h"
#include <stdbool.h>
//#include "liblinked-list.so"

//course is an object with grade and name inside courses linkedlist
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

struct Course* course_init( const char *name, const int grade){
    struct Course *course = (struct Course*)malloc(sizeof(struct Course));
    course->name=(char*)malloc((strlen(name)+1)*sizeof(char));//TODO CHECK!!!!!!!!!!!
    strcpy(course->name,name);
    course->score=grade;
    return course;
}
int course_clone(struct Course *course, struct Course **new_course ) {
    if (!course) {
        *new_course = NULL;
        return 1;
    }
    *new_course = (struct Course*)malloc(sizeof(struct Course));
    (*new_course)->name = (char*)malloc((strlen(course->name)+1)*sizeof(char));
    strcpy((*new_course)->name,course->name);
    (*new_course)->score = course->score;
    return 0;


}
void course_destroy(struct Course *course) {
    if (course){
        if(course->name){
            free(course->name);
        }
        free(course);
    }
}
int student_clone(struct Student *student, struct Student **output){
    //checks
    if(!student){
        *output = NULL;
        return 1;
    }
    //initiate and copy non-list types
    struct Student *new_stu;
    new_stu = (struct Student*)malloc(sizeof(struct Student));
    new_stu->name = (char*)malloc(strlen((student->name)+1)*sizeof(char));
    strcpy(new_stu->name,student->name);
    new_stu->id = student->id;
    new_stu->courses = list_init(course_clone, course_destroy);

    //copy courses
    struct iterator* idx = list_begin(student->courses);
    struct Course *temp_course=0;
    while(idx != NULL){
        course_clone(list_get(idx), &temp_course);
        list_push_back(new_stu->courses, temp_course);
        list_next(idx);
    }
    *output=new_stu;
    //free(idx);

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
struct grades* grades_init(){
    // (struct grades*) casting removed !?
    struct grades *grades = malloc(sizeof(struct grades)); //TODO room for error?
    grades->students = list_init(student_clone, student_destroy);
    return grades;
}
/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
    if(grades){ //TODO  perhaps also remove each student's courses manunally ?
        list_destroy(grades->students);
        free(grades);
    }
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
    //invaild grade check
    if (grade>100 || grade<0){
        return 1;
    }

    //go over all the students, find student with id "id"  and add a course with the needed data
    struct iterator *current_student_iterator = list_begin(grades->students);
    struct Student *current_student_element;
    while(current_student_iterator && grades!=NULL){
            current_student_element = list_get(current_student_iterator);
        if ( current_student_element->id == id){
            struct iterator *current_course_iterator = list_begin(current_student_element->courses);
            struct Course *current_course_element;

            //passing over all the courses in student to check if it already exists
            while (current_course_iterator!=NULL){
                current_course_element = list_get(current_course_iterator);
                char* current_course_name = current_course_element->name;
                if ( !strcmp(current_course_name,name) ){
                    return 1;
                }



                current_course_iterator = list_next(current_course_iterator);
            }

            struct Course* new_course = course_init(name,grade);
            //new way of adding course ?
            list_push_back(current_student_element->courses, new_course);
            course_destroy(new_course);
            /*  OLD WAY
 *           list_insert(current_student_element->courses,
            list_end(current_student_element->courses),
            new_course
            );*/
//TODO check for segfault
            return 0;
        }
        current_student_iterator = list_next(current_student_iterator);
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
    //check: is grades valid, and does id already exists
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
    student->name = (char*)malloc((strlen(name)+1)*sizeof(char));
    strcpy(student->name, name);
    student->id = id;
    student->courses = list_init(course_clone, course_destroy);


    //add to grades:
    if(list_push_back(grades->students, student)) printf("pushback unsuccesful");
  //  printf("%s\n", name);
   // printf("%s\n", student->name);

    // new way does not touch the data?

    /*
    struct iterator *current_student_iterator = list_begin(grades->students);
    size_t num_of_current_students =list_size(grades->students);
    for (size_t i = 0; i < num_of_current_students ; ++i) {
        current_student_iterator=list_next(current_student_iterator);
    }
    list_insert(grades->students,current_student_iterator,student);
    */

    //printf("%s\n", list_get(current_student_iterator)->name);
    //printf("%d\n", list_get(current_student_iterator)->id);

   //free student, list has a copy
   student_destroy(student);



  /* LLALALL
    //check: is grades valid, and does id already exists

    printf("testing");
    if(!grades) return 1;

    struct iterator *idx = list_begin(grades->students);
    struct Student *temp_stu;
    while(idx != NULL){
        temp_stu = list_get(idx);
        if(temp_stu->id == id) return 1;
        idx = list_next(idx);
    }

    //initiate
    struct Student *student = malloc(sizeof(struct Student));
    student->name = (char*)malloc((strlen(name)+1)*sizeof(char));
    strcpy(student->name, name);
    student->id = id;
    student->courses = list_init(course_clone, course_destroy);


    printf("list size is:  %ld before insert\n", list_size(grades->students) );

    printf("element to insert DATA\n");
    printf("%d\n", student->id);
    printf("%s\n", student->name);

    //add to grades:
    //old way - caused segfaults
    /// assuming addition is successful
    struct iterator *current_student_iterator = list_begin(grades->students);

    if (current_student_iterator==NULL){
        printf("current_student_iterator is NULL\n");
        if(list_push_back(grades->students, student)) printf("pushback unsuccesful!\n");
    }
    else{
        printf("current_student_iterator is GOOD!!!\n");
        int num_of_current_students = (int)list_size(grades->students);
        for (int i = 0; i < num_of_current_students ; ++i) {
            current_student_iterator=list_next(current_student_iterator);
        }
        list_insert(grades->students,current_student_iterator,student);
    }


    printf("list size is:  %ld (after insert)\n", list_size(grades->students) );

    //printf("%s\n", list_get(current_student_iterator)->name);
    //printf("%d\n", list_get(current_student_iterator)->id);

    //free student, list has a copy
    free(student->name);
    free(student);
    //  student_destroy(student);


*/

   // printf("amount of students after addition %ld \n", list_size(grades->students));
    return 0;

}
float grades_calc_avg(struct grades *grades, int id, char **out){
    //go over all the students, find student with id "id"  and calc avg
    float avg;
    *out=NULL;
    if (!grades) return -1;

    struct iterator *current_student_iterator = list_begin(grades->students);
    struct Student *current_student_element;

    while(current_student_iterator){
        current_student_element = list_get(current_student_iterator);


        if ( current_student_element->id == id){
          //  size_t num_of_courses=0;
            size_t num_of_courses = list_size(current_student_element->courses);
            struct iterator *current_course_iterator = list_begin(current_student_element->courses);
/*            if (num_of_courses==NULL || num_of_courses==0 ) {
                current_course_iterator=0;
            }*/
            int total_score = 0;
            int current_grade = 0;
            while(current_course_iterator){
                struct Course *current_course_element = list_get(current_course_iterator);
                current_grade = current_course_element->score;
                total_score += current_grade;
                current_course_iterator = list_next(current_course_iterator);
            }
            *out = (char*)malloc((strlen(current_student_element->name)+1)*sizeof(char));
            strcpy(*out, current_student_element->name);
            avg = (num_of_courses) ? (((float)total_score)/((float)num_of_courses)) : 0.00;
            //free(*out);
            return avg;
        }
        current_student_iterator = list_next(current_student_iterator);
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
    if (!grades) return 1;

    struct iterator* current_student_iterator = list_begin(grades->students);
    struct Student* current_student_element;


    while(current_student_iterator){
        current_student_element = list_get(current_student_iterator);
        //if found the student, print data
        if ( current_student_element && current_student_element->id == id){
            printf("%s %d:",
                   current_student_element->name,
                   current_student_element->id);
            //Loop on courses:
            struct iterator* current_course_iterator =list_begin(current_student_element->courses);
            struct Course *current_course_element;
            while(current_course_iterator){
                current_course_element = list_get(current_course_iterator);

                current_course_iterator = list_next(current_course_iterator);
                if (current_course_iterator){
                    printf(" %s %u,",
                           current_course_element->name,
                           current_course_element->score);
                }
                else{
                    printf(" %s %u",
                           current_course_element->name,
                           current_course_element->score);
                }


            }
            printf("\n");
           return 0;
        }
       // printf("nope (inside loop)\n");
        current_student_iterator = list_next(current_student_iterator);
    }
   // printf("very nope (outside loop)\n");
    return 1;
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
int grades_print_all(struct grades *grades){
    //checks
    if(!grades) return 1;

    struct iterator *idx = list_begin(grades->students);
    struct Student *temp;
    while(idx != NULL){
        temp = list_get(idx);
        if(grades_print_student(grades, temp->id)) return 1;
        idx = list_next(idx);
    }

    return 0;
}
