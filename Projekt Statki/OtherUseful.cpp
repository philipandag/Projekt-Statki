


int intLength(int tocount, int base = 10) {

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