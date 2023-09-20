/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prot_mal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:11:51 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/20 23:59:43 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stddef.h>

char	*esejoint(char *str1, char *str2)
{
	char	*result;

	result = ft_strjoin(str1, str2);
	if (!result)
	{
		perror("JOIN");
		exit(errno);
	}
	return (result);
}

char	**esesplit(char *str, char c)
{
	char	**result;

	result = ft_split(str, c);
	if (!result)
	{
		perror("SPLIT");
		exit(errno);
	}
	return (result);
}

char	*esesubstr(char *s, int start, size_t len)
{
	char	*result;

	result = ft_substr(s, start, len);
	if (!result)
	{
		perror("SUBSTR");
		exit(errno);
	}
	return (result);
}
