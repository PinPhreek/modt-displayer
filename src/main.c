#define _POSIX_C_SOURCE 200809L
#define MOOD_GOOD 0
#define MOOD_BAD 1
#define MOOD_RANDOM 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <time.h>

long* get_current_time_with_ns (long* l);
int isEven(long* number);
int main(int argc, char* argv[]){

    int mood = MOOD_RANDOM;

    for (int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-b")){
            mood = MOOD_BAD;
        }
        else if(!strcmp(argv[i], "-g")){
            mood = MOOD_GOOD;
        }
        else if(!strcmp(argv[i], "-r")){
            mood = MOOD_RANDOM;
        }
        else{
            printf("Unknown argument %s\n", argv[i]);
        }
    }

    FILE* fp;
    ssize_t read;
    char* line;
    size_t len = 0;

    size_t line_count = 0;
    time_t t;
    srand((unsigned) time(&t));

    if((fp = fopen("motd.txt", "r")) == NULL){
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        line_count++;
    }

    if(mood == MOOD_RANDOM){
        mood = isEven(get_current_time_with_ns(&read)) ? 1 : 0;
    }
    if(mood == MOOD_BAD){
        do{
            mood = rand() % line_count;
        }while(isEven((long*) &mood));
    }
    else if(mood == MOOD_GOOD){
        do{
            mood = rand() % line_count;
        }while(!isEven((long*) &mood));
    }

    line_count = 0;
    line = memset(&line, 0, sizeof(line));
    len = 0;

    fclose(fp);

    if((fp = fopen("motd.txt", "r")) == NULL){
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        if (mood == line_count){
            printf("%s", line);
            break;
        }
        line_count++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

}
long* get_current_time_with_ns (long* l){
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    *l = spec.tv_nsec;
    return l;
}
int isEven(long* number){
    if(*number %2 == 0)
        return 1;
    else
        return 0;
}