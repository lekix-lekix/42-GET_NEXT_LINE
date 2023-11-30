/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:20:39 by kipouliq          #+#    #+#             */
/*   Updated: 2023/11/30 18:05:17 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

char	*something_happened(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (NULL);
}

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
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1)); // ok
	if (!str)
		return (something_happened(str, NULL));
	while (++i < BUFFER_SIZE + 1)
		str[i] = '\0';
	*bytes_read = read(fd, str, BUFFER_SIZE);
	return (str);
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
	final_str = malloc(sizeof(char) * (s1_size + s2_size + 1)); // ok
	if (!final_str)
		return (something_happened(s1, s2));
	ft_strlcpy(final_str, s1, s1_size + 1);
	ft_strlcpy(final_str + s1_size, s2, s2_size + 1);
	free(s1);
	free(s2);
	return (final_str);
}

char	*ft_strcpy_malloc(char *src, char *end_ptr)
{
	char	*final_str;
	int		i;

	i = 0;
	final_str = malloc(sizeof(char) * (end_ptr - src + 1)); // ok
	if (!final_str)
		return (something_happened(src, NULL));
	while (src + i != end_ptr)
	{
		final_str[i] = src[i];
		i++;
	}
	final_str[i] = '\0';
	return (final_str);
}

char	*ft_dup_malloc_free(char *str, char *to_free)
{
	char	*final_str;
	int		i;

	i = -1;
	final_str = malloc(sizeof(char) * ft_strlen(str) + 1); // ok
	if (!final_str)
		return (something_happened(final_str, to_free));
	while (str[++i])
		final_str[i] = str[i];
	final_str[i] = '\0';
	if (to_free)
		free(to_free);
	return (final_str);
}

int	check_static_str(char *static_str, char **eol)
{
	int	i;

	i = -1;
	*eol = NULL;
	if (!static_str)
		return (0);
	while (static_str[++i])
	{
		if (static_str[i] == '\n')
		{
			*eol = static_str + i;
			break ;
		}
	}
	if (*eol)
		return (1);
	else
		return (0);
}

char	*ft_end_of_file(char **line, char **static_str)
{
	free(*line);
	*line = ft_dup_malloc_free(*static_str, *static_str);
	if (!line)
		return (NULL);
	*static_str = NULL;
	return (*line);
}

char	*ft_fill_static(char **static_str, char **eol, int *bytes_read, int fd)
{
	char	*line;

	// line = malloc(1);
	// if (!line)
	// return (something_happened(line, NULL));
	while (!check_static_str(*static_str, eol))
	{
		// free(line);
		line = get_nbytes(fd, bytes_read);
		if (!line)
			return (NULL);
		if (!(*bytes_read))
			break ;
		*static_str = ft_strjoin(*static_str, line);
		if (!(*static_str))
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line;
	char		*eol;
	int			bytes_read;

    // eol = NULL;
	if (!check_static_str(static_str, &eol))
	{
		line = ft_fill_static(&static_str, &eol, &bytes_read, fd);
		if (!line)
			return (something_happened(static_str, NULL));
	}
	if (eol)
	{
		line = ft_strcpy_malloc(static_str, eol + 1);
		if (!line)
			return (NULL);
		static_str = ft_dup_malloc_free(eol + 1, static_str);
		if (!static_str)
			return (something_happened(line, NULL));
		return (line);
	}
	if (!bytes_read && static_str)
		return (ft_end_of_file(&line, &static_str));
	if (line)
		free(line);
	return (NULL);
}

int	main(void)
{
	char	*str;
	int		fd;

	fd = open("./test.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
		{
			free(str);
			break ;
		}
		printf("str = %s\n", str);
		free(str);
	}
}
