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

	dst = mb->libx.addr + (y * mb->libx.line_length + x * (mb->libx.bytes_per_pixel / 8));
	*(unsigned *)dst = color;
}

void	init_values(float *a, float *b, int *c, float *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

double	rescale(float val, double in_max, double out_min, double out_max)
{
	return (out_min + (val * (out_max - out_min) / in_max));
}

int	render_img(t_mother *mb)
{
	double tmp;

	tmp = 0;

	//init_values(&mb->f.i, &mb->f.j, &mb->f.count, &mb->f.max_itter);
	double i = 0;

	double j = 0;
	double count = 0;
	double x = 0;
	double y = 0;
	double c1 = 0;
	double c2 = 0;


	while (i++ < 1000)
	{

		j = 0;
		while (j++ < 1000)
		{
			count = 0;

			x = rescale(i, 1000, -2, 2) * mb->vars.zoom;
			y = rescale(j, 1000, 2, -2) * mb->vars.zoom;
			c1 = x;
			c2 = y;

			while (count <= 10)
			{
				tmp = x;
				x = (x * x) - (y * y);
				y = 2 * tmp * y;
				x = x + c1;
				y = y + c2;

				if ((x * x) + (y * y) > 4)
				{

					p_put(mb, i, j, 0xFFFFFF);
					break;
				}

				count += 1;
			}
			if (count >= 10)
					p_put(mb, i, j, 0x000000);
		}
	}
	return (0);
}

int	mouse_hook(int keycode, t_mother *mb)
{
	int aa = write(1, "xdd", 3);
	aa++;
	mb->vars.zoom += 0.2;
	render_img(mb);
	if (keycode == 4)
	{
		(void)mb;
		int a = write(1, "xdd", 3);
		a++;
//		mb->vars.zoom += 0.2;
//		render_img(mb);
//		return write(1, "MW UP", 5);
		return (1);
//		mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_mother mb;
	mb.vars.zoom = 1;

	mb.libx.mlx = mlx_init();
	mb.vars.screen_height = 1000;
	mb.vars.screen_width = 1000;
	if (ac > 1)
		mb.libx.win = mlx_new_window(mb.libx.mlx, 1000, 1000, av[1]);
	else
	{
		return (1);
	}
	mb.libx.img = mlx_new_image(mb.libx.mlx, 1000, 1000);
	mb.libx.addr = mlx_get_data_addr(mb.libx.img, &mb.libx.bytes_per_pixel, &mb.libx.line_length, &mb.libx.endian);
	render_img(&mb);
//	render_img(&mb);
//	mlx_mouse_hook(mb.libx.win, mouse_hook, &mb);
	mlx_key_hook(mb.libx.win, mouse_hook, &mb);
	mlx_put_image_to_window(mb.libx.mlx, mb.libx.win, mb.libx.img, 0, 0);
	mlx_loop(mb.libx.mlx);
	return (0);
}
