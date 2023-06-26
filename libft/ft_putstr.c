/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:49:13 by slegaris          #+#    #+#             */
/*   Updated: 2023/05/23 19:32:30 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <sys/_types/_null.h>
#include <unistd.h>

int	ft_putstr_checked(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putstr(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6), 6);
	else
		return (ft_putstr_checked(str));
}
