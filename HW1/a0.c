#include <stdio.h>
#include <stdlib.h>

#define MY_INFO "/proc/my_info"

int main()
{
    FILE* myfile = fopen(MY_INFO,"rb");
    
    while((char word = fgetc(myfile)) != EOF )
    {
        printf(“%c”,word);
        return 0;
    }
}
