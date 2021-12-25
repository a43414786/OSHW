#include <stdio.h>
#include <stlib.h>

FILE*trace = fopen("trace.txt", "r");
char word;
while((word = fgetc(trace)) != EOF){
    printf("%c",word);
}