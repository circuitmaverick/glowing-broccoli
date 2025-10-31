#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {
    struct node *prev, *next;
    int val;
} NODE;

typedef enum sortdirection {
    asc, desc
} SORTORDER;

// create dll function (recursive)
NODE* createDLL(NODE *prev) {
    NODE *new = (NODE *)malloc(sizeof(NODE));
    if(!new) { printf("\nMEMORY ALLOCATION FAILED\n"); return NULL; }
    printf("\nEnter value: ");
    scanf("%d", &new->val);
    new->prev = prev; new->next = NULL;
    getchar();
    printf("Add element? (Y/n) ");
    char addelechoice; scanf("%c", &addelechoice);
    switch (addelechoice)
    {
    case 'n':
    case 'N':
        new->next = NULL;
        break;
    default:
        new->next = createDLL(new);
        break;
    }
    return new;
}

// delete a dll function (recursive)
NODE *deleteDLL(NODE* dll) {
    if(!dll) { printf("\nDLL doesn't exist\n"); }
    if(dll->next) return deleteDLL(dll->next);
    free(dll);
    return NULL;
}

// traverse dll function (recursive);
void traverseDLL(NODE *dll) {
    if(!dll) { printf("\nDLL doesn't exist\n"); return; }
    printf(" %d ", dll->val);
    if(dll->next) { printf("<->"); traverseDLL(dll->next); }
    else printf("\n");
}

// count nodes in dll function (recursive)
int countNodes(NODE *dll) {
    if(!dll) return 0;
    return 1+countNodes(dll->next);
}

// insert functions

// insert at beginning
void insertAtBeginning(NODE **dll, int val) {
    NODE *new = (NODE*)malloc(sizeof(NODE));
    if(!new) { printf("\nMEMORY ALLOCATION FAILED\n"); return; }
    new->val = val; new->prev = NULL; new->next = *dll;
    *dll = new;
    printf("\nElement inserted at the beginning\n");
}

// insert at end
void insertAtEnd(NODE **dll, int val) {
    NODE *new = (NODE*)malloc(sizeof(NODE));
    if(!new) { printf("\nMEMORY ALLOCATION FAILED\n"); return; }
    new->val = val; new->next = NULL;
    if(!*dll) { new->prev = NULL; *dll = new; }
    NODE *curr = *dll;
    while(curr->next) curr=curr->next;
    curr->next = new;
    new->prev = curr;
    printf("Element inserted at the end\n");
}

// insert at i-th position
void insertAtPos(NODE **dll, int val, int pos) {
    if(!*dll) { printf("\nDLL doesn't exist.\n"); return; }
    NODE *new = (NODE*)malloc(sizeof(NODE));
    new->val = val;
    if(pos == 1) return insertAtBeginning(dll, val);
    int i=1; NODE *curr = *dll;
    while(curr->next) {
        if(pos == i) break;
        curr = curr->next;
        i++;
    }
    if(pos == i+1) { free(new); return insertAtEnd(dll, val); }
    else if(pos != i) { printf("\nPosition out of bounds\n"); free(new); return; }
    new->next = curr;
    new->prev = curr->prev;
    curr->prev->next = new;
    curr->prev = new;
    printf("\nElement inserted at position %d\n", pos);
}

// insert after an element
void insertAfterEle(NODE *dll, int val, int key) {
    if(!dll) { printf("\nDLL doesn't exist\n"); return; }
    NODE *new = (NODE*)malloc(sizeof(NODE));
    if(!new) { printf("\nMEMORY ALLOCATION FAILED\n"); return; }
    new->val = val;
    while(dll) {
        if(dll->val == key) break;
        dll = dll->next;
    }
    if(!dll) { printf("\nElement not found\n"); return; }
    new->next = dll->next;
    new->prev = dll;
    if(dll->next) dll->next->prev = new;
    dll->next = new;
    printf("\nElement inserted after element %d\n", key);
}

// delete functions

