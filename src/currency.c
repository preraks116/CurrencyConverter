#include "../include/defs.h"
#include "../include/colors.h"
#include "../include/graph.h"

PtrCurrFromNode findCurrFromNode(PtrCurrFromNode TrvCurrFrom, char currname[]) //given the name of the currency the user wants to find as argument, this function returns a pointer to the CurrFromNode with that name
{
    for(; TrvCurrFrom->next != NULL; TrvCurrFrom = TrvCurrFrom->next) {
        if(strcmp(TrvCurrFrom->currname, currname) == 0) {
            return TrvCurrFrom;
        }
    }
    return NULL;
}

// given the name of the currency the user wants to find as argument, this function returns a pointer to the CurrToNode with that name
PtrCurrToNode findCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]) { 
    PtrCurrToNode TrvCurrTo = TrvCurrFrom->FirstCurrTo;
    while (strcmp(TrvCurrTo->currname, currname) != 0) TrvCurrTo = TrvCurrTo->next;
    return TrvCurrTo;
}

PtrCurrFromNode addCurrFromNode(PtrCurrFromNode CurrHead, char currname[]) // Adds a CurrFromNode at the end of the link list of CurrFromNodes, with its name as the string passed as an argument
{
    while (CurrHead->next != NULL) CurrHead = CurrHead->next;
    PtrCurrFromNode Temp = InitCurrFromNode();
    strcpy(Temp->currname, currname);
    CurrHead->next = Temp;
    return Temp;
}

bool CurrencyAlreadyPresent(PtrCurrFromNode TrvCurrFrom, char currname[], int mode) //takes a string as argument and returns 1 if a CurrFromNode has same name as that string, else returns 0
{
    for(; TrvCurrFrom->next != NULL; TrvCurrFrom = TrvCurrFrom->next) {
        if(strcmp(TrvCurrFrom->currname, currname) == 0) {
            if (mode == 1)
            {
                printf(RED);
                printf("\nError: Currency %s already exist\n\n", currname);
                printf(RESET);
            }
            return 1;
        }
    }
    return 0;
}

bool NoCurrencyExists(PtrBankNode BankHead, char bankname[], int mode) { //returns 1 if no currencies have been added to a bank, else returns 0
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    if (BankTrv->currno == 0)
    {
        if (mode == 1)
        {
            printf(RED);
            printf("\nError: No currencies exists in bank %s\n\n", bankname);
            printf(RESET);
        }
        return 1;
    }
    return 0;
}


// adding a CurrToNode at the end of list of CurrToNodes
void addCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]) {
    // case where the pointer to the CurrFromNode that is given as argument has no CurrToNodes linked to it
    if (TrvCurrFrom->FirstCurrTo == NULL) {
        PtrCurrToNode temp = InitCurrToNode();
        strcpy(temp->currname, currname);
        TrvCurrFrom->FirstCurrTo = temp;
    } else {
        PtrCurrToNode TrvCurrTo = TrvCurrFrom->FirstCurrTo;
        while (TrvCurrTo->next != NULL) TrvCurrTo = TrvCurrTo->next;
        PtrCurrToNode temp = InitCurrToNode();
        strcpy(temp->currname, currname);
        TrvCurrTo->next = temp;
    }
}

// adds a CurrFromNode to a bank
void addCurr(PtrBankNode BankHead, char bankname[], char currname[]) {
    PtrBankNode BankTrv = findBank(BankHead, bankname); // stores the pointer to the bank in which we need to add the currency
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;    // Traversal pointer which moves through the link list of CurrFromNodes
    if (!CurrencyAlreadyPresent(TrvCurrFrom, currname, 1))
    {
        PtrCurrFromNode NewCurr = addCurrFromNode(BankTrv->Currhead, currname); //adds a CurrFromNode at the end of link list of CurrFromNodes
        while (TrvCurrFrom->next != NewCurr)
        {
            TrvCurrFrom = TrvCurrFrom->next;
            addCurrToNode(TrvCurrFrom, currname);          //adding a CurrToNode at the end of every link list of CurrFromNodes where TrvCurrFrom is pointing to the head pointer of these lists
            addCurrToNode(NewCurr, TrvCurrFrom->currname); //adds a CurrToNode at the end of link list of CurrToNodes with NewCurr being the head pointer
        }
        addCurrToNode(NewCurr, currname);
        (BankTrv->currno)++;
        printf(GREEN); printf("\nAdded currency %s to bank %s\n\n", currname, bankname); printf(RESET);
    }
}

void printAllCurr(PtrBankNode BankHead, char bankname[]) //prints the adjacency matrix for a given bank
{
    printf("\n\n");
    PtrBankNode BankTrv = findBank(BankHead, bankname);

    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    printf("\t\t");
    //printf("\t");
    //Together these two while loops print the adjacency matrix
    while (TrvCurrFrom->next != NULL) //while loop to print the heading of each column
    {
        TrvCurrFrom = TrvCurrFrom->next;
        printf(GREEN);
        printf("%s\t\t", TrvCurrFrom->currname);
        printf(RESET);
    }

    printf("\n\n");
    TrvCurrFrom = BankTrv->Currhead;
    while (TrvCurrFrom->next != NULL) //prints heading of each row and currconv stored in each CurrToNode
    {
        TrvCurrFrom = TrvCurrFrom->next;
        PtrCurrToNode TrailCurrFrom = TrvCurrFrom->FirstCurrTo;
        printf(GREEN);
        printf("%s\t\t", TrvCurrFrom->currname);
        printf(RESET);
        while (TrailCurrFrom != NULL)
        {
            printf("%.2f\t\t", TrailCurrFrom->currconv);
            TrailCurrFrom = TrailCurrFrom->next;
        }
        printf("\n\n\n");
    }
}

