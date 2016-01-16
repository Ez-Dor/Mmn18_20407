#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "dataBase.h"

node *nilT;

int main()
{
    initNilT();
    initRandom();
    int accountID[10];
    int cash;
    int i;
    node *root = nilT;
    root->parent = nilT;
    root->left = nilT;
    root->right = nilT;
    for(i=0;i<10;i++)
    {
        accountID[i] = randomNumber(0,100);
        cash = randomNumber(-500,500);
        insert(&root,accountID[i],i,cash,'avi');
        printf("%i inorder Traversal Is : ",accountID[i]);
        inorder(root);
        printf("\n");
    }
    for(i=0;i<10;i++)
    {
        delete(&root,accountID[i]);
        printf("%i deleted, inorder after delete : ",accountID[i]);
        inorder(root);
        printf("\n");
    }

    return 0;
}

void initNilT()
{
    nilT = (node*)calloc(ONE_NODE, sizeof(node));
    nilT->parent = NULL;
    nilT->left = NULL;
    nilT->right = NULL;
    nilT->color = BLACK;
}

void initRandom()
{
    srand(time(NULL));
}

/*The function give us an random number in a range*/
int randomNumber(int min, int max)
{
    max -= min;
    return (rand()% max)+min;
}
