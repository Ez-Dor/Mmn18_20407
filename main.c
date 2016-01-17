#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "dataBase.h"

node *nilT;

int main(int argc, char* argv[])
{
    initNilT();
    initRandom();
    int accountID[10];
    int cash;
    int i;
    node *accountIDTreeRoot = nilT, *balanceTreeRoot = nilT;
    node *x;
    accountIDTreeRoot->parent = nilT;
    accountIDTreeRoot->left = nilT;
    accountIDTreeRoot->right = nilT;
    balanceTreeRoot->parent = nilT;
    balanceTreeRoot->left = nilT;
    balanceTreeRoot->right = nilT;
    char *name[10] = {"avi", "noam", "lo", "po", "you", "mani", "moyo", "dpo", "non", "cipo"};

    for(i = 0; i < 10; i++)
    {
        accountID[i] = randomNumber(1000000, 9999999);
        cash = randomNumber(-5000, 5000);
        addNewClient(&accountIDTreeRoot,&balanceTreeRoot,accountID[i],i,cash,name[i]);
    }
    theRicher(&balanceTreeRoot);
    inorderByID(accountIDTreeRoot);
    printf("\n");
    printf("MINUS:\n");
    showDebtors(balanceTreeRoot);
    printf("\n");
    updateBalance(&accountIDTreeRoot,&balanceTreeRoot, accountID[5], -348);
    showClientBalance(&accountIDTreeRoot,accountID[5]);

    for(i = 0; i < 10; i++)
    {
        x =searchByID(accountIDTreeRoot, accountID[i]);
        updateBalance(&accountIDTreeRoot,&balanceTreeRoot, x->accountID, (-1)*x->balance);
        deleteClient(&accountIDTreeRoot,&balanceTreeRoot,accountID[i]);
    }


    return 0;
}

void initNilT()
{
    nilT = (node *) calloc(ONE_NODE, sizeof(node));
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
    return (rand() % max) + min;
}

/*If client update his balance we should change it in the balance tree and the account tree*/
int updateBalance(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int balanceChange)
{
    node *x = searchByID(*accountIDTreeRoot, accountID);
    node *y;
    deleteByBalance(balanceTreeRoot, x->accountID, x->balance);
    x->balance = x->balance + balanceChange;
    insertByBalance(balanceTreeRoot, x->accountID, x->ID, x->balance, x->name);
    printf("Dear %s your correct balance is: %i\n",x->name, x->balance);
    return x->balance;
}

void addNewClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int ID, int balance, char *name)
{
    insertByID(accountIDTreeRoot, accountID, ID, balance, name);
    insertByBalance(balanceTreeRoot, accountID, ID, balance, name);
    printf("Congratulations %s :) your account number is: %i and your balance: %i\n", name, accountID, balance);
}

void deleteClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID)
{
    node *x = searchByID(*accountIDTreeRoot, accountID);
    if(x->balance == 0)
    {
        deleteByBalance(balanceTreeRoot, x->accountID, x->balance);
        deleteByID(accountIDTreeRoot, x->accountID);
        printf("The client %s left us :( his account number was %i RIP\n", x->name, x->accountID);
    }
    else
        printf("The program cannot delete %s because his balance is %i please take care of it and try again\n",x->name,x->balance);
}

void showClientBalance(node **accountIDTreeRoot, int accountID)
{
    node *x = searchByID(*accountIDTreeRoot, accountID);
    printf("Hey %s your balance is: %i i hope you glad\n",x->name, x->balance);
}

void theRicher(node **balanceTreeRoot)
{
    node *x = (*balanceTreeRoot);
    while(x->right != nilT)
        x = x->right;
    printf("Wow!! the richer is %s with account number %i and his balance %i\n",x->name, x->accountID, x->balance);
}

void showDebtors (node *x)
{
        if(x == nilT)
            return;
        showDebtors(x->left);
        if(x->balance < 0)
        {
            printf("Account number: %i Name: %s Balance: %i\n",x->accountID,x->name, x->balance);
            showDebtors(x->right);
        }
}
