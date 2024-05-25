/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaucarri <jaucarri@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:40:07 by jaucarri          #+#    #+#             */
/*   Updated: 2023/09/19 16:51:28 by jaucarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	strcount(char *s, char c)
{
	int	i;

	i = 1;
	while (*s == c && *s)
		s++;
	if (*s == 0)
		return (-1);
	if (c != '\0')
	{
		while (*s)
		{
			if (*s == c && *(s + 1) != c && *(s + 1) != 0)
				i++;
			s++;
		}
	}
	return (i);
}

static char	*strend(char *s, char c)
{
	while (*s != c && *s)
		s++;
	return (s);
}

static char	*strstart(char *s, char c)
{
	while (*s == c && *s)
		s++;
	return (s);
}

static void	initsplit(int *i, char c, char const *s)
{
	i[0] = strcount((char *)s, c);
	i[1] = 0;
	if (i[0] == 0 && ft_strlen(s) > 0)
		i[0] = 1;
	else if (ft_strlen(s) == 0 || i[0] == -1)
		i[0] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**tmp;
	int		i[2];
	char	*end;

	end = (char *)s;
	initsplit(i, c, s);
	tmp = (char **)malloc((size_t)(i[0] + 1) * sizeof(char *));
	if (tmp == 0)
		return (0);
	while (i[1] < i[0])
	{
		s = (char const *)strstart(end, c);
		end = strend((char *)s, c);
		tmp[i[1]] = ft_substr(s, 0, (int)(end - s));
		if (!tmp[i[1]])
		{
			while (i[1] >= 0)
				free(tmp[i[1]--]);
			free(tmp);
			return (0);
		}
		i[1]++;
	}
	tmp[i[1]] = 0;
	return (tmp);
}
