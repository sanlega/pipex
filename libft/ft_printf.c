/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:58:40 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/26 18:55:18 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcheck(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_p(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr_p(va_arg(args, char *)));
	if (c == 'p')
		return (ft_putptr_p(va_arg(args, void *)));
	if (c == 'd')
		return (ft_putnbr_p(va_arg(args, int)));
	if (c == 'i')
		return (ft_putnbr_p(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr_unsg_p(va_arg(args, int)));
	if (c == 'x')
		return (ft_putnbrhex_minus_p(va_arg(args, int)));
	if (c == 'X')
		return (ft_putnbrhex_mayus_p(va_arg(args, int)));
	if (c == '%')
		return (ft_putchar_p('%'));
	return (0);
}

static int	ft_formatcheck(char *str, va_list args)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%' && (i == 0 || str[i - 1] != '%'))
		{
			length += ft_putchar_p(str[i]);
			i++;
		}
		else if (str[i] == '%' && str[i + 1] != '\0')
		{
			length += ft_charcheck(str[i + 1], args);
			i += 2;
		}
		else
		{
			length += ft_putchar_p(str[i]);
			i++;
		}
	}
	return (length);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		length;

	va_start(args, format);
	length = ft_formatcheck((char *)format, args);
	va_end(args);
	return (length);
}

// int main()
// {
// 	// // Printing a character
// 	// char c = 'A';
// 	// ft_printf("The character is: %c\n", c);
// 	// printf("The character is: %c\n", c);
// 	// printf("%d\n", ft_printf("The character is: %c\n", c));
//
// 	// Printing a string
// 	// char *str = "Hello, world!";
// 	// ft_printf("%s\n", (char *)NULL);
// 	// printf("%s\n", (char *)NULL);
//
// 	// // Printing a pointer
// 	// char *p = &c;
// 	// ft_printf("The pointer is: %p\n", p);
// 	// printf("The pointer is: %p\n", p);
// 	//
// 	// Printing a decimal number
// 	int d = INT_MIN;
// 	ft_printf("The decimal number is: %d\n", d);
// 	printf("The decimal number is: %d\n", d);
// 	//
// 	// // Printing an integer
// 	// int i = 5678;
// 	// ft_printf("The integer is: %i\n", i);
// 	// printf("The integer is: %i\n", i);
// 	//
// 	// // Printing an unsigned number
// 	// unsigned int u = 1234567890;
// 	// ft_printf("The unsigned number is: %u\n", u);
// 	// printf("The unsigned number is: %u\n", u);
// 	//
	// Printing a hexadecimal number (lowercase)
	// int x = -10;
	// ft_printf("%x\n", x);
	// printf("%x\n", x);
// 	//
// 	// // Printing a hexadecimal number (uppercase)
// 	// int X = 0xABC;
// 	// ft_printf("The hexadecimal number (uppercase) is: %X\n", X);
// 	// printf("The hexadecimal number (uppercase) is: %X\n", X);
// 	//
// 	// // Printing a percentage symbol
// 	// ft_printf("The percentage symbol is: %%\n");
// 	// printf("The percentage symbol is: %%\n");
//
// 	return 0;
// }
