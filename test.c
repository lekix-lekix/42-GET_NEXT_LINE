/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:20:39 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/27 18:00:33 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char    *get_nbytes(int fd, int *bytes_read)
{
	char *str;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	*bytes_read = read(fd, str, BUFFER_SIZE);
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		s1_size;
	size_t		s2_size;
	char		*final_str;

	if (!s1)
		return (s2);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	final_str = malloc(sizeof(char) * (s1_size + s2_size) + 1);
	if (!final_str)
		return (NULL);
	ft_strlcpy(final_str, s1, s1_size + 1);
	ft_strlcpy(final_str + s1_size, s2, s2_size + 1);
	free(s1);
	free(s2);
	return (final_str);
}

char    *get_next_line(int fd)
{
	char    *line;
	char    *final_str;
	int     bytes_read;
	
	bytes_read = 5;
	final_str = NULL;
	while (bytes_read)
	{
		line = get_nbytes(fd, &bytes_read);
		line[bytes_read] = '\0';
		printf("bytes read = %d\n", bytes_read);
		if (!line)
			return (NULL);
		final_str = ft_strjoin(final_str, line);
		if (!final_str)
			return (NULL);
	}
	printf("final str = %s\n", final_str);
	return (final_str);
}

int	main()
{    
	char *str;
	int fd = open("./test.txt", O_RDONLY);
	printf("fd = %d\n", fd);
	str = get_next_line(fd);
	printf("str1 = %s\n", str);
	free(str);
}