#ifndef MMN18_20407_DATABASE_H
#define MMN18_20407_DATABASE_H

#endif
/*Constants*/
#define RED 'r'
#define BLACK 'b'
#define ONE_NODE 1

/*A Red-Black tree node structure*/
typedef struct node
{
    int accountID;
    char color;
    int ID;
    int balance;
    char *name;
    /*links for left, right children and parent*/
    struct node *left, *right, *parent;
} node;

/*Functions prototype*/

/*RB-Tress functions*/
void leftRotate(node **root, node *x);

void insertFixUp(node **root, node *z);

void insertByID(node **root, int accountID, int ID, int balance, char *name);

void insertByBalance(node **root, int accountID, int ID, int balance, char *name);

void inorderByID(node *root);

struct node *searchByID(node *x, int accountID);

struct node *searchByBalance(node *x, int accountID, int balance);

struct node *successor(node *x);

void deleteByID(node **root, int accountID);

void deleteByBalance(node **root, int accountID, int balance);

void deleteFixup(node **root, node *x);

/*Bank program functions*/
void showDebtors(node *x);

void theRicher(node **balanceTreeRoot);

void showClientBalance(node **accountIDTreeRoot, int accountID);

void deleteClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID);

void addNewClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int ID, int balance, char *name);

int updateBalance(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int balanceChange);

/*Other functions*/
void initNilT();

int lineCounter(FILE *file);

void freeRBTree(node *root);
