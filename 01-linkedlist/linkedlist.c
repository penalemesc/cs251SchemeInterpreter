#include "linkedlist.h"

// Create a new EMPTY_TYPE value node.
SchemeVal *makeEmpty()
{
    SchemeVal *head = malloc(sizeof(EMPTY_TYPE));
    head->type = EMPTY_TYPE;
    return head;
}

// Create a new CONS_TYPE value node.
SchemeVal *cons(SchemeVal *newCar, SchemeVal *newCdr)
{
    SchemeVal *cons = malloc(sizeof(CONS_TYPE));
    cons->type = CONS_TYPE;
    cons->car = newCar;
    cons->cdr = newCdr;
    return cons;
}

// Display the contents of the linked list to the screen in some kind of
// readable format
void display(SchemeVal *list)
{
    
}

// questions for dave: how does the output of assert work? Like does it return 1 if not true and 0 if true?
// We have to malloc a list in makeEmpty, how do we calculate the size that we need to malloc it as?
// Where should we put the behaviours of schemeval type? It is mentioned we should use a switch,
// thus should we make a schemeval.c that checks what happens when a list is of type x?
// or does it go into linkedlist.c?

// If code is written correctly then assert is never happening
// So what we want to check for example is in length we want to make sure that value is never c null, but yes
// scheme null which means that the check could/should be something like value == null, because if we malloc everything correclty
// then it will be != because it is of empty_type (which is scheme null, rather than c null)