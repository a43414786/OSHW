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

int main()
{
     
    FILE* myfile = fopen(MY_INFO,"rb");
    
    while((char word = fgetc(myfile)) != EOF )
    {
        printf(“%c”,word);
        return 0;
    }
}
