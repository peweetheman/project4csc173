//
// Created by btroo on 11/19/2018.
//

#ifndef PROJECT3CSC173ATTEMPT2_DATABASE_H
#define PROJECT3CSC173ATTEMPT2_DATABASE_H

#endif //PROJECT3CSC173ATTEMPT2_DATABASE_H
#include <stdio.h>
#include <malloc.h>
#include <mem.h>

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

int hashSNAP(int key){
    return key % 1009;
}

void printSNAP(){
    for(int i = 0; i < 1009; i++){
        TUPLELISTSNAP temp = HTSNAP[i];
        while(temp != NULL){
            printf("%d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            temp = temp->next;
        }
    }
}

void addToSNAPList(TUPLELISTSNAP toAdd, TUPLELISTSNAP main){
    toAdd->next = main;
    main = toAdd;
}

TUPLELISTSNAP lookup_SNAP(int id, char* name, char* address, char* phone){
    TUPLELISTSNAP matching = malloc(sizeof (struct SNAP));
    for(int i = 0; i < 1009; i++){
        TUPLELISTSNAP temp = HTSNAP[i];

        while(temp != NULL){
            printf("temp: %d, %s, %s, %s", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            //(match, match, match, match)
            if(temp->StudentId == id && strcmp(temp->Name, name) == 0 && strcmp(temp->Address, address) == 0 && strcmp(temp->Phone, phone) == 0){
                addToSNAPList(temp, matching);
                printf("poopie bed\n");
            }

            //(*, m, m, m) use 00000 as "*" equivalent for integers
            if(id == 00000 && strcmp(temp->Name, name) == 0 && strcmp(temp->Address, address) == 0 && strcmp(temp->Phone, phone) == 0){
                addToSNAPList(temp, matching);
                printf("(*, m, m, m)\n");
            }
            //(m, *, m, m)
            if(temp->StudentId == id && strcmp("*", name) == 0 && strcmp(temp->Address, address) == 0 && strcmp(temp->Phone, phone) == 0){
                addToSNAPList(temp, matching);
                printf("(m, *, m, m)\n");
            }
            //(m, m, *, m)
            if(temp->StudentId == id && strcmp(temp->Name, name) == 0 && strcmp("*", address) == 0 && strcmp(temp->Phone, phone) == 0){
                addToSNAPList(temp, matching);
                printf("(m, m, *, m)\n");
            }
            //(m, m, m, *)
            if(temp->StudentId == id && strcmp(temp->Name, name) == 0 && strcmp(temp->Address, address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(m, m, m, *)\n");
            }
            //(*, *, m, m)
            if(00000 == id && strcmp("*", name) == 0 && strcmp(temp->Address, address) == 0 && strcmp(temp->Phone, phone) == 0){
                addToSNAPList(temp, matching);
                printf("(*, *, m, m)\n");
            }
            //(*, m, *, m)
            if(00000 == id && strcmp(temp->Name, name) == 0 && strcmp("*", address) == 0 && strcmp(temp->Phone, phone) == 0){
                addToSNAPList(temp, matching);
                printf("(*, m, *, m)\n");
            }
            //(m, *, *, m)
            if(temp->StudentId == id && strcmp("*", name) == 0 && strcmp("*", address) == 0 && strcmp(temp->Phone, phone) == 0){
                addToSNAPList(temp, matching);
                printf("(m, *, *, m)\n");
            }
            //(*, m, m, *)
            if(00000 == id && strcmp(temp->Name, name) == 0 && strcmp(temp->Address, address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(*, m, m, *)\n");
            }
            //(m, m, *, *)
            if(temp->StudentId == id && strcmp(temp->Name, name) == 0 && strcmp("*", address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(m, m, *, *)\n");
            }
            //(m, *, m, *)
            if(temp->StudentId == id && strcmp("*", name) == 0 && strcmp(temp->Address, address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(m, *, m, *)\n");
            }
            //(*, *, *, m)
            if(00000 == id && strcmp("*", name) == 0 && strcmp("*", address) == 0 && strcmp(temp->Phone, phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, *, *, m)\n");
            }
            //(*, m, *, *)
            if(00000 == id && strcmp(temp->Name, name) == 0 && strcmp("*", address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(*, m, *, *)");
            }
            //(*, *, m, *)
            if(00000 == id && strcmp("*", name) == 0 && strcmp(temp->Address, address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(*, *, m, *)\n");
            }
            //(m, *, *, *)
            if(temp->StudentId == id && strcmp("*", name) == 0 && strcmp("*", address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(m, *, *, *)\n");
            }
            //(*, *, *, *)
            if(00000 == id && strcmp("*", name) == 0 && strcmp("*", address) == 0 && strcmp("*", phone) == 0){
                addToSNAPList(temp, matching);
                printf("(*, *, *, *)\n");
            }
            temp = temp->next;
            printf("ending normally?\n");
        }
    }



    return matching;
}

//handles collisions as far as I know
void insert_SNAP(int id, char* name, char* address, char* phone){
    TUPLELISTSNAP data = malloc(sizeof (struct SNAP));
    data->StudentId = id;
    strcpy(data->Name, name);
    strcpy(data->Address, address);
    strcpy(data->Phone, phone);
    data->next = NULL;
    int hashIndex = hashSNAP(id);
    if(HTSNAP[hashIndex] == NULL){
        HTSNAP[hashIndex] = data;
        printf("added empty\n");
    }
    else{
        printf("collision\n");
        TUPLELISTSNAP temp = HTSNAP[hashIndex];

        while(temp != NULL){
            printf("temp: %d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            if(temp->StudentId == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                printf("duplicate found\n");
                return;
            }
            temp = temp->next;
            printf("updating temp\n");
        }
        data->next = HTSNAP[hashIndex];
        HTSNAP[hashIndex] = data;
        printf("added\n");

    }

}
