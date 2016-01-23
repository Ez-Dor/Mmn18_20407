#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "rb_tree.h"

#define FIRST_ARGUMENT 1
#define SECOND_ARGUMENT 2
#define THIRD_ARGUMENT 3
#define FOURTH_ARGUMENT 4
#define FIFTH_ARGUMENT 5
#define SIXTH_ARGUMENT 6
#define SKIP_ON_FIRST_LINE 25

/*Global variable for the nil[T]*/
node *nilT;

int main(int argc, char *argv[])
{
    /*Variables*/
    int accountID, cash, i, id, lineNumbers;
    char **name;
    char temp[30];
    node *accountIDTreeRoot, *balanceTreeRoot;
    FILE *fp = fopen("input.txt", "r");
    if(!fp)
    {
        printf("Input file is missing please configure your working directory\n");
        exit(0);
    }
    if(argc == 1)
    {
        printf("Please insert command");
        return 0;
    }
    /*Initiate the global nil[T]*/
    initNilT();
    /*Create roots for the to RB-Trees one order by the account number and the second by the balance*/
    accountIDTreeRoot = nilT;
    balanceTreeRoot = nilT;
    accountIDTreeRoot->parent = nilT;
    accountIDTreeRoot->left = nilT;
    accountIDTreeRoot->right = nilT;
    balanceTreeRoot->parent = nilT;
    balanceTreeRoot->left = nilT;
    balanceTreeRoot->right = nilT;

    /*Reading from the input file - initiate the program with clients the init input can be edit from the
     * input.txt file (attached) - in each edit make sure the first line is like before*/
    lineNumbers = lineCounter(fp);
    /*Allocate memory for the names from the input file*/
    name = (char **) calloc(lineNumbers, sizeof(char *));
    if(!name)
    {
        printf("Memory allocation failed");
        exit(0);
    }
    /*Going back to the beginning of the file*/
    fseek(fp, SKIP_ON_FIRST_LINE, SEEK_SET);
    /*Collect the input*/
    for(i = 0; i < lineNumbers; i++)
    {
        name[i] = (char *) malloc(sizeof(char) * 30);
        if(!name[i])
        {
            printf("Memory allocation failed");
            exit(0);
        }
        fscanf(fp, "%i %i %i %s", &accountID, &id, &cash, name[i]);
        /*Insert the client to the RB-Trees (both)*/
        insertByID(&accountIDTreeRoot, accountID, id, cash, name[i]);
        insertByBalance(&balanceTreeRoot, accountID, id, cash, name[i]);
    }
    fclose(fp);
    /*Check if it's a query and assign to the relevant function*/
    if(!strcmp(argv[FIRST_ARGUMENT], "?"))
    {
        if(!strcmp(argv[SECOND_ARGUMENT], "MAX"))
            theRicher(&balanceTreeRoot);
        else if(!strcmp(argv[SECOND_ARGUMENT], "MINUS"))
            showDebtors(balanceTreeRoot);
        else
            showClientBalance(&accountIDTreeRoot, atoi(argv[SECOND_ARGUMENT]));
    }
        /*New client*/
    else if(!strcmp(argv[FIRST_ARGUMENT], "+"))
    {
        strcpy(temp, argv[SECOND_ARGUMENT]);
        strcat(temp, " ");
        strcat(temp, argv[THIRD_ARGUMENT]);
        addNewClient(&accountIDTreeRoot, &balanceTreeRoot, atoi(argv[FIFTH_ARGUMENT]), atoi(argv[FOURTH_ARGUMENT]),
                     atoi(argv[SIXTH_ARGUMENT]), temp);
    }
        /*Delete client*/
    else if(!strcmp(argv[FIRST_ARGUMENT], "-"))
    {
        deleteClient(&accountIDTreeRoot, &balanceTreeRoot, atoi(argv[SECOND_ARGUMENT]));
    }
        /*Update balance*/
    else
        updateBalance(&accountIDTreeRoot, &balanceTreeRoot, atoi(argv[THIRD_ARGUMENT]), atoi(argv[FOURTH_ARGUMENT]));

    /*C mange memory*/
    for(i = 0; i < lineNumbers; i++)
    {
        free(name[i]);
    }
    free(name);
    freeRBTree(balanceTreeRoot);
    freeRBTree(accountIDTreeRoot);
    free(nilT);
    return 0;
}

/*Initiate the nil[T] with the relevant values*/
void initNilT()
{
    nilT = (node *) calloc(ONE_NODE, sizeof(node));
    if(!nilT)
    {
        printf("Memory allocation failed");
        exit(0);
    }
    nilT->parent = NULL;
    nilT->left = NULL;
    nilT->right = NULL;
    nilT->color = BLACK;
}


/*If client update his balance we should change it in the balance tree and the account tree*/
int updateBalance(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int balanceChange)
{
    node *x = searchByID(*accountIDTreeRoot, accountID);
    if(x == nilT)
    {
        printf("Account number incorrect");
        exit(0);
    }
    deleteByBalance(balanceTreeRoot, x->accountID, x->balance);
    x->balance = x->balance + balanceChange;
    insertByBalance(balanceTreeRoot, x->accountID, x->ID, x->balance, x->name);
    printf("Dear %s your correct balance is: %i\n", x->name, x->balance);
    return x->balance;
}

/*Add new client to the RB-Trees (both)*/
void addNewClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int ID, int balance, char *name)
{
    insertByID(accountIDTreeRoot, accountID, ID, balance, name);
    insertByBalance(balanceTreeRoot, accountID, ID, balance, name);
    printf("Congratulations %s :) your account number is: %i and your balance: %i\n", name, accountID, balance);
}

/*Delete client from the RB-Trees (both)*/
void deleteClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID)
{
    node *x = searchByID(*accountIDTreeRoot, accountID);
    char name[30];
    strcpy(name, x->name);
    if(x->balance == 0)
    {
        deleteByBalance(balanceTreeRoot, x->accountID, x->balance);
        deleteByID(accountIDTreeRoot, x->accountID);
        printf("The client %s left us :( his account number was %i RIP\n", name, accountID);
    }
    else
        printf("The program cannot delete %s because his balance is %i please take care of it and try again\n", x->name,
               x->balance);
}

/*Print the user balance for the query*/
void showClientBalance(node **accountIDTreeRoot, int accountID)
{
    node *x = searchByID(*accountIDTreeRoot, accountID);
    printf("Hey %s your balance is: %i i hope you glad\n", x->name, x->balance);
}

/*For the MAX query print the user with the higher balance*/
void theRicher(node **balanceTreeRoot)
{
    node *x = (*balanceTreeRoot);
    while(x->right != nilT)
        x = x->right;
    printf("Wow!! the richer is %s with account number %i and his balance %i\n", x->name, x->accountID, x->balance);
}

/*For MINUS query show all the debtors*/
void showDebtors(node *x)
{
    if(x == nilT)
        return;
    showDebtors(x->left);
    if(x->balance < 0)
    {
        printf("Account number: %i Name: %s Balance: %i\n", x->accountID, x->name, x->balance);
        showDebtors(x->right);
    }
}

/*Return the number line in the file*/
int lineCounter(FILE *file)
{
    int counter = 0;
    char c;
    /*Going back to beginning of the file*/
    fseek(file, SKIP_ON_FIRST_LINE, SEEK_SET);
    /*Check if have 1 line at least */
    if(fgetc(file) != EOF)
        counter++;

    while((c = fgetc(file)) != EOF)
    {
        if(c == '\n')
            counter++;
    }
    /*return number lines */
    return counter;
}
