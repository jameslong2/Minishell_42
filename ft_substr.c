/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaucarri <jaucarri@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:28:14 by jaucarri          #+#    #+#             */
/*   Updated: 2023/09/16 09:10:22 by jaucarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (len > (size_t)ft_strlen(s) && start < (unsigned int)ft_strlen(s))
	{
		len = (size_t)ft_strlen(s) + 1;
		len = len - start;
	}
	else if (start >= (unsigned int)ft_strlen(s) || len == 0)
	{
		len = 1;
		start = (unsigned int)ft_strlen(s);
	}
	else if (start < (unsigned int)ft_strlen(s) && len <= (size_t)ft_strlen(s)
		&& (size_t)start + len <= (size_t)ft_strlen(s))
		len++;
	tmp = (char *)malloc(len);
	if (tmp == 0)
		return (0);
	ft_strlcpy(tmp, s + start, len);
	return (tmp);
}
