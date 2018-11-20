#include <stdio.h>
#include "database.h"

void main() {
    TUPLELISTSNAP HTSNAP = malloc(sizeof (struct SNAP) * 1009);
    initializeHTSNAP();
    insert_SNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
    insert_SNAP(12345, "C. Brown", "24 Apple St.", "555-1234");
    insert_SNAP(12345, "C. Brown", "36 Apple St.", "555-1234");
    insert_SNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
    insert_SNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");

    printSNAP();
    printf("\n");
    TUPLELISTSNAP matching = lookup_SNAP(0, "C. Brown", "*", "555-1234");
    printf("\nprinting matching:\n");
    printSNAPTUPLEList(matching);
    free(HTSNAP);

}