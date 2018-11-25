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
    char Course[6];
    char PrereqCourse[6];
    TUPLELISTCP next;
};
TUPLELISTCP HTCP[128];

typedef struct CDH *TUPLELISTCDH;
struct CDH{
    char Course[6];
    char Day[3];
    char Hour[5];
    TUPLELISTCDH next;
};
TUPLELISTCDH HTCDH[128];

typedef struct CR *TUPLELISTCR;
struct CR{
    char Course[6];
    char Room[30];
    TUPLELISTCR next;
};
TUPLELISTCR HTCR[128];

typedef struct id *TUPLELISTid;
struct id{
    int id;
    TUPLELISTid next;
};

typedef struct CRDH *TUPLELISTCRDH;
struct CRDH{
    char Course[6];
    char Room[30];
    char Day[3];
    char Hour[5];
    TUPLELISTCRDH next;
};

typedef struct DH *TUPLELISTDH;
struct DH{
    char Day[3];
    char Hour[5];
    TUPLELISTDH next;
};
//key is Course
int hashCR(char* course){
    int ascii = 0;
    for(int i = 0; i < 5; i++){
        ascii += (int) course[0];
    }
    return (int) ascii % 128;
}

void printCR(){
    for(int i = 0; i < 128; i++){

        TUPLELISTCR temp = HTCR[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %s \n", temp->Course, temp->Room);
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
    TUPLELISTCR matching = (TUPLELISTCR) malloc (sizeof(struct CR));
    for(int i = 0; i < 128; i++) {
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
void insert_CR(char* course, char* room){
    TUPLELISTCR data = (TUPLELISTCR) malloc(sizeof (struct CR));
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

void delete_CR(char* course, char* room){
    for(int i = 0; i < 128; i++) {
        TUPLELISTCR temp = HTCR[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->Room, room) == 0 || strcmp("*", room) == 0)) {
                if(temp->next == NULL){
                    free(temp->Course);
                    free(temp->Room);
                    temp=NULL;
                    HTCR[i] = NULL;
                }
                else {
                    strcpy(temp->Course, temp->next->Course);
                    strcpy(temp->Room, temp->next->Room);
                    temp->next = temp->next->next;
                }
            }
            else{
                temp = temp->next;
            }
        }
    }
}
void delete_CSG(char* course, int studentID, char* Grade){
    for(int i = 0; i < 128; i++) {
        TUPLELISTCSG temp = HTCSG[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (temp->StudentId == studentID || studentID == 0)
                && (strcmp(temp->Grade, Grade) == 0 || strcmp("*", Grade) == 0)){
                if(temp->next == NULL){
                    free(temp->Course);
                    free(temp->Grade);
                    temp=NULL;
                    HTCSG[i] = NULL;
                }
                else {
                    strcpy(temp->Course, temp->next->Course);
                    strcpy(temp->Grade, temp->next->Grade);
                    temp->next->StudentId = temp->StudentId;
                    temp->next = temp->next->next;
                }
            }
            else{
                temp = temp->next;
            }
        }
    }
}
void delete_SNAP(int studentID, char* Name, char* address, char* phone){
    for(int i = 0; i < 128; i++) {
        TUPLELISTSNAP temp = HTSNAP[i];
        while (temp != NULL) {
            if ((strcmp(temp->Phone, phone) == 0 || strcmp("*", phone) == 0)
                && (temp->StudentId == studentID || studentID == 0)
                && (strcmp(temp->Address, address) == 0 || strcmp("*", address) == 0)
                && (strcmp(temp->Name, Name) == 0 || strcmp("*", Name) == 0)){
                if(temp->next == NULL){
                    free(temp->Name);
                    free(temp->Address);
                    free(temp->Phone);
                    temp=NULL;
                    HTSNAP[i] = NULL;
                }
                else {
                    strcpy(temp->Phone, temp->next->Phone);
                    strcpy(temp->Name, temp->next->Name);
                    strcpy(temp->Address, temp->next->Address);
                    temp->next->StudentId = temp->StudentId;
                    temp->next = temp->next->next;
                }
            }
            else{
                temp = temp->next;
            }
        }
    }
}

void delete_CDH(char* course, char* Day, char* Hour){
    for(int i = 0; i < 128; i++) {
        TUPLELISTCDH temp = HTCDH[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->Hour, Hour) == 0 || strcmp("*", Hour) == 0)
                && (strcmp(temp->Day, Day) == 0 || strcmp("*", Day) == 0)){
                if(temp->next == NULL){
                    free(temp->Course);
                    free(temp->Day);
                    temp=NULL;
                    HTCDH[i] = NULL;
                }
                else {
                    strcpy(temp->Course, temp->next->Course);
                    strcpy(temp->Day, temp->next->Day);
                    strcpy(temp->Hour, temp->next->Hour);
                    temp->next = temp->next->next;
                }
            }
            else{
                temp = temp->next;
            }
        }
    }
}
void delete_CP(char* course, char* prq){
    for(int i = 0; i < 128; i++) {
        TUPLELISTCP temp = HTCP[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->PrereqCourse, prq) == 0 || strcmp("*", prq) == 0)){
                if(temp->next == NULL){
                    free(temp->Course);
                    free(temp->PrereqCourse);
                    temp=NULL;
                    HTCP[i] = NULL;
                }
                else {
                    strcpy(temp->Course, temp->next->Course);
                    strcpy(temp->PrereqCourse, temp->next->PrereqCourse);
                    temp->next = temp->next->next;
                }
            }
            else{
                temp = temp->next;
            }
        }
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
    for(int i = 0; i < 128; i++){
        TUPLELISTCSG temp = HTCSG[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %d, %s \n", temp->Course, temp->StudentId, temp->Grade);
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

TUPLELISTCSG lookup_CSG(char* course, int id, char* Day){
    TUPLELISTCSG firstNode = NULL;
    TUPLELISTCSG matching = (TUPLELISTCSG) malloc(sizeof(struct CSG));
    for(int i = 0; i < 128; i++) {
        TUPLELISTCSG temp = HTCSG[i];
        while (temp != NULL) {
            if ((id == 0 || id == temp->StudentId)
                && (strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->Grade, Day) == 0 || strcmp("*", Day) == 0)) {
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
void insert_CSG(char* course, int id, char* Day){
    TUPLELISTCSG data = (TUPLELISTCSG) malloc(sizeof (struct CSG));
    data->StudentId = id;
    strcpy(data->Course, course);
    strcpy(data->Grade, Day);
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
            printf("%d, %s, %s, %s \n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
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
    for(int i = 0; i < 128; i++){
        TUPLELISTCP temp = HTCP[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %s \n", temp->Course, temp->PrereqCourse);
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
    TUPLELISTCP matching = (TUPLELISTCP) malloc(sizeof(struct CP));
    for(int i = 0; i < 128; i++) {
        TUPLELISTCP temp = HTCP[i];
        while (temp != NULL) {
            if ((strcmp(temp->Course, course) == 0 || strcmp("*", course) == 0)
                && (strcmp(temp->PrereqCourse, pre) == 0 || strcmp("*", pre) == 0)) {
                TUPLELISTCP temp2 = (TUPLELISTCP) malloc(sizeof(struct CP));
                strcpy(temp2->Course, temp->Course);
                strcpy(temp2->PrereqCourse, temp->PrereqCourse);
                temp2->next = NULL;
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
void insert_CP(char* course, char* pre){
    TUPLELISTCP data = (TUPLELISTCP) malloc(sizeof (struct CP));
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
    for(int i = 0; i < 128; i++){
        TUPLELISTCDH temp = HTCDH[i];
        int index = 0;
        while(temp != NULL){
            printf("%s, %s, %s \n", temp->Course, temp->Day, temp->Hour);
            temp = temp->next;
            index++;
        }
    }
}

void printCDHTUPLEList(TUPLELISTCDH main){
    TUPLELISTCDH temp = main;
    while(temp != NULL){
        printf("%s, %s, %s\n", temp->Course, temp->Day, temp->Hour);
        temp = temp->next;
    }
    printf("\n");
}


TUPLELISTCDH lookup_CDH(char* course, char* day, char* hour){
    TUPLELISTCDH firstNode = NULL;
    TUPLELISTCDH matching = (TUPLELISTCDH) malloc(sizeof(struct CDH));
    for(int i = 0; i < 128; i++) {
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

void insert_CDH(char* course, char* day, char hour[]){
    TUPLELISTCDH data = (TUPLELISTCDH) malloc(sizeof (struct CDH));
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

//PART TWO FUNCTIONS!!

void getDay(char* studentName, char* courseName){
    TUPLELISTSNAP possibleTuple = lookup_SNAP(0, studentName, "*", "*");
    while(possibleTuple != NULL) {
        TUPLELISTCSG possibleCSG = lookup_CSG(courseName, possibleTuple->StudentId, "*");
        if(possibleCSG!= NULL){
            printf("%s got a Grade of %s in the course %s \n", studentName, possibleCSG->Grade, courseName);
            return;
        }
        possibleTuple = possibleTuple->next;
    }
    printf("It doesn't look like %s took the course %s \n", studentName, courseName);
}

void getRoom(char* studentName, char* time, char* day){
    TUPLELISTSNAP possibleSNAP = lookup_SNAP(0, studentName, "*", "*");
    while(possibleSNAP != NULL) {
        TUPLELISTCSG possibleCSG = lookup_CSG("*", possibleSNAP->StudentId, "*");
        //elimnate duplicate courses!
        while(possibleCSG!= NULL){
            TUPLELISTCDH possibleCDH = lookup_CDH(possibleCSG->Course, day, time);
            while(possibleCDH!=NULL){
                TUPLELISTCR possibleCR = lookup_CR(possibleCDH->Course, "*");
                if(possibleCR!=NULL){
                    printf("%s is in %s at %s on %s \n", studentName, possibleCR->Room, time, day);
                    return;
                }
                possibleCDH = possibleCDH->next;
            }
            possibleCSG = possibleCSG->next;
        }
        possibleSNAP = possibleSNAP->next;
    }
    printf("It doesn't look like we have that information \n");
}

//Part iii methods

TUPLELISTCSG select_CSG(char* course, int id, char* Day){ // for part iii
    TUPLELISTCSG stuff = (lookup_CSG(course, id, Day));
    return stuff;
}

TUPLELISTid project_CSG(TUPLELISTCSG CSG){
    TUPLELISTid firstID = (TUPLELISTid) malloc(sizeof(TUPLELISTCSG));
    TUPLELISTid temp1 = firstID;
    while(CSG!=NULL){
        temp1->id = CSG->StudentId;
        TUPLELISTid temp2 = (TUPLELISTid) malloc(sizeof(TUPLELISTCSG));
        CSG = CSG->next;
        if(CSG!=NULL){
            temp1->next = temp2;
            temp2->next = NULL;
            temp1 = temp2;
        }
    }

    return firstID;
}


void printID(TUPLELISTid id){
    TUPLELISTid temp = id;
    while(temp != NULL){
        printf("%d \n", temp->id);
        temp = temp->next;
    }
    printf("\n");
}
void printCRDHTUPLELIST(TUPLELISTCRDH main){
    TUPLELISTCRDH temp = main;
    while(temp != NULL){
        printf("%s, %s, %s, %s \n", temp->Course, temp->Room, temp->Day, temp->Hour);
        temp = temp->next;
    }
    printf("\n");
}
void printDH(TUPLELISTDH main){
    TUPLELISTDH temp = main;
    while(temp != NULL){
        printf("%s, %s \n", temp->Day, temp->Hour);
        temp = temp->next;
    }
    printf("\n");
}

TUPLELISTCRDH select_CRDH(char* room, TUPLELISTCRDH crdh){ // for part iii
    TUPLELISTCRDH first = NULL;
    TUPLELISTCRDH temp1 = malloc(2*sizeof(struct CRDH));
    while(crdh!=NULL){
        if ((strcmp(crdh->Room, room) == 0)) {
            TUPLELISTCRDH temp2 = malloc(2*sizeof(struct CRDH));
            strcpy(temp2->Room, crdh->Room);
            strcpy(temp2->Course, crdh->Course);
            strcpy(temp2->Day, crdh->Day);
            strcpy(temp2->Hour, crdh->Hour);
            if (first == NULL) {
                first = temp2;
                temp1 = temp2;
            } else {
                temp1->next = temp2;
                temp1 = temp2;
            }
        }
        crdh = crdh->next;
    }
    return first;
}

TUPLELISTCRDH join_CR_CDH(TUPLELISTCR cr, TUPLELISTCDH cdh){
    TUPLELISTCRDH firstCRDH = NULL;
    TUPLELISTCDH cdhorg = cdh;
    TUPLELISTCRDH temp2 = (TUPLELISTCRDH) malloc(30*sizeof(cdh));
    while(cr!=NULL){
        while(cdh!=NULL) {
            if(strcmp(cdh->Course, cr->Course) ==0){
                TUPLELISTCRDH temp1 = (TUPLELISTCRDH) malloc(30*sizeof(cdh));
                strcpy(temp1->Course, cdh->Course);
                strcpy(temp1->Hour, cdh->Hour);
                strcpy(temp1->Day, cdh->Day);
                strcpy(temp1->Room, cr->Room);
                if(firstCRDH == NULL){
                    firstCRDH = temp1;
                    temp2 = temp1;
                }
                else{
                    temp2->next = temp1;
                    temp2 = temp1;
                }
            }
            cdh = cdh->next;
        }
        cdh = cdhorg;
        cr = cr->next;
    }
    return firstCRDH;
}

TUPLELISTDH project_CRDH(TUPLELISTCRDH crdh){
    TUPLELISTDH first = (TUPLELISTDH) malloc(5*sizeof(TUPLELISTCRDH));
    TUPLELISTDH temp1 = first;
    while(crdh!=NULL){
        strcpy(temp1->Hour, crdh->Hour);
        strcpy(temp1->Day, crdh->Day);
        TUPLELISTDH temp2 = (TUPLELISTDH) malloc(5*sizeof(TUPLELISTCRDH));
        crdh = crdh->next;
        if(crdh!=NULL){
            temp1->next = temp2;
            temp2->next = NULL;
            temp1 = temp2;
        }
        else{
        }
    }
    return first;
}
