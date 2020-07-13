#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE* fp;
    ssize_t read;
    char* line;
    size_t len = 0;

    if((fp = fopen("motd.txt", "r")) == NULL){
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

}