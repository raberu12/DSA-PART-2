#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myheader.h"

// [ANSWER No. 1] insert your function definition for removeAfter()
Node* removeAfter(Node** head, int ditem) {
    int found = 0;
    
    NodePtr *trav;
    NodePtr temp;
    NodePtr travNew = NULL;
    
    NodePtr returnList = NULL;
    NodePtr *returnTail = &returnList;

    // Find the node with data == ditem
    for (trav = head; *trav != NULL && !found; trav = &(*trav)->next) {
        if ((*trav)->data == ditem) {
            found = 1;
        }
    }
    
    // If found and not the last node
    if (found && *trav != NULL) {
        travNew = (*trav)->next;
        (*trav)->next = NULL;  // Cut off the rest of the list
        
        // Copy remaining nodes to returnList
        while (travNew != NULL) {
            temp = travNew;
            travNew = travNew->next;
            
            temp->next = NULL;  // Disconnect node from original list
            *returnTail = temp;  // Add to return list
            returnTail = &temp->next;
        }
    }
    return returnList;
}

// the main()
int main() {
	Node* head = NULL;
	int n, item;

	printf("Enter number of elements: ");
	scanf("%d", &n);

	// Input and insert nodes into the list
	for(int i = 0; i < n; ++i) {
		printf("Enter element %d: ", i+1);
		scanf("%d", &item);
		insertNode(&head, item);
	}

	printf("List: ");
	printList(head);

	int ditem;
	NodePtr removedList = NULL;

	printf("\nEnter item: ");
	scanf("%d", &ditem);

	// [ANSWER No. 2] Add function call for removeAfter()
	removedList = removeAfter(&head, ditem);

	//end of Answer No. 2

	printf("Orginal List (after delete): ");
	printList(head);
	printf("Deleted List: ");
	printList(removedList);

	return 0;
}
