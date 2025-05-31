#include "../include/cub3d.h"

/**
 * @brief Helper function to convert color components to RGB values
 * 
 * This function converts the string color components to integers and 
 * calculates the hexadecimal RGB representation for ceiling and floor colors.
 * 
 * @param vars The main program structure
 * @param temp Array of ceiling color component strings (R,G,B)
 * @param temp2 Array of floor color component strings (R,G,B)
 */
static void	assign_colors_2(t_vars *vars, char **temp, char **temp2)
{
	vars->colors->c_r = ft_atoi(temp[0]);
	vars->colors->c_g = ft_atoi(temp[1]);
	vars->colors->c_b = ft_atoi(temp[2]);
	vars->colors->f_r = ft_atoi(temp2[0]);
	vars->colors->f_g = ft_atoi(temp2[1]);
	vars->colors->f_b = ft_atoi(temp2[2]);
	vars->colors->c_hex = (vars->colors->c_r << 16)
		| (vars->colors->c_g << 8) | (vars->colors->c_b);
	vars->colors->f_hex = (vars->colors->f_r << 16)
		| (vars->colors->f_g << 8) | (vars->colors->f_b);
}

/**
 * @brief Parse and convert color strings to RGB values
 * 
 * This function processes the floor and ceiling color strings (format: "R,G,B")
 * and converts them to integer RGB values. It validates that each color has
 * exactly three components and handles memory allocation for the string parsing.
 * 
 * @param vars The main program structure
 */
void	assign_colors(t_vars *vars)
{
	int		i;
	char	**temp;
	char	**temp2;

	i = 0;
	temp = ft_split(vars->colors->c, ',');
	if (!temp)
		return (perror("malloc"), exit(1));
	while (temp[i])
		i++;
	if (i != 3)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1));
	i = 0;
	temp2 = ft_split(vars->colors->f, ',');
	if (!temp2)
		return (perror("malloc"), exit(1));
	while (temp2[i])
		i++;
	if (i != 3)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1));
	assign_colors_2(vars, temp, temp2);
	free_char_matrix(temp);
	free_char_matrix(temp2);
}