// delete from beginning
int deleteFromBeginning(NODE **dll) {
    if(!*dll) { printf("\nEmpty DLL\n"); return 0; }\
    NODE *curr = *dll; int val;
    if(!curr->next) {
        *dll = NULL;
        val = curr->val;
        free(curr);
        return val;
    }
    curr->next->prev = NULL;
    *dll = curr->next;
    val = curr->val;
    free(curr);
    return val;
}

// delete from end      FIXING REQUIRED
int deleteFromEnd(NODE **dll) {
    if(!*dll) { printf("\nEmpty DLL\n"); return 0; }
    NODE *curr = *dll; int val;
    if(!curr->next) {
        val = curr->val;
        free(curr);
        *dll = NULL;
        return val;
    }
    while(curr->next) curr = curr->next;
    curr->prev->next = NULL;
    val = curr->val;
    free(curr);
    return val;
}

// delete from position
int deleteFromPos(NODE **dll, int pos) {
    if(!*dll) { printf("\nEmpty DLL\n"); return 0; }
    NODE *curr = *dll; int val, i=1;
    if(pos == 1) return deleteFromBeginning(dll);
    while(curr->next) {
        if(pos==i) break;
        curr=curr->next; i++;
    }
    if(pos==i+1) return deleteFromEnd(dll);
    else if(pos!=i) { printf("\nPosition out of bounds\n"); return 0; }
    val = curr->val;
    curr->prev->next = curr->next;
    if(curr->next) curr->next->prev = curr->prev;
    free(curr);
    return val;
}

// delete an element
int deleteEle(NODE *dll, int key) {
    if(!dll) { printf("\nEmpty DLL\n"); return 0; }
    while(dll) {
        if(dll->val == key) break;
        dll = dll->next;
    }
    if(!dll || !dll->next) { printf("\nElement not found\n"); return 0; }
    dll->next->prev = dll->prev;
    dll->prev->next = dll->next;
    int val = dll->val;
    free(dll->next);
    return val;
}

