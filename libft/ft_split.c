/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:50:11 by slegaris          #+#    #+#             */
/*   Updated: 2023/03/24 18:10:49 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void	flyingfree(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	indexword(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!j)
			{
				j = 1;
				i++;
			}
		}
		else
			j = 0;
		s++;
	}
	return (i);
}

static int	wordlen(char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = indexword((char *)s, c);
	words = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			words[i] = ft_substr(s, 0, wordlen((char *)s, c));
			if (!words[i])
				return (flyingfree(words), NULL);
			s += wordlen((char *)s, c);
			i++;
		}
		else
			s++;
	}
	return (words);
}
//
// int main(void)
// {
// 	char **result;
// 	int i;
//
// 	result = ft_split("Hello, how are you?", ' ');
// 	for (i = 0; result[i] != NULL; i++)
// 		printf("Word %d: %s\n", i + 1, result[i]);
// 	for (i = 0; result[i] != NULL; i++)
// 		free(result[i]);
// 	// free(result);
// 	system("leaks a.out");
// 	return (0);
// }
