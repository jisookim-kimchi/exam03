
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *ft_strdup(char *str)
{
    if (str == NULL)
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
char *get_next_line(int fd)
{
    static int offset;
    static int readbytes;
    char buf[42];
    int i = 0;

    char *cur;
    char line[70000];
    while (1)
    {
        if (offset >= readbytes)
        {
            readbytes = read(fd ,buf, 42);
            if (readbytes <= 0)
                return NULL;
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
    if (i == 0)
        return NULL;
    i++;
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