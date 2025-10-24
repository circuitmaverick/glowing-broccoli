#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} NODE;

// recursive function to create sll
// dynamically according to number of nodes as per user
NODE* createSLL() {
    NODE* new = (NODE*)malloc(sizeof(NODE));
    if(new == NULL) { printf("\nMEMORY ALLOCATION FAILED\n"); return NULL; }
    printf("Enter value: ");
    scanf("%d", &new->val);
    char choice;
    printf("Add new node? (y/N) ");
    scanf("%c", &choice);
    switch (choice) {
        case 'y':
        case 'Y':
            new->next = createSLL();
            break;
        default:
            new->next = NULL;
            break;
    }
    return new;
}

// recursive function to delete sll
void deleteSLL(NODE* sll) {
    NODE *temp = sll->next;
    free(sll);
    if(temp != NULL) deleteSLL(temp);
    else return;
}

// recursive function to traverse sll
void traverseSLL(NODE* sll) {
    printf("%d", sll->val);
    if(sll->next) { printf(" -> "); traverseSLL(sll->next); }
    else return;
}

// recursive function to count nodes
int countNodes(NODE* sll) {
    if(sll) return 1 + countNodes(sll->next);
    else return 0;
}

// function to insert node at beginning
NODE* insertAtBeginning(NODE* sll, int ele) {
    NODE* new = (NODE*)malloc(sizeof(NODE));
    if(new == NULL) { printf("\nMEMORY ALLOCATION FAILED\n"); return sll; }
    new->val = ele;
    new->next = sll;
    return new;
}

// function to insert node at end
void insertAtEnd(NODE* sll, int ele) {
    NODE *new = (NODE*)malloc(sizeof(NODE));
    if(new == NULL) { printf("\nMEMORY ALLOCATION FAILED\n"); return; }
    new->val;
    new->next=NULL;
    while(sll->next != NULL) sll = sll->next;
    sll->next = new;
}

NODE* insertAtPos(NODE* sll, int pos, int ele) {
    NODE* start = sll;
    if(pos == 1) start = insertAtBeginning(sll, ele);
    else {
        while(sll->next != NULL && pos>2) {
            sll = sll->next;
            pos--;
        }
        if(pos!=2) { printf("\nPosition out of bounds\n"); }
        else {
            NODE* new = (NODE*)malloc(sizeof(NODE));
            if(new == NULL) { printf("\nMEMORY ALLOCATION FAILED\n"); return; }
            new->val = ele;
            new->next = sll->next?sll->next->next:NULL;
            sll->next = new;
        }
    }
    return start;
}

void insertAfterEle(NODE* sll, int key, int ele) {
    NODE *new = (NODE*)malloc(sizeof(NODE));
    if(new == NULL) { printf("\nMEMORY ALLOCATION FAILED\n"); return; }
    new->val = ele;
    int flag = 0;
    while(sll->next!=NULL && !flag) {
        if(sll->val == key) { flag = 1; break; }
        sll = sll->next;
        if(sll->val == key) { flag = 1; break; }
    }
    if(flag) {
        new->next = sll->next->next;
        sll->next = new;
    } else printf("\nGiven element not found...\n");
}

int deleteAtBeginning(NODE** sll) {
    NODE* temp = *sll;
    *sll = (*sll)->next;
    int val = temp->val;
    free(temp);
    return val;
}

int deleteAtEnd(NODE** sll) {
    NODE* prev = NULL, *temp = NULL, *curr = *sll; int val;
    if((*sll)->next = NULL) {
        temp = *sll;
        val = temp->val;
        *sll = NULL;
        free(temp);
        return val;
    }
    while(curr->next = NULL) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    temp = curr;
    val = curr->val;
    free(temp);
    return val;
}

int deleteAtPos(NODE** sll, int pos) {
    NODE *curr = *sll, *temp; int val;
    if(pos == 1) return deleteAtBeginning(sll);
    while(curr->next != NULL && pos>=2) {
        curr = curr->next;
        pos--;
    }
    if(pos != 2) { printf("\nPosition out of bounds\n"); return 0; }
    temp = curr->next;
    curr->next = curr->next->next;
    val = temp->val;
    free(temp);
    return val;
}

