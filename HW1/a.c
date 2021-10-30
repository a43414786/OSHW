#include <stdio.h>
#include <stdlib.h>

#define MY_INFO "/proc/my_info"

typedef struct node* nodeptr;

struct node
{
    char c;
    nodeptr next;
};
nodeptr createnode(char c)
{
    nodeptr temp = malloc(sizeof(nodeptr));
    temp->c = c;
    temp->next = NULL;
    return temp;
}
void addnode(nodeptr *root,char c)
{
    nodeptr temp = *root;
    if(temp != NULL)
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = createnode(c);
    }
    else
    {
        *root = createnode(c);
    }
}

void print_info(nodeptr root)
{

    while(root)
    {

        printf("%c",root->c);
        root = root->next;

    }

}


void print_device_info(nodeptr all,nodeptr *ptrs,char input)
{   
    char word;
    FILE* myfile1 = fopen("/proc/meminfo","rb");
    while((word = fgetc(myfile1)) != EOF){
    	printf("%c",word);
    }
    printf("\n\n");
    fclose(myfile1);
    
    switch(input)
    {
    case 'v':
        printf("Version: ");
        print_info(ptrs[0]);
        break;
    case 'c':
        printf("CPU information:\n");
        print_info(ptrs[1]);
        break;
    case 'm':
        printf("Memory information:\n");
        print_info(ptrs[2]);
        break;
    case 't':
        printf("Time information:\n");
        print_info(ptrs[3]);
        break;
    case 'a':
        print_info(all);
        break;
    default:
        break;
    }

    
}

void Makeinfolist(char input){
    
    char word;
    short flag1 = 0,flag2 = 0;
    nodeptr all = NULL,ptrs[4] = {NULL,NULL,NULL,NULL},temp = NULL;
    int counter = -1;
    FILE* myfile = fopen(MY_INFO,"rb");
    
    while((word = fgetc(myfile)) != EOF )
    {
        addnode(&all,word);
        if(word == '=')
        {
            flag1 = 1;
            flag2 = 0;
        }
        if(flag2)
        {
            addnode(&ptrs[counter],word);
        }
        if(flag1)
        {

            if(word == '\n')
            {

                if(counter >= 0)
                {

                    for(int i = 0 ; i < 65 ; i++)
                    {

                        addnode(&ptrs[counter],'-');

                    }

                    addnode(&ptrs[counter],'\n');
                    addnode(&ptrs[counter],'\n');

                }
                counter++;
                flag1 = 0;
                flag2 = 1;
            }
        }

    }
    addnode(&all,'\n');
    addnode(&ptrs[counter],'\n');
    for(int i = 0 ; i < 65 ; i++)
    {
        addnode(&all,'-');
        addnode(&ptrs[counter],'-');

    }
    addnode(&all,'\n');
    addnode(&all,'\n');
    addnode(&ptrs[counter],'\n');
    addnode(&ptrs[counter],'\n');
    fclose(myfile);
    print_device_info(all,ptrs,input);
    while(all){
        temp = all->next;
        free(all);
        all = temp;
    }
    for(int i = 0 ; i < 4 ; i++){
        while(ptrs[i]){
            temp = ptrs[i]->next;
            free(ptrs[i]);
            ptrs[i] = temp;
        } 
    }
}

int main()
{
    char input = ' ';
    nodeptr all = NULL,verinfo = NULL,cpuinfo = NULL,meminfo = NULL,timeinfo = NULL;
    while(input != 'e')
    {
        printf("Which information do you want?\nVersion(v),CPU(c),Memory(m),Time(t),All(a),Exit(e)?\n");
        scanf("\n%c",&input);
        Makeinfolist(input);
        
    }
    
    return 0;
}

