#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE*trace = fopen("trace.txt", "r");
    char word = 0;
    while((word = getc(trace)) != EOF){
        printf("%c",word);
    }
    return 0;
}