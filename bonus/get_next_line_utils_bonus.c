/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:33:05 by dacastil          #+#    #+#             */
/*   Updated: 2025/04/16 16:10:27 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ls1;
	size_t	ls2;
	size_t	i;
	size_t	j;
	char	*strresult;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	i = 0;
	j = 0;
	strresult = ft_calloc((ls1 + ls2) + 1, sizeof(char));
	if (!strresult)
		return (NULL);
	while (s1[i] != '\0')
	{
		strresult[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		strresult[i++] = s2[j++];
	return (strresult);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	totalsz;
	void	*pr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	totalsz = nmemb * size;
	pr = malloc(totalsz);
	if (pr == NULL)
		return (NULL);
	ft_bzero(pr, totalsz);
	return (pr);
}
