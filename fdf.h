/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:23:31 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/26 22:22:20 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// # include <mlx.h>
# include "./libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "./include/MLX42/MLX42_Int.h"
# include "./include/MLX42/MLX42.h"
# include <limits.h>

/*Standard definitions*/
# ifndef WINDOW_NAME
#  define WINDOW_NAME "FdF"
# endif

# define SIZE 30
# define LAYOUT_WIDTH 50
# define LAYOUT_HEIGHT 50
# ifndef RESIZEABLE
#  define RESIZEABLE true
# endif

/*Structures definition*/
typedef struct s_coords
{
	char			**coordinate;
	struct s_point	*points;
	struct s_coords	*next;
}				t_coords;

typedef struct s_point
{
	uint32_t		x;
	uint32_t		y;
	int32_t			z;
	uint32_t		iso_x;
	uint32_t		iso_y;
	uint32_t		color;
	struct s_point	*next;
}				t_points;

typedef struct s_vars
{
	mlx_t		*mlx;
	void		*win;
	mlx_image_t	*img;
	t_coords	*coords;
	uint32_t	width;
	uint32_t	height;
	uint32_t	x;
	uint32_t	y;
	uint32_t	ymax;
	uint32_t	ymin;
	uint32_t	xmax;
	uint32_t	zmax;
}				t_vars;

typedef struct s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;
}			t_color;

typedef struct s_pixel
{
	uint32_t	x;
	uint32_t	y;
	long		d_x;
	long		d_y;
	long		slope_error;
	uint32_t	color_fr;
	uint32_t	color_to;
}				t_pixel;

/*Vars functions*/
t_vars		*init_vars(char *file_name);

/*Coordinates functions*/
t_coords	*init_coords(t_coords **coords, char **data);
int			parse_coordinates(char *file_name, t_vars *vars);
void		move_picture(t_vars *vars);

/*Points functions*/
void		init_isometrics(t_vars *vars);
t_points	*init_point(t_points **points, uint32_t x, uint32_t y, int32_t z);
t_points	*init_points(t_coords *coords, uint32_t step_x,
				uint32_t step_y, uint32_t line);
t_coords	*init_pointcoord(t_coords **coords, t_vars *vars);
void		move_picture(t_vars *vars);

/*Terminate and free functions*/
void		*free_points(t_points **points);
void		*free_coordinates(char **ptr);
void		*free_coords(t_coords **coords);
void		*terminate_vars(t_vars **vars);

/*Other utils*/
uint32_t	ft_arraystrlen(char **array);
uint32_t	limits(uint32_t num, uint32_t num2, uint32_t max);
int32_t		zmax(t_vars *vars);
int32_t		zmin(t_vars *vars);
uint32_t	xmax(t_vars *vars);
void		yext(t_vars *vars);
uint32_t	iso(t_vars *vars, t_points *point, char axes);
uint32_t	min_max_point(t_vars *vars, char axes);
void		init_colors_points(t_vars *vars);
uint32_t	htoi_color(const char *str);
void		clean_pixel(mlx_image_t *img, uint32_t x, uint32_t y);

/*Hooks*/
void		ft_hook_buttons(void *param);

/*Colors & pixels*/
// void		put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void		put_pixel(mlx_image_t *img, t_pixel pixel, uint32_t y);
// void		draw_pixel(uint8_t *pixel, uint32_t color);
void		draw_pixel(uint8_t *pixel, t_color color);

/*Maths function*/
int32_t		max(int32_t n1, int32_t n2);
int32_t		min(int32_t n1, int32_t n2);

/*Bresenhams line lgorithm drawers*/
void		draw_line_slope(t_vars *vars, t_points *column,
				t_points *next_column);
void		draw_line_negslope(t_vars *vars, t_points *column,
				t_points *next_column);
void		draw_column_slope(t_vars *vars, t_points *line,
				t_points *next_line);
void		draw_column_negslope(t_vars *vars, t_points *line,
				t_points *next_line);
void		put_iso_column(t_vars *vars);
void		put_iso_line(t_vars *vars);

#endif
