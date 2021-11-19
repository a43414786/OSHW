#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct msg{
    char key[101];
    char value[101];
};
int decode(char*input,struct msg* smsg){
    printf("%s",input);
    char cmd[7],key[101],value[101];
    int counter = 0;
    int cmdc = 0,kc = 0,vc = 0;
    for(int i = 0 ; i < strlen(input);i++){
        if(input[i] == ' '){
            counter += 1;
            cmd[cmdc] = '\0';
            break;
        }else{
            printf("%c",input[i]);
            cmd[cmdc++] = input[i];
            counter++;
        }
    }
    for(int i = counter ; i < strlen(input);i++){
        if(input[i] == ' '){
            counter += 1;
            key[kc] = '\0';
            break;
        }else{
            printf("%c",input[i]);
            key[kc++] = input[i];
            counter++;
        }
    }
    for(int i = counter ; i < strlen(input);i++){
        if(input[i] == '\0'){
            counter += 1;
            value[vc] = '\0';
            break;
        }else{
            printf("%c",input[i]);
            value[vc++] = input[i];
            counter++;
        }
    }

    printf("%s\n%s\n%s\n",cmd,key,value);
}
int main(){
    
    struct msg smsg,rmsg;
    char cmd[10];
    char key[101];
    char value[101];
    scanf("\n%s %s %s",cmd,key,value);
    printf("%s\n%s\n%s\n",cmd,key,value);
    return 0;
}