/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:32:11 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/03/20 21:19:45 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

#include <errno.h>

void	ft_error(char *msg, int flag)
{
	int	i;

	i = 0;
	ft_putstr(msg);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(flag);
}

void	fr_words(char **wds)
{
	int	i;

	i = 0;
	while (wds[i])
	{
		free(wds[i]);
		i++;
	}
	free(wds);
}

void	ft_putstr(char *s)
{
	int	ln;

	ln = 0;
	if (!s)
		s = "(null)";
	while (s[ln])
	{
		write (1, &s[ln], 1);
		ln++;
	}
	return ;
}

// #include <stdio.h>

// int main()
// {
// 	char	s[] = " 1  2a, 3 --h ";
// 	char	d;
// 	char	**result;

// 	d = ' ';
// 	result = ft_split(s, d);
// 	if (result)
// 	{
// 		for (int i = 0; result[i]; i++)
// 			printf("%s\n", result[i]);  // Imprimir cada subcadena
// 	}
// 	return (0);
// }
