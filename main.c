#include <stdio.h>
#include "database.h"

int main() {
    TUPLELISTSNAP HTSNAP = malloc(sizeof (struct SNAP) * 1009);
    printf("NOW SHOWING S-N-A-P relation: \n");

    insert_SNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
    insert_SNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
    insert_SNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");

    printSNAP();
    printf("\nlookup function on 0, \"*\", \"12 Apple St.\", \"*\": \n");
    TUPLELISTSNAP matching = lookup_SNAP(0, "*", "12 Apple St.", "*");
    printSNAPTUPLEList(matching);

    free(HTSNAP);
    printf("\n\n");

    printf("NOW SHOWING C-S-G relation: \n");

    TUPLELISTCSG HTCSG = malloc(sizeof (TUPLELISTCSG) * 128);
    insert_CSG("CS101", 12345, "A");
    insert_CSG("CS101", 67890, "B");
    insert_CSG("EE200", 12345, "C");
    insert_CSG("EE200", 22222, "B+");
    insert_CSG("CS101", 33333, "A-");
    insert_CSG("PH100", 67890, "C+");
    insert_CSG("CS101", 33333, "A-");
    printCSG();
    printf("\nlookup function on \"CS101\", 12345, \"*\": \n");
    TUPLELISTCSG matching5 = lookup_CSG("CS101", 12345, "*");
    printCSGTUPLEList(matching5);

    printf("\n\n");
    printf("NOW SHOWING C-P relation: \n");
    
    TUPLELISTCP HTCP = malloc(sizeof (TUPLELISTCP) * 128);
    insert_CP("CS101", "CS100");
    insert_CP("EE200", "EE005");
    insert_CP("EE200", "CS100");
    insert_CP("CS120", "CS101");
    insert_CP("CS121", "CS120");
    insert_CP("CS205", "CS101");
    insert_CP("CS206", "CS121");
    insert_CP("CS206", "CS205");

    printCP();

    //TESTING FROM EXAMPLE 8.2!!!

    printf("\nlookup function on \"CS205\", \"CS120\": \n");
    TUPLELISTCP textbookTest = lookup_CP("CS205", "CS120");
    printCPTUPLEList(textbookTest);

    insert_CP("CS205", "CS120");
    insert_CP("CS205", "CS101");

    printf("lookup function on \"CS205\", \"CS120\" AFTER INSERTING IT:");
    TUPLELISTCP textbookTest2 = lookup_CP("CS205", "CS120");
    printCPTUPLEList(textbookTest2);

    //TESTING '*' CAPABILITY
    printf("\nlookup function on \"CS206\", \"*\": \n");
    TUPLELISTCP matching4 = lookup_CP("CS206", "*");
    printCPTUPLEList(matching4);
        printf("\n\n");
    printf("NOW SHOWING C-D-H relation: \n");


    //CONCANTENATION ISSUE WHICH CAN'T BE SOLVED WITH THE ABOVE METHOD
    TUPLELISTCDH HTCDH = malloc(sizeof (TUPLELISTCDH) * 128);
    insert_CDH("CS101", "M", "9AM");
    insert_CDH("CS101", "W", "9AM");
    insert_CDH("CS101", "F", "9AM");
    insert_CDH("EE200", "Tu", "10AM");
    insert_CDH("EE200", "W", "1PM");
    insert_CDH("EE200", "Th", "10AM");
    insert_CDH("EE200", "Th", "10AM");
    printCDH();
    printf("\nlookup function of *, *, '9AM' : \n");
    TUPLELISTCDH matching3 = lookup_CDH("*", "*", "9AM");
    printCDHTUPLEList(matching3);

    printf("\n\n");
    printf("NOW SHOWING C-R relation: \n");
    TUPLELISTCR HTCR = malloc(sizeof (TUPLELISTCR) * 128);
    insert_CR("CS101", "Turing Aud.");
    insert_CR("EE200", "25 Ohm Hall");
    insert_CR("PH100", "Newton Lab.");
    insert_CR("PH100", "Newton Lab.");
    insert_CR("CS101", "DELETE ME ROOM");
    printCR();

    printf("\nlookup function of \"CS101\", \"Turing Aud.\": \n");
    TUPLELISTCR matching2 = lookup_CR("CS101", "Turing Aud.");
    printCRTUPLEList(matching2);

    printf("Deleting \"CS101\", \"DELETE ME ROOM\": \n");
    delete_CR("CS101", "DELETE ME ROOM");
    printCR();


   return 0;
}