// reverse dll
void reverseDLL(NODE **dll) {
    if(!*dll) { printf("\nEmpty DLL\n"); return; }
    if(!(*dll)->next) return;
    NODE *curr = *dll, *prev = NULL, *next=NULL;
    while(curr) {
        next = curr->next;
        curr->prev = next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *dll = prev;
}

// append two dll and store in the former dll
void appendDLL(NODE **dll1, NODE **dll2) {
    if(!*dll1 || !*dll2) {
        printf("\nEnter two valid DLLs.\n"); return;
    }
    NODE *curr = *dll1;
    while(curr->next) curr = curr->next;
    curr->next = *dll2;
    (*dll2)->prev = curr;
    *dll2 = NULL;
}

// find mid element without counting
int findMid(NODE *dll) {
    if(!dll) {
        printf("\nEmpty DLL\n"); return 0;
    }
    if(!dll->next) return dll->val;
    NODE *jumper = dll;
    while(jumper) {
        jumper->next?(jumper = jumper->next->next): (jumper = jumper->next);
        dll = dll->next;
    }
    return dll->prev->val;
}

// find max element
int findMax(NODE *dll) {
    if(!dll) {
        printf("\nEmpty DLL\n"); return 0;
    }
    int max = dll->val;
    while(dll) {
        dll->val > max ? (max = dll->val): max;
        dll = dll->next;
    }
    return max;
}

// find min element
int findMin(NODE *dll) {
    if(!dll) {
        printf("\nEmpty DLL\n"); return 0;
    }
    int min = dll->val;
    while(dll) {
        dll->val < min ? (min = dll->val): min;
        dll = dll->next;
    }
    return min;
}

// swap two nodes in a dll
void swapNodes(NODE **node1, NODE **node2) {
    int temp = (*node1)->val;
    (*node1)->val = (*node2)->val;
    (*node2)->val = temp;
}

void sortDLL(NODE *dll, SORTORDER order) {
    if(!dll) { printf("\nEmpty DLL\n"); return; }
    if(!(dll)->next) return;
    NODE *curr; int length = countNodes(dll);
    for(int i=0; i<length - 1; i++) {
        curr = dll;
        bool swapped = false;
        for(int j=0; j<length-i-1; j++, curr=curr->next) {
            switch (order)
            {
            case asc:
                if(curr->val > curr->next->val) {
                    swapNodes(&curr, &curr->next);
                    swapped = true;
                }
                break;
            case desc:
                if(curr->val < curr->next->val) {
                    swapNodes(&curr, &curr->next);
                    swapped = true;
                }
            default:
                break;
            }
        }
        if(!swapped) break;
    }
}

void main() {
    NODE *dll1 = NULL, *dll2 = NULL;
    while (1)
    {
        int choice;
        printf("\n-------MENU--------\n");
        printf("\n1\tCREATE DLL");
        printf("\n2\tDELETE DLL");
        printf("\n3\tTRAVERSE");
        printf("\n4\tCOUNT NODES");
        printf("\n5\tINSERT");
        printf("\n6\tDELETE");
        printf("\n7\tREVERSE");
        printf("\n8\tAPPEND 2 DLL");
        printf("\n9\tFIND MIDDLE WITHOUT COUNTING");
        printf("\n10\tFIND MAX");
        printf("\n11\tFIND MIN");
        printf("\n12\tSORT");
        printf("\n\n0\tEXIT\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int dllchoice, val, key;
        switch (choice)
        {
        case 1:
            // create a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            switch (dllchoice)
            {
            case 1:
                dll1 = createDLL(NULL);
                break;
            case 2:
                dll2 = createDLL(NULL);
                break;
            default:
                printf("\nInvalid DLL\n");
                break;
            }
            printf("\nCreated DLL\n");
            break;
        case 2:
            // delete a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            switch (dllchoice)
            {
            case 1:
                dll1 = deleteDLL(dll1);
                break;
            case 2:
                dll2 = deleteDLL(dll2);
                break;
            default:
                printf("\nInvalid DLL\n");
                break;
            }
            printf("\nDeleted DLL\n");
            break;
        case 3:
            // traverse a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            switch (dllchoice)
            {
            case 1:
                traverseDLL(dll1);
                break;
            case 2:
                traverseDLL(dll2);
                break;
            default:
                printf("\nInvalid DLL\n");
                break;
            }
            break;
        case 4:
            // count nodes of a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            switch (dllchoice)
            {
            case 1:
                printf("\nNo. of nodes in DLL1: %d\n", countNodes(dll1));
                break;
            case 2:
                printf("\nNo. of nodes in DLL2: %d\n", countNodes(dll2));
                break;
            default:
                printf("\nInvalid DLL\n");
                break;
            }
            break;
        case 5:
            // insert element in a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            int insertchoice;
            printf("Select where to insert:\n\n\t1\tbeginning\n\t2\tend\n\t3\ti-th position\n\t4\tafter an element\n\n>\t");
            scanf("%d", &insertchoice);
            printf("\nEnter element to insert: ");
            scanf("%d", &val);
            switch (insertchoice)
            {
            case 1:
                // insert element at beginning of the dll
                if(dllchoice == 1) insertAtBeginning(&dll1, val);
                else if(dllchoice == 2) insertAtBeginning(&dll2, val);
                else printf("\nInvalid DLL\n");
                break;
            case 2:
                // insert element at the end of the dll
                if(dllchoice == 1) insertAtEnd(&dll1, val);
                else if(dllchoice == 2) insertAtEnd(&dll2, val);
                else printf("\nInvalid DLL\n");
                break;
                break;
            case 3:
                // insert element at i-th position in the dll
                printf("\nEnter position (starts from 1): "); scanf("%d", &key);
                if(dllchoice == 1) insertAtPos(&dll1, val, key);
                else if(dllchoice == 2) insertAtPos(&dll2, val, key);
                else printf("\nInvalid DLL\n");
                break;
            case 4:
                // insert elemenet after an element in the dll
                printf("\nEnter element after which to insert: "); scanf("%d", &key);
                if(dllchoice == 1) insertAfterEle(dll1, val, key);
                else if(dllchoice == 2) insertAfterEle(dll2, val, key);
                else printf("\nInvalid DLL\n");
                break;
            default:
                printf("\nInvalid choice\n");
                break;
            }
            break;
        case 6:
            // delete element from a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            int deletechoice;
            printf("Select where to delete:\n\n\t1\tbeginning\n\t2\tend\n\t3\ti-th position\n\t4\element\n\n>\t");
            scanf("%d", &deletechoice);
            switch (deletechoice)
            {
            case 1:
                // delete from beginning
                if(dllchoice == 1) printf("\nDeleted from DLL1: %d\n", deleteFromBeginning(&dll1));
                else if(dllchoice == 2) printf("\nDeleted from DLL2: %d\n", deleteFromBeginning(&dll2));
                else printf("\nInvalid DLL\n");
                break;
            case 2:
                // delete from end
                if(dllchoice == 1) printf("\nDeleted from DLL1: %d\n", deleteFromEnd(&dll1));
                else if(dllchoice == 2) printf("\nDeleted from DLL2: %d\n", deleteFromEnd(&dll2));
                else printf("\nInvalid DLL\n");
                break;
            case 3:
                // delete from i-th position
                printf("\nEnter position: "); scanf("%d", &key);
                if(dllchoice == 1) printf("\nDeleted from DLL1: %d\n", deleteFromPos(&dll1, key));
                else if(dllchoice == 2) printf("\nDeleted from DLL2: %d\n", deleteFromPos(&dll2, key));
                else printf("\nInvalid DLL\n");
                break;
            case 4:
                // delete after an element
                printf("\nEnter element: "); scanf("%d", &key);
                if(dllchoice == 1) printf("\nDeleted from DLL1: %d\n", deleteEle(dll1, key));
                else if(dllchoice == 2) printf("\nDeleted from DLL2: %d\n", deleteEle(dll2, key));
                else printf("\nInvalid DLL\n");
                break;
            default:
                printf("\nInvalid choice\n");
                break;
            }
            break;
        case 7:
            // reverse a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            switch (dllchoice)
            {
            case 1:
                reverseDLL(&dll1); printf("\nReversed DLL\n");
                break;
            case 2:
                reverseDLL(&dll2); printf("\nReversed DLL\n");
                break;
            default:
                printf("\nInvalid DLL\n");
                break;
            }
            break;
        case 8:
            // append two double linked lists into the former one
            printf("Select DLL:\n\n1\tDLL1<->DLL2\n2\tDLL2<->DLL1\n>\t");
            scanf("%d", &dllchoice);
            if(dllchoice == 1) appendDLL(&dll1, &dll2);
            else if(dllchoice == 2) appendDLL(&dll2, &dll2);
            break;
        case 9:
            // find middle element in a double linked list without counting
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            if(dllchoice==1) printf("\nMid of DLL1: %d\n", findMid(dll1));
            else if(dllchoice==2) printf("\nMid of DLL2: %d\n", findMid(dll2));
            else printf("\nInvalid DLL\n");
            break;
        case 10:
            // find max element from a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            if(dllchoice==1) printf("\nMax of DLL1: %d\n", findMax(dll1));
            else if(dllchoice==2) printf("\nMax of DLL2: %d\n", findMax(dll2));
            else printf("\nInvalid DLL\n");
            break;
        case 11:
            // find min element from a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            if(dllchoice==1) printf("\nMin of DLL1: %d\n", findMin(dll1));
            else if(dllchoice==2) printf("\nMin of DLL2: %d\n", findMin(dll2));
            else printf("\nInvalid DLL\n");
            break;
        case 12:
            // sort elements in a double linked list
            printf("Select DLL:\n\n1\tDLL1\n2\tDLL2\n>\t");
            scanf("%d", &dllchoice);
            printf("Enter order:\n\n\t0\tASCENDING\n\t1\tDESCENDING\n");
            SORTORDER order; scanf("%d", &order);
            if(dllchoice==1) sortDLL(dll1, order);
            else if(dllchoice==2) sortDLL(dll2, order);
            else printf("\nInvalid DLL\n");
            break;
        default: return;
            break;
        }
    }
}