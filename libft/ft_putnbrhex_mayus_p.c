/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhex_mayus_p.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:58:37 by slegaris          #+#    #+#             */
/*   Updated: 2023/07/03 12:39:02 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_base_p(unsigned int nbr, char *base)
{
	int		len;
	long	nb;
	int		count;

	len = ft_strlen(base);
	nb = nbr;
	count = 0;
	if (nb < 0)
	{
		count += ft_putchar_p('-');
		nb *= -1;
	}
	if (nb < len)
	{
		count += ft_putchar_p(base[nb]);
	}
	if (nb >= len)
	{
		count += ft_putnbr_base_p(nb / len, base);
		count += ft_putnbr_base_p(nb % len, base);
	}
	return (count);
}

int	ft_putnbrhex_mayus_p(int n)
{
	int				count;
	char			*base;
	unsigned int	nbr;

	count = 0;
	base = "0123456789ABCDEF";
	nbr = (unsigned int)n;
	count = ft_putnbr_base_p(nbr, base);
	return (count);
}
