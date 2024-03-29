/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:11:24 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/22 15:40:44 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clean_halt(int fd, t_list **edges, char *line, char **coords)
{
	if (fd > 0)
		close(fd);
	lstclear(edges);
	free(line);
	if (coords)
		arrclear(coords);
	perror("Error");
	exit(EXIT_FAILURE);
}

static int	parse_color(char *token)
{
	unsigned int	color;
	const char		*start = ft_strchr(token, ',');

	color = 0x000000;
	if (!start)
		return (0xFFFFFF);
	token = (char *)start + 1;
	if (!ft_strncmp(token, "0x", 2) || !ft_strncmp(token, "0X", 2))
		token += 2;
	while (ft_isdigit(*token) || (*token >= 'a' && *token <= 'f')
		|| (*token >= 'A' && *token <= 'F'))
	{
		color *= 16;
		if (ft_isdigit(*token))
			color += (*token - '0');
		else if (*token >= 'a' && *token <= 'f')
			color += (*token - 'a' + 10);
		else if (*token >= 'A' && *token <= 'F')
			color += (*token - 'A' + 10);
		token++;
	}
	return (color);
}

static t_edge	*parse_coord(int x, int y, char *token)
{
	t_edge	*edge;

	edge = ft_calloc(1, sizeof(t_edge));
	if (!edge)
		return (NULL);
	(*edge).axis = x;
	(*edge).ordinate = y;
	(*edge).altitude = ft_atoi(token);
	(*edge).color = parse_color(token);
	return (edge);
}

static void	parse_line(char *line, t_list **edges, int ordinate, int fd)
{
	t_list	*new;
	t_edge	*edge;
	char	**coords;
	int		x;

	coords = ft_split(line, ' ');
	if (!coords)
		clean_halt(fd, edges, line, NULL);
	x = 0;
	while (*(coords + x))
	{
		edge = parse_coord(x, ordinate, *(coords + x));
		if (!edge)
			clean_halt(fd, edges, line, coords);
		new = ft_lstnew(edge);
		ft_lstadd_back(edges, new);
		if (!new)
			clean_halt(fd, edges, line, coords);
		x++;
	}
	arrclear(coords);
}

void	parse_map(char *pathname, t_list **edges)
{
	char		*line;
	int			fd;
	int			ordinate;
	const char	*spinner = "|/-\\";

	fd = open(pathname, O_RDONLY);
	if (fd < 0)
		clean_halt(fd, edges, NULL, NULL);
	ordinate = 0;
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("Parsing line %d %c\r", ordinate, *(spinner + (ordinate
					% ft_strlen(spinner))));
		parse_line(line, edges, ordinate++, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (!ft_lstsize(*edges))
		clean_halt(fd, edges, NULL, NULL);
	ft_printf("Parsing complete!                  \n");
	close(fd);
}
