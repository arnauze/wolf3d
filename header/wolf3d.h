/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 03:57:59 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/02 03:58:01 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/libft.h"
# include <math.h>
# include "../mlx/mlx.h"
# include <stdio.h>

typedef struct				s_color
{
	int						b;
	int						g;
	int						r;
	int						a;
}							t_color;

typedef	struct				s_vector
{
	double					x;
	double					y;
}							t_vector;

typedef	struct				s_ray
{
	double					x;
	double					y;
	int						side;
	t_vector				map;
	t_vector				dist_side;
	t_vector				delta_dist;
	t_vector				step;
}							t_ray;

typedef	struct				s_player
{
	t_vector				position;
	t_vector				direction;
	t_vector				projection_plane;
}							t_player;

typedef	struct				s_map
{
	char					**map;
	int						x;
	int						y;
}							t_map;

typedef	struct				s_mlx
{
	void					*mlx;
	void					*image;
	void					*window;
	unsigned char			*pixel;
	int						trash_a;
	int						trash_b;
	int						trash_c;
}							t_mlx;

typedef	struct 				s_move
{
	int 					up;
	int 					down;
	int 					left;
	int 					right;
	int 					rotate_right;
	int 					rotate_left;
}							t_move;

typedef	struct				s_variables
{
	t_ray					ray;
	t_player				player;
	t_mlx					mlx;
	t_map					map;
	t_move					move;
	double					camera;
	double					distance;
}							t_variables;

# define MAX_X 				1280.0
# define MAX_Y 				780.0
# define BLOCK_SIZE 		64
# define WALL_HEIGHT 		64
# define DISTANCE_PLANE 	1108

# define ANGLE 				60.0 * M_PI/180.0
# define ANG 				ANGLE / MAX_X
# define EYE_H 				32
# define ROT_SPEED 			3.0 / 180.0 * M_PI
# define MOVE_SPEED 		0.05

# define KEY_ESCAPE			53
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_E				14
# define KEY_CTRL_LEFT		256
# define KEY_SPACEBAR		49
# define KEY_LEFT			123
# define KEY_DOWN			125
# define KEY_RIGHT			124
# define KEY_UP				126
# define KEY_DEL			117

void						put_pixel(unsigned char *pixel, t_color color);
void						put_column(t_variables **data, int x, double size, t_color color);
int							keyboard(int key, void *param);
void						start_modelization(t_variables *data);
void						wolf_this_shit(t_variables *data);
t_map						get_map(char *path);
void						init_player(t_variables *data);
void						angle(t_vector *d, t_vector *pp, int key);
int							change_pos(t_variables *data);
void						algorithm(t_variables *data);
void						new_frame(unsigned char *pixels, int size);
t_color						set_color(char *str);
t_color						get_color(t_variables *data);
void						dda(t_variables **data);
void						init_variables(t_variables **data, int x);
int 						key_release(int key, void *param);
int 						key_press(int key, void *param);
int 						key_exit(void);

#endif