//
// Created by btroo on 11/19/2018.
//

#ifndef PROJECT3CSC173ATTEMPT2_DATABASE_H
#define PROJECT3CSC173ATTEMPT2_DATABASE_H

#endif //PROJECT3CSC173ATTEMPT2_DATABASE_H
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct CSG *TUPLELISTCSG;
struct CSG{
    char Course[5];
    int StudentId;
    char Grade[2];
    TUPLELISTCSG next;
};
TUPLELISTCSG HTCSG[1009];

typedef struct SNAP *TUPLELISTSNAP;
struct SNAP{
    int StudentId;
    char Name[30];
    char Address[50];
    char Phone[9]; //string for temp->phone outputting gibberish......
    TUPLELISTSNAP next;
};
TUPLELISTSNAP HTSNAP[1009];

typedef struct CP *TUPLELISTCP;
struct CP{
    char Course[5];
    char PrereqCourse[5];
    TUPLELISTCP next;
};
typedef TUPLELISTCP HTCP[1009];

typedef struct CDH *TUPLELISTCDH;
struct CDH{
    char Course[5];
    char Day[2];
    char Hour[4];
    TUPLELISTCDH next;
};
typedef TUPLELISTCDH HTCDH[1009];

typedef struct CR *TUPLELISTCR;
struct CR{
    char Course[5];
    char Room[30];
    TUPLELISTCR next;
};
typedef TUPLELISTCR HTCR[1009];

//key is student id
int hashSNAP(int key){
    return key % 1009;
}

void printSNAP(){
    for(int i = 0; i < 1009; i++){
        TUPLELISTSNAP temp = HTSNAP[i];
        int index = 0;
        while(temp != NULL){
            printf("%d, %s, %s, %s, %d\n", temp->StudentId, temp->Name, temp->Address, temp->Phone, index);
            temp = temp->next;
            index++;
        }
    }
}

void printSNAPTUPLEList(TUPLELISTSNAP main){
    TUPLELISTSNAP temp = main;
    while(temp != NULL){
        printf("%d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
        temp = temp->next;
    }
    printf("\n");
}


TUPLELISTSNAP lookup_SNAP(int id, char* name, char* address, char* phone){
    TUPLELISTSNAP firstNode = NULL;
    TUPLELISTSNAP matching;
    for(int i = 0; i < 1009; i++) {
        TUPLELISTSNAP temp = HTSNAP[i];
        while (temp != NULL) {
            if ((id == 0 || id == temp->StudentId)
                && (strcmp(temp->Name, name) == 0 || strcmp("*", name) == 0)
                && (strcmp(temp->Address, address) == 0 || strcmp("*", address) == 0)
                && (strcmp(temp->Phone, phone) == 0 || strcmp("*", phone) == 0)) {
                TUPLELISTSNAP temp2 = temp;
                temp2->StudentId = temp->StudentId;
                strcpy(temp2->Name, temp->Name);
                strcpy(temp2->Address, temp->Address);
                strcpy(temp2->Phone, temp->Phone);
                if (firstNode == NULL) {
                    firstNode = temp2;
                    matching = firstNode;
                } else {
                    matching->next = temp2;
                    matching = matching->next;
                }
            }
            temp = temp->next;
        }
    }
    return firstNode;
}

//handles collisions as far as I know
void insert_SNAP(int id, char* name, char* address, char* phone){
    TUPLELISTSNAP data = (TUPLELISTSNAP) malloc(sizeof (struct SNAP));
    data->StudentId = id;
    strcpy(data->Name, name);
    strcpy(data->Address, address);
    strcpy(data->Phone, phone);
    data->next = NULL;
    int hashIndex = hashSNAP(id);
    if(HTSNAP[hashIndex] == NULL){
        HTSNAP[hashIndex] = data;
//        printf("added empty\n");
    }
    else{
//        printf("collision\n");
        TUPLELISTSNAP temp = HTSNAP[hashIndex];
        while(temp != NULL){
//            printf("temp: %d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            if(temp->StudentId == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
//                printf("duplicate found\n");
                return;
            }
            temp = temp->next;
//            printf("updating temp\n");
        }
        data->next = HTSNAP[hashIndex];
        HTSNAP[hashIndex] = data;
//        printf("added\n");
    }
}
