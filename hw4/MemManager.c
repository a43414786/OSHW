#include <stdio.h>
#include <stdlib.h>

FILE*trace = fopen("trace.txt", "r");
char word;
while((word = getc(trace)) != EOF){
    printf("%c",word);
}