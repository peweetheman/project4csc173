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
    struct attributes * next;
}attributes;


attributes * attrInit(char *);

void appendAttribute(attributes * head, char * attr){
    //  attributes * temp = head;
    while(head->next!=NULL){
        head=head->next;
    }
    attributes * data = attrInit(attr);
    head->next=data;
};

attributes * InternalattrInit(){
    attributes * a = malloc(sizeof(attributes));
    a->attr=NULL;
    a->next=NULL;
    return a;
};

attributes * InternalappendAttributes(attributes * head, char * attr){
    if(head->attr==NULL){
        head->attr=attr;
    }else{
        appendAttribute(head, attr);
    }
};

attributes * attrInit(char * attr){
    attributes * a = malloc(sizeof(attributes));
    a->attr=attr;
    a->next=NULL;
    return a;
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
    attributes * attributes;
    node * data[1009];
    struct Table * nextTable;
}Table;

typedef struct RealSQL{
    Table * root;
}RealSQL;


typedef struct conditionsRoot{
    attributes * attr;
    struct conditions * args;
}conditionsRoot;

typedef struct conditions{
    char * attr;
    char * value;
    char * condToPrevious;
    struct conditions * Nextargs;
    struct conditions * Lowerargs;
}conditions;

conditions * conditionsInit(char * attr, char * value, char * condToPre){
    conditions * cond = malloc(sizeof(conditions));
    cond->attr=attr;
    cond->value=value;
    cond->condToPrevious=condToPre;
    cond->Nextargs=NULL;
    cond->Lowerargs=NULL;
    return cond;
};

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

