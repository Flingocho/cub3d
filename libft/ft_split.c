/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:03:02 by jvidal-t          #+#    #+#             */
/*   Updated: 2024/10/16 20:22:41 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			words++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

static int	word_len(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static int	*clear_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		index[3];

	split = (char **)ft_calloc(count_words((char *)s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	index[0] = 0;
	index[1] = 0;
	while (s[index[0]])
	{
		if (s[index[0]] != c)
		{
			index[2] = word_len((char *)&s[index[0]], c) + 1;
			split[index[1]] = (char *)ft_calloc(index[2], sizeof(char));
			if (!split[index[1]])
				return ((char **)clear_split(split));
			ft_strlcpy(split[index[1]], &s[index[0]], index[2]);
			index[0] += index[2] - 1;
			index[1]++;
		}
		else
			index[0]++;
	}
	return (split);
}
