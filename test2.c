#include <unistd.h>
#include <stdarg.h>

int	print_c(const char c, int counts)
{
	if ( c == '\0')
		return counts;
	if (write(1,&c, 1)== -1)
		return -1;
	counts++;
	return counts;
}
int print_s(const char *str, int counts)
{
	if(str == NULL)
		str = "(null)";
	int i = 0;
	while(str[i])
	{
		counts = print_c(str[i],counts);
		if(counts == -1)
			return -1;
		i++;
	}
	return counts;
}

int	print_d(int nb, int counts)
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
		counts = print_d(temp / 10, counts);
		if(counts == -1)
			return -1;
	}
	c = temp %10 +'0';
	counts = print_c(c, counts);
	if (counts == -1)
		return -1;
	return counts;
}

int	print_x(unsigned int nb, int counts)
{
	char hex = "0123456789abcdef";
	char c;
	int rem = 0;

	if (nb >= 16)
	{
		counts = print_x(nb / 16, counts);
		if (counts == -1)
			return -1;
	}
	rem = nb % 16;
	if (format == x)
	{
		c = hex[rem];
	}
	counts = print_c(c, counts);
	if (counts == -1)
		return -1;
	return counts;
}

int ft_printf(const char *format, ...)
{
	va_list args;
	int counts = 0;

	va_start(args,format);
	while(*format)
	{
		if (*format == '%')
		{
			format++;
			{
				if (*format == 'd')
				{
					counts =print_d(va_arg(args, int), counts);
					if (counts == -1)
						return -1;
				}
				else if(*format == 's')
				{

				}
				else if(*format == 'x')
				{

				}
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
	static char buf[42];
	static int readsize;
	static int offset;
	char *cur;
	char line[55555];
	int i = 0;
	while(1)
	{
		if (offset >= readsize)
		{
			readsize = read(fd,buf,42);
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
		if(line[i] == '\n')
			break;
	}
	i++;
	line[i] = '\0';
	return ft_strdup(line);
}

char *gnl(int fd)
{
	static int offset;
	static char buf[42];
	static int readsize;
	char line[55555];
	char *cur;
	int i = 0;

	while (1)
	{
		if(offset>= readsize)
		{
			readsize = read(fd,buf,42);
			if(readsize == -1)
				return NULL;
			if(readsize == 0)
			{
				if(i > 0)
					break;
				return NULL;
			}
			offset = 0;
		}
		cur = buf+offset;
		line[i] = *cur;
		offset++;
		if (line[i] == '\n')
		{
			break;
		}
		i++;
	}
	i++;
	line[i] = '\0';
	return ft_strdup(line);
}