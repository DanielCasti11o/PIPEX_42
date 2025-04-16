/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:26 by dacastil          #+#    #+#             */
/*   Updated: 2025/04/16 16:20:41 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_heredoc(char **argv)
{
	t_pid	*prh;
	int		fd_temp;
	char	*line;

	prh->pid1 = fork();
	if (prh->pid1 == 0)
	{
		fd_temp = open("here_doc_temp", O_CREAT, O_RDWR, O_TRUNC, 0644);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			{
				free(line);
				break ;
			}
			write(fd_temp, line, ft_strlen(line));
			write(fd_temp, "\n", 1);
			free(line);
		}
		close(fd_temp);
		exit(0);
	}
	else
		waitpid(prh->pid1, NULL, 0);
}
