//
// Created by Andy on 11/22/2018.
//

#ifndef UNTITLED_REALSQL_H
#define UNTITLED_REALSQL_H

#endif //UNTITLED_REALSQL_H

typedef struct element{
    char name[50];
    char value[50];
    struct element * nextElement;
}element;

//a entity of data
typedef struct node{
    int hashId;
    struct element head;
    struct node * nextNode;
}node;

typedef struct Table{
    char name[50];
    //array of strings
    char attributs[50][50];
    node * data[1009];
}Table;