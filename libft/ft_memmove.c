/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:11:08 by jvidal-t          #+#    #+#             */
/*   Updated: 2024/09/25 16:29:58 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src2;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	i = 0;
	if (dest2 > src2)
	{
		while (n-- > 0)
			dest2[n] = src2[n];
	}
	else
	{
		while (i < n)
		{
			dest2[i] = src2[i];
			i++;
		}
	}
	return (dest);
}
