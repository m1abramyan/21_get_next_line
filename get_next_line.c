#include <stdio.h>
#include <fcntl.h> // open
#include <stdlib.h>
#include <unistd.h> // read

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*str;
	void				*res;

	str = (const unsigned char *)s;
	c = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == c)
		{
			res = (void *)(str);
			return (res);
		}
		str++;
	}
	if (c == '\0' && *str == '\0')
	{
		res = (void *)(str);
		return (res);
	}
	return (0);
}

// GNL

char	*check_memory(char *memory, char *line)
{	
	if (memory)
		line = ft_strdup(memory);
	else
		line = "\0";
	return(line);
}


char    *get_next_line(int fd)
{
    char    	buf[1001]; // буффер
    char    	*line; // спрочитанная строка
    int     	byte; // колличесвто прочитанный байтов
	char		*pointer_n; // указатель на конец строки
	int			flag; // флаг для выхода из цикла
	static char	*memory; // остаток прочитанной строки

	flag = 1;
	// check_memory(memory, line);
	if (memory)
		line = ft_strdup(memory);
	else
		line = "\0";
    while (flag && (byte = read(fd, buf, 1000)))
    {
		if((pointer_n = ft_strchr(buf, '\n')))
		{
			*pointer_n = '\0';
			flag = 0;
			pointer_n++;
			memory = ft_strdup(pointer_n);
		}
        buf[byte] = '\0';
        line = ft_strjoin(line, buf);
    }    
    return(line);
}

int main(void)
{
    char    *line;
    int     fd;

    fd = open("text.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("%s\n", line);

	line = get_next_line(fd);
    printf("%s\n", line);

}