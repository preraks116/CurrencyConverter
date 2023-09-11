#include "../include/defs.h"
#include "../include/colors.h"
#include "../include/graph.h"

PtrBankNode InitBankNode() // initializes a BankNode
{
    PtrBankNode P = (PtrBankNode)malloc(sizeof(BankNode));
    P->currno = 0;
    P->Currhead = NULL;
    PtrCurrFromNode Temp = InitCurrFromNode(); // initializes the Currhead node in the bank that the user is adding
    P->Currhead = Temp;
    P->next = NULL;
    return P;
}

PtrCurrFromNode InitCurrFromNode() // initializes a CurrFromNode
{
    PtrCurrFromNode P = (PtrCurrFromNode)malloc(sizeof(CurrFromNode));
    P->FirstCurrTo = NULL;
    P->next = NULL;
    return P;
}

PtrCurrToNode InitCurrToNode() // initializes a CurrToNode
{
    PtrCurrToNode P = (PtrCurrToNode)malloc(sizeof(CurrToNode));
    P->currconv = 0;
    P->next = NULL;
    return P;
}

PtrBankNode findBank(PtrBankNode BankHead, char bankname[]) // given the name of the bank we want to find as an argument, this function returns a pointer to the BankNode with that name
{
    PtrBankNode BankTrv = BankHead;
    while ((strcmp(BankTrv->bankname, bankname) != 0) && BankTrv->next != NULL)
        BankTrv = BankTrv->next;
    return BankTrv;
}

bool BankDoesntExist(PtrBankNode BankHead, char bankname[], int mode) // to check if a bank with the given name exists in the link list of BankNodes
{
    // moves through link list of BankNodes and performs strcmps to check whether the name of the BankNode matches with the string bankname passed as argument
    PtrBankNode BankTrv = BankHead;
    while (BankTrv->next != NULL)
    {
        BankTrv = BankTrv->next;
        if (strcmp(BankTrv->bankname, bankname) == 0)
        {
            return 0;
        }
    }

    if (mode == 1)
    {
        printf(RED);
        printf("\nBank %s does not exist\n\n", bankname);
        printf(RESET);
    }
    return 1;
}

bool NoBanksExist(PtrBankNode BankHead, int mode) // returns 0 if no banks exist, else returns 1
{
    PtrBankNode BankTrv = BankHead;
    if (BankTrv->next == NULL)
    {
        if (mode == 1)
        {
            printf(RED);
            printf("\nNo banks exist\n\n");
            printf(RESET);
        }
        return 1;
    }
    return 0;
}

bool cycle(PtrBankNode BankHead, char bankname[]) // finding the cycle using dfs
{
    PtrBankNode BankTrv = findBank(BankHead, bankname); // conversion of adjacency matrix to adjacency list same as the getList function
    int n = BankTrv->currno;
    char index[n][20];
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    for (int i = 0; TrvCurrFrom->next != NULL; i++)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        strcpy(index[i], TrvCurrFrom->currname);
    }

    PtrListNode AdjList[n];
    for (int i = 0; i < n; i++)
    {
        AdjList[i] = InitListNode();
        AdjList[i]->index = i;
        PtrListNode TrvRow = AdjList[i];
        for (int j = 0; j < n; j++)
        {
            int conv = getConv(BankTrv->Currhead, index[i], index[j]);
            if (conv != 0)
            {
                PtrListNode P = InitListNode();
                P->currconv = conv;
                P->index = j;
                TrvRow->next = P;
                TrvRow = P;
            }
        }
    }
    // boolean array to store the visited nodes
    // boolean stack to keep a track of elements in the stack once you've visited the nodes connecting the given node
    bool visited[n], stack[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
        PtrListNode P = AdjList[i];
        if (iscycle(P, visited, stack, AdjList))
        {
            return true;
        }
    }
    return false;
}

void addBank(PtrBankNode BankHead, char bankname[])
{ // adds a BankNode to the link list of BankNodes
    PtrBankNode BankTrv = findBank(BankHead, " ");
    PtrBankNode Temp = InitBankNode();
    strcpy(Temp->bankname, bankname);
    BankTrv->next = Temp;
    Temp->next = NULL;
    printf(GREEN), printf("\nAdded bank %s\n\n", bankname), printf(RESET);
}

// prints list of BankNodes
void printBanks(PtrBankNode BankHead)
{
    printf("\n");
    for (PtrBankNode BankTrv = BankHead->next; BankTrv != NULL; BankTrv = BankTrv->next)
    {
        printf(BOLD), printf("%s", BankTrv->bankname), printf(RESET);
        if (BankTrv->next != NULL)
            printf(", ");
    }
    printf("\n\n");
}

// deletes BankNode from list of BankNodes and deletes the adjaceny matrix of this bank if it exists
void delBank(PtrBankNode BankHead, char bankname[])
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    PtrBankNode BankTrvPrev = BankHead;
    while (BankTrvPrev->next != BankTrv)
    {
        BankTrvPrev = BankTrvPrev->next;
    }
    BankTrvPrev->next = BankTrv->next;

    for (PtrCurrFromNode A = BankTrv->Currhead->next; A != NULL; A = A->next)
    {
        delCurr(BankHead, A->currname, bankname, 2);
    }
    free(BankTrv->Currhead);
    free(BankTrv);
    printf(GREEN);
    printf("\nDeleted bank %s\n\n", bankname);
    printf(RESET);
}

