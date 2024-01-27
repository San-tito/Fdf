/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 01:13:59 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libftprintf/include/ft_printf.h"
# include "../libs/minilibx/mlx.h"
# include <fcntl.h>

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_edge;

/* ************************************************************************** */
/*                            Parsing Helpers                                 */
/* ************************************************************************** */
char	*get_next_line(int fd);
void	parse_map(char *pathname, t_list **edges);

/* ************************************************************************** */
/*                           Rendering Function                               */
/* ************************************************************************** */
void	render_wireframe(t_list **edges);

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void	lstclear(t_list **lst);
void	arrclear(char **arr);

#endif
