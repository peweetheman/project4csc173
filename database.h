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
TUPLELISTCSG HTCSG[128];

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
    int doesAbsolutelyNothing;
    char PrereqCourse[5];
    TUPLELISTCP next;
};
TUPLELISTCP HTCP[128];

typedef struct CDH *TUPLELISTCDH;
struct CDH{
    char Course[5];
    char Day[2];
    int doesAbsolutelyNothing;
    char Hour[4];
    TUPLELISTCDH next;
};
TUPLELISTCDH HTCDH[128];

typedef struct CR *TUPLELISTCR;
struct CR{
    char Course[5];
    int doesAbsolutelyNothing;
    char Room[30];
    TUPLELISTCR next;
};
TUPLELISTCR HTCR[128];



//key is Course
int hashCR(char* course){
    int ascii = 0;
    for(int i = 0; i < 5; i++){
        ascii += (int) course[0];
    }
    return (int) ascii % 128;
}

void printCR(){
    for(int i = 0; i < 1009; i++){
        TUPLELISTCR temp = HTCR[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %s, %d\n", temp->Course, temp->Room, index);
            temp = temp->next;
            index++;
        }
    }
}

void printCRTUPLEList(TUPLELISTCR main){
    TUPLELISTCR temp = main;
    while(temp != NULL){
        printf("%s, %s\n", temp->Course, temp->Room);
        temp = temp->next;
    }
    printf("\n");
}


TUPLELISTCR lookup_CR(char* course, char* room){
    TUPLELISTCR firstNode = NULL;
    TUPLELISTCR matching;
    for(int i = 0; i < 1009; i++) {
        TUPLELISTCR temp = HTCR[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->Room, room) == 0 || strcmp("*", room) == 0)) {
                TUPLELISTCR temp2 = temp;
                strcpy(temp2->Room, temp->Room);
                strcpy(temp2->Course, temp->Course);
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
void insert_CR(char* course, char* room, int doNothing){
    TUPLELISTCR data = (TUPLELISTCR) malloc(sizeof (struct CR));
    data->doesAbsolutelyNothing = doNothing;
    strcpy(data->Course, course);
    strcpy(data->Room, room);
    data->next = NULL;
    int hashIndex = hashCR(course);
    if(HTCR[hashIndex] == NULL){
        HTCR[hashIndex] = data;
//        printf("added empty\n");
    }
    else{
//        printf("collision\n");
        TUPLELISTCR temp = HTCR[hashIndex];
        while(temp != NULL){
//            printf("temp: %d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            if(strcmp(temp->Course, data->Course) == 0 && strcmp(temp->Room, data->Room) == 0){
//                printf("duplicate found\n");
                return;
            }
            temp = temp->next;
//            printf("updating temp\n");
        }
        data->next = HTCR[hashIndex];
        HTCR[hashIndex] = data;
//        printf("added\n");
    }
}







//key is Course
int hashCSG(char* course){
    int ascii = 0;
    for(int i = 0; i < 5; i++){
        ascii += (int) course[0];
    }
    return (int) ascii % 128;
}

void printCSG(){
    for(int i = 0; i < 1009; i++){
        TUPLELISTCSG temp = HTCSG[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %d, %s, %d\n", temp->Course, temp->StudentId, temp->Grade, index);
            temp = temp->next;
            index++;
        }
    }
}

void printCSGTUPLEList(TUPLELISTCSG main){
    TUPLELISTCSG temp = main;
    while(temp != NULL){
        printf("%s, %d, %s\n", temp->Course, temp->StudentId, temp->Grade);
        temp = temp->next;
    }
    printf("\n");
}


