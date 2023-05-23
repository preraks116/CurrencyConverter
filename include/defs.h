#ifndef DEFS_H_
#define DEFS_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define max 1e5 + 5
#define max 1e5 + 5


typedef struct bankNode BankNode;
typedef struct bankNode * PtrBankNode;

typedef struct currFromNode CurrFromNode;
typedef struct currFromNode * PtrCurrFromNode;

typedef struct currToNode CurrToNode;
typedef struct currToNode * PtrCurrToNode;

struct bankNode //these nodes contain information about the banks that have been added
{
    char bankname[20]; //name of the bank
    int currno; //stores the number of currencies in the bank
    PtrBankNode next; // points to the next bankNode
    PtrCurrFromNode Currhead; //points to the first node in the adjacency matrix
};

// Every conversion is done FROM a currency TO a currency, so 2 different structs have been defined for the same
// Currencies in each bank are stored in the form of adjacency matrix


struct currFromNode //CurrFromNodes are head pointers for the link list of CurrToNodes
{
    char currname[20]; //name of the currency
    PtrCurrFromNode next; //points to the next CurrFromNode
    PtrCurrToNode FirstCurrTo; //points to the first CurrToNode
};

struct currToNode
{
    char currname[20];
    float currconv; //stores the conversion rate of the currency name of the currFromNode this node is linked to, to the currency that currname of this node stores.
    PtrCurrToNode next; //points to the next CurrToNode
};

PtrBankNode InitBankNode();
PtrBankNode findBank(PtrBankNode BankHead, char bankname[]);

PtrCurrFromNode InitCurrFromNode();
PtrCurrFromNode findCurrFromNode(PtrCurrFromNode TrvCurrFrom, char currname[]);
PtrCurrFromNode addCurrFromNode(PtrCurrFromNode CurrHead, char currname[]);

PtrCurrToNode InitCurrToNode();
PtrCurrToNode findCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]);

bool BankDoesntExist(PtrBankNode BankHead, char bankname[],int mode);
bool NoBanksExist(PtrBankNode BankHead,int mode);
bool CurrencyAlreadyPresent(PtrCurrFromNode TrvCurrFrom, char currname[],int mode);
bool NoCurrencyExists(PtrBankNode BankHead, char bankname[],int mode);
bool cycle(PtrBankNode BankHead,char bankname[]);

void addBank(PtrBankNode BankHead, char bankname[]);
void printBanks(PtrBankNode BankHead);
void addCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]);
void addCurr(PtrBankNode BankHead, char bankname[], char currname[]);
void printAllCurr(PtrBankNode BankHead,char bankname[]);
void delCurr(PtrBankNode BankHead, char currname[],char bankname[],int mode);
void findLoc(PtrCurrFromNode P, char currfrom[],char currto[],float currconv);
void addConv(PtrBankNode BankHead,char currfrom[],char currto[],float currconv, char bankname[], int mode);
void delBank(PtrBankNode BankHead,char bankname[]);
void bestConv(PtrBankNode BankHead,char currfrom[],char currto[]);

int getConv(PtrCurrFromNode P, char currfrom[], char currto[]);
int getList(PtrBankNode BankHead, char currfrom[], char currto[], char bankname[]);

#endif