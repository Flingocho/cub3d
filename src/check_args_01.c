#include "../include/cub3d.h"

/**
 * @brief Check if the correct number of arguments is provided
 * 
 * This function verifies that exactly one argument is provided to the program
 * (the path to the map file).
 * 
 * @param argc The argument count from main function
 * @return OK if exactly one argument is provided, ERROR otherwise
 */
static int	check_args_number(int argc)
{
	if (argc == 2)
		return (OK);
	return (ERROR);
}

/**
 * @brief Check if the provided map file has the correct extension
 * 
 * This function verifies that the map file provided has a .cub extension,
 * which is the required format for the program.
 * 
 * @param argv Array of command line arguments
 * @return OK if the file has a .cub extension, ERROR otherwise
 */
static int	check_argv_extension(char *argv[])
{
	int	i;

	i = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4) == OK)
		return (OK);
	return (ERROR);
}

/**
 * @brief Main argument validation function
 * 
 * This function performs a series of checks on the command line arguments:
 * 1. Verifies the correct number of arguments
 * 2. Checks if the file has the correct extension (.cub)
 * 3. Ensures the map file exists and can be opened
 * If all checks pass, it reads the map file and processes its contents
 * 
 * @param argc The argument count from main function
 * @param argv Array of command line arguments
 * @param vars Pointer to the main structure storing program state
 * @return OK if all checks pass, ERROR otherwise (with program termination)
 */
int	check_args(int argc, char *argv[], t_vars *vars)
{
	if (check_args_number(argc) == OK && check_argv_extension(argv) == OK
		&& check_map_exists(argv[1], vars) == OK)
	{
		read_fd_file(vars);
		return (OK);
	}
	else
	{
		ft_putstr_fd("Error:\nProblem with arguments.\n", STDERR_FILENO);
		exit(ERROR);
	}
	return (ERROR);
}
