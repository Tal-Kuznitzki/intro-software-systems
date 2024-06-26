#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#define UPPERBOUND 100
#define LOWERBOUND 0


int Error(int lineNumber, int Grade){
    fprintf(stderr,"Error at line %d: grade %d invalid",lineNumber,Grade);
    return 1;
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int median(FILE *fp ){
//firstly, pass on the line of the file and count the number of line, thus receiving N
//afterwards allocate an array at that size and populate
//preform qsort on it
// return the element in the median spot

//old plan
//~ afterwards, run on the histogram to find what number fit that range~
//~after that, run on the list again to find the number that match that range and count till ~
//~getting to the right index~
int median;
int lineNum=0;
int grade;
char buf[sizeof (int)+1]={0};
while(fgets(buf,sizeof(int)+1,fp)){ //getting the number of elements
        lineNum++;
    }
int median_pos=((lineNum+1)/2);
int *grades=(int*)malloc(sizeof(int)*lineNum);
fseek(fp,0,SEEK_SET);
lineNum=0;
    while(fgets(buf,sizeof(int)+1,fp)){
        grade=atoi(buf);
        if ( ( grade>UPPERBOUND ) || ( grade<LOWERBOUND ) ) {
            free(grades);
            return Error(lineNum,grade);
        }
        grades[lineNum]=grade;
        lineNum++;
    }
    qsort(grades,lineNum,sizeof(int),cmpfunc);
    median=grades[median_pos-1];
    free(grades);
    fclose(fp);
   // printf("number of grades is: %d\nmedian is %d",lineNum,median);

    return median;
}
int main(int argc,char **argv) {
    FILE *fp;

    if ( (argc==1) || !strcmp(argv[1],"-") ){
        fp=stdin;
    }
    else{
        fp=fopen(argv[1],"r");
    };
    if (!fp){
        fprintf(stderr,"FILE NOT FOUND!!");
    }

    fprintf(stdout,"%d",median(fp));
//    return median(fp);
    return 1;
}
