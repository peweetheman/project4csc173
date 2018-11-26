//
// Created by Andy on 11/25/2018.
//

#ifndef UNTITLED_QUERYPARSER_H
#define UNTITLED_QUERYPARSER_H

#endif //UNTITLED_QUERYPARSER_H

#include "database.h"

attributes * splitEqual(char* input){
    char* duplicateInput = strdup(input);
    char * split;
    attributes* head = attrInit("null");
    //printf ("Spliting string \"%s\" into tokens:\n", duplicateInput);
    split = strtok (duplicateInput,"=");
    while (split != NULL)
    {
        if(strcmp(head->attr, "null") == 0){
            head = attrInit(split);
        }else{
            appendAttribute(head, split);
            //printf ("%s\n",split);
        }
        split = strtok (NULL, "=");

    }
    return head;
};

int getLen(attributes * a){
    int len=0;
    attributes * temp =a;
    while(temp!=NULL){
        len=len+1;
        temp=temp->next;
    }
    return len;
}

bool checkConditions(attributes * con){
    attributes * temp = con;
    int incond = 1;
    while(temp!=NULL){
        if(incond==1){
            attributes * temp1 = splitEqual(temp->attr);
            //printAttributes(temp1);
            if(getLen(temp1)!=2){
                printf("%d",getLen(temp1));
                return 0;
            }else{
                incond=0;
            }
        }else if(incond==0){
            attributes * temp1 = splitEqual(temp->attr);
            if(strcmp("AND",temp1->attr)==0||strcmp("OR",temp1->attr)==0){
                incond=1;
            }else{
                return 0;
            }
        }
        temp=temp->next;
    }
    return 1;
};

void ExecuteQuery(RealSQL * SQL, char * Query){
    attributes * query = splitSpaces(Query);
    if(strcmp(query->attr,"SHOWTABLES")==0){
        if(SQL->root==NULL){
            printf(("NO tables sorry bro"));
            return;
        }
        printSQLtables(SQL);
    }else if(strcmp(query->attr,"DROPTABLE")==0){
        if(query->next!=NULL){
            dropTable(SQL,query->next->attr);
        }else{
            printf("improper Query\n");
        }
    }else if(strcmp(query->attr,"DESC")==0){
        if(query->next!=NULL){
            if(tableExist(SQL,query->next->attr)){
                Table * temp=returnTable(SQL,query->next->attr);
                printf("The name of table is: %s\n", temp->name);
                printf("Attributes are: \n");
                printAttributes(temp->attributes);
            }else{
                printf("Table doesn't exist\n");
            }
        }else{
            printf("improper Query\n");
        }
    }else if(strcmp(query->attr,"CREATETABLE")==0){
        if(query->next!=NULL){
            if(query->next->next!=NULL){
                char * a = query->next->next->attr;
                createTable(SQL,query->next->attr,splitCommas(a));
            }else{
                printf("improper Query\n");
            }
        }else{
            printf("improper Query\n");
        }
    }else if(strcmp(query->attr,"INSERTINTO")==0){
        if(query->next!=NULL){
            if(query->next->next!=NULL){
//                char * a = query->next->next->attr;
//                createTable(SQL,query->next->attr,splitCommas(a));
                if(tableExist(SQL, query->next->attr)){
                    char * tname = query->next->attr;
                    attributes * temp = query->next->next;
                    while(temp!=NULL){
                        attributes * data = splitCommas(temp->attr);
                        node * tempn = nodeInit(returnTable(SQL,tname));
                        attributes * datapointer = data;
                        while(datapointer!=NULL){
                            appendElement(tempn,datapointer->attr);
                            datapointer=datapointer->next;
                        }
                        int res = insertIntoTable(SQL,tname,tempn);
                        if(res==1){
                            printf("insert successful\n");
                        }
                        temp=temp->next;
                    }
                }else{
                    printf("table doesn't exist\n");
                }
            }else{
                printf("no data entered\n");
            }
        }else{
            printf("tablename can't be NULL\n");
        }
    }else if(strcmp(query->attr,"SELECT")==0){
        if(query->next!=NULL){
            if(strcmp(query->next->next->attr,"FROM")==0){
                if(query->next->next->next!=NULL){
                    attributes * args = splitCommas(query->next->attr);
                    char * tname = query->next->next->next->attr;
                    if(query->next->next->next->next==NULL){
                        SELECT(SQL, tname, args, NULL);
                    }else{
                        if(strcmp(query->next->next->next->next->attr,"WHERE")==0){
                            //initialize conditions
                            attributes * condpointer = query->next->next->next->next->next;
                            if(condpointer!=NULL){
                                if(checkConditions(condpointer)==1){
                                    int inConditions=1;
                                    //recognize conditions
                                    conditionsRoot *root=conditionsRootInit();
                                    attributes * condfirst = splitEqual(condpointer->attr);
                                    appendCondition(root,NULL,condfirst->attr,condfirst->next->attr);
                                    inConditions=0;
                                    condpointer=condpointer->next;
                                    int precon = 0; //0: and, 1: or
                                    while(condpointer!=NULL){
                                        if(inConditions==1){
                                            attributes * condits = splitEqual(condpointer->attr);
                                            if(precon==1){
                                                appendCondition(root,"OR",condits->attr,condits->next->attr);
                                            }else{
                                                appendCondition(root,"AND",condits->attr,condits->next->attr);
                                            }
                                            inConditions=0;
                                        }else if(inConditions==0){
                                            if(strcmp("AND", condpointer->attr)==0){
                                                precon=0;
                                            }else{
                                                precon=1;
                                            }
                                            inConditions=1;
                                        }
                                        condpointer=condpointer->next;
                                    }
                                    SELECT(SQL,tname, args, root);
                                }else{
                                    printf("improper conditions\n");
                                }

                            }else{
                                printf("Please enter some conditions");
                            }
                        }else{
                            printf("You have to have WHERE KEYWORD");
                        }

                    }
                }else{
                    printf("table name can't be NULL\n");
                }
//                if(tableExist(SQL, query->next->attr)){
//                    char * tname = query->next->attr;
//                    attributes * temp = query->next->next;
//                    while(temp!=NULL){
//                        attributes * data = splitCommas(temp->attr);
//                        node * tempn = nodeInit(returnTable(SQL,tname));
//                        attributes * datapointer = data;
//                        while(datapointer!=NULL){
//                            appendElement(tempn,datapointer->attr);
//                            datapointer=datapointer->next;
//                        }
//                        int res = insertIntoTable(SQL,tname,tempn);
//                        if(res==1){
//                            printf("insert successful\n");
//                        }
//                        temp=temp->next;
//                    }
//                }else{
//                    printf("table doesn't exist\n");
//                }
            }else{
                printf("you have to have FROM keyword\n");
            }
        }else{
            printf("no column selected\n");
        }
    }else{
        printf("please enter proper keyword, your query doesn't make sense\n");
    }
};

void SQLREPL(RealSQL * SQL){
    //ask user input
    printf("Please enter Your Query: \n");
    char * input = malloc(1000* sizeof(char));
    scanf(" %[^\n]s",input);
    if(strcmp("quit",input)==0){
        return;
    }else{
        ExecuteQuery(SQL,input);
        printf("\n");
        free(input);
        SQLREPL(SQL);
    }

    //while not quit
};