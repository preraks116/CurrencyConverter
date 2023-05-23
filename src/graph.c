#include "../include/graph.h"

PtrListNode InitListNode() //initializes a ListNode
{
    PtrListNode P = (PtrListNode)malloc(sizeof(ListNode));
    P->index = 0;
    P->currconv = 0;
    P->next = 0;
    return P;
}

PtrPQueueNode newPNode(int n, int dist) // to create a PQueue node
{
    PtrPQueueNode PNode = (PtrPQueueNode)malloc(sizeof(PQueueNode));
    PNode->n = n;
    PNode->dist = dist;
    return PNode;
}

PtrPQueue createPQueue(int capacity) // To create a priority queue of capacity equal to no. of vertices
{
    PtrPQueue pQueue = (PtrPQueue)malloc(sizeof(struct PQueue));
    pQueue->position = (int *)malloc(capacity * sizeof(int)); // position array's size would be no. of vertices as it keeps track of position of vertices in pqueue
    pQueue->size = 0;                                         //initially size is 0 as no minheap node is created
    pQueue->capacity = capacity;                              //capacity is fixed,always equal to no. of vertices
    pQueue->node = (PtrPtrPQueueNode)malloc(capacity * sizeof(PtrPQueueNode));
    return pQueue;
}

PtrPQueueNode extractMin(PtrPQueue pQueue) // to extarct minimum node from pqueue which would be first node
{
    if (isEmpty(pQueue))
        return NULL;

    PtrPQueueNode root = pQueue->node[0]; // store the first node in root node and do operations on it

    PtrPQueueNode lastNode = pQueue->node[pQueue->size - 1]; //here root node is replaced with last node
    pQueue->node[0] = lastNode;

    pQueue->position[root->n] = pQueue->size - 1; // positions are updated in array for above replacement
    pQueue->position[lastNode->n] = 0;

    --pQueue->size;        // size is decreased by one as one node is extracted,capacity or size of array will remain same
    minHeapify(pQueue, 0); // heapify the root to make sure minheap condition is followed

    return root;
}

bool IsInPqueue(PtrPQueue PQueue, int n) // to check whether vertex n is priority queue or not
{
    if (PQueue->position[n] < PQueue->size) // if it is not there then it would be outside the current size of priority queue
    {
        return true;
    }
    return false;
}

bool iscycle(PtrListNode P, bool visited[], bool stack[], PtrListNode AdjList[]) // recursive function to check if the nodes were visited before
{
    PtrListNode T = P;
    if (visited[T->index] == false)
    {
        visited[T->index] = true;
        stack[T->index] = true;
        P = AdjList[P->index];
        while (P->next != NULL)
        {
            P = P->next;
            // printf("%d\n", P->index);
            if (!visited[P->index] && iscycle(P, visited, stack, AdjList)) // recursively checking the iscycle function for vertices adjacent to the first one
            {
                //printf(" Go %d\n",P -> index);
                return true;
            }
            else if (stack[P->index])
            {
                return true;
            }
        }
    }
    stack[T->index] = false; // equal to removing the element of the stack
    return false;
}

void swapMinHeapNode(PtrPtrPQueueNode a, PtrPtrPQueueNode b) //swap 2 pqueue nodes,would be required as during heapify swapping is must
{
    PtrPQueueNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(PtrPQueue pQueue, int index) // heapify process is there to make PQueue follow the minheap condition
{                                            // that every node is smaller than its children
    int smallest, left, right;               // Here in this function we will also swap nodes and change their position in  position array
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;

    if (left < pQueue->size && pQueue->node[left]->dist < pQueue->node[smallest]->dist)
        smallest = left;

    if (right < pQueue->size && pQueue->node[right]->dist < pQueue->node[smallest]->dist)
        smallest = right;

    if (smallest != index)
    {
        PtrPQueueNode smallestNode = pQueue->node[smallest]; // Nodes which are neded to be swapped in minheap
        PtrPQueueNode idxNode = pQueue->node[index];         // so that condition of minheap is followed

        pQueue->position[smallestNode->n] = index; // here positions of nodes are changed
        pQueue->position[idxNode->n] = smallest;   // which would be swapped

        swapMinHeapNode(&pQueue->node[smallest], &pQueue->node[index]); // the nodes are swapped here

        minHeapify(pQueue, smallest); //need to recursively call this function to convert entire tree in minheap
    }
}

void decreaseKey(PtrPQueue pQueue, int n, int dist) // function to update the distance value(decrease distance particullarly) in heap nodes
{
    int i = pQueue->position[n]; // here position array is used to get the position of particular vertex in minheap directly

    pQueue->node[i]->dist = dist; // get to node with the help if i found above and update its distance value

    while (i && pQueue->node[i]->dist < pQueue->node[(i - 1) / 2]->dist) //travel up the tree while checking with parent that whether minheap condition is followed or not
    {
        pQueue->position[pQueue->node[i]->n] = (i - 1) / 2; // if minheap condition is not followed you will enter in loop
        pQueue->position[pQueue->node[(i - 1) / 2]->n] = i; // and keep on swapping node with parent untill minheap condition is not followed,swap position in position array also
        swapMinHeapNode(&pQueue->node[i], &pQueue->node[(i - 1) / 2]);

        i = (i - 1) / 2; ///go to next parent
    }
}

int cmpfunc(const void *p, const void *q) // comparator function in qsort
{
    Ptrstore u = (Ptrstore)p;
    Ptrstore v = (Ptrstore)q;
    return (u->cost - v->cost);
}

int isEmpty(PtrPQueue pQueue) //to check if PQueue is empty or not
{
    return pQueue->size == 0; // if size is 0 that means there are no minheap nodes in our priority queue.
}
