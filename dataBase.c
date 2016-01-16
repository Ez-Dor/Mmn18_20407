#include <stdio.h>
#include <stdlib.h>
#include <tkDecls.h>
#include "dataBase.h"

/*A Red-Black tree node structure*/


/*Left Rotation*/
void leftRotate(node **root, node *x)
{
    /*y stored pointer of right child of x*/
    node *y = x->right;

    /*store y's left subtree's pointer as x's right child*/
    x->right = y->left;

    /*update parent pointer of x's right*/
    if(y->left != NULL)
        y->left->parent = x;

    /*update y's parent pointer*/
    y->parent = x->parent;

    /*if x's parent is null make y as root of tree*/
    if(x->parent == NULL)
        (*root) = y;

        /*store y at the place of x*/
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    /*make x as left child of y*/
    y->left = x;

    /*update parent pointer of x*/
    x->parent = y;
}


/*Right Rotation (Similar to LeftRotate)*/
void rightRotate(node **root, node *x)
{
    node *y = x->left;
    x->left = y->right;
    if(y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL)
        (*root) = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

/*Utility function to fixup the Red-Black tree after standard BST insertion*/
void insertFixUp(node **root, node *z)
{
    /*iterate until z is not the root and z's parent color is red*/
    while(z != *root && z->parent->color == RED)
    {
        node *y;

        /*Find uncle and store uncle in y*/
        if(z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            /*Case 1*/
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
                /*Case 2*/
            else if(z == z->parent->right)
            {
                z = z->parent;
                leftRotate(root, z);
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
                /*Case 3*/
            else
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            /*Case 1*/
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
                /*Case 2*/
            else if(z == z->parent->right)
            {
                z = z->parent;
                leftRotate(root, z);
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
                /*Case 3*/
            else
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK; //keep root always black
}

// Utility function to insert newly node in RedBlack tree
void insert(node **root, int accountID, int ID, int cash, char *name)
{
    // Allocate memory for new node
    node *z = (node *) malloc(sizeof(node));
    z->accountID = accountID;
    z->name = name;
    z->ID = ID;
    z->cash = cash;
    z->left = z->right = z->parent = NULL;

    //if root is null make z as root
    if(*root == NULL)
    {
        z->color = BLACK;
        (*root) = z;
    }
    else
    {
        node *y = NULL;
        node *x = (*root);

        // Follow standard BST insert steps to first insert the node
        while(x != NULL)
        {
            y = x;
            if(z->accountID < x->accountID)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if(y == NULL)
            (*root) = z;
        else if(z->accountID < y->accountID)
            y->left = z;
        else
            y->right = z;
        z->color = RED;

        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixUp(root, z);
    }
}

struct node* search(node *x, int accountID)
{
    while(x!=NULL)
    {
        if(accountID < x->accountID)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

struct node* successor(node* x)
{
    node* y;
    if(x->right != NULL)
    {
        x = x->right;
        while(x->left != NULL)
            x = x->left;
        return x;
    }
    y = x->parent;
    while(y != NULL && x == y->right)
    {
        x=y;
        y = y->parent;
    }
    return y;
}

void delete(node **root, int accountID)
{
    node *z = search(*root,accountID);
    node *x,*y;
    if(z->left == NULL || z->right == NULL)
        y=z;
    else
        y = successor(z);
    if(y->left != NULL)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if(y->parent == NULL)
        *root = x;
    else if(y==y->parent->left)
        y->parent->left =x;
    else
        y->parent->right = x;
    if(y!=z)
    {
        z->accountID = y->accountID;
        z->name = y->name;
        z->ID = y->ID;
        z->cash = y->cash;
    }
    if(y->color == BLACK)
        deleteFixup(root,x);
    return y;
}

void deleteFixup(node **root,node *x)
{
    while(x!=*root && x->color =BLACK)
    {
        if(x == x->parent->left)
            /********To be continue**********/
    }
}

// A utility function to traverse Red-Black tree in inorder fashion
void inorder(node *root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->accountID);
    inorder(root->right);
}