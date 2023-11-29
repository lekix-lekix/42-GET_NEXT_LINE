/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:20:39 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/29 19:04:48 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
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

char	*get_nbytes(int fd, int *bytes_read)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (++i < BUFFER_SIZE + 1)
		str[i] = '\0';
	*bytes_read = read(fd, str, BUFFER_SIZE);
	return (str);
}

int	get_str_size(char *str, char *end_ptr)
{
	int	i;

	i = 0;
	while (str != end_ptr)
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*final_str;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
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

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char    *ft_strcpy_malloc(char *src, char *end_ptr)
{
	char *final_str;
	int   i;

	i = 0;
	final_str = malloc(sizeof(char) * get_str_size(src, end_ptr) + 1); // test + modif si necessaire
	if (!final_str)
		return (NULL);
	while (src + i != end_ptr)
	{
		final_str[i] = src[i];
		i++;
	}
	final_str[i] = '\0';
	return (final_str);
}

void    ft_bzero(void *s, size_t n)
{
	size_t  i;

	i = -1;
	while (++i < n)
		*((char *)s + i) = '\0';
}

char    *ft_dup_malloc_free(char *str, char *to_free)
{
	char *final_str;
	int   i;
	
	i = -1;
	final_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!final_str)
		return (NULL);
	while (str[++i])
		final_str[i] = str[i];
	final_str[i] = '\0';
	if (to_free)
		free(to_free);
	// printf("final str = %s\n", final_str);
	return (final_str);   
}

// char	*get_next_line_old(int fd)
// {
// 	static char	*static_str;
// 	char		*line;
// 	char		*eol;
// 	int			bytes_read;

// 	bytes_read = 1;
// 	while (bytes_read)
// 	{
// 		if (!static_str && !line)
// 			break ;
// 		if (ft_strchr(static_str, '\0') && !bytes_read)
// 		{
// 			free(line);
// 			return (static_str);
// 		}
// 		eol = ft_strchr(static_str, '\n');
// 		if (eol)
// 		{
// 			line = ft_strcpy_malloc(static_str, eol + 1);
// 			static_str = ft_dup_malloc_free(eol + 1, static_str);
// 			if (!static_str || !line)
// 				return (NULL);
// 			return (line);
// 		}
// 		line = get_nbytes(fd, &bytes_read);
// 		if (!line)
// 			return (NULL);
// 		static_str = ft_strjoin(static_str, line);
// 		if (!static_str)
// 			return (NULL);
// 		if (bytes_read != BUFFER_SIZE)
// 		{
// 			line = ft_dup_malloc_free(static_str, static_str);
// 			if (!line)
// 				return (NULL);
// 			return (line);
// 		}
// 	}
// 	if (ft_strchr(static_str, '\0') && !bytes_read)
// 		return (static_str);
// 	return (NULL);
// }

int		check_static_str(char *static_str, char **eol)
{
	*eol = ft_strchr(static_str, '\n');
	if (*eol)
		return (1);
	else
		return (0); 
	
}

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line;
	char		*eol;
	int			bytes_read;

	eol = NULL;
	line = get_nbytes(fd, &bytes_read);
	if (!bytes_read)
		return (NULL);
	while (!check_static_str(static_str, &eol))
	{
		line = get_nbytes(fd, &bytes_read);
		if (!line)
			return (NULL);
		if (!bytes_read)
			break ;
		static_str = ft_strjoin(static_str, line);
		if (!static_str)
			return (NULL);
	}
	if (eol)
	{
		line = ft_strcpy_malloc(static_str, eol + 1);
		static_str = ft_dup_malloc_free(eol + 1, static_str);
		if (!static_str || !line)
			return (NULL);
		return (line);
	}
	if (!bytes_read)
	{
		line = ft_dup_malloc_free(static_str, static_str);
		static_str = NULL;
		return (line);
	}
	return (NULL);
}

int	main(void)
{
	char *str;
	int fd = open("./test.txt", O_RDONLY);
	int i = 0;

	while (i < 5)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("str = %s\n", str);
		free(str);
		i++;
	}
}
