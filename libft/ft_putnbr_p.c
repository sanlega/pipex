/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:10:41 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/26 19:02:05 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>

int	ft_putnbr_p(int n)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
	{
		ft_putstr_p("-2147483648");
		count += 11;
		return (count);
	}
	if (n < 0)
	{
		count += ft_putchar_p('-');
		count += ft_putnbr_p(-n);
	}
	else if (n > 9)
	{
		count += ft_putnbr_p(n / 10);
		count += ft_putnbr_p(n % 10);
	}
	else
		count += ft_putchar_p(n + '0');
	return (count);
}
