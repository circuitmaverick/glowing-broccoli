#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    struct node *prev, *next;
    int val;
} NODE;

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
    if(dll->next) { printf("->"); traverseDLL(dll->next); }
    else printf("\n");
}

// count nodes in dll function (recursive)
int countNodes(NODE *dll) {
    if(!dll) return 0;
    return 1+countNodes(dll->next);
}

void main() {
    NODE *dll1, *dll2;
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
        int dllchoice;
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
            break;
        case 6:
            // delete element from a double linked list
            break;
        case 7:
            // reverse a double linked list
            break;
        case 8:
            // append two double linked lists into the former one
            break;
        case 9:
            // find middle element in a double linked list without counting
            break;
        case 10:
            // find max element from a double linked list
            break;
        case 11:
            // find min element from a double linked list
            break;
        case 12:
            // sort elements in a double linked list
            break;
        default: return;
            break;
        }
    }
}