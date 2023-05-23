#ifndef GRAPH_H_
#define GRAPH_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct ListNode ListNode;
typedef struct ListNode *PtrListNode;

typedef struct PQueueNode PQueueNode;
typedef struct PQueueNode * PtrPQueueNode;
typedef struct PQueueNode ** PtrPtrPQueueNode;

typedef struct PQueue PQueue;
typedef struct PQueue * PtrPQueue;

typedef struct store store;
typedef struct store * Ptrstore;

struct ListNode //struct for the adjacency list
{
    int index; //index of each node in the graph
    int currconv; //stores the weight of each edge in the graph, which is the conversion rate
    PtrListNode next; //points to the next List node
};

struct PQueueNode   //minheap nodes
{
    int  n;//Vertex no. or index of vertex
    int dist;// will store the current distance value of vertex
};

struct PQueue
{
    int size;   // No. of heapnodes in Pqueue present,capacity  will remain same but size will decrease when minnodes will be extracted 
    int capacity; // No. of vertices in this particular graph
    int *position; // To keep track of the position of vertex in minheap,can directly access that vertex in minheap  as its position is stored here
    PtrPtrPQueueNode node; //Will point to PqueueNode or minheap nodes
};

struct store
{
    int cost;
    char bankname[20];
};

PtrListNode InitListNode();

struct PQueueNode *newPNode(int n, int dist);
struct PQueueNode *extractMin(struct PQueue *pQueue);

struct PQueue *createPQueue(int capacity);

bool IsInPqueue(struct PQueue *pQueue, int n);
bool iscycle(PtrListNode P,bool visited[],bool stack[],PtrListNode AdjList[]);
void swapMinHeapNode(struct PQueueNode **a, struct PQueueNode **b);
void minHeapify(struct PQueue *pQueue, int index);
void decreaseKey(struct PQueue *pQueue, int n, int dist);

int cmpfunc(const void *p, const void *q);
int isEmpty(struct PQueue *pQueue);
#endif