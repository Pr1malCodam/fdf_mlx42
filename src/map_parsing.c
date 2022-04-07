#include "../include/fdf.h"

/*==============================================================================
 * Reads an ".fdf" file , through the passed argv argument,stores the data 
 * in a string and converts it to an int array and stores this in a struct.
 * It also counts the width and height of the map and stores this in the same
 * struct.
 * 
 * parse_map expects a string that has the relative filepath to the mapfile.
 * parse map return a t_map struct with: map.map_points, map.map_width, 
 * map.map_height.
=============================================================================*/

static int	count_width(char *str_map)
{
	int	width_count;
	int	i;

	width_count = 0;
	i = 0;
	while (str_map[i] != '\n')
	{
		if (ft_isdigit(str_map[i]))
		{
			width_count++;
			while (ft_isdigit(str_map[i]))
				i++;
		}
		if (str_map[i] == ' ' || str_map[i] == '-')
			i++;
		if (str_map[i] == ',')
		{
			while (!ft_isspace(str_map[i]))
				i++;
		}
	}
	return (width_count);
}

static t_map	process(char *str_map, int depth_count)
{
	t_map	map;
	int		i;
	int		num;

	i = 0;
	num = 0;
	map.height = depth_count;
	map.width = count_width(str_map);
	map.points = (int *)ft_calloc(depth_count * map.width, sizeof(int));
	while (str_map[i])
	{
		if (ft_isdigit(str_map[i]) || str_map[i] == '-')
		{
			map.points[num] = ft_atoi(&str_map[i]);
			num++;
		}
		while (!ft_isspace(str_map[i]) && str_map[i])
			i++;
		while (ft_isspace(str_map[i]) && str_map[i])
			i++;
	}
	free (str_map);
	return (map);
}

t_map	parse_map(const char *filepath)
{
	int		fd;
	int		depth_count;
	char	*temp;
	char	*str_map;

	depth_count = 0;
	str_map = NULL;
	fd = open(filepath, O_RDONLY);
	if (fd < 0 || !ft_strnstr(filepath, ".fdf", ft_strlen(filepath)))
		error(RED"Invalid pathname! Needs to be \".fdf\""RESET);
	while (true)
	{
		temp = ft_get_next_line(fd);
		if (temp)
		{
			str_map = ft_strappend(str_map, temp);
			depth_count++;
		}
		else
			break ;
		free(temp);
	}
	close(fd);
	return (process(str_map, depth_count));
}