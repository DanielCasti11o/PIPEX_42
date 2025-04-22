/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:40:57 by dacastil          #+#    #+#             */
/*   Updated: 2025/04/21 14:21:35 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "pipex.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*free_join(char *buffer, char *buff);
char	*ft_next(char *buffer);
char	*obt_line(char *buffer);
char	*read_line(int fd, char *buffer);

#endif
