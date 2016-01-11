
#ifndef MMN18_20407_DATABASE_H
#define MMN18_20407_DATABASE_H

#endif //MMN18_20407_DATABASE_H
#define RED 'r'
#define BLACK 'b'

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

void LeftRotate(node **root,node *x);
void insertFixUp(node **root,node *z);
void insert(node **root, int accountID,int ID, int cash, char* name);
void inorder(node *root);