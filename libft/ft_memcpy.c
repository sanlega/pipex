/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:47:54 by slegaris          #+#    #+#             */
/*   Updated: 2023/03/21 17:47:24 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*d1;
	unsigned char	*s2;

	d1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	i = 0;
	if (d1 == NULL && s2 == NULL)
		return (dst);
	while (i < n)
	{
		d1[i] = s2[i];
		i++;
	}
	return (dst);
}
