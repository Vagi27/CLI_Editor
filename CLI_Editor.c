#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

char arr[50][100];
int top = -1;

// input functions
struct Node *newNode(int, char[], int);
void pushAtBegin(struct Node **, struct Node *);
void push(char *);
void deleteArray(int);
void print();
void printhead(struct Node *);
struct Node *undopop();
struct Node *redopop();
void undostack();
void redo();

struct Node
{
    int position;
    char string[100];
    int operation;
    struct Node *next;
} *head = NULL, *redoStack = NULL;

int main()
{
    
    int choice = 0;
    char info[50];
    
    do
    {
        printf("\nEnter any character to execute operations: ");
        getch();
        printf("\n\n**********  This is a Command Line Editor **********\n");
        printf("\tWhat is your choice of operation.\n");
        printf("\t 1. Input \n");
        printf("\t 2. Delete \n");
        printf("\t 3. Print \n");
        printf("\t 4. Undo \n");
        printf("\t 5. Redo \n");
        // printf("\t 6. Search \n");
        printf("\tEnter any other key to EXIT.\n\n");
        printf("Enter from 1 to 6:\t");

        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
            printf("Enter String: ");
            gets(info);
            top++;
            strcpy(arr[top], info);
            struct Node *node = newNode(top + 1, info, choice);
            pushAtBegin(&head, node);
            break;

        case 2:
            if (top >= 0)
            {
                printf("\nTotal number of inputs are:  %d\n", top + 1);
                printf("Enter which position to delete?:   ");
                int pos;
                scanf("%d", &pos);
                if (pos > top + 1)
                    printf("\n\tOUT OF BOUNDS!\n\t**Enter a valid position!**\n");
                else
                {
                    struct Node *node = newNode(pos, arr[pos - 1], 2);
                    pushAtBegin(&head, node);
                    deleteArray(pos - 1);
                    printf("****Deletion Successful!****\n");
                }
            }
            else
            {
                printf("\tString is Empty!!\n\t TRY AGAIN!\n");
            }
            break;

        case 3:
            if (!(top < 0))
            {
                print();
            }
            else
                printf("\n\t*String is Empty!*\n");
            break;

        case 4: // checking linked list data.
            undostack();
            break;
            // case 4:
            //     // undo();
            //     // head=Delete(head);
            //     break;

        case 5:
            redo();
            // printhead(redoStack);

            break;

            // case 6:
            //
            //     break;
        }

    } while (choice >= 1 && choice <= 6);

    return 0;
}

struct Node *newNode(int pos, char arr[], int op)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->position = pos;
    strcpy(node->string, arr);
    node->operation = op;
    node->next = NULL;
    return node;
}

// void push(struct Node *)
// {
// }

void pushAtBegin(struct Node **head, struct Node *node)
{
    if (*head == NULL)
    {
        *head = node;
    }
    else
    {
        node->next = *head;
        *head = node;
    }
}

void print()
{
    for (int i = 0; i <= top; i++)
    {
        printf("line[%d]: %s\n", i+1, arr[i]);
    }
}

void deleteArray(int pos)
{

    for (int i = pos; i <= top - 1; i++)
    {
        strcpy(arr[i], arr[i + 1]);
    }

    top--;
}

// void printhead(struct Node *head)
// {
//     struct Node *ptr = head;
//     while (ptr != NULL)
//     {
//         printf("position:[%d] \tstring: %s\n", ptr->position, ptr->string);
//         ptr = ptr->next;
//     }
// }

void undostack()
{
    if (head == NULL)
    {
        printf("\t**No Operation Performed**\n\t**Cannot Undo**\n");
        return;
    }

    struct Node *node = undopop();
    if (node->operation == 1)
    {
        deleteArray(node->position - 1);
    }
    else if (node->operation == 2)
    {
        int i;
        top++;

        for (i = top - 1; i >= node->position - 1; i--)
        {
            strcpy(arr[i + 1], arr[i]);
        }
        strcpy(arr[i + 1], node->string);
    }
    struct Node *redoNode = newNode(node->position, node->string, node->operation);
    pushAtBegin(&redoStack, redoNode);
    printf("\t** UNDO Successful!!**\n");
}

struct Node *undopop()
{

    struct Node *node = head;
    head = head->next;
    return node;
}

struct Node *redopop()
{

    struct Node *node = redoStack;
    redoStack = redoStack->next;
    return node;
}

void redo()
{
    if (redoStack == NULL)
    {
        printf("\n\tUnsuccessful!!\n");
        return;
    }
    struct Node *redoNode = redopop();
    // printf("%s----", redoNode->string);
    if (redoNode->operation == 1)
    {
        int i;
        top++;
        for (i = top - 1; i >= redoNode->position - 1; i--)
        {
            strcpy(arr[i + 1], arr[i]);
        }
        strcpy(arr[i + 1], redoNode->string);
    }
    else if (redoNode->operation == 2)
    {
        deleteArray(redoNode->position - 1);
    }
    printf("\t** REDO Successful!!**\n");

    struct Node *node = newNode(redoNode->position, redoNode->string, redoNode->operation);
    pushAtBegin(&head, node);
}