void bestConv(PtrBankNode BankHead, char currfrom[], char currto[])
{
    PtrBankNode BankTrv = BankHead;
    int bankno = BankHead->currno;
    store bank[bankno];
    bool error = 1;
    for (int i = 0; BankTrv->next != NULL; i++)
    {
        BankTrv = BankTrv->next;
        if (CurrencyAlreadyPresent(BankTrv->Currhead, currfrom, 0) && CurrencyAlreadyPresent(BankTrv->Currhead, currto, 0))
        {
            error = 0;
            bank[i].cost = getList(BankHead, currfrom, currto, BankTrv->bankname);
        }
        else
        {
            bank[i].cost = max;
        }
        strcpy(bank[i].bankname, BankTrv->bankname);
    }

    if (error == 1)
    {
        printf(RED);
        printf("\nError: No bank with conversion from %s to %s exists\n\n", currfrom, currto);
        printf(RESET);
    }
    else
    {
        qsort(bank, bankno, sizeof(store), cmpfunc);
        if (bank[0].cost == max)
        {
            printf(RED);
            printf("\nError: No bank with conversion from %s to %s exists\n\n", currfrom, currto);
            printf(RESET);
        }
        else
        {
            printf(GREEN);
            printf("\nThe best conversion rate from %s to %s exists in bank %s with conversion rate %d\n\n", currfrom, currto, bank[0].bankname, bank[0].cost);
            printf(RESET);
        }
    }
}

int getList(PtrBankNode BankHead, char currfrom[], char currto[], char bankname[])
{
    // dijkstra

    // code to free the list
    // here we convert the adjacency matrix into an adjacency List to help us reduce time complexity

    int source, dest;
    PtrBankNode BankTrv = findBank(BankHead, bankname); // Pointer BankTrv is a pointer that points to the Bank as entered by the user
    int n = BankTrv->currno;
    char index[n][20];
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;

    for (int i = 0; TrvCurrFrom->next != NULL; i++)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        strcpy(index[i], TrvCurrFrom->currname);
    }

    for (int i = 0; i < n; i++)
    {
        if (strcmp(currfrom, index[i]) == 0)
        {
            source = i;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (strcmp(currto, index[i]) == 0)
        {
            dest = i;
            break;
        }
    }

    PtrListNode AdjList[n]; // This is the Adjacency List
    for (int i = 0; i < n; i++)
    {
        AdjList[i] = InitListNode(); // Initializing each node the Adjacency List
        AdjList[i]->index = i;       // The index of every Adjacency node is stored here
        PtrListNode TrvRow = AdjList[i];
        for (int j = 0; j < n; j++)
        {
            int conv = getConv(BankTrv->Currhead, index[i], index[j]); // Adding the cost of the edges to the edge nodes
            if (conv != 0)
            {
                PtrListNode P = InitListNode(); // Initialzing each node connected to the nodes of the Adj List
                P->currconv = conv;
                P->index = j;
                TrvRow->next = P;
                TrvRow = P;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf(BOLD);
        printf("%d -> ", AdjList[i]->index);
        printf(RESET);
        PtrListNode TrvRow = AdjList[i];
        while (TrvRow->next != NULL)
        {
            TrvRow = TrvRow->next;
            printf("(%d,%d) ", TrvRow->index, TrvRow->currconv);
        }
        printf("\n");
    }
    printf("\n");

    // Dijkstra
    int vertex = n;
    int v = vertex;
    int distance[v]; // distance array;
    // calling priority queue to make the algo more efficient

    PtrPQueue pq = createPQueue(v); // Creating a priority queue pq

    for (int i = 0; i < v; i++)
    {
        distance[i] = max;                      // Initialzing the distance to infinity
        pq->node[i] = newPNode(i, distance[i]); // adding nodes to pq
        pq->position[i] = i;
    }
    distance[source] = 0;
    pq->position[source] = source;
    pq->size = v;
    decreaseKey(pq, source, distance[source]); // decreasing the cost/distance
    while (!isEmpty(pq))
    {
        PtrPQueueNode pqnode;
        pqnode = extractMin(pq); // extracting the root of the pq
        int x;
        x = pqnode->n;
        for (PtrListNode P = AdjList[x]->next; P != NULL; P = P->next)
        {
            int y;
            y = P->index;
            if (IsInPqueue(pq, y) && distance[x] != max && P->currconv + distance[x] < distance[y])
            { // relaxing the cost/distance array
                distance[y] = distance[x] + P->currconv;
                decreaseKey(pq, y, distance[y]);
            }
        }
    }
    PtrListNode f, j;

    for (int i = 0; i < n; i++)
    {
        f = AdjList[i]->next;
        while (f != NULL)
        {
            j = f->next;
            free(f);
            f = j;
        }
    }

    for (int i = 0; i < n; i++)
        free(AdjList[i]);

    return distance[dest];
}

// returns conversion rate for conversion between 2 currencies
int getConv(PtrCurrFromNode P, char currfrom[], char currto[])
{
    P = findCurrFromNode(P, currfrom);
    PtrCurrToNode Q = findCurrToNode(P, currto);
    return Q->currconv;
}