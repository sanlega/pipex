/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:27:32 by slegaris          #+#    #+#             */
/*   Updated: 2023/05/23 03:50:41 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>
#include <stdio.h>

static int	ft_putptr_base(uintptr_t nbr, char *base)
{
	int	len;
	int	count;

	len = ft_strlen(base);
	count = 0;
	if (nbr >= (uintptr_t)len)
	{
		count += ft_putptr_base(nbr / len, base);
		count += ft_putptr_base(nbr % len, base);
	}
	else
	{
		count += ft_putchar(base[nbr]);
	}
	return (count);
}

int	ft_putptr(void *ptr)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	count = ft_putchar('0');
	count += ft_putchar('x');
	count += ft_putptr_base((uintptr_t)ptr, base);
	return (count);
}
