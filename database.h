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
void initializeHTSNAP(){
    for(int i = 0; i < 1009; i ++){
        HTSNAP[i] = NULL;
    }
}

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
}

TUPLELISTSNAP lookup_SNAP(int id, char* name, char* address, char* phone){
    TUPLELISTSNAP matching = NULL;
    TUPLELISTSNAP data = (TUPLELISTSNAP) malloc(sizeof (struct SNAP));
    data->StudentId = id;
    strcpy(data->Name, name);
    strcpy(data->Address, address);
    strcpy(data->Phone, phone);
    data->next = NULL;
    for(int i = 0; i < 1009; i++){
        TUPLELISTSNAP temp = HTSNAP[i];
        int counter = 0;
        while(temp != NULL){

            printf("temp: %d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            //(match, match, match, match)
            if(temp->StudentId == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp(temp->Phone, phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, m, m, m)\n");
                return matching;
            }

            //(*, m, m, m) use 0 as "*" equivalent for integers
            else if(data->StudentId == 0 && strcmp(temp->Name, data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, m, m, m)\n");
            }
            //(m, *, m, m)
            else if(temp->StudentId == data->StudentId && strcmp("*", data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, *, m, m)\n");
            }
            //(m, m, *, m)
            else if(temp->StudentId == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, m, *, m)\n");
            }
            //(m, m, m, *)
            else if(temp->StudentId == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, m, m, *)\n");
            }
            //(*, *, m, m)
            else if(0 == data->StudentId && strcmp("*", data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, *, m, m)\n");
            }
            //(*, m, *, m)
            else if(0 == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, m, *, m)\n");
            }
            //(m, *, *, m)
            else if(temp->StudentId == data->StudentId && strcmp("*", data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, *, *, m)\n");
            }
            //(*, m, m, *)
            else if(0 == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, m, m, *)\n");
            }
            //(m, m, *, *)
            else if(temp->StudentId == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, m, *, *)\n");
            }
            //(m, *, m, *)
            else if(temp->StudentId == data->StudentId && strcmp("*", data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, *, m, *)\n");
            }
            //(*, *, *, m)
            else if(0 == data->StudentId && strcmp("*", data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp(temp->Phone, data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, *, *, m)\n");
            }
            //(*, m, *, *)
            else if(0 == data->StudentId && strcmp(temp->Name, data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, m, *, *)");
            }
            //(*, *, m, *)
            else if(0 == data->StudentId && strcmp("*", data->Name) == 0 && strcmp(temp->Address, data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, *, m, *)\n");
            }
            //(m, *, *, *)
            else if(temp->StudentId == data->StudentId && strcmp("*", data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(m, *, *, *)\n");
            }
            //(*, *, *, *)
            else if(0 == data->StudentId && strcmp("*", data->Name) == 0 && strcmp("*", data->Address) == 0 && strcmp("*", data->Phone) == 0){
                temp->next = matching;
                matching = temp;
                printf("(*, *, *, *)\n");
            }
            temp = temp->next;
            //printf("Assigning %d, %s, %s, %s to %d, %s, %s, %s\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
            printf("loop ran: %d\n", counter);
            counter++;
        }

    }



    return matching;
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