void delCurr(PtrBankNode BankHead, char currname[], char bankname[], int mode) //deletes a currency from the adjacency matrix of a bank
{
    // To delete a currency from the adjaceny matrix, we need to delete the link list of CurrToNodes which has its head pointer's name as the name of the currency the user wants to delete
    // Then it deletes a node from every other link list of CurrToNodes that has its currname as the string passed as argument
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    if (!CurrencyAlreadyPresent(TrvCurrFrom, currname, 0)) //if the no currency name in the bank matches with the string given as input, the function prints an error
    {
        if (mode == 1)
        {
            printf(RED);
            printf("\nError: Currency %s does not exist in bank %s\n\n", currname, bankname);
            printf(RESET);
        }
    }
    else
    {
        PtrCurrFromNode Temp2 = findCurrFromNode(TrvCurrFrom, currname); //Temp2 stores the head pointer of the link list that needs to be deleted
        PtrCurrFromNode Temp = BankTrv->Currhead;
        while (Temp->next != Temp2) // Temp will point to the CurrFromNode right before Temp2
        {
            Temp = Temp->next;
        }
        (BankTrv->currno)--;

        if (Temp2 == BankTrv->Currhead->next) //if Temp2 is pointing to the first currency in the adjacency matrix (top left corner case)
        {
            PtrCurrFromNode TrvTemp = Temp2;
            while (TrvTemp->next != NULL) //deleting the first CurrToNode of every link list of CurrToNode
            {
                TrvTemp = TrvTemp->next;
                PtrCurrToNode TrvRowTemp = TrvTemp->FirstCurrTo;
                TrvTemp->FirstCurrTo = TrvRowTemp->next;
                free(TrvRowTemp);
            }
            PtrCurrToNode RowTemp = Temp2->FirstCurrTo; // pointing to the first CurrToNode of the list of CurrToNodes that needs to be completely deleted
            while (RowTemp->next != NULL)               //deleting entire list of CurrToNodes
            {
                PtrCurrToNode Temp3 = RowTemp->next;
                RowTemp->next = Temp3->next;
                free(Temp3);
            }
            BankTrv->Currhead->next = Temp2->next;
            free(Temp2); //deleting CurrFromNode from link list of CurrFromNodes
            printf(GREEN);
            printf("\nDeleted currency %s from bank %s\n\n", currname, bankname);
            printf(RESET);
        }
        else
        {
            TrvCurrFrom = BankTrv->Currhead;
            while (TrvCurrFrom->next != NULL)
            {
                TrvCurrFrom = TrvCurrFrom->next;
                PtrCurrToNode RowTemp = TrvCurrFrom->FirstCurrTo;
                PtrCurrToNode TrailRowTemp = RowTemp;
                while (strcmp(RowTemp->currname, currname) != 0) //finding and deleting CurrToNodes that have same currname as the currency that needs to be deleted
                {
                    TrailRowTemp = RowTemp;
                    RowTemp = RowTemp->next;
                }
                TrailRowTemp->next = RowTemp->next;
                free(RowTemp);
            }
            PtrCurrToNode S = Temp2->FirstCurrTo;
            Temp->next = Temp2->next;
            while (S->next != NULL) //deleting entire list of CurrToNodes
            {
                PtrCurrToNode Temp4 = S->next;
                S->next = Temp4->next;
                free(Temp4);
            }
            free(Temp2); //deleting CurrFromNode from link list of CurrFromNodes
            printf(GREEN);
            printf("\nDeleted currency %s from bank %s\n\n", currname, bankname);
            printf(RESET);
        }
    }
}

void findLoc(PtrCurrFromNode P, char currfrom[], char currto[], float currconv) //adds conversion rate at specified location in the adjacency matrix
{
    P = findCurrFromNode(P, currfrom);
    PtrCurrToNode Q = findCurrToNode(P, currto);
    Q->currconv = currconv;
}

void addConv(PtrBankNode BankHead, char currfrom[], char currto[], float currconv, char bankname[], int mode) //checks for errors and if none then calls findLoc and adds conversion rate to adjacency matrix
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    if (CurrencyAlreadyPresent(BankTrv->Currhead, currfrom, 0))
    {
        if (CurrencyAlreadyPresent(BankTrv->Currhead, currto, 0))
        {
            if (strcmp(currto, currfrom) == 0)
            {
                printf(RED);
                printf("\nError: Conversion between same currency not possible\n\n");
                printf(RESET);
            }
            else
            {
                PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
                findLoc(TrvCurrFrom, currfrom, currto, currconv);
                if (mode == 1)
                {
                    printf(GREEN);
                    printf("\nAdded conversion %s to %s to bank %s\n\n", currfrom, currto, bankname);
                    printf(RESET);
                }
                else
                {
                    printf(GREEN);
                    printf("\nDeleted conversion %s to %s in bank %s\n\n", currto, currfrom, bankname);
                    printf(RESET);
                }

            }
        }
        else
        {
            printf(RED);
            printf("\nError: Currency %s does not exist in %s\n\n", currto, bankname);
            printf(GREEN);
        }
    }
    else
    {
        printf(RED);
        printf("\nError: Currency %s does not exist in %s\n\n", currfrom, bankname);
        printf(GREEN);
    }
}
