/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:35 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/28 22:23:12 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_scene scene;

	scene.xlib = (t_xlib){};
	scene.edges = NULL;
	if (argc != 2)
		return (EXIT_SUCCESS);
	parse_map(*(argv + 1), &scene.edges);
	render_wireframe(&scene);
	lstclear(&scene.edges);
	xlibclear(&scene.xlib);
	return (EXIT_SUCCESS);
}
