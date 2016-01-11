#include <stdio.h>
#include <stdlib.h>
#include "dataBase.h"

/*A Red-Black tree node structure*/


/*Left Rotation*/
void LeftRotate(node **root,node *x)
{
    /*y stored pointer of right child of x*/
    node *y = x->right;

    /*store y's left subtree's pointer as x's right child*/
    x->right = y->left;

    /*update parent pointer of x's right*/
    if (y->left != NULL)
        y->left->parent = x;

    /*update y's parent pointer*/
    y->parent = x->parent;

    /*if x's parent is null make y as root of tree*/
    if (x->parent == NULL)
        (*root) = y;

        /*store y at the place of x*/
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    /*make x as left child of y*/
    y->left = x;

    /*update parent pointer of x*/
    x->parent = y;
}


/*Right Rotation (Similar to LeftRotate)*/
void rightRotate(node **root,node *x)
{
    node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        (*root) = y;
    else if (x == x->parent->right)
        x->parent->right= y;
    else x->parent->left= y;
    y->right = x;
    x->parent = y;
}

/*Utility function to fixup the Red-Black tree after standard BST insertion*/
void insertFixUp(node **root,node *z)
{
    /*iterate until z is not the root and z's parent color is red*/
    while (z != *root && z->parent->color == RED)
    {
        node *y;

        /*Find uncle and store uncle in y*/
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;

        /*If uncle is RED, do following*/
        /*(i) Change color of parent and uncle as BLACK*/
        /*(ii) Change color of grandparent as RED*/
        /*(iii) Move z to grandparent*/
        if (y->color == RED)
        {
            y->color = BLACK;
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent;
        }

            /*Uncle is BLACK, there are four cases (LL, LR, RL and RR)*/
        else
        {
            // Left-Left (LL) case, do following
            // (i) Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent);
            }

            // Left-Right (LR) case, do following
            // (i) Swap color of current node and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent);
                rightRotate(root,z->parent->parent);
            }

            // Right-Right (RR) case, do following
            // (i) Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            if (z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent->parent);
            }

            // Right-Left (RL) case, do following
            // (i) Swap color of current node and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            if (z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent);
                LeftRotate(root,z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK; //keep root always black
}

// Utility function to insert newly node in RedBlack tree
void insert(node **root, int accountID,int ID, int cash, char* name)
{
    // Allocate memory for new node
    node *z = (node*)malloc(sizeof(node));
    z->accountID = accountID;
    z->name = name;
    z->ID = ID;
    z->cash = cash;
    z->left = z->right = z->parent = NULL;

    //if root is null make z as root
    if (*root == NULL)
    {
        z->color = BLACK;
        (*root) = z;
    }
    else
    {
        node *y = NULL;
        node *x = (*root);

        // Follow standard BST insert steps to first insert the node
        while (x != NULL)
        {
            y = x;
            if (z->accountID < x->accountID)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == NULL)
            (*root) = z;
        else if (z->accountID < y->accountID)
            y->left = z;
        else
            y->right = z;
        z->color = RED;

        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixUp(root,z);
    }
}

// A utility function to traverse Red-Black tree in inorder fashion
void inorder(node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->accountID);
    inorder(root->right);
}