#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int	print_c(const char c, int counts)
{
	if (c == '\0')
		return counts;
	if(write(1,&c,1) == -1)
		return -1;
	counts++;
	return counts;
}
int print_s(const char *str, int counts)
{
	if (str == NULL)
		str = "(null)";
	int i = 0;
	while(str[i])
	{
		counts = print_c(str[i], counts);
		if(counts == -1)
			return-1;
		i++;
	}
	return counts;
}

int	print_d(int nb, int counts)
{
	long long temp;
	char c;

	temp = nb;
	if (temp < 0)
	{
		counts = print_c('-',counts);
		if (counts == -1)
			return -1;
		temp = -temp;
	}
	if (temp >= 10)
	{
		counts = print_d(temp / 10, counts);
		if(counts == -1)
			return -1;
	}
	c = temp % 10 +'0';
	counts =print_c(c, counts);
	if (counts == -1)
		return -1;
	return counts;
}

int	print_x(unsigned int nb, int counts, const char format)
{
	char *hex = "0123456789abcdef";
	//char *hexup = "0123456789ABCDEF";
	int rem = 0;
	char c = '\0';

	if (nb >= 16)
	{
		counts = print_x(nb / 16, counts ,format);
		if(counts == -1)
			return -1;
	}
	rem = nb % 16;
	if (format == 'x')
	{
		c = hex[rem];
	}
	counts = print_c(c, counts);
	if (counts == -1)
		return -1;
	return counts;
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int counts = 0;

	va_start (args, format);
	while (*format)
	{
		if(*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				counts = print_d(va_arg(args, int), counts);
				if(counts == -1)
					return -1;
			}
			else if (*format == 's')
			{
				counts = print_s(va_arg(args, char *), counts);
				if(counts == -1)
					return -1;

			}
			else if (*format == 'x')
			{
				counts = print_x(va_arg(args, unsigned int), counts, *format);
				if(counts == -1)
					return -1;
			}
		}
		else
		{
			counts = print_c(*format, counts);
			if(counts == -1)
			return -1;
		}
		format++;
	}
	va_end(args);
	return counts;
}


char *gnl(int fd)
{
	static int readsize;
	static int offset;
	char line[70000];
	static char buf[42];
	char *cur;

	cur = NULL;
	int i = 0;
	while (1)
	{
		if (offset >= readsize)
		{
			readsize = read(fd, buf, 42);
			if (readsize == -1)
				return NULL;
			if (readsize == 0)
			{
				if (i > 0)
					break;
				return NULL;
			}
			offset = 0;
		}
		cur= buf +offset;
		line[i] = *cur;
		offset++;
		if (line[i] == '\n')
			break;
		i++;
	}
	i++;
	line[i] = '\0';
	return ft_strdup(line);
}

char *gnl2(int fd)
{
	static int	readsize;
	static char buf[42];
	static int	offset;
	char line[55555];
	char *cur;
	int i = 0;
	while (1)
	{
		if (offset >= readsize)
		{
			readsize = read(fd, buf, 42);
			if(readsize == -1)
				return NULL;
			if (readsize == 0)
			{
				if (i > 0)
					break;
				return NULL;
			}
			offset = 0;
		}
		cur = buf + offset;
		line[i] = *cur;
		offset++;
		if (line[i] == '\n')
			break;
		i++;
	}
	i++;
	line[i] = '\0';
	return ft_strdup(line);
}