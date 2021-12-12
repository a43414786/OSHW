#include <stdio.h>

int main(){
    int the_num;

    int min = 65400;
    int max = 65410;

    while(1)
    {
        srand(time(NULL));
        the_num = rand() % (max - min + 1) + min;
        if(the_num == 65409)
        {
            fprintf(stdout,"I found 65409.\n");
            fflush(stdout);
            min = 0;
            max = 0;
        }
    }
    return 0;
}