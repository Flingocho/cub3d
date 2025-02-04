/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:42 by jvidal-t          #+#    #+#             */
/*   Updated: 2024/10/17 00:57:18 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
	{
		count += ft_putchar(*s++);
	}
	return (count);
}

int	ft_putnbr(int nb)
{
	char			digit;
	unsigned int	nbr;
	int				count;

	count = 0;
	if (nb < 0)
	{
		nbr = nb * -1;
		count += ft_putchar('-');
	}
	else
		nbr = nb;
	if (nbr >= 10)
		count += ft_putnbr(nbr / 10);
	digit = nbr % 10 + '0';
	count += ft_putchar(digit);
	return (count);
}

int	ft_putnbr_u(unsigned int nbr)
{
	char	digit;
	int		count;

	count = 0;
	if (nbr >= 10)
		count += ft_putnbr(nbr / 10);
	digit = nbr % 10 + '0';
	count += ft_putchar(digit);
	return (count);
}

int	format_selector(char const *format, va_list args)
{
	int	count;

	count = 0;
	if (*format == '%')
		count += ft_putchar('%');
	else if (*format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (*format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (*format == 'd' || *format == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (*format == 'u')
		count += ft_putnbr_u(va_arg(args, int));
	else if (*format == 'x')
		count += ft_putnbr_base(va_arg(args, int), "0123456789abcdef");
	else if (*format == 'X')
		count += ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF");
	else if (*format == 'p')
		count += ft_putptr(va_arg(args, unsigned long long), "0123456789abcdef",
				1);
	return (count);
}
