#include <stdio.h>
#include "database.h"

void main() {
    TUPLELISTSNAP HTSNAP = malloc(sizeof (struct SNAP) * 1009);

    insert_SNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
    insert_SNAP(12345, "C. Brown", "24 Apple St.", "555-1234");
    insert_SNAP(67890, "C. Brown", "12 Apple St.", "555-1234");
    insert_SNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
    insert_SNAP(67890, "L. Van Pelt", "68 Pear Ave.", "555-5678");

    insert_SNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");
    insert_SNAP(22222, "C. Brown", "12 Apple St.", "555-1234");
    insert_SNAP(23432, "C. Brown", "12 Apple St.", "555-1234");

    printSNAP();
    printf("\nlookup function: \n");
    TUPLELISTSNAP matching = lookup_SNAP(0, "*", "12 Apple St.", "*");
    printSNAPTUPLEList(matching);

    free(HTSNAP);

}