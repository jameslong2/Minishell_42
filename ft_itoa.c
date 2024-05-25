/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaucarri <jaucarri@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:28 by jaucarri          #+#    #+#             */
/*   Updated: 2023/09/19 16:28:42 by jaucarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	poweritoa(int num, int power)
{
	long	po;
	long	i;

	po = 1;
	i = 0;
	while (i < power)
	{
		po = po * num;
		i++;
	}
	return (po);
}

static void	recursiveitoa(char *tmp, int nb, long div)
{
	if (nb < 0)
	{
		*tmp++ = '-';
		if (nb == -2147483648)
		{
			*tmp++ = '2';
			nb += 2000000000;
			div /= 10;
		}
		nb *= -1;
	}
	if (div != 0)
	{
		*tmp = ((long)nb / div) % 10 + '0';
		recursiveitoa(tmp + 1, nb % div, div / 10);
	}
	else
	{
		*tmp = '\0';
	}
}

static void	inititoa(int *counter, int *extra, int *temp)
{
	*counter = 0;
	*extra = 0;
	if (*temp == -2147483648)
		*temp += 1;
	if (*temp <= 0)
	{
		*temp *= -1;
		*extra = 1;
	}
	while (*temp >= 1)
	{
		*temp /= 10;
		*counter += 1;
	}
}

char	*ft_itoa(int n)
{
	int		temp;
	int		counter;
	int		extra;
	char	*tmp;

	temp = n;
	inititoa(&counter, &extra, &temp);
	tmp = (char *)malloc((counter + extra + 1) * sizeof(char));
	if (n != 0 && tmp != 0)
		recursiveitoa(tmp, n, poweritoa(10, counter - 1));
	else if (tmp != 0)
	{
		tmp[0] = '0';
		tmp[1] = '\0';
	}
	return (tmp);
}
