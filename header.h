/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:19:09 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/02 02:09:17 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_vars
{
	int		choice;
	int		screen_width;
	int		screen_height;

	float	x1;
	float	x2;
	float	y1;
	float	y2;
	float	zoom;

}	t_vars;

typedef struct s_fractal
{
	float	max_itter;

	double	x;
	double	y;
	double	c1;
	double	c2;
	double	v_shift;
	double	h_shift;

	double	julia_c1;
	double	julia_c2;

	float	i;
	float	j;
	float	count;
	float	c_shift;
	double	tmp;

}	t_fractal;

typedef struct s_libx
{
	void	*mlx;
	void	*win;
	void	*img;

	int		bytes_per_pixel;
	int		line_length;
	int		endian;

	char	*addr;
}	t_libx;

typedef struct s_pyta
{
	double	x;
	double	y;
}	t_pyta;

typedef struct s_motherboard
{
	t_vars		vars;
	t_fractal	f;
	t_libx		libx;

}	t_mother;

void	init_mlx(t_mother *mb);
void	init_value(char *choice, t_mother mb);
void	init_fractal(t_mother *mb, int choice, double a, double b);
void	setup_hooks(t_mother *mb);
void	p_put(t_mother *mb, int x, int y, int color);
void	init_values(float *a, float *b, float *c);
int		key_hook(int keycode, t_mother *mb);
int		render_img(t_mother *mb);
int		mouse_hook(int keycode, int x, int y, t_mother *mb);
int		clear_data(t_mother *mb);
int		ft_strcmp(const char *s1, const char *s2);
int		color_picker(int count, t_mother *mb);
double	rescale(float val, double in_max, double out_min, double out_max);
double	d_atoi(char *str);

#endif
