/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:17:28 by jvidal-t          #+#    #+#             */
/*   Updated: 2024/09/25 12:46:07 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(char const letter, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (letter == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	s1len;
	char	*new;

	start = 0;
	s1len = ft_strlen(s1);
	while (s1[start] != '\0' && checkset(s1[start], set))
	{
		start++;
	}
	while (s1len > start && checkset(s1[s1len - 1], set))
	{
		s1len--;
	}
	new = (char *)malloc((s1len - start + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1 + start, (s1len - start + 1));
	return (new);
}
