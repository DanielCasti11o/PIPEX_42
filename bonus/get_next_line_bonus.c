/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:31:02 by dacastil          #+#    #+#             */
/*   Updated: 2025/04/21 18:06:35 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line_bonus.h"
#include "../include/pipex.h"

char	*free_join(char *buffer, char *buff)
{
	char	*temp;

	temp = ft_strjoin(buffer, buff);
	if (!temp)
		return (NULL);
	free (buffer);
	return (temp);
}

char	*ft_next(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*next;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	next = ft_calloc(((ft_strlen(buffer) - i) + 1), sizeof (char));
	if (!next)
		return (free(buffer), NULL);
	i++;
	while (buffer[i])
	{
		next[j] = buffer[i];
		i++;
		j++;
	}
	free (buffer);
	return (next);
}

char	*obt_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc((i + 2), sizeof(char));
	else
		line = ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
		line[i] = '\n';
	return (line);
}

char	*read_line(int fd, char *buffer)
{
	int		bytes_read;
	char	*buff_temp;

	bytes_read = 1;
	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	buff_temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff_temp)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff_temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff_temp);
			free (buffer);
			return (NULL);
		}
		buff_temp[bytes_read] = 0;
		buffer = free_join(buffer, buff_temp);
		if (ft_strchr(buff_temp, '\n'))
			break ;
	}
	free (buff_temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (ft_strlen(buffer[fd]) == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = obt_line(buffer[fd]);
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}

// #include <stdio.h>

// int main(void)
// {
//     int fd1, fd2;
//     char *line;

//     // Abre varios archivos en modo lectura
//     fd1 = open("text.txt", O_RDONLY);
//     fd2 = open("rfx.txt", O_RDONLY);

//     // Lee las líneas del primer archivo
//     printf("Leyendo archivo1.txt:\n");
//     while ((line = get_next_line(fd1)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }

//     // Lee las líneas del segundo archivo
//     printf("\nLeyendo archivo2.txt:\n");
//     while ((line = get_next_line(fd2)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }

//     // Cierra los archivos
//     close(fd1);
//     close(fd2);

//     return (0);
// }

