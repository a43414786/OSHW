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
    Makeinfolist();
    return 0;
}
