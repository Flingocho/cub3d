#include "../include/cub3d.h"

/**
 * @brief Skip through configuration lines to find the start of the map data
 * 
 * This function navigates through texture and color configuration lines
 * until it reaches the actual map data (which starts with '0' or '1').
 * 
 * @param file The buffer containing the entire map file content
 * @param i Pointer to the current position in the buffer
 * @return OK if the map data is found, ERROR if we reach end of file
 */
static int	skip_vals_lines(char *file, int *i)
{
	while (file[*i])
	{
		while (file[*i] && file[*i] != '\n')
			(*i)++;
		if (file[*i] == '\0')
			break ;
		(*i)++;
		while (file[*i] && isspace(file[*i]))
			(*i)++;
		if (file[*i] && (file[*i] == '0' || file[*i] == '1'))
			break ;
	}
	if (!file[*i])
		return (ERROR);
	return (OK);
}

/**
 * @brief Check for invalid newlines within the map data
 * 
 * This function verifies that the map is contiguous without empty lines
 * between its data rows. An empty line after map data indicates the end of
 * the map, but empty lines inside the map data are not allowed.
 * 
 * @param file The buffer containing the entire map file content
 * @return OK if the map is valid, ERROR if invalid empty lines are found
 */
static int	check_n_between_map(char *file)
{
	int	i;

	i = 0;
	if (skip_vals_lines(file, &i) == ERROR)
		return (ERROR);
	while (file[i])
	{
		while (file[i] && file[i] != '\n')
			i++;
		if (file[i] == '\0')
			break ;
		i++;
		if (file[i] == '\n')
		{
			while (file[i] && (isspace(file[i]) || file[i] == '\n'))
				i++;
			if (file[i] == '\0')
				return (OK);
			else
				return (ERROR);
		}
	}
	return (OK);
}

/**
 * @brief Read and process the map file
 * 
 * This function reads the map file into a buffer, checks its format,
 * and prepares it for parsing. It performs the following operations:
 * 1. Allocates memory for the buffer
 * 2. Reads the file content into the buffer
 * 3. Validates the map structure (no empty lines within map data)
 * 4. Splits the buffer into lines for further processing
 * 5. Cleans up resources and initiates file parsing
 * 
 * @param vars Pointer to the main structure storing program state
 */
void	read_fd_file(t_vars *vars)
{
	vars->buffer = ft_calloc(sizeof(char *), BUFF_SIZE);
	if (!vars->buffer)
		return (perror("malloc"), close(vars->map_path_fd),
			free(vars->map_path), exit(ERROR));
	vars->bytes_read = read(vars->map_path_fd, vars->buffer, BUFF_SIZE);
	if (vars->bytes_read == -1 || vars->buffer[BUFF_SIZE - 1] != '\0')
		return (perror("read"), close(vars->map_path_fd), free(vars->map_path),
			exit(ERROR));
	if (check_n_between_map(vars->buffer) == ERROR)
		return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
			exit(1));
	vars->file = ft_split(vars->buffer, '\n');
	if (!vars->file)
		(perror("read"), exit(ERROR));
	close(vars->map_path_fd);
	free(vars->buffer);
	parse_file(vars);
}

/**
 * @brief Check if the map file exists and can be opened
 * 
 * This function attempts to open the map file to verify it exists
 * and is accessible for reading.
 * 
 * @param path Path to the map file
 * @param vars Pointer to the main structure storing program state
 * @return OK if the file exists and can be opened, ERROR otherwise
 */
int	check_map_exists(char *path, t_vars *vars)
{
	vars->map_path_fd = open(path, O_RDONLY);
	if (vars->map_path_fd < 0)
		return (perror("open"), exit(ERROR), ERROR);
	return (OK);
}
