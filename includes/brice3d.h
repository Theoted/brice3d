/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:42:34 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/27 12:00:33 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRICE3D_H
# define BRICE3D_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# define PI 3.14159265359
// Keycode
	# define MOUSE_UP 4
	# define MOUSE_DOWN 5
	# define MOUSE_WHELL 3
	# define LMB 1
	# define RMB 2
	# define KEY_C 8
	# define KEY_V 9
	# define KEY_B 11
	# define KEY_Q 12
	# define KEY_R 15
	# define KEY_O 31
	# define KEY_P 35
	# define KEY_TAB 48
	# define KEY_ESC 53
	# define KEY_UP 126
	# define KEY_DOWN 125
	# define KEY_LEFT 123
	# define KEY_RIGHT 124
	# define KEY_W 13
	# define KEY_E 14
	# define KEY_S 1
	# define KEY_A 0
	# define KEY_D 2
	# define KEY_1 83
	# define KEY_2 84
	# define KEY_4 86
	# define KEY_5 87
	# define KEY_7 89
	# define KEY_8 91
	# define KEY_PLUS 69
	# define KEY_MINUS 78

typedef struct s_vector2_d
{
	int	x;
	int	y;
} t_vector2_d;

typedef struct s_vector2_f
{
	float	x;
	float	y;
} t_vector2_f;

typedef struct t_ray {
	t_vector2_f	hit_point;
	t_vector2_d cell;
	double 		length;
	int 		side_hit;
	double 		angle;
} t_ray;

typedef struct s_data
{
	// MiniLibX
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_height;
	int		win_width;

	// Tab
	int		**tab;
	int		tab_width;
	int		tab_height;
	int		cell_size;

	// event
	int			mouse_button;
	t_vector2_d mouse_pos;
	int			mouse_pressed;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int 	init_tab(t_data *data);
void	set_grid_cell(t_data *data, int x, int y);
void	print_grid(t_data *data);

int _bresenham(t_data *data, int x0, int y0, int x1, int y1);

t_vector2_f	vector_d_to_f(t_vector2_d vector_d);
t_vector2_d	vector_f_to_d(t_vector2_f vector_f);

float	ft_abs_f(float nbr);
int		ft_abs_d(int nbr);

double	get_angle(t_vector2_d start, t_vector2_d end);
double	get_angle_f(t_vector2_f start, t_vector2_f end);

#endif