TUPLELISTCSG lookup_CSG(char* course, int id, char* grade){
    TUPLELISTCSG firstNode = NULL;
    TUPLELISTCSG matching;
    for(int i = 0; i < 1009; i++) {
        TUPLELISTCSG temp = HTCSG[i];
        while (temp != NULL) {
            if ((id == 0 || id == temp->StudentId)
                && (strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->Grade, grade) == 0 || strcmp("*", grade) == 0)) {
                TUPLELISTCSG temp2 = temp;
                temp2->StudentId = temp->StudentId;
                strcpy(temp2->Course, temp->Course);
                strcpy(temp2->Grade, temp->Grade);
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
void insert_CSG(char* course, int id, char* grade){
    TUPLELISTCSG data = (TUPLELISTCSG) malloc(sizeof (struct CSG));
    data->StudentId = id;
    strcpy(data->Course, course);
    strcpy(data->Grade, grade);
    data->next = NULL;
    int hashIndex = hashCSG(course);
    if(HTCSG[hashIndex] == NULL){
        HTCSG[hashIndex] = data;
//        printf("added empty\n");
    }
    else{
//        printf("collision\n");
        TUPLELISTCSG temp = HTCSG[hashIndex];
        while(temp != NULL){
//            printf("temp: %d, %s, %s, %s\n", temp->Course, temp->StudentId, temp->Address, temp->Phone);
            if(temp->StudentId == data->StudentId && strcmp(temp->Course, data->Course) == 0 && strcmp(temp->Grade, data->Grade) == 0){
//                printf("duplicate found\n");
                return;
            }
            temp = temp->next;
//            printf("updating temp\n");
        }
        data->next = HTCSG[hashIndex];
        HTCSG[hashIndex] = data;
//        printf("added\n");
    }
}







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







//key is Course
int hashCP(char* course){
    int ascii = 0;
    for(int i = 0; i < 5; i++){
        ascii += (int) course[0];
    }
    return (int) ascii % 128;
}

void printCP(){
    for(int i = 0; i < 1009; i++){
        TUPLELISTCP temp = HTCP[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %s, %d\n", temp->Course, temp->PrereqCourse, index);
            temp = temp->next;
            index++;
        }
    }
}

void printCPTUPLEList(TUPLELISTCP main){
    TUPLELISTCP temp = main;
    while(temp != NULL){
        printf("%s, %s\n", temp->Course, temp->PrereqCourse);
        temp = temp->next;
    }
    printf("\n");
}


TUPLELISTCP lookup_CP(char* course, char* pre){
    TUPLELISTCP firstNode = NULL;
    TUPLELISTCP matching;
    for(int i = 0; i < 1009; i++) {
        TUPLELISTCP temp = HTCP[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->PrereqCourse, pre) == 0 || strcmp("*", pre) == 0)) {
                TUPLELISTCP temp2 = temp;
                strcpy(temp2->Course, temp->Course);
                strcpy(temp2->PrereqCourse, temp->PrereqCourse);
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
void insert_CP(char* course, char* pre, int doNothing){
    TUPLELISTCP data = (TUPLELISTCP) malloc(sizeof (struct CP));
    data->doesAbsolutelyNothing = doNothing;
    strcpy(data->Course, course);
    strcpy(data->PrereqCourse, pre);
    data->next = NULL;
    int hashIndex = hashCP(course);
    if(HTCP[hashIndex] == NULL){
        HTCP[hashIndex] = data;
//        printf("added empty\n");
    }
    else{
//        printf("collision\n");
        TUPLELISTCP temp = HTCP[hashIndex];
        while(temp != NULL){
//            printf("temp: %d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            if(strcmp(temp->Course, data->Course) == 0 && strcmp(temp->PrereqCourse, data->PrereqCourse) == 0){
//                printf("duplicate found\n");
                return;
            }
            temp = temp->next;
//            printf("updating temp\n");
        }
        data->next = HTCP[hashIndex];
        HTCP[hashIndex] = data;
//        printf("added\n");
    }
}


//key is Course
int hashCDH(char* course){
    int ascii = 0;
    for(int i = 0; i < 5; i++){
        ascii += (int) course[0];
    }
    return (int) ascii % 128;
}

void printCDH(){
    for(int i = 0; i < 1009; i++){
        TUPLELISTCDH temp = HTCDH[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %s, %s, %d\n", temp->Course, temp->Day, temp->Hour, index);
            temp = temp->next;
            index++;
        }
    }
}

void printCDHTUPLEList(TUPLELISTCDH main){
    TUPLELISTCDH temp = main;
    while(temp != NULL){
        printf("%s, %d, %s\n", temp->Course, temp->Day, temp->Hour);
        temp = temp->next;
    }
    printf("\n");
}


TUPLELISTCDH lookup_CDH(char* course, char* day, char* hour){
    TUPLELISTCDH firstNode = NULL;
    TUPLELISTCDH matching;
    for(int i = 0; i < 1009; i++) {
        TUPLELISTCDH temp = HTCDH[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->Day, day) == 0 || strcmp("*", day) == 0)
                && (strcmp(temp->Hour, hour) == 0 || strcmp("*", hour) == 0)) {
                TUPLELISTCDH temp2 = temp;
                strcpy(temp2->Day, temp->Day);
                strcpy(temp2->Course, temp->Course);
                strcpy(temp2->Hour, temp->Hour);
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

//CONCANTENATION ISSUE THAT CAN'T BE SOLVED WITH THE CD TRICK
void insert_CDH(char* course, char* day, char* hour, int doNothing){
    TUPLELISTCDH data = (TUPLELISTCDH) malloc(sizeof (struct CDH));
    data->doesAbsolutelyNothing = doNothing;
    strcpy(data->Course, course);
    strcpy(data->Day, day);
    strcpy(data->Hour, hour);
    data->next = NULL;
    int hashIndex = hashCDH(course);
    if(HTCDH[hashIndex] == NULL){
        HTCDH[hashIndex] = data;
//        printf("added empty\n");
    }
    else{
//        printf("collision\n");
        TUPLELISTCDH temp = HTCDH[hashIndex];
        while(temp != NULL){
//            printf("temp: %d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            if(strcmp(temp->Course, data->Course) == 0 && strcmp(temp->Day, data->Day) == 0 && strcmp(temp->Hour, data->Hour) == 0){
//                printf("duplicate found\n");
                return;
            }
            temp = temp->next;
//            printf("updating temp\n");
        }
        data->next = HTCDH[hashIndex];
        HTCDH[hashIndex] = data;
//        printf("added\n");
    }
}