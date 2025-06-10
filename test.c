#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef BUFFERSIZE
#define BUFFERSIZE 4
#endif

int	print_c(const char c, int counts)
{
	if (c == '\0')
	{
		return counts;
	}
	if (write(1, &c, 1)== -1)
		return -1;
	counts++;
	return counts;
}

int print_d(int nb, int counts)
{
	long long temp = nb;
	char c;

	if (temp < 0)
	{
		counts = print_c('-', counts);
		if (counts == -1)
			return -1;
		temp = -temp;
	}
	if (temp >= 10)
	{
		counts = print_d(temp/10, counts);
		if (counts == -1)
			return -1;
	}
	c = temp % 10 + '0';
	counts =print_c(c, counts);
	if (counts == -1)
		return -1;
	return counts;
}

int	print_x (int nb, int counts, const char format)
{
	int remainder = 0;
	char *hexlow = "0123456789abcedf";
	char *hexup = "0123456789ABCDEF";
	char c;
	if (nb >= 16)
	{
		counts = print_x(nb / 16, counts, format);
		if (counts == -1)
			return -1;
	}
	remainder = nb % 16;
	if (format == 'x')
	{
		c = hexlow[remainder];
	}
	if (format == 'X')
	{
		c = hexup[remainder];
	}
	counts = print_c(c, counts);
	if (counts== -1)
		return -1;
	return counts;
}

int print_s(char *str, int counts)
{
	if (str == NULL)
		str = "(null)";
	int i = 0;
	while(str[i])
		i++;
	i = 0;
	while(str[i])
	{
		counts = print_c(str[i],counts);
		if (counts == -1)
			return -1;
		i++;
	}
	return counts;
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int counts = 0;

	va_start(args, format);
	while(*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
			{
				counts = print_s(va_arg(args, char *), counts);
				if (counts == -1)
					return -1;
			}
			else if (*format == 'd')
			{
				counts = print_d(va_arg(args, int), counts);
				if (counts == -1)
					return -1;
			}
			else if (*format == 'x')
			{
				counts = print_x(va_arg(args, unsigned int), counts, *format);
				if (counts == -1)
					return-1;
			}
		}
		else
		{
			counts = print_c(*format, counts);
			if (counts == -1)
				return -1;
		}
		format++;
	}
	va_end(args);
	return counts;
}

#include <stdlib.h>

char *ft_strdup(char *str)
{
	if (!str)
		return NULL;
	int i = 0;
	while (str[i])
		i++;
	char *temp = malloc(i + 1);
	if (!temp)
		return NULL;
	i = 0;
	while(str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return temp;
}

/*
	BUFFERSIZE 4
	a\n\nb
	cd[eof]

	offset : abcd
	i    :  abcd
*/
char	*gnl(int fd)
{
	static int readsize;
	static int offset;
	char line[77777];
	static char buf[BUFFERSIZE + 1];
	char *cur;

	if (fd < 0 || BUFFERSIZE <= 0)
		return NULL;
	int i = 0;
	while(1)
	{
		if (offset >= readsize)
		{
			readsize = read(fd, buf, BUFFERSIZE);
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
		cur = buf + offset;
		line[i] = *cur;
		offset++;
		if (line[i] == '\n')
		{
			break;
		}
		i++;
	}
	if (line[i] == '\n')
		i++;
	line[i] = '\0';
	return ft_strdup(line);
}

#include <fcntl.h>
int main()
{
	ft_printf("input >> \n");

	// int fd = open("test", O_RDONLY);
	// 	char *test = gnl(fd);
	// 	ft_printf("output>> %s", test);
		
	// 	test = gnl(fd);
	// 	ft_printf("output>> %s", test);

	// 	test = gnl(fd);
	// 	ft_printf("output>> %s", test);

	// 	test = gnl(fd);
	// 	ft_printf("output>> %s", test);
		
	int fd = open("test", O_RDONLY);
	while(1)
	{
		char *test = gnl(fd);
		if (test == NULL)
			break;
		ft_printf("output>> %s", test);
	}

	// int test = 42;
	// int hex = 255;
	// int a = ft_printf("exit test : %d, hex : %x\n",test ,hex);
	// ft_printf("my : %d\n", a);

	// int b = printf("exit test : %d, hex : %x\n",test ,hex);
	// printf("org : %d\n", b);
}