int deleteAfterEle(NODE* sll, int key) {
    int flag = 0, val = 0; NODE* prev = NULL;
    while(sll->next != NULL) {
        if(sll->val == key) { flag = 1; break; }
        prev = sll;
        sll = sll->next;
        if(sll->val == key) { flag = 1; break; }
    }
    if(flag) {
        prev->next = sll->next;
        val = sll->val;
        free(sll);
    } else printf("\nGiven element not found\n");
    return val;
}

NODE* reverseSLL(NODE* sll) {
    if (sll == NULL || sll->next == NULL) {
        return sll;
    }
    NODE* rest = reverseSLL(sll->next);
    sll->next->next = sll;
    sll->next = NULL;
    return rest;
}



void main() {
    NODE* sll1 = NULL, *sll2 = NULL;
    while(1) {
        int choice;
        printf("\n-------MENU--------\n");
        printf("\n1\tCREATE SLL");
        printf("\n2\tDELETE SLL");
        printf("\n3\tTRAVERSE");
        printf("\n4\tCOUNT NODES");
        printf("\n5\tINSERT");
        printf("\n6\tDELETE");
        printf("\n7\tREVERSE");
        printf("\n8\tAPPEND 2 SLL");;
        printf("\n9\tFIND MIDDLE WITHOUT COUNTING");
        printf("\n10\tFIND MAX");
        printf("\n11\tFIND MIN");
        printf("\n12\tSORT");
        printf("\n\n0\tEXIT\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if(sll1 == NULL && sll2 == NULL) {
                int sllchoice;
                printf("\nSelect SLL to create:\n\n1\tSLL1\n2\tSLL2\n");
                scanf("%d", &sllchoice);
                switch (sllchoice)
                {
                case 1:
                    printf("\nCreating SLL1...\n");
                    sll1 = createSLL();
                    break;
                case 2:
                    printf("\nCreating SLL2...\n");
                    sll2 = createSLL();
                default:
                    printf("\nSelect a valid sll...");
                    break;
                }
            }
            else if(sll1 == NULL) { printf("Creating SLL1..."); sll1 = createSLL(); }
            else if(sll2 == NULL) { printf("Creating SLL2..."); sll2 = createSLL(); }
            else printf("Delete an SLL to create another one...");
            break;
        case 2:
            int sllchoice;
            printf("\nSelect SLL to delete:\n\n1\tSLL1\n2\tSLL2\n");
            scanf("%d", &sllchoice);
            switch (sllchoice)
            {
            case 1:
                if (sll1 == NULL) printf("\nEmpty SLL\n");
                else {
                    printf("\nDeleting SLL1...\n");
                    deleteSLL(sll1);
                    printf("\nDeleted SLL1\n");
                }
                break;
            case 2:
                if (sll2 == NULL) printf("\nEmpty SLL\n");
                else {
                    printf("\nDeleting SLL2...\n");
                    deleteSLL(sll2);
                    printf("\nDeleted SLL2\n");
                }
                break;
            default:
                break;
            }
            break;
        case 3:
            printf("\nSelect SLL to traverse:\n\n1\tSLL1\n2\tSLL2\n");
            int sllchoice;
            scanf("%d", &sllchoice);
            switch (sllchoice)
            {
            case 1:
                printf("\nTraversing SLL1...\n");
                traverseSLL(sll1);
                break;
            case 2:
                printf("\nTraversing SLL2...\n");
                traverseSLL(sll2);
                break;
            default:
                break;
            }
            break;
        case 4:
            printf("\nSelect SLL to count nodes:\n\n1\tSLL1\n2\tSLL2\n");
            int sllchoice;
            scanf("%d", &sllchoice);
            switch (sllchoice)
            {
            case 1:
                printf("\nNodes in SLL1: %d\n", countNodes(sll1));
                break;
            case 2:
                printf("\nNodes in SLL2: %d\n", countNodes(sll2));
                break;
            default:
                break;
            }
        case 5:
            printf("\nSelect SLL to insert node:\n\n1\tSLL1\n2\tSLL2\n");
            int sllchoice;
            scanf("%d", &sllchoice);
            printf("\nInsert at...\n\n\t1\t beginning\n\t2\tend\n\t3\ti-th position\n\t4\tafter element\n");
            int opchoice;
            scanf("%d", opchoice);
            printf("\nEnter element: ");
            int ele;
            scanf("%d", &ele);
            switch (opchoice)
            {
            case 1:
                // insert at beginning
                switch (sllchoice)
                {
                case 1:
                    // insert in sll1
                    sll1 = insertAtBeginning(sll1, ele);
                    break;
                case 2:
                    // insert in sll2
                    sll2 = insertAtBeginning(sll2, ele);
                    break;
                default:
                    break;
                }
                break;
            case 2:
                // insert at end
                switch (sllchoice)
                {
                case 1:
                    // insert at sll1
                    insertAtEnd(sll1, ele);
                    break;
                case 2:
                    // insert at sll2
                    insertAtEnd(sll2, ele);
                    break;
                default:
                    break;
                }
                break;
            case 3:
                // insert at i-th position
                int i;
                printf("\nEnter i-th position: ");
                scanf("%d", &i);
                switch (sllchoice)
                {
                case 1:
                    insertAtPos(sll1, i, ele);
                    break;
                case 2:
                    insertAtPos(sll2, i, ele);
                    break;
                default:
                    break;
                }
                break;
            case 4:
                // insert after given element
                int key;
                printf("\nEnter after which element to insert: ");
                scanf("%d", &key);
                switch (sllchoice)
                {
                case 1:
                    insertAfterEle(sll1, key, ele);
                    break;
                case 2:
                    insertAfterEle(sll2, key, ele);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        case 6:
            printf("\nSelect SLL to insert node:\n\n1\tSLL1\n2\tSLL2\n");
            int sllchoice;
            scanf("%d", &sllchoice);
            printf("\Delete at...\n\n\t1\t beginning\n\t2\tend\n\t3\ti-th position\n\t4\tafter element\n");
            int opchoice;
            scanf("%d", opchoice);
            int ele;
            switch (opchoice)
            {
            case 1:
                // delete first node
                switch (sllchoice)
                {
                case 1:
                    ele = deleteAtBeginning(&sll1);
                    break;
                case 2:
                    ele = deleteAtBeginning(&sll2);
                    break;
                default:
                    break;
                }
                break;
            case 2:
                // delete last node
                switch (sllchoice)
                {
                case 1:
                    ele = deleteAtEnd(&sll1);
                    break;
                case 2:
                    ele = deleteAtEnd(&sll1);
                    break;
                default:
                    break;
                }
                break;
            case 3:
                // delete node at i-th positino
                printf("Enter the i-th position: ");
                int i;
                scanf("%d", &i);
                switch (sllchoice)
                {
                case 1:
                    ele = deleteAtPos(&sll1, i);
                    break;
                case 2:
                    ele = deleteAtPos(&sll2, i);
                    break;
                default:
                    break;
                }
                break;
            case 4:
                // delete node after a given element
                printf("\nEnter the element after which to delete: ");
                int key;
                scanf("%d", &key);
                switch (sllchoice)
                {
                case 1:
                    ele = deleteAfterEle(sll1, key);
                    break;
                case 2:
                    ele = deleteAfterEle(sll2, key);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            printf("\nDeleted: %d\n", ele);
            break;
        case 7:
            // reverse
            break;
        case 8:
            // append 2 sll
            break;
        case 9:
            // find mid without counting
            break;
        case 10:
            // find max
            break;
        case 11:
            // find min
            break;
        case 12:
            // sort
            break;
        default:
            break;
        }
    }
}
