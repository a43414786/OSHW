#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
    char name[100];
    int frame;
    struct node*next;
}typedef Node;

Node*cnode(char*name,int frame){
    Node*temp = malloc(sizeof(Node));
    memset(temp,0,sizeof(Node));
    strcpy(temp->name,name);
    temp->frame = frame;
    temp->next = NULL;
    return temp;
}

void addnode(Node**root,char*name,int frame){
    Node*temp = *root;
    if(!temp){
        *root = cnode(name,frame);
    }else{
        while(temp->next){
            temp = temp->next;
        }
        temp->next = cnode(name,frame);
    }
}

void pr_info(Node*root){
    while(root){
        printf("%s %d\n",root->name,root->frame);
        root = root->next;
    }
}

Node* get_trace(){
    FILE*trace = fopen("trace.txt", "r");
    char word;
    char name[10];
    char frame[10];
    int namecount = 0;
    int framecount = 0;
    int flag1 = 0;
    int flag2 = 0;
    Node*root = NULL;
    memset(name, 0, sizeof(name));
    while(word = getc(trace)){
        if(word == '\n' || word == EOF){
            addnode(&root,name,atoi(frame));
            namecount = 0;
            framecount = 0;
            memset(name, 0, sizeof(name));
            memset(frame, 0, sizeof(frame));
            if(word == EOF){
                break;
            }
            continue;
        }
        if(word == '('){
            flag1 = !flag1;
            continue;
        }
        if(word == ','){
            flag1 = !flag1;
            flag2 = !flag2;
            continue;
        }
        if(word == ')'){
            flag2 = !flag2;
            continue;
        }
        if(flag1){
            name[namecount++] = word;
        }
        if(flag2){
            frame[framecount++] = word;
        }
    }
    return root;
}

void get_sys_config(char*TLB_policy,char*page_policy,char*frame_policy,int*process_num,int*vir_num,int*phy_num){
    FILE*sys_config = fopen("sys_config.txt", "r");
    char word;
    int flag = 0;
    int counter = 0;
    int counter2 = 0;
    char input[10];
    memset(input, 0, sizeof(input));
    
    while(word = getc(sys_config)){
        if(word == ':'){
            flag = !flag;
            continue;
        }
        if(word == '\n' || word == EOF){
            flag = !flag;

            switch(counter2){
                case 0:
                    strcpy(TLB_policy,input);
                    counter2++;
                    break;
                case 1:
                    strcpy(page_policy,input);
                    counter2++;
                    break;
                case 2:
                    strcpy(frame_policy,input);
                    counter2++;
                    break;
                case 3:
                    *process_num = atoi(input);
                    counter2++;
                    break;
                case 4:
                    *vir_num = atoi(input);
                    counter2++;
                    break;
                case 5:
                    *phy_num = atoi(input);
                    counter2++;
                    break;
                default:
                    break;
            }
            
            counter = 0;
            memset(input,0,sizeof(input));
            if(word == EOF){
                return;
            }
            continue;
        }
        if(flag){ 
            
            if(word == ' '){
                continue;
            }
            input[counter++] = word;

        }
        
    }
}

int main(){
    char TLB_policy[10];
    char page_policy[10];
    char frame_policy[10];
    int process_num = 0;
    int vir_num = 0;
    int phy_num = 0;
    int TLB[32][3];
    memset(TLB,0,sizeof(TLB));
    get_sys_config(TLB_policy,page_policy,frame_policy,&process_num,&vir_num,&phy_num);
    int vir_page[vir_num][2];
    int phy_frame[phy_num];
    
    Node*root = get_trace();
    //pr_info(root);
    printf("%s\n%s\n%s\n%d\n%d\n%d\n",
    TLB_policy,
    page_policy,
    frame_policy,
    process_num,
    vir_num,
    phy_num);
    return 0;
    
}