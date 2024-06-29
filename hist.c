#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BINS 10

void operation(FILE *f, int bins);

int main(int argc, char **argv){
    FILE *f;
    int bins = DEFAULT_BINS;
    f = stdin; //default
    
    //arg check
    for(int i=1; i<argc; i++){
        if((argc==1)||(!strcmp("-",argv[i]))){ 
            f = stdin;
        } else if(!strcmp("-nbins",argv[i]) && i < argc-1){
            bins = atoi(argv[i+1])>0 ? atoi(argv[i+1]) : 10;
            i++;
        } else {
            f = fopen(argv[i], "r");

        }
    }
    if(f==NULL){
        exit(1);
    }

    //call math operation of this code
    operation(f,bins);
}


void operation(FILE *f, int bins){
    //return grades hist
    int curr_num = 0;
    int line_num = 0;
    int scan_op = 0;
    int *hist = (int*)malloc(sizeof(int)*bins);
    int bins_size = 100/bins;

    while(1){
        scan_op = fscanf(f, "%d", &curr_num);
        
        if(scan_op == EOF){
            break;
        } else if((scan_op != 1) || (curr_num < 0 || curr_num > 100)){
            fprintf(stderr, "Error at line %d: invalid grade %d\n", 
            line_num, curr_num);
            free(hist);
            exit(1);
        } else{
            if(curr_num==100){
                hist[curr_num/bins_size-1]++;
            } else {
                hist[curr_num/bins_size]++;
            }
        }
        line_num++;
    }

    //print hist
    for(int i=0; i<bins; i++){
        if (i==bins-1){
            fprintf(stdout, "%d-%d\t%d\n", i*bins_size, 100, hist[i]);
        } else{
            fprintf(stdout, "%d-%d\t%d\n", i*bins_size, (i+1)*bins_size-1, hist[i]);
        }
    }

    free(hist);
}