/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:15:13 by kpolatci          #+#    #+#             */
/*   Updated: 2023/10/23 15:12:18 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//#include <stdio.h>
//#define BUFFER_SIZE 5

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len++;
	return (len);
}

void	ft_strlcpy(char *src, char *dst, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (0);
	if (s1)
		ft_strlcpy(s1, join, ft_strlen(s1));
	if (s2)
		ft_strlcpy(s2, join + ft_strlen(s1), ft_strlen(s2));
	free(s2);
	return (join);
}

int	ft_find_char(char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_read_line(int fd, char *str)
{
	char	*buf;
	int		read_size;

	while (!ft_find_char(str, '\n'))
	{
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
		{
			free(buf);
			return (str);
		}
		buf[read_size] = '\0';
		str = ft_strjoin(str, buf);
	}
	return (str);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		index;

	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		index++;
	line = (char *)malloc(sizeof(char) * index + 1);
	if (!line)
		return (0);
	ft_strlcpy(str, line, index);
	return (line);
}

char	*ft_clean_str(char *str)
{
	char	*clean;
	int		index;
	int		j;

	j = 0;
	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	if (!str[index++])
	{
		free(str);
		return (0);
	}
	while (str[index])
	{
		j++;
		index++;
	}
	index -= j;
	clean = (char *)malloc(sizeof(char) * j + 1);
	ft_strlcpy(str + index, clean, j);
	free(str);
	return (clean);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read_line(fd, str);
	if (!str)
		return (0);
	line = ft_get_line(str);
	str = ft_clean_str(str);
	return (line);
}

//int	main(void)
//{
//	int		fd;
//	char	*str;

//	fd = open("a.txt", O_RDWR, 0777);
//	while (1)
//	{
//		str = get_next_line(fd);
//		if (!str)
//			break ;
//		printf("%s", str);
//		free(str);
//	}
//}
