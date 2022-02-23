#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NumberOfNodes 20 //Max nodes

#define NilValue -1

typedef enum {
    FALSE, TRUE
} boolean;

typedef int ListElementType;
typedef int ListPointer;

typedef struct {
    ListElementType Data; //Data of the node
    ListPointer Next;   //Pointer to the next node
} NodeType;

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateLList(ListPointer *List);
boolean EmptyLList(ListPointer List);
boolean FullLList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void TraverseLinked(ListPointer List, NodeType Node[]);
void menu(int *choice);
void sort_list(ListPointer *List, NodeType Node[], boolean Ascending);
void swap(ListPointer PrevPtr, ListPointer CurrentPtr, ListPointer NextPtr, NodeType Node[], ListPointer *List);

main(){
    boolean Ascending;  //If true then asc. else desc.
    ListPointer List, FreePtr, PredPtr = NilValue;
    NodeType Node[NumberOfNodes];
    ListElementType choice;
    int Item, i, n;

    CreateLList(&List);

    InitializeStoragePool(Node, &FreePtr);  //Pool with the nodes

    while(1){
        printf("Enter number of integers: ");
        scanf("%d",&n);
        if(n > 1 && n < 20)break;   //Numbers must be more than 1 and less than 20
    }

    for(i=0; i<n; i++){
        printf("Enter an integer: ");
        scanf("%d",&Item);
        Insert(&List, Node, &FreePtr, PredPtr, Item);
    }

    menu(&choice);

    Ascending = TRUE;
    if(choice == 2) //If choice was desc.
        Ascending = FALSE;

    sort_list(&List, Node, Ascending);

    TraverseLinked(List, Node); //Show the numbers

    system("PAUSE");
}

//Create 20 empty nodes
void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr){
    int i;

    for(i=0; i<NumberOfNodes-1; i++){
        Node[i].Next=i+1;
        Node[i].Data=-1;
    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes-1].Data=NilValue;
    *FreePtr=0;
}

//Create a list
void CreateLList(ListPointer *List){
    *List=NilValue;
}

//Check if the list is empty
boolean EmptyLList(ListPointer List){
    return (List==NilValue);
}

//Check if the list is full
boolean FullLList(ListPointer FreePtr){
    return (FreePtr == NilValue);
}

//Get a node
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]){
    *P = *FreePtr;
    if(!FullLList(*FreePtr))
        *FreePtr =Node[*FreePtr].Next;
}

//Insert a node in the list
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item){
    ListPointer TempPtr;
    GetNode(&TempPtr,FreePtr,Node);
    if(!FullLList(TempPtr)) {
        if(PredPtr==NilValue){
            Node[TempPtr].Data =Item;
            Node[TempPtr].Next =*List;
            *List =TempPtr;
        }
        else{
            Node[TempPtr].Data =Item;
            Node[TempPtr].Next =Node[PredPtr].Next;
            Node[PredPtr].Next =TempPtr;
        }
    }
    else
        printf("Full List ...\n");
}

//Show the data of the nodes
void TraverseLinked(ListPointer List, NodeType Node[]){
    ListPointer CurrPtr;

    if (!EmptyLList(List)){
        CurrPtr =List;
        while (CurrPtr != NilValue){
            printf("%d ",Node[CurrPtr].Data);
            CurrPtr=Node[CurrPtr].Next;
        }
        printf("\n");
    }
    else
        printf("Empty List ...\n");
}

void menu(int *choice){
    printf("--------------------------SELECT--------------------------\n");
    printf("1. Sort Ascending \n");
    printf("2. Sort Descending \n");

    while(1){
        printf("Choice 1-2: ");
    	scanf("%d", choice);
    	if(*choice == 1 || *choice == 2)
            break;
    }
}

void sort_list(ListPointer *List, NodeType Node[], boolean Ascending){
    ListPointer PrevPtr, CurrPtr, NextPtr, OutPtr;
    boolean change = FALSE;

    if(!EmptyLList(*List)){
        OutPtr = *List;

        while(OutPtr != NilValue){
            CurrPtr = *List;
            PrevPtr = NilValue;
            NextPtr = Node[CurrPtr].Next;

            while(NextPtr != NilValue){
                change = FALSE;

                if(Ascending){
                    if(Node[CurrPtr].Data > Node[NextPtr].Data){
                        change = TRUE;
                    }
                }
                else{
                    if(Node[CurrPtr].Data < Node[NextPtr].Data){
                        change = TRUE;
                    }
                }
                if(change == TRUE){
                    swap(PrevPtr, CurrPtr, NextPtr, Node, List);
                    if(OutPtr == CurrPtr)
                        OutPtr = NextPtr;
                }
                PrevPtr = CurrPtr;
                CurrPtr = NextPtr;
                NextPtr = Node[CurrPtr].Next;
            }
            OutPtr = Node[OutPtr].Next;
        }
    }
    else
        printf("Empty List \n");
}

void swap(ListPointer PrevPtr, ListPointer CurrentPtr, ListPointer NextPtr, NodeType Node[], ListPointer *List){
    if(CurrentPtr == *List)
        *List = Node[CurrentPtr].Next;

    Node[CurrentPtr].Next = Node[NextPtr].Next;
    Node[NextPtr].Next = CurrentPtr;

    if(PrevPtr != NilValue)
        Node[PrevPtr].Next = NextPtr;
}
