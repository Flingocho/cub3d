/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:58:59 by jvidal-t          #+#    #+#             */
/*   Updated: 2024/10/16 21:55:43 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	unsigned int	base_len;
	int				count;

	base_len = 16;
	count = 0;
	if (nbr >= base_len)
	{
		count += ft_putnbr_base(nbr / base_len, base);
		count += ft_putnbr_base(nbr % base_len, base);
	}
	else
		count += ft_putchar(base[nbr]);
	return (count);
}

int	ft_putptr(unsigned long long nbr, char *base, int first)
{
	unsigned long long	base_len;
	int					count;

	base_len = 16;
	count = 0;
	if (!nbr && first)
		return (count = ft_putstr("(nil)"));
	if (first)
		count += ft_putstr("0x");
	if (nbr >= base_len)
	{
		count += ft_putptr(nbr / base_len, base, 0);
		count += ft_putptr(nbr % base_len, base, 0);
	}
	else
		count += ft_putchar(base[nbr]);
	return (count);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += format_selector(format, args);
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	int		original;
	int		copy;
	char	*albert;

	albert = "NULL";
	original = 0;
	copy = 0;
	printf("\n**************************************************\n");
	printf("* Welcome to the super main tester for printf :) *");
	printf("\n**************************************************\n");
	printf("\n________________STRING HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("%s\n", "This is a cool, but simple string!");
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("%s\n", "This is a cool, but simple string!");
	printf("Your int value: %d\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	printf("\n________________CHAR HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("%c\n", 'K');
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("%c\n", 'K');
	printf("Your int value: %d\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	printf("\n________________PERCENTAGE HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("%%\n");
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("%%\n");
	printf("Your int value: %d\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	printf("\n________________INTEGER HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("Number is: %d\n", -12345);
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("Number is: %d\n", -12345);
	printf("Your int value: %d\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	printf("\n________________UNSIGNED HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("Number is: %u\n", UINT_MAX);
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("Number is: %u\n", UINT_MAX);
	printf("Your int value: %u\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	printf("\n________________HEXA LOWER HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("Number is: %x\n", -123);
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("Number is: %x\n", -123);
	printf("Your int value: %u\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	printf("\n________________HEXA UPPER HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("Number is: %X\n", 123);
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("Number is: %X\n", 123);
	printf("Your int value: %u\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	printf("\n________________POINTER HANDLING________________\n\n");
	printf("······Original printf behaviour······\n\n");
	original = printf("Number is: %p\n and this is a number! %d\n", albert, 3);
	printf("Original int value: %d\n", original);
	printf("\n······Your printf behaviour······\n\n");
	copy = ft_printf("Number is: %p\n and this is a number! %d\n", albert, 3);
	printf("Your int value: %u\n", copy);
	printf("\n··············RESULTS··············\n\n");
	if (original == copy)
		printf("Return values: OK!\n");
	else
		printf("Return values: KO :(\n");
	return (0);
}
*/
