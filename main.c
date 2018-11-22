#include <stdio.h>
#include "database.h"
#include "RealSQL.h"


void REPL(){
    printf("\nQuery of 'What GRADE did STUDENTNAME get in COURSENAME' \n");

    char* studentName = malloc(20*sizeof(char));
    printf("Enter the Student's Name: ");
    scanf(" %[^\n]s",studentName);

    char* courseName = malloc(10*sizeof(char));
    printf("Enter the Course Name: ");
    scanf(" %[^\n]s",courseName);

    getGrade(studentName, courseName);
    printf("Enter 1 to continue this REPL or anything else to move on: ");
    char check[100];
    scanf(" %[^\n]s",check);
    if(strcmp(check, "1") == 0){
        REPL();
    }
}

void REPL2(){
    printf("\nQuery of 'Where(what ROOM) is STUDENTNAME at TIME on DAY' \n");

    char* studentName = malloc(20*sizeof(char));
    printf("Enter the Student's Name: ");
    scanf(" %[^\n]s",studentName);

    char* time = malloc(10*sizeof(char));
    printf("Enter the time: ");
    scanf(" %[^\n]s",time);

    char* day = malloc(10*sizeof(char));
    printf("Enter the initials of the day: ");
    scanf(" %[^\n]s",day);

    getRoom(studentName, time, day);

    printf("Enter 1 to continue this REPL or anything else to move on: ");
    char check[100];
    scanf(" %[^\n]s",check);
    if(strcmp(check, "1") == 0){
        REPL();
    }

}

