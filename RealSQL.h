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
#include <stdlib.h>


typedef struct attributes{
    char * attr;
    struct attitubes * next;
}attributes;


attributes * attrInit(char * attr){
    attributes * a = malloc(sizeof(attributes));
    a->attr=attr;
    a->next=NULL;
    return a;
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
        printf("%s\t\t",attr->attr);
        attr=attr->next;
    }while(attr!=NULL);
    printf("\n");
};

typedef struct element{
    char * name;
    char * value;
    struct element * nextElement;
}element;

//a entity of data
typedef struct node{
    int hashId;
    struct element * head;
    struct node * nextNode;
    int properWidth;
    struct attributes * attributes;
    int dataLen;
    int readyToDeploy;
    //deployability
    //0: not able to deploy but able to add more
    //1: ready deploy
    //-1: additional data exceeded the limit, fail
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
        t->data[i]=NULL;
    }
    //printf("created\n");
    if(SQL->root==NULL){
        SQL->root=t;
    }else{
        Table * temp=SQL->root;
        while(SQL->root->nextTable!=NULL){
            SQL->root=SQL->root->nextTable;
        }
        SQL->root->nextTable=t;
        SQL->root=temp;
    }

    return 1;
};

void printSQLschema(RealSQL * SQL){
    Table * temp=SQL->root;
    do{
          printf("Name of the Table: %s\n",SQL->root->name);
          printAttributes(SQL->root->attributes);
          SQL->root=SQL->root->nextTable;
    }while(SQL->root!=NULL);
    SQL->root=temp;
};

//return the table given name as a string
Table * returnTable(RealSQL* SQL, char * name){
  Table* temp =SQL->root;
  while(temp!=NULL){
      if(strcmp(temp->name,name)==0){
          return temp;
      }
      temp=temp->nextTable;
  }
  return NULL;
};

int getWidthOfTable(Table * table){
    int result = 0;
    attributes * temp= table->attributes;
    while(temp!=NULL){
        result+=1;
        temp=temp->next;
    }
    return result;
}

node * nodeInit(Table * table){
    node * n = malloc(sizeof(node));
    n->head=NULL;
    n->hashId=NULL;
    n->nextNode=NULL;
    n->attributes=table->attributes;
    n->properWidth=getWidthOfTable(table);
    n->readyToDeploy=0;
    n->dataLen=0;
    return n;
};

int getHashid(char * firstVal){
   int result=0;
    for (int i =0; i< strlen(firstVal); i++){
        int num = firstVal[i]-'(';
        result+=num;
     //   printf("%d\n",result);
    }
   // printf("%d\n",result);
    int res= result%1009;
    return res;

//    if(table->hashLen==0){
//        return 0;
//    }else{
//        node * temp = table->data[0];
//        for(int i=0; i<table->hashLen; i++){
//            if(strcmp(temp->head->value,firstVal)==0){
//                return i;
//            }
//            temp =table->data[i+1];
//        }
//        table->hashLen+=1;
//        return table->hashLen;
//    }
//
};


void printNode(node * node){
    element * temp = node->head;
    while(temp!=NULL){
        printf("%s\t\t", temp->value);
        temp=temp->nextElement;
    }
    printf("\n");
}

void appendElement(node* node, char * data){
    element * e = malloc(sizeof(element));
    node->dataLen+=1;
    e->nextElement=NULL;
    e->value=data;
    e->name=NULL;
    //deployability
    //0: not able to deploy but able to add more
    //1: ready deploy
    //-1: additional data exceeded the limit, fail -> invalid input
    if(node->properWidth==node->dataLen){
        node->readyToDeploy=1;
    }else if(node->properWidth>node->dataLen){
        node->readyToDeploy=0;
    }else if(node->properWidth<node->dataLen){
        node->readyToDeploy=-1;
    }
   // printf("we are still good %d\n", node->readyToDeploy);
    if(node->hashId==NULL){
        node->hashId=getHashid(data);
    }

    if(node->readyToDeploy!=-1){
        attributes * temp1= node->attributes;
        for(int i=1; i< node->dataLen; i++){
            temp1=temp1->next;
        }
       //printNode(node);
        e->name=temp1->attr;
       // printf("%s\n",e->name);
        if(node->head==NULL){
            node->head=e;
        }else{
            element * temp =node->head;
            while(node->head->nextElement!=NULL){
                node->head=node->head->nextElement;
            }
            node->head->nextElement=e;
            node->head=temp;
        }
    }
   // printNode(node);
};


//return 0 if the same
//return 1 if different
int compareNodes(node * n1, node * n2){
    element * temp1= n1->head;
    element* temp2 = n2->head;
    while(temp1!=NULL){
        if(strcmp(temp1->value, temp2->value)!=0){
            return 1;
        }
        temp1=temp1->nextElement;
        temp2=temp2->nextElement;
    }
    return 0;
};


//insert into the table
//0: the table doesn't exist
//-1: improper data
//2: duplicate input
//1: insert successful
int insertIntoTable(RealSQL * SQL, char * tableName, node * data){
    if(tableExist(SQL,tableName)==1){
     //   printf("table exited");
        if(data->readyToDeploy!=1){
            return -1;
        }else{
            Table * temp = returnTable(SQL, tableName);
           // printf("%s", temp->name);
            int dataHash = data->hashId;
            if(temp->data[dataHash]==NULL){
              //  printf("%d", data->hashId);
                temp->data[data->hashId]=data;
            }else{
                node * tempNode= temp->data[data->hashId];
                while(temp->data[data->hashId]->nextNode!=NULL){
                    if(compareNodes(data, temp->data[data->hashId])==1){
                        temp->data[data->hashId]=temp->data[data->hashId]->nextNode;
                    }else{
                        //duplicate input
                        temp->data[data->hashId]=tempNode;
                        return 2;
                    }
                }
                temp->data[data->hashId]->nextNode=data;
                temp->data[data->hashId]=tempNode;
            }
        }

    }else{
        //the table doesn't exist
        return 0;
    }
};



void printTable(Table * table){
    printf("Name of the table: %s\n", table->name);
    printAttributes(table->attributes);
    for(int i=0; i<1009; i++){
        if(table->data[i]==NULL){
            continue;
        }else{
            node * temp = table->data[i];
            while(temp!=NULL){
                printNode(temp);
                temp=temp->nextNode;
            }
        }
    }
}

