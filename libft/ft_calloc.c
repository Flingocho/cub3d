/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:12:45 by jvidal-t          #+#    #+#             */
/*   Updated: 2024/10/04 12:21:16 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	new = (void *)malloc(nmemb * size);
	if (!new)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}
