#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void operation(FILE *f);

int main(int argc, char **argv){
    FILE *f;

    //arg check
    if((argc==1)||(!strcmp("-",argv[1]))){ 
        f = stdin;
    } else {
        f = fopen(argv[1], "r");
    }
    
    //call math operation of this code
    operation(f);
}


void operation(FILE *f){
    //return min grade
    int curr_num = 0;
    int line_num = 0;
    int scan_op = 0;
    int min = 100;

    while(1){
        scan_op = fscanf(f, "%d", &curr_num);
        
        if(scan_op == EOF){
            break;
        } else if((scan_op != 1) || (curr_num < 0 || curr_num > 100)){
            fprintf(stderr, "Error at line %d: invalid grade %d\n", 
            line_num, curr_num);
            fclose(f);
            exit(1);
        } else{
            if(curr_num < min){
                min = curr_num;
            }
        }
        line_num++;
    }

    fprintf(stdout, "%d\n", min);
    fclose(f);

}