int main() {
//    TUPLELISTSNAP HTSNAP = malloc(sizeof (struct SNAP) * 1009);
//    printf("NOW SHOWING S-N-A-P relation: \n");
//
//    insert_SNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
//    insert_SNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
//    insert_SNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");
//
//    printSNAP();
//    printf("\nlookup function on 0, \"*\", \"12 Apple St.\", \"*\": \n");
//    TUPLELISTSNAP matching = lookup_SNAP(0, "*", "12 Apple St.", "*");
//    printSNAPTUPLEList(matching);
//
//    free(HTSNAP);
//    printf("\n\n");
//
//    printf("NOW SHOWING C-S-G relation: \n");
//
//    TUPLELISTCSG HTCSG = malloc(sizeof (TUPLELISTCSG) * 128);
//    insert_CSG("CS101", 12345, "A");
//    insert_CSG("CS101", 67890, "B");
//    insert_CSG("EE200", 12345, "C");
//    insert_CSG("EE200", 22222, "B+");
//    insert_CSG("CS101", 33333, "A-");
//    insert_CSG("PH100", 67890, "C+");
//    insert_CSG("CS101", 33333, "A-");
//    printCSG();
//    printf("\nlookup function on \"CS101\", 12345, \"*\": \n");
//    TUPLELISTCSG matching5 = lookup_CSG("CS101", 12345, "*");
//    printCSGTUPLEList(matching5);
//
//    printf("\n\n");
//    printf("NOW SHOWING C-P relation: \n");
//
//    TUPLELISTCP HTCP = malloc(sizeof (TUPLELISTCP) * 128);
//    insert_CP("CS101", "CS100");
//    insert_CP("EE200", "EE005");
//    insert_CP("EE200", "CS100");
//    insert_CP("CS120", "CS101");
//    insert_CP("CS121", "CS120");
//    insert_CP("CS205", "CS101");
//    insert_CP("CS206", "CS121");
//    insert_CP("CS206", "CS205");
//
//    printCP();
//
//    //TESTING FROM EXAMPLE 8.2!!!
//
//    printf("\nlookup function on \"CS205\", \"CS120\": \n");
//    TUPLELISTCP textbookTest = lookup_CP("CS205", "CS120");
//    printCPTUPLEList(textbookTest);
//
//    insert_CP("CS205", "CS120");
//    insert_CP("CS205", "CS101");
//
//    printf("lookup function on \"CS205\", \"CS120\" AFTER INSERTING IT: \n");
//    TUPLELISTCP textbookTest2 = lookup_CP("CS205", "CS120");
//    printCPTUPLEList(textbookTest2);
//
//    //TESTING '*' CAPABILITY
//    printf("\nlookup function on \"CS206\", \"*\": \n");
//    TUPLELISTCP matching4 = lookup_CP("CS206", "*");
//    printCPTUPLEList(matching4);
//        printf("\n\n");
//    printf("NOW SHOWING C-D-H relation: \n");
//
//
//    //CONCANTENATION ISSUE WHICH CAN'T BE SOLVED WITH THE ABOVE METHOD
//    TUPLELISTCDH HTCDH = malloc(sizeof (TUPLELISTCDH) * 128);
//    insert_CDH("CS101", "M", "9AM");
//    insert_CDH("CS101", "W", "9AM");
//    insert_CDH("CS101", "F", "9AM");
//    insert_CDH("EE200", "Tu", "10AM");
//    insert_CDH("EE200", "W", "1PM");
//    insert_CDH("EE200", "Th", "10AM");
//    insert_CDH("EE200", "Th", "10AM");
//    printCDH();
//    printf("\nlookup function of *, *, '9AM' : \n");
//    TUPLELISTCDH matching3 = lookup_CDH("*", "*", "9AM");
//    printCDHTUPLEList(matching3);
//
//    printf("\n\n");
//    printf("NOW SHOWING C-R relation: \n");
//    TUPLELISTCR HTCR = malloc(sizeof (TUPLELISTCR) * 128);
//    insert_CR("CS101", "Turing Aud.");
//    insert_CR("EE200", "25 Ohm Hall");
//    insert_CR("PH100", "Newton Lab.");
//    insert_CR("PH100", "Newton Lab.");
//    printCR();
//
//    printf("\nlookup function of \"CS101\", \"Turing Aud.\": \n");
//    TUPLELISTCR matching2 = lookup_CR("CS101", "Turing Aud.");
//    printCRTUPLEList(matching2);
//
//    printf("Deleting \"CS101\", \"Turing Aud.\" and printing remaining: \n");
//    delete_CR("CS101", "Turing Aud.");
//    printCR();
//
//    insert_CR("CS101", "Turing Aud."); //ADDING BACK FOR PART 2
//
//
//    //PART TWO!!!
//    printf("\n\n\n NOW TESTING PART TWO REPL \n");
////    REPL();
////    REPL2();
//
//    //PART THREE!!!!!
//    printf("\n\n NOW TESTING PART THREE \n");
//    printf("printing SELECT course='CS101' on CSG: \n");
//    TUPLELISTCSG selectedTuples = select_CSG("CS101", 0, "*");
//    printCSGTUPLEList(selectedTuples);
//
//    printf("printing PROJECT 'studentID' of SELECT course='CS101' of CSG:\n");
//    TUPLELISTid id = project_CSG(selectedTuples);
//    printID(id);
//
//    TUPLELISTCR cr = lookup_CR("*", "*");
//    TUPLELISTCDH cdh = lookup_CDH("*", "*", "*");
//    printf("printing JOIN of CR and CDH on Course:\n");
//    TUPLELISTCRDH crdh = join_CR_CDH(cr, cdh);
//    printCRDHTUPLELIST(crdh);
//
//    printf("printing PROJECT 'day, hour' of SELECT 'Turing Aud.' of JOIN of CR and CDH on Course: \n");
//    TUPLELISTCRDH crdh2 = select_CRDH("Turing Aud.", crdh);
//    TUPLELISTDH dh = project_CRDH(crdh2);
//    printDH(dh);
//    return 0;

    RealSQL * SQL= sqlinit();
    //printf("%s", SQL->root);
    attributes * a = attrInit("studentid");
    appendAttribute(a, "name");
    appendAttribute(a, "room");
    appendAttribute(a, "grade");
    //printAttributes(a);
    createTable(SQL,"Students",a);
    printf("%s\n",SQL->root->name);
    printAttributes(SQL->root->attributes);

    attributes * b = attrInit("fuckid");
    appendAttribute(b, "name");
    appendAttribute(b, "room");
    appendAttribute(b, "grade");
    createTable(SQL,"fuck",a);
    printf("%s\n",SQL->root->nextTable->name);
    printAttributes(SQL->root->nextTable->attributes);

    createTable(SQL,"Ssdafds",b);
//    printf("%s\n",SQL->root->nextTable->nextTable->name);
//    printAttributes(SQL->root->nextTable->nextTable->attributes);
}
