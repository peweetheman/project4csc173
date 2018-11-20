#include <stdio.h>
#include "database.h"

void main() {
//    TUPLELISTSNAP HTSNAP = malloc(sizeof (struct SNAP) * 1009);
//
//    insert_SNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
//    insert_SNAP(12345, "C. Brown", "24 Apple St.", "555-1234");
//    insert_SNAP(67890, "C. Brown", "12 Apple St.", "555-1234");
//    insert_SNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
//    insert_SNAP(67890, "L. Van Pelt", "68 Pear Ave.", "555-5678");
//
//    insert_SNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");
//    insert_SNAP(22222, "C. Brown", "12 Apple St.", "555-1234");
//    insert_SNAP(23432, "C. Brown", "12 Apple St.", "555-1234");
//
//    printSNAP();
//    printf("\nlookup function: \n");
//    TUPLELISTSNAP matching = lookup_SNAP(0, "*", "12 Apple St.", "*");
//    printSNAPTUPLEList(matching);
//
//    free(HTSNAP);


//    TUPLELISTCSG HTCSG = malloc(sizeof (TUPLELISTCSG) * 128);
//    insert_CSG("CS101", 12345, "A");
//    insert_CSG("CS101", 67890, "B");
//    insert_CSG("EE200", 12345, "C");
////    insert_CSG("EE200", 22222, "B+");
//    insert_CSG("CS101", 33333, "A-");
//    insert_CSG("PH100", 67890, "C+");
//    insert_CSG("CS101", 33333, "A-");
//    printCSG();
//    printf("\nlookup function: \n");
//    TUPLELISTCSG matching = lookup_CSG("CS101", 0, "*");
//    printCSGTUPLEList(matching);


//for whatever reason, C concantenates the strings automatically so I need an arbitrary number to print the strings out without concantenation...
//so use -1
//    TUPLELISTCP HTCP = malloc(sizeof (TUPLELISTCP) * 128);
//    insert_CP("CS101", "CS100", -1);
//    insert_CP("EE202", "EE005", -1);
//    insert_CP("EE200", "CS100", -1);
//    insert_CP("CS120", "CS101", -1);
//    insert_CP("CS121", "CS120", -1);
//    insert_CP("CS205", "CS101", -1);
//    insert_CP("CS206", "CS121", -1);
//    insert_CP("CS206", "CS205", -1);
//    insert_CP("CS206", "CS205", -1);
//    printCP();
//    printf("\nlookup function: \n");
//    TUPLELISTCP matching = lookup_CP("CS206", "*");
//    printCPTUPLEList(matching);


    //CONCANTENATION ISSUE WHICH CAN'T BE SOLVED WITH THE ABOVE METHOD
//    TUPLELISTCDH HTCDH = malloc(sizeof (TUPLELISTCDH) * 128);
//    insert_CDH("CS101", "M", "9AM", -1);
//    insert_CDH("CS101", "W", "9AM", -1);
//    insert_CDH("CS101", "F", "9AM", -1);
//    insert_CDH("EE200", "Tu", "10AM", -1);
//    insert_CDH("EE200", "W", "1PM", -1);
//    insert_CDH("EE200", "Th", "10AM", -1);
//    insert_CDH("EE200", "Th", "10AM", -1);
//    printCDH();
//    printf("\nlookup function: \n");
//    TUPLELISTCDH matching = lookup_CDH("*", "*", "9AM");
//    printCDHTUPLEList(matching);

//for some reason the insert command causes a memory error
    TUPLELISTCR HTCR = malloc(sizeof (TUPLELISTCR) * 128);
    insert_CR("CS101", "Turing Aud.", -1);
    insert_CR("EE200", "25 Ohm Hall", -1);
    insert_CR("PH100", "Newton Lab.", -1);
    insert_CR("PH100", "Newton Lab.", -1);

    printCR();
    printf("\nlookup function: \n");
    TUPLELISTCR matching = lookup_CR("CS101", "Turing Aud.");
    printCRTUPLEList(matching);

}