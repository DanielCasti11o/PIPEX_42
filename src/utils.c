/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:32:11 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/03/20 14:45:30 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(char *msg, int flag)
{
	int	i;

	i = 0;
	perror(msg);
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
