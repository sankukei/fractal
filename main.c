/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:42:15 by leothoma          #+#    #+#             */
/*   Updated: 2025/02/20 00:42:17 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "header.h"
#include <stdio.h>
#include <unistd.h>

void	p_put(t_mother *mb, int x, int y, int color)
{
	char	*dst;

	dst = mb->libx.addr + (y * mb->libx.line_length + x
			* (mb->libx.bytes_per_pixel / 8));
	*(unsigned *)dst = color;
}

void	init_values(float *a, float *b, float *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int	color_picker(int count, t_mother *mb)
{
	float	clr;

	clr = (float)count / mb->f.max_itter;

	int red;
	int blue; 
	int green;

	red = (int)(9 * clr * clr * clr * (1 - clr) * 255);
	green = (int)(15 * clr * clr * (1 - clr) * (1 - clr) * 255);
	blue = (int)(8.5 * clr * (1 - clr) * (1 - clr) * (1 - clr) * 255);
	return ((red << 16) | (green << 8) | blue);

}

double	rescale(float val, double in_max, double out_min, double out_max)
{
	return (out_min + (val * (out_max - out_min) / in_max));
}

void	calculate1(t_mother *mb)
{
	mb->f.x = (rescale(mb->f.i, 1000, -2, 0.47) * mb->vars.zoom + mb->f.v_shift);
	mb->f.y = (rescale(mb->f.j, 1000, 1.12, -1.12) * mb->vars.zoom + mb->f.h_shift);
	mb->f.c1 = mb->f.x;
	mb->f.c2 = mb->f.y;
}

void	calulate2(t_mother *mb)
{
	mb->f.tmp = mb->f.x;
	mb->f.x = (mb->f.x * mb->f.x) - (mb->f.y * mb->f.y);
	mb->f.y = 2 * mb->f.tmp * mb->f.y;
	mb->f.x = mb->f.x + mb->f.c1;
	mb->f.y = mb->f.y + mb->f.c2;
}

int	render_img(t_mother *mb)
{
	mb->f.tmp = 0;
	init_values(&mb->f.i, &mb->f.j, &mb->f.count);
	while (mb->f.i++ < mb->vars.screen_width)
	{
		mb->f.j = 0;
		while (mb->f.j++ < mb->vars.screen_height)
		{
			mb->f.count = 0;
			calculate1(mb);	
			while (mb->f.count < mb->f.max_itter)
			{
				calulate2(mb);
				if ((mb->f.x * mb->f.x) + (mb->f.y * mb->f.y) > 4)
				{
					p_put(mb, mb->f.i, mb->f.j, color_picker(mb->f.count, mb));
					break;
				}
				mb->f.count += 1;
			}
			if (mb->f.count >= mb->f.max_itter)
					p_put(mb, mb->f.i, mb->f.j, 0x000000);
		}
	}
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_mother *mb)
{	
	(void)x;
	(void)y;
	if (keycode == 1)
	{
		mb->f.max_itter *= 1.2;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	if (keycode == 3)
	{
		mb->f.max_itter *= 0.8;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	if (keycode == 4)
	{
		mb->vars.zoom *= 0.9;
		mb->f.max_itter *= 1.05;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	if (keycode == 5)
	{
		mb->vars.zoom *= 1.1;
		mb->f.max_itter *= 0.95;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	return (0);
}

int	key_hook(int keycode, t_mother *mb)
{
//	printf("%d", keycode);
//	fflush(stdout);
	if (keycode == 65363)
	{
		mb->f.v_shift += 0.5 * mb->vars.zoom;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	if (keycode == 65361)
	{
		mb->f.v_shift -= 0.5 * mb->vars.zoom;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	if (keycode == 65362)
	{
		mb->f.h_shift += 0.5 * mb->vars.zoom;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	if (keycode == 65364)
	{
		mb->f.h_shift -= 0.5 * mb->vars.zoom;
		render_img(mb);
		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}

	if (keycode == 65307)
	{
		mlx_destroy_window(mb->libx.mlx, mb->libx.win);
		return (2);
	}
	return (0);	
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


double	d_atoi(char *str)
{
	int	i;
	int	y;
	double	res1;
	double	res2;
	int	neg;

	neg = 1;
	res1 = 0;
	res2 = 0;
	i = 0;
	y = 0;
	if (str[i] == '-')
		neg = -1;
	while (str[i] && str[i] != '.')
		res1 = (res1 * 10) + str[i++] - 48;
	i++;
	while (str[i] && i < ft_strlen(str))
	{
		res2 = (res2 * 10) + str[i++] - 48;
		y++;
	}
	while (y--)
		res2 /= 10;
	return ((res1 + res2) * neg);
}
int	main(int ac, char **av)
{
	d_atoi("10.6902");
	t_mother mb;
	if (!(ft_strcmp(av[1], "mandelbrot")))
	{
		write(1, "yes", 3);
	}
	else if (!(ft_strcmp(av[1], "julia")))
	{
	}
	else
		return (0);
	mb.vars.zoom = 1;
	mb.f.v_shift = 0;
	mb.f.h_shift = 0;
	mb.f.max_itter = 100;
	mb.libx.mlx = mlx_init();
	mb.vars.screen_height = 1000;
	mb.vars.screen_width = 1000;
	if (ac > 1)
		mb.libx.win = mlx_new_window(mb.libx.mlx, 1000, 1000, av[1]);
	else
		return (1);
	mb.libx.img = mlx_new_image(mb.libx.mlx, 1000, 1000);
	mb.libx.addr = mlx_get_data_addr(mb.libx.img, &mb.libx.bytes_per_pixel, &mb.libx.line_length, &mb.libx.endian);
	render_img(&mb);
	mlx_mouse_hook(mb.libx.win, mouse_hook, &mb);
	mlx_key_hook(mb.libx.win, key_hook, &mb);
	mlx_put_image_to_window(mb.libx.mlx, mb.libx.win, mb.libx.img, 0, 0);
	mlx_loop(mb.libx.mlx);
	return (0);
}
