#include <cs50.h>
#include <math.h>
#include <stdio.h>

int get_doubled_digits_sum(long int number);
int get_regular_digits_sum(long int number);
int get_starting_digits(long int number, int digits_count);
void check_card_type(long int number);
int length(long int number);

int main(void)
{
    long int card_number = get_long("Number: ");

    int luhn_formula_checksum =
        get_regular_digits_sum(card_number) + get_doubled_digits_sum(card_number);

    // Validate checksum before checking card type
    if (luhn_formula_checksum % 10 == 0)
    {
        check_card_type(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_doubled_digits_sum(long int number)
{
    int doubled_digit;
    int doubled_digits_sum = 0;
    long int iterator = 10; // Start from second-to-last digit

    for (int i = 0; i < length(number); i++)
    {
        doubled_digit = ((number / iterator) % 10) * 2;

        // If doubled digit is two digits, add both separately
        if (doubled_digit > 9)
        {
            for (int j = 1; j < 11; j *= 10)
            {
                doubled_digits_sum += (doubled_digit / j) % 10;
            }
        }
        else
        {
            doubled_digits_sum += doubled_digit;
        }

        iterator *= 100; // Move to the next second digit
    }

    return doubled_digits_sum;
}

int get_regular_digits_sum(long int number)
{
    int regular_digit;
    int regular_digits_sum = 0;
    long int iterator = 1;

    for (int i = 0; i < length(number); i++)
    {
        regular_digit = ((number / iterator) % 10);
        regular_digits_sum += regular_digit;

        iterator *= 100;
    }

    return regular_digits_sum;
}

int get_starting_digits(long int number, int digits_count)
{
    int starting_digits;
    long int pow = 1;

    // Shift digits right until only desired starting digits remain
    for (int i = 0; i < length(number) - digits_count; i++)
    {
        pow *= 10;
    }

    starting_digits = number / pow;

    return starting_digits;
}

void check_card_type(long int number)
{
    int len = length(number);
    int first_two = get_starting_digits(number, 2);
    int first = get_starting_digits(number, 1);

    // Identify card types based on their length and starting digits
    if ((first_two == 34 || first_two == 37) && len == 15)
    {
        printf("AMEX\n");
    }
    else if (first_two >= 51 && first_two <= 55 && len == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (first == 4 && (len == 16 || len == 13))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int length(long int number)
{
    int length = 0;

    do
    {
        number /= 10;
        length++;
    }
    while (number != 0);

    return length;
}
