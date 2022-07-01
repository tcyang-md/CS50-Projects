#include <cs50.h>
#include <stdio.h>

bool checkCard(long card)
{
    int sum = 0;
    long digit = 100;
    int digitVal = 0;

    // sum of every other digit starting from second to last
    while (card / digit != 0)
    {
        // get the digit value
        digitVal = (card % digit) / (digit / 10);
        digitVal *= 2;
        //printf("This is digit: %i\n", digitVal);

        // double digit catch
        if (digitVal >= 10)
        {
            sum += 1 + (digitVal % 10);
        }
        else
        {
            sum += digitVal;
        }

        // next digit
        digit *= 100;
    }

    // gets last digit
    digitVal = (card % digit) / (digit / 10);
    digitVal *= 2;
    //printf("This is digit: %i\n", digitVal);
    if (digitVal >= 10)
    {
        sum += 1 + (digitVal % 10);
    }
    else
    {
        sum += digitVal;
    }

    //printf("%i\n", sum);

    // gets the remaining digits starting from last on the right
    digitVal = 0;
    digit = 10;
    while (card / digit != 0)
    {
        digitVal = (card % digit) / (digit / 10);
        //printf("This is digit: %i\n", digitVal);

        sum += digitVal;

        digit *= 100;

    }
    // catch last digit
    digitVal = (card % digit) / (digit / 10);
    //printf("This is digit: %i\n", digitVal);
    sum += digitVal;

    return (sum % 10 == 0);
}

int main(void)
{
    // get credit card number
    long cardNum = get_long("Number: ");
    if (cardNum > 5599999999999999)
    {
        printf("INVALID\n");
    }
    else if ((cardNum / 5500000000000000 != 0 || cardNum / 5400000000000000 != 0 || cardNum / 5300000000000000 != 0 ||
              cardNum / 5200000000000000 != 0 || cardNum / 5100000000000000 != 0) && checkCard(cardNum))
    {
        printf("MASTERCARD\n");
    }
    else if ((cardNum / 4000000000000000 != 0) && checkCard(cardNum))
    {
        printf("VISA\n");
    }
    else if (cardNum / 370000000000000 != 0 && checkCard(cardNum))
    {
        printf("AMEX\n");
    }
    else if ((cardNum < 370000000000000 && cardNum > 340000000000000))
    {
        printf("INVALID\n");
    }
    else if (cardNum / 340000000000000 != 0 && checkCard(cardNum))
    {
        printf("AMEX\n");
    }
    else if ((cardNum / 4000000000000 != 0) && checkCard(cardNum))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}