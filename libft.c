#include "philo.h"

static inline bool is_space(char c)
{
    return ((c >= 9 && c <= 13) || 32 == c);
}

static inline bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static const char *valid_input(const char *str)
{
    int len;
    const char *number;

    len = 0;
    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
        error_exit("Negative number");
    if (!is_digit(*str))
        error_exit("Invalid number");
    number = str;
    while (is_digit(number[len]))
        len++;
    if (len > 10)
        error_exit("Number > INT_MAX");
    return (number);
}

long ft_atol(const char *str)
{
    long num;

    num = 0;
    str = valid_input(str);
    while (is_digit(*str))
    {
        num = num * 10 + *str - '0';
        str++;
    }
    if (num > INT_MAX)
        error_exit("Number > INT_MAX");
    return (num);
}

void ft_memset(void *s, int c, size_t n)
{
    unsigned char *ptr;

    ptr = (unsigned char *)s;
    while (n--)
        *ptr++ = (unsigned char)c;
}