void printSQLtables(RealSQL * SQL){
    Table * temp=SQL->root;
    do{
        printf("Name of the Table: %s\n",SQL->root->name);
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

bool nodeExisted(Table * table, node* n){
    node * t= table->data[n->hashId];
    while(t!=NULL){
        if(compareNodes(t, n)==1){
            t=t->nextNode;
        }else if(compareNodes(t, n)==0){
            return 1;
        }
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
            printf("Improper data\n");
            return -1;
        }else{
            Table * temp = returnTable(SQL, tableName);
            // printf("%s", temp->name);
            int dataHash = data->hashId;
            if(temp->data[dataHash]==NULL){
                temp->data[data->hashId]=data;
            }else{
                if(nodeExisted(temp, data)==1){
                    printf("duplicated entry\n");
                    return 2;
                }
                node * tempNode= temp->data[data->hashId];
                while(temp->data[data->hashId]->nextNode!=NULL){
                    temp->data[data->hashId]=temp->data[data->hashId]->nextNode;
                }
                temp->data[data->hashId]->nextNode=data;
                temp->data[data->hashId]=tempNode;
            }
            return 1;
        }

    }else{
        printf("the table doesn't exist\n");
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

//Table * selectHelper(RealSQL * SQL,char * tableName, attributes * attributes){
//
//};
bool countStars(attributes * attr){
    int count =0;
    attributes * temp= attr;
    while(temp!=NULL){
        if(strcmp(temp->attr,"*")==0){
            count++;
        }
        temp=temp->next;
    }
    return count;
}

bool selectAll(attributes * a){
    if(strcmp(a->attr,"*")==0 && a->next==NULL){
        return 1;
    }
    return 0;
}

//attributes tableA contains attributes A
bool tableContainsRequired(attributes * tableA, attributes * A){
    attributes * tempA=A;
    attributes * tempT=tableA;
    int contained = 0;
    while(tempA!=NULL){

        while(tempT!=NULL){
            if(strcmp(tempT->attr,tempA->attr)==0){
                contained=1;
                break;
            }
            tempT=tempT->next;
        }
        if(contained==0){
            return 0;
        }else if(contained==1){
            contained=0;
        }
        tempA=tempA->next;
        tempT=tableA;
    }
    return 1;
};

//make sure that the attributes you want is acutally in the table
bool EnsureProperAttributes(Table * table, attributes * A){
    attributes * temp = table->attributes;
    if(tableContainsRequired(temp, A)==1){
        return 1;
    }else{
        return 0;
    }
};

void internalInsertion(Table * temp, node * data){
    //Table * temp = returnTable(SQL, tableName);
    // printf("%s", temp->name);
    int dataHash = data->hashId;
    if(temp->data[dataHash]==NULL){
        temp->data[data->hashId]=data;
    }else{
//        if(nodeExisted(temp, data)==1){
//            printf("duplicated entry\n");
//            return 2;
//        }
        node * tempNode= temp->data[data->hashId];
        while(temp->data[data->hashId]->nextNode!=NULL){
            temp->data[data->hashId]=temp->data[data->hashId]->nextNode;
        }
        temp->data[data->hashId]->nextNode=data;
        temp->data[data->hashId]=tempNode;
    }
};

//you might want to free the table that this function created
Table * generateResultTable(Table * target, attributes * resultAttributes){
    Table * t = malloc(sizeof(Table));
    t->name="InternalTempTable";
    t->attributes=resultAttributes;
    t->nextTable=NULL;
    for (int i = 0; i < 1009; i++) {
        t->data[i]=malloc(sizeof(node));
        t->data[i]=NULL;
    }

    for(int i = 0; i<1009; i++){
        if(target->data[i]==NULL){
            continue;
        }else{
            node * temp = target->data[i];
            while(temp!=NULL){
                node * tempNode = nodeInit(t);
                //tempNode->attributes=resultAttributes;
                attributes * internalApointer = resultAttributes;
                element * elementPointer=temp->head;
                while(internalApointer!=NULL){
                    while(elementPointer!=NULL){
                        if(strcmp(elementPointer->name,internalApointer->attr)==0){
                            appendElement(tempNode, elementPointer->value);
                            elementPointer=temp->head;
                            break;
                        }
                        elementPointer=elementPointer->nextElement;
                    }
                    internalApointer=internalApointer->next;
                }

                //insert the tempNode into the table
                internalInsertion(t, tempNode);
                temp=temp->nextNode;

            }
        }
    }

    return t;

}

void removeNode(Table * target, node * n){
    node * temp = target->data[n->hashId];
    if(compareNodes(temp, n)==0){
        target->data[n->hashId]=target->data[n->hashId]->nextNode;
        return;
    }else{
        while(compareNodes(n, temp->nextNode)==1){
            temp=temp->nextNode;
        }
        temp->nextNode=temp->nextNode->nextNode;
        return;
    }

};

bool satisfyOneArg(conditions * cond, node * n){
    attributes * temp =attrInit(cond->attr);
    if(tableContainsRequired(n->attributes, temp)==1){
        element * temp1 = n->head;
        while(temp1!=NULL){
            if(strcmp(temp1->name, cond->attr)==0){
                if(strcmp(temp1->value, cond->value)==0){
                    return 1;
                }else{
                    return 0;
                }
            }
            temp1=temp1->nextElement;
        }
    }else{
        return 0;
    }
};

bool satisfyArgs(node * n, conditionsRoot * root){
    conditions * temparg = root->args;
    while (temparg!=NULL) {
        conditions *temparg1 = temparg;
        while (temparg1 != NULL) {
            if(satisfyOneArg(temparg1, n)==0){
                break;
            }
            temparg1 = temparg1->Lowerargs;
        }
        if (temparg1 == NULL) {
            return 1;
        }
        temparg=temparg->Nextargs;
    }
    return 0;
};

Table * applyConditions(Table * resultTable, conditionsRoot * root){

    for(int i=0; i< 1009; i++){
        node * tempNode = resultTable->data[i];
        while(tempNode!=NULL){
            if(satisfyArgs(tempNode, root)==0){
                removeNode(resultTable, tempNode);
            }
            tempNode=tempNode->nextNode;
        }
    }
    return resultTable;

};


Table * SELECT(RealSQL * SQL,char * tableName, attributes * A, conditionsRoot * root){
    if(tableExist(SQL, tableName)){
        Table * tempTable = returnTable(SQL, tableName);
        int stars = countStars(A);
        attributes * Apointer;
        //RealSQL * SQL, char * name, attributes * attributes
        if(selectAll(A)==1){
            //all the attributes
            // return tempTable;
            Apointer = tempTable->attributes;
        }else{
            //projects
            //x==1 && y==2 || z ==3
            //make sure that attributes are entered properly
            if(EnsureProperAttributes(tempTable, A)==1){
                Apointer = A;
            }else{
                //improper attributes input
                printf("your attributes doesn't match the table\n");
                return NULL;
            }
        }
        //generic loopup
        //generate result table
        Table  * resultTable = generateResultTable(tempTable, Apointer);

        //apply the conditions
        if(root==NULL){
            //projection
            printTable(resultTable);
            return resultTable;
        }else{
            Table * it= applyConditions(resultTable, root);
            if(it==NULL){
                //improper conditions
                printf("improper conditions\n");
                return NULL;
            }else{
                //return that table
                printTable(it);
                return it;
            }
        }

    }else{
        //table doesn't exist
        printf("The table you entered doesn't exist\n");
        return NULL;
    }
};

void dropTable(RealSQL * SQL, char * tablename){
    if(tableExist(SQL,tablename)==1){
        //drop the table
        Table * tablepointer = SQL->root;
        Table * deleteTable = returnTable(SQL,tablename);
        //  printf("here");
        if(tablepointer==deleteTable){
            SQL->root=tablepointer->nextTable;
            printf("%s is deleted\n", tablename);
            return;
        }
        while(tablepointer->nextTable!=deleteTable){
            tablepointer=tablepointer->nextTable;
        }

        if(deleteTable->nextTable==NULL){
            tablepointer->nextTable=NULL;
        }else{
            tablepointer->nextTable=deleteTable->nextTable;
        }
        printf("%s is deleted\n", tablename);
    }else{
        printf("table doesn't exist\n");
    }
};


conditionsRoot * conditionsRootInit(){
    conditionsRoot * con =malloc(sizeof(conditionsRoot));
    con->attr=InternalattrInit();
    //con->condToPrevious=NULL;
    con->args=malloc(sizeof(conditions));
    con->args=NULL;
    return con;
};

void appendCondition(conditionsRoot * root, char * condtopre, char * attr, char * value){
    InternalappendAttributes(root->attr,attr);
    if(condtopre==NULL){
        conditions * condi = conditionsInit(attr, value, NULL);
        root->args=condi;
    }else {
        if(strcmp(condtopre,"AND")==0){
            conditions * tempCon = root->args;
            while(tempCon->Nextargs!=NULL){
                tempCon=tempCon->Nextargs;
            }
            while(tempCon->Lowerargs!=NULL){
                tempCon=tempCon->Lowerargs;
            }
            tempCon->Lowerargs=conditionsInit(attr,value,"AND");
            //     while()
        }else if(strcmp(condtopre,"OR")==0){
            conditions * tempCon = root->args;
            while(tempCon->Nextargs!=NULL){
                tempCon=tempCon->Nextargs;
            }
            tempCon->Nextargs=conditionsInit(attr,value,"OR");
        }
    }

};
//void
//key words: select, desc, createTable, insert, showTables, dropTable

