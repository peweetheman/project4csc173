//
// Created by Andy on 11/22/2018.
//

#ifndef UNTITLED_REALSQL_H
#define UNTITLED_REALSQL_H

#endif //UNTITLED_REALSQL_H
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


typedef struct attributes{
    char * attr;
    struct attitubes * next;
}attributes;


attributes * attrInit(char * attr){
    attributes * a = malloc(sizeof(attributes));
    a->attr=attr;
    a->next=NULL;
}

void appendAttribute(attributes * head, char * attr){
  //  attributes * temp = head;
    while(head->next!=NULL){
        head=head->next;
    }
    attributes * data = attrInit(attr);
    head->next=data;
};

void printAttributes(attributes * attr){
    do{
        printf("%s  ",attr->attr);
        attr=attr->next;
    }while(attr!=NULL);
    printf("\n");
};

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
    char * name;
    //array of strings
    struct attributes * attributes;
    node * data[1009];
    struct Table * nextTable;
}Table;

typedef struct RealSQL{
    Table * root;
}RealSQL;


//initialize the SQL
RealSQL * sqlinit(){
    RealSQL * s = malloc(sizeof(RealSQL));
    //load the data
    s->root=NULL;
    return s;
}

bool tableExist(RealSQL * SQL, char * name) {

    if (SQL->root == NULL) {
        return 0;
    } else {
        Table *temp = SQL->root;
         do{
            if (strcmp(name, temp->name) == 0) {
                return 1;
            }
            temp = temp->nextTable;
        }while (temp != NULL);
         return 0;
        //   temp->nextTable=t;
    }
};
//create table
bool createTable(RealSQL * SQL, char * name, attributes * attributes){
    if(tableExist(SQL,name)==1){
        printf("Existed");
        return 0;
    }
    Table * t = malloc(sizeof(Table));
    t->name=name;
    t->attributes=attributes;
    t->nextTable=NULL;
    for (int i = 0; i < 1009; i++) {
        t->data[i]=malloc(sizeof(node));
    }
    printf("created\n");
    if(SQL->root==NULL){
        SQL->root=t;
    }else{
       // Table * temp=SQL->root;
        while(SQL->root->nextTable!=NULL){
            SQL->root=SQL->root->nextTable;
        }
        SQL->root->nextTable=t;
        printf("done\n");
    }

    return 1;
};



//insert into the table
bool insertIntoTable(RealSQL * SQL, char * tableName, node * data){

};