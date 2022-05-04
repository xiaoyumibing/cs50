//FILE *fopen(const char *filename, const char *mode)
//filename is a string, not a FILE variable
//This function will return a FILE pointer
#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;

    fp = fopen("file.txt","w+");
    fprintf(fp, "%s %s %s %d","We","are","in",2012);

    fclose(fp);

    return 0;
}
