/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:20:14 by slegaris          #+#    #+#             */
/*   Updated: 2023/03/21 18:43:29 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	s;

	i = 0;
	n = 0;
	s = 1;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (s * n);
}
/*
int main()
{
	printf("%i\n", ft_atoi("20000000000"));
	printf("%i\n", ft_atoi("     ------+++++---12341"));
	printf("%i\n", ft_atoi("     ------+++++---123413"));
	printf("%i\n", ft_atoi("00000000002147483647"));
	printf("%i\n", ft_atoi("-2147483648"));
	printf("%i\n", ft_atoi("a"));
}*/
