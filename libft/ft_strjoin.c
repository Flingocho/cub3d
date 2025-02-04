/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:25:24 by jvidal-t          #+#    #+#             */
/*   Updated: 2024/09/25 12:48:10 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*new;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	new = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, s1len + 1);
	ft_strlcpy(new + s1len, s2, s2len + 1);
	return (new);
}
