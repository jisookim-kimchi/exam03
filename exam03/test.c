#include <unistd.h>
#include <stdarg.h>

/*
    먼저 캐릭터 프린트 출력 함수필요하고
    그러면 이걸로 문자열 출력가능,
    문제는
    %d를 어떻게 ,?
    이거는
    123 을 1,2,3 이렇게
    재귀를 하면

    long long temp = nb
    if (temp >= 10) 123 12 1
        print_d(temp / 10, counts);
    char c = temp % 10 + '0'
    write(1, &c, 1);


    unsigned int 란말이지,,,
    char *hex = "123456789abcdef";
    if (nb >= 16)
    {
        print_x(nb / 16); //15 , 255
    }
    ret = nb % 16;
    char c = hex[ret];
    print_c(1, &c, 1);
*/
int print_c(const char c, int counts)
{
    if (c == '\0')
        return counts;
    if (write(1, &c, 1)== -1)
        return -1;
    counts++;
    return counts;
}

int print_d (int nb, int counts)
{
    char c;
    long long temp;

    temp = nb;
    if (temp < 0)
    {
        counts = print_c('-', counts);
        if (counts == -1)
            return -1;
        temp = -temp;
    }
    if (10 <= temp)
    {
        counts = print_c(temp / 10, counts);
        if (counts == -1)
            return -1; 
    }
    c = temp % 10 + '0';
    if (write(1, &c, 1) == -1)
        return -1;
    return counts;
}

int print_x (unsigned int nb, int counts, const char format)
{
    char *hex = "0123456789abcdef";
    char *hexup = "0123456789ABCDEF";
    int ret = 0;
    char c;

    if (nb >= 16)
    {
        counts = print_x(nb / 16, counts , format);
        if (counts == -1)
            return;
    }
    ret = nb % 16;
    if (format == 'x')
    {
       c = hex[ret];
    }
    if (format == 'X')
    {
        c= hexup[ret];
    }
    counts = print_c(hex[ret], counts);
    if (counts == -1)
        return -1;
    return counts;
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int counts = 0;

    va_start(args, format);
    while(*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'd')
            {

            }
            else if (*format == 's')
            {

            }
            else if (*format == 'x')
            {

            }
        }
        else
        {
            if (write(1, format, 1) == -1)
                return -1;
            else
                counts++;
        }
        format++;
    }
    va_end(args);
    return counts;
}