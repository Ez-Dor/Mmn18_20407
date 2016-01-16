
#ifndef MMN18_20407_DATABASE_H
#define MMN18_20407_DATABASE_H

#endif //MMN18_20407_DATABASE_H
#define RED 'r'
#define BLACK 'b'
#define ONE_NODE 1

/*A Red-Black tree node structure*/
typedef struct node
{
    int accountID;	 // for accountID part
    char color; // for color property
    int ID;
    int cash;
    char* name;
    /*links for left, right children and parent*/
    struct node *left, *right, *parent;
}node;

void initNilT();
void leftRotate(node **root,node *x);
void insertFixUp(node **root,node *z);
void insert(node **root, int accountID, int ID, int cash, char* name);
void inorder(node *root);
struct node* search(node *x, int accountID);
struct node* successor(node *x);
void delete(node **root, int accountID);
void deleteFixup(node **root, node *x);
void initRandom();
int randomNumber(int min, int max);
