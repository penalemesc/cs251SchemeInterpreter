#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
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
    if (list->car->type == CONS_TYPE)
    {
        while (list->car->type != EMPTY_TYPE)
        {
            switch (list->car->type)
            {
            case INT_TYPE:
                printf("The value at this point of the list in the car is an int and is: %i\n", list->car->i);
                break;
            case DOUBLE_TYPE:
                printf("The value at this point of the list in the car is a double and is: %f\n", list->car->d);
                break;
            case STR_TYPE:
                printf("The value at this point of the list in the car is a string and is: %s\n", list->car->s);
                break;
            case CONS_TYPE:
                printf("The value at this point of the list in the car is a cons type and is: %i, %s\n", list->car->i, list->cdr->s);
                break;
            case EMPTY_TYPE:
                printf("The value at this point of the list in the car is: ()\n");
                break;
            }

            list->car = list->cdr;
        }
    }
    else if (list->car->type == EMPTY_TYPE)
    {
        printf("The value at this point of the list is: ()\n");
    }
}

// Return a new list that is the reverse of the one that is passed in. All
// content within the list should be duplicated; there should be no shared
// memory whatsoever between the original list and the new one.
//
// FAQ: What if there are nested lists inside that list?
// ANS: There won't be for this assignment. There will be later, but that will
// be after we've got an easier way of managing memory.
// SchemeVal *reverse(SchemeVal *list)
// {
//     SchemeVal *reverseHelper = list;
//     SchemeVal *reversedPrev;
//     reversedPrev->type = EMPTY_TYPE;
//     SchemeVal *reverseCdr;

//     while (reverseHelper != EMPTY_TYPE)
//     {
//         reverseCdr = reverseHelper->cdr;
//         reverseHelper->cdr = reversedPrev->car;

//         reversedPrev = reverseHelper;
//         reverseHelper = reverseCdr;
//     }
//     return reverseHelper;
// }

SchemeVal *reverse(SchemeVal *list)
{
    assert(list != NULL);
    SchemeVal *reversed = makeEmpty(); // this starts with an empty list

    while (list->type != EMPTY_TYPE)
    {
        SchemeVal *copiedVal = malloc(sizeof(SchemeVal));
        copiedVal->type = list->car->type; // sets types to be the same

        switch (list->car->type)
        {
        case INT_TYPE:
            copiedVal->i = list->car->i;
            break;
        case DOUBLE_TYPE:
            copiedVal->d = list->car->d;
            break;
        case STR_TYPE:
            copiedVal->s = strdup(list->car->s); // this will duplicate string memory
            break;
        case EMPTY_TYPE:
            break;
        case CONS_TYPE:
            break;
        }
        reversed = cons(copiedVal, reversed);
        list = list->cdr;
    }
    return reversed;
}

// Frees up all memory directly or indirectly referred to by list. This includes strings.
//
// FAQ: What if a string being pointed to is a string literal? That throws an
// error when freeing.
//
// ANS: Don't put a string literal into the list in the first place. All strings
// added to this list should be able to be freed by the cleanup function.
//
// FAQ: What if there are nested lists inside that list?
//
// ANS: There won't be for this assignment. There will be later, but that will
// be after we've got an easier way of managing memory.
void cleanup(SchemeVal *list)
{
    assert(list != NULL);
    while (list != NULL)
    {
        
        free(list);
    }
}

// Utility to make it less typing to get car value. Use assertions to make sure
// that this is a legitimate operation.
SchemeVal *car(SchemeVal *list)
{
    return list;
}

// Utility to make it less typing to get cdr value. Use assertions to make sure
// that this is a legitimate operation.
SchemeVal *cdr(SchemeVal *list)
{
    assert(list != NULL);
    assert(list == CONS_TYPE);
    SchemeVal *cdrOfList = list->cdr;
    assert(cdrOfList != NULL);
    return cdrOfList;
}

SchemeVal *car(SchemeVal *list)
{
    assert(list != NULL);
    SchemeVal *carOfList = list->car;
    assert(carOfList != NULL);
    return carOfList;
}

// Utility to check if pointing to a NULL_TYPE value. Use assertions to make sure
// that this is a legitimate operation.
bool isEmpty(SchemeVal *value)
{
    assert(value != NULL);
    /* Tests that likely were not what was asked of us but did it late enough that it made sense
    assert(value->car->type != NULL);
    assert(value->cdr->type != NULL); */
    if (value->type == EMPTY_TYPE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Measure length of list. Use assertions to make sure that this is a legitimate
// operation.
int length(SchemeVal *value)
{
    assert(value != NULL);
    int size = 0;
    while (value->type != EMPTY_TYPE)
    {
        assert(value != NULL);
        size = size + 1;
        value = value->cdr;
    }
    return size;
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