#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct msg{
    char key[101];
    char value[101];
};
int decode(char*input,(struct msg*)smsg){
    char cmd[7],key[101],value[101];
    int counter = 0;
    int cmdc = 0,kc = 0,vc = 0
    for(int i = 0 ; i < strlen(input),i++){
        if(input[i] == ' '){
            counter += 2;
            break
        }else{
            cmd[cmdc++] = input[i];
            counter++;
        }
    }
    for(int i = counter ; i < strlen(input),i++){
        if(input[i] == ' '){
            counter += 2;
            break
        }else{
            key[kc++] = input[i];
            counter++;
        }
    }
    for(int i = counter ; i < strlen(input),i++){
        if(input[i] == ' '){
            counter += 2;
            break
        }else{
            value[vc++] = input[i];
            counter++;
        }
    }

    print("%s\n%s\n%s\n",cmd,key,value);
}
int main(){
    
    struct msg smsg,rmsg;
    char input[300];
    scanf("%s",input);
    decode(input,&smsg);
    return 0;
}