#include "OtherUseful.h"


int intLength(int tocount, int base) 
{
    int digits = 0;
    while (tocount)
    {
        ++digits;
        tocount /= base;
    }
    return digits;
}

int power10(int power) //power > 0
{
    int value = 1;
    if (power > 0)
    {
        for (int i = 0; i < power; i++)
            value *= 10;
    }
    return value;
}

int findMax(const int* tab, int length)
{
    int highest = 0;
    for (int i = 0; i < length; i++)
        if (tab[i] > highest)
            highest = tab[i];
    return highest;
}

void boolSet(Bool* pointer, Bool value, int length)
{
    for (int i = 0; i < length; i++)
        pointer[i] = value;
}