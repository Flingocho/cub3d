/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:23:01 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/04 18:43:39 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//clear split
void free_matrix(char **mtx)
{
	int i;

	i = 0;
	while(mtx[i])
		free(mtx[i++]);
	free(mtx);
}

int	main(int argc, char *argv[])
{
	t_vars vars;
	vars.paths = calloc(sizeof(t_paths), 1);
	check_args(argc, argv, &vars);
	free_matrix(vars.file);
	return (OK);
}
