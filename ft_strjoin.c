/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaucarri <jaucarri@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:42:07 by jaucarri          #+#    #+#             */
/*   Updated: 2023/09/19 16:20:25 by jaucarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initjoin(char const *s1, char const *s2, int *i)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = ft_strlen(s1);
	i[3] = ft_strlen(s1) + ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		i[4];

	initjoin(s1, s2, i);
	tmp = (char *)malloc(i[3] * sizeof(char) + 1);
	if (tmp == 0)
		return (0);
	else if (ft_strlen(s1) == 0 && ft_strlen(s2) > 0)
		ft_strlcpy(tmp, (const char *)s2, (size_t)ft_strlen(s2) + 1);
	else if (ft_strlen(s2) == 0 && ft_strlen(s1) > 0)
		ft_strlcpy(tmp, (const char *)s1, (size_t)ft_strlen(s1) + 1);
	else
	{
		while (i[0] < i[3])
		{
			if (*s1)
				tmp[i[1]++] = *((char *)s1++);
			if (*s2)
				tmp[i[2]++] = *((char *)s2++);
			i[0]++;
		}
		tmp[i[0]] = '\0';
	}
	return (tmp);
}
