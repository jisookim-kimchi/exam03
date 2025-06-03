#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *ft_strdup(char *str)
{
    char *dup;
    int len = 0;
    int i = 0;

    while (str[len] != '\0')
        len++;
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    
    while (str[i])
    {
        dup[i] = str[i];  // 인덱스로 접근
        i++;
    }
    dup[i] = '\0';
    return (dup);  // dup은 그대로 시작 주소
}

char *get_next_line(int fd)
{
    static int offset;
    static int readsize;
    static char buf[42];
    char *cur;

    int i =0;
    char line[70000];
    while (1)
    {
        if (offset >= readsize)
        {
            readsize = read(fd, buf, readsize);
            if (readsize <= 0)
                return NULL;
            offset = 0;
        }
        cur = buf + offset;
        line[i] = *cur;
        offset++;
        if (line[i] == '\n')
        {
            i++;
            break;
        }
        i++;
    }
    if (i == 0)
        return NULL;
    line[i] = '\0';
}

char *get_next_line(int fd)
{
	static int pos;
	static int readsize;
	static char buf[BUFFER_SIZE];
    char *cur;
    
	int i = 0;
	char line[70000];
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (pos >= readsize)
		{
			readsize = read(fd, buf, BUFFER_SIZE);
			pos = 0;
			if (readsize <= 0)
				break;
		}
        cur = buf + pos;
		line[i] = *cur;
        pos++;
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
    if (i == 0)
	    return (NULL);
	line[i] = '\0';
	return (ft_strdup(line));
}


int main()
{
    char *str;
    
    printf("여러 줄 입력해보세요 (Ctrl+D로 종료):\n");
    
    // 계속 반복해서 읽기
    while ((str = get_next_line(0)) != NULL)
    {
        printf("읽은 내용: [%s]", str);
        free(str);
    }
    
    printf("프로그램 종료\n");
    return (0);
}
