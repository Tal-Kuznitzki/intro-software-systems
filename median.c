#include <stdio.h>
#include <string.h>
#define UPPERBOUND 100
#define LOWERBOUND 0

int Error(int lineNumber, int Grade){

    fprintf(stderr,"Error at line %d: grade %d invalid",lineNumber,Grade);
    return 1;
}

int median(FILE *fp ){

    int lineNum;
    int grade;
    int median=0 //median is (N+1)/2 where N is the number of elements 

	cursorPositionForNumber=

//firstly, pass on the line of the file and count the number of line, thus receiving N
//afterwards, run on the histogram to find what number fit that range
//after that, run on the list again to find the number that match that range and count till 
//getting to the right index



    if ( ( grade>UPPERBOUND ) || ( grade<LOWERBOUND ) ) {
        return Error(lineNum,grade);
    }
    // i assume i receive a file that looks like this
    // 100
    // 9
    //11
    //60
    //33
    //pass on everyline, if a number is >100 out to stderr
	


    fclose(fp);


    return median;


}
int main(int argc,char **argv) {
    FILE *fp;

    if ( (argc==1) || !strcmp(argv[1]) ){
        fp=stdin;
    }
    else{
        fp=fopen(argv[1],"r");
    };
    if (!fp){
        fprintf(stderr,"FILE NOT FOUND!!");
    }

    return median(fp);
}
