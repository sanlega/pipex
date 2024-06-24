/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:52:01 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/24 10:42:24 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlen_g(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return (&s[ft_strlen_g(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *left, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left)
	{
		left = (char *)malloc(1 * sizeof(char));
		if (!left)
			return (NULL);
		left[0] = '\0';
	}
	if (!left || !buff)
		return (free(left), NULL);
	str = malloc(sizeof(char) * ((ft_strlen_g(left) + ft_strlen_g(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left)
		while (left[++i] != '\0')
			str[i] = left[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen_g(left) + ft_strlen_g(buff)] = '\0';
	return (free(left), str);
}

char	*ft_get_line(char *left_str)
{
	size_t	i;
	size_t	len;
	char	*str;

	if (!left_str || !left_str[0])
		return (NULL);
	len = ft_line_length(left_str);
	str = (char *)malloc(sizeof(char) * (len + 1 + (left_str[len] == '\n')));
	if (!str)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
		return (free(left_str), NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen_g(left_str) - i + 1));
	if (!str)
		return (free(left_str), NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}
