/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:49:13 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/18 20:48:59 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putstr_checked(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_p(str[i]);
		i++;
	}
	return (i);
}

int	ft_putstr_p(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6), 6);
	else
		return (ft_putstr_checked(str));
}
