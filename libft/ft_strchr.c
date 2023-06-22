/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:30 by slegaris          #+#    #+#             */
/*   Updated: 2023/03/24 14:47:52 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*z;

	i = 0;
	z = (char *)s;
	while (z[i] != '\0')
	{
		if (z[i] == (char)c)
			return (&z[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&z[i]);
	return (NULL);
}
// char	*ft_strchr(const char *s, int c)
// {
// 	return (ft_memchr(s, c, ft_strlen(s) + 1));
// }
//
// int	main(void)
// {
// 	char *s = "test";
// 	int c = 's';
//
// 	printf("%s\n", ft_strchr(s, c));
// 	printf("%s\n", strchr(s, c));
// 	return 0;
// }
