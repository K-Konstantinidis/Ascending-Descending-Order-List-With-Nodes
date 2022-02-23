#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NumberOfNodes 20

#define NilValue -1

typedef enum {
    FALSE, TRUE
} boolean;

typedef int ListElementType;

typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer Next;
} NodeType;

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateLList(ListPointer *List);
boolean EmptyLList(ListPointer List);
boolean FullLList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);

void menu(int *choice);

void sort_list(ListPointer *List, NodeType Node[], boolean Ascending);
void swap(ListPointer PrevPtr, ListPointer CurrentPtr, ListPointer NextPtr, NodeType Node[], ListPointer *List);

main(){
    boolean Ascending;
    ListPointer List, FreePtr, PredPtr = NilValue;
    NodeType Node[NumberOfNodes];
    ListElementType choice;
    int Item, i, n;

    CreateLList(&List);

    InitializeStoragePool(Node, &FreePtr);

    while(1){
        printf("Enter number of integers: ");
        scanf("%d",&n);
        if(n > 1 && n < 20)break;
    }

    for(i=0; i<n; i++){
        printf("Enter an integer: ");
        scanf("%d",&Item);

        Insert(&List, Node, &FreePtr, PredPtr, Item);
    }

    menu(&choice);

    Ascending = TRUE;
    if(choice == 2)
        Ascending = FALSE;

    sort_list(&List, Node, Ascending);

    TraverseLinked(List, Node);

    system("PAUSE");
}

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

void CreateLList(ListPointer *List){
    *List=NilValue;
}

boolean EmptyLList(ListPointer List){
    return (List==NilValue);
}

boolean FullLList(ListPointer FreePtr){
    return (FreePtr == NilValue);
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]){
    *P = *FreePtr;
    if(!FullLList(*FreePtr))
        *FreePtr =Node[*FreePtr].Next;
}

void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr){
    Node[P].Next =*FreePtr;
    Node[P].Data = -1;
    *FreePtr =P;
}

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

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr){
    ListPointer TempPtr ;

    if(!EmptyLList(*List))
        if(PredPtr == NilValue){
            TempPtr =*List;
            *List =Node[TempPtr].Next;
            ReleaseNode(Node,TempPtr,FreePtr);
        }
        else
        {
            TempPtr =Node[PredPtr].Next;
            Node[PredPtr].Next =Node[TempPtr].Next;
            ReleaseNode(Node,TempPtr,FreePtr);
        }
    else
        printf("Empty List ...\n");
}

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
