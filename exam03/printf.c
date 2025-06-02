# include <stdarg.h>
# include <unistd.h>

int	print_c(char c, int counts)
{
	if (c == '\0')
	{
		return counts;
	}
	if (write(1, &c, 1) == -1)
		return -1;
	counts++;
	return counts;
}

int	print_s(const char *str, int counts)
{
	if (str == NULL)
	{
		str = "(null)";
	}
	int i = 0;
	while (str[i])
	{
		counts = print_c(str[i], counts);
		if (counts == -1)
			return -1;
		i++;
	}
	return counts;
}

int	print_d(int nb, int counts)
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
	if (10 <= temp) //123 1, 2 , 3
	{
		counts = print_d(temp / 10, counts); 
		if (counts == -1)
			return -1;
	}
	c = (temp % 10) + '0';
	counts = print_c(c, counts);
	if (counts == -1)
		return -1;
	return counts;
}

int	print_x(unsigned int nb, int counts, const char *format)
{
	int	ret = 0;
	char *hexlow = "0123456789abcdef";
	char *hexupp = "0123456789ABCDEF";
	char c;

	if (nb >= 16)
	{
		counts = print_x(nb / 16, counts, format);
		if (counts == -1)
			return (-1);
	}
	ret = nb % 16;
	if (*format == 'x')
	{
		c = hexlow[ret];
	}
	if (*format == 'X')
	{
		c = hexupp[ret];
	}
	counts = print_c(c, counts);
	if (counts == -1)
		return -1;
	return (counts);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		counts;

	counts = 0;
	va_start(args, format);
	while(*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				counts = print_d(va_arg(args, int), counts);
				if (counts == -1)
					return -1;
			}
			else if (*format == 's')
			{
				counts = print_s(va_arg(args, char *), counts);
				if (counts == -1)
					return -1;
			}
			else if (*format == 'x')
			{
				counts = print_x(va_arg(args, unsigned int), counts, format);
				if (counts == -1)
					return -1;
			}
			format++;
		}
		else
		{
			if (write (1, format, 1) == -1)
				return -1;
			format++;
			counts++;
		}
		
	}
	va_end(args);
	return (counts);
}

int main()
{
	int ret = ft_printf("%d", 123);
	ft_printf("%d\n", ret);

	unsigned int a = 255;
	char *str = "hello world";
	ret = ft_printf("%s\n", str);
	ft_printf("%s, %d, %x\n", str, ret, a);
}