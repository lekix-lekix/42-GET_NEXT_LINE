/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:20:39 by kipouliq          #+#    #+#             */
/*   Updated: 2023/12/01 16:26:30 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

char	*ft_dup_cpy_malloc_free(char *str, char *end_ptr, char *to_free)
{
	char	*final_str;
	int		i;

	i = -1;
	if (end_ptr)
	{
		final_str = malloc(sizeof(char) * (end_ptr - str + 1)); // ok
		if (!final_str)
			return (something_happened(str, NULL));
		while (str + ++i != end_ptr)
			final_str[i] = str[i];
	}
	else
	{
		final_str = malloc(sizeof(char) * ft_strlen(str) + 1); // ok
		if (!final_str)
			return (something_happened(final_str, to_free));
		while (str[++i])
			final_str[i] = str[i];
	}
	final_str[i] = '\0';
	if (to_free)
		free(to_free);
	return (final_str);
}

char	*ft_end_of_file(char **line, char **static_str)
{
	free(*line);
    *line = ft_dup_cpy_malloc_free(*static_str, NULL, *static_str);
	if (!(*line))
		return (NULL);
	*static_str = NULL;
    if (!ft_strlen(*line))
    {
        free(*line);
        return (NULL);
    }
	return (*line);
}

char	*ft_fill_static(char **static_str, char **eol, int *bytes_read, int fd)
{
	char	*line;

	while (!check_static_str(*static_str, eol))
	{
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

char	*ft_return_line(char **static_str, char *eol, int fd, int bytes)
{
	char	*new_line;
    (void) fd;

	new_line = ft_dup_cpy_malloc_free(*static_str, eol + 1, NULL);
	if (!new_line)
		return (NULL);
	*static_str = ft_dup_cpy_malloc_free(eol + 1, NULL, *static_str);
	if (!static_str)
		return (something_happened(new_line, NULL));
	if ((bytes < BUFFER_SIZE) && (fd >= 0 && fd <= 2)) // a modifier
		free(*static_str);
	if (static_str && static_str[0] == NULL)
		free(*static_str);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line;
	char		*eol;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!check_static_str(static_str, &eol))
	{
		line = ft_fill_static(&static_str, &eol, &bytes_read, fd);
		if (!line)
			return (something_happened(static_str, NULL));
	}
	if (eol)
		return (ft_return_line(&static_str, eol, fd, bytes_read));
	if (!bytes_read && static_str)
		return (ft_end_of_file(&line, &static_str));
	if (line)
		free(line);
	return (NULL);
}

// int	main(void)
// {
// char	*str;

// int		fd;
// fd = open("./get_next_line.c", O_RDONLY);
// while (1)
// {
// 	str = get_next_line(fd);
// 	if (!str)
// 	{
// 		free(str);
// 		break ;
// 	}
// 	printf("str = %s\n", str);
// 	free(str);
// }
// free(str);
// str = get_next_line(1000);
// printf("str = %s\n", str);
// free(str);
// }