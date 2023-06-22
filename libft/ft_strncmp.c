/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:38:39 by slegaris          #+#    #+#             */
/*   Updated: 2023/03/08 18:29:42 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*f1;
	unsigned char	*f2;

	f1 = (unsigned char *) s1;
	f2 = (unsigned char *) s2;
	i = 0;
	while (f1[i] && f2[i] && i < n)
	{
		if (f1[i] != f2[i])
			return (f1[i] - f2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (f1[i] - f2[i]);
}
/*
int	main(void)
{
	char *s1 = "  Buenosdias";
	char *s2 = "  Buenos";
	unsigned int n = -3;

	printf("%d\n", ft_strncmp(s1, s2, n));
	return 0;
}*/
