/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:27:24 by arthur            #+#    #+#             */
/*   Updated: 2024/05/30 13:45:06 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
static int	ft_estim(long n)
{
	size_t	estim;
	int		signe;

	estim = 0;
	signe = 0;
	if (n < 0)
	{
		estim++;
		signe++;
		n = -n;
	}
	while (n >= 1)
	{
		estim++;
		n /= 10;
	}
	return (estim);
}

static char	*ft_gen(char *rtn, long nbr, int len, int signe)
{
	if (nbr != 0)
		rtn = malloc(sizeof(char) * (len + 1));
	else
		return (rtn = ft_strdup("0"));
	if (!rtn)
		return (0);
	signe = 0;
	if (nbr < 0)
	{
		signe++;
		nbr = -nbr;
	}
	rtn[len] = '\0';
	while (--len)
	{
		rtn[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (signe == 1)
		rtn[0] = '-';
	else
		rtn[0] = (nbr % 10) + '0';
	return (rtn);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*rtn;
	long	nbr;
	int		signe;

	nbr = n;
	len = ft_estim(nbr);
	rtn = 0;
	signe = 0;
	rtn = ft_gen(rtn, nbr, len, signe);
	if (!rtn)
		return (0);
	return (rtn);
}
*/