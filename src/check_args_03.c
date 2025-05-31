#include "../include/cub3d.h"

/**
 * @brief Process floor and ceiling color identifiers in the map file
 * 
 * This function handles the 'F' (floor) and 'C' (ceiling) color identifiers
 * in the map file. It extracts the color values and stores them in the 
 * vars->colors structure, ensuring each identifier appears only once.
 * 
 * @param vars The main program structure
 * @param value The configuration line containing the color identifier
 * @return OK on success, ERROR on failure (memory allocation or duplicate identifiers)
 */
int	set_value_03(t_vars *vars, char *value)
{
	if (ft_strncmp(value, "F", 1) == OK)
	{
		if (vars->colors->f)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->colors->f = ft_strtrim(value + 2, " \t");
		if (!vars->colors->f)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "C", 1) == OK)
	{
		if (vars->colors->c)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->colors->c = ft_strtrim(value + 2, " \t");
		if (!vars->colors->c)
			return (perror("malloc"), ERROR);
	}
	return (OK);
}

/**
 * @brief Process west and east texture identifiers in the map file
 * 
 * This function handles the 'WE' (west) and 'EA' (east) texture identifiers
 * in the map file. It extracts the texture paths and stores them in the
 * vars->paths structure, ensuring each identifier appears only once.
 * It delegates to set_value_03 for floor and ceiling color handling.
 * 
 * @param vars The main program structure
 * @param value The configuration line containing the texture identifier
 * @return OK on success, ERROR on failure
 */
static int	set_value_02(t_vars *vars, char *value)
{
	if (ft_strncmp(value, "WE", 2) == OK)
	{
		if (vars->paths->we)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->we = ft_strtrim(value + 3, " \t");
		if (!vars->paths->we)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "EA", 2) == OK)
	{
		if (vars->paths->ea)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->ea = ft_strtrim(value + 3, " \t");
		if (!vars->paths->ea)
			return (perror("malloc"), ERROR);
	}
	else if (set_value_03(vars, value) == ERROR)
		return (ERROR);
	return (OK);
}

/**
 * @brief Process north and south texture identifiers in the map file
 * 
 * This function handles the 'NO' (north) and 'SO' (south) texture identifiers
 * in the map file. It also recognizes the start of map data (lines beginning with '1').
 * It extracts the texture paths and stores them in the vars->paths structure,
 * ensuring each identifier appears only once.
 * 
 * @param vars The main program structure
 * @param value The configuration line containing the texture identifier
 * @return 2 if map data starts, OK on success, ERROR on failure
 */
static int	set_value(t_vars *vars, char *value)
{
	if (value[0] == '1')
		return (2);
	else if (ft_strncmp(value, "NO", 2) == OK)
	{
		if (vars->paths->no)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->no = ft_strtrim(value + 3, " \t");
		if (!vars->paths->no)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "SO", 2) == OK)
	{
		if (vars->paths->so)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->so = ft_strtrim(value + 3, " \t");
		if (!vars->paths->so)
			return (perror("malloc"), ERROR);
	}
	else if (set_value_02(vars, value) == ERROR)
		return (ERROR);
	return (OK);
}

/**
 * @brief Parse the map file contents and extract configuration
 * 
 * This function processes the map file line by line to extract texture paths,
 * colors, and identify the start of the actual map data. It skips empty lines
 * and processes each non-empty line by calling set_value().
 * Once it finds the start of the map data, it assigns color values and sets
 * the map pointer to the current position in the file array.
 * 
 * @param vars The main program structure
 */
void	parse_file(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->file[i])
	{
		j = 0;
		while (vars->file[i][j] != '\0' && isspace(vars->file[i][j]))
			j++;
		if (vars->file[i][j] != '\0')
		{
			if (set_value(vars, &vars->file[i][j]) == 2)
			{
				assign_colors(vars);
				vars->map = &vars->file[i];
				break ;
			}
		}
		i++;
	}
}
