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

	dst = mb->libx.addr + (y * mb->libx.line_length + x * 
			(mb->libx.bytes_per_pixel / 8));
	*(unsigned *)dst = color;
}

void	init_values(float *a, float *b, float *c, float *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

double	rescale(int val, double in_max, double out_min, double out_max)
{
	return (out_min + (val * (out_max - out_min) / in_max));
}

void	render_img(t_mother *mb)
{
	double tmp;

	tmp = 0;
	mb->vars.screen_height = 1000;
	mb->vars.screen_width = 1000;
	init_values(&mb->f.i, &mb->f.j, &mb->f.count, &mb->f.max_itter);
	while (mb->f.i++ < mb->vars.screen_width)
	{
		mb->f.j = 0;
		while (mb->f.j++ < mb->vars.screen_height)
		{
			mb->f.count = 0;
			mb->f.x = rescale(mb->f.i, 1000, -2, 2);
			mb->f.y = rescale(mb->f.j, 1000, -2, 2);
			mb->f.c1 = mb->f.x;
			mb->f.c2 = mb->f.y;
			while (mb->f.count <= 10)
			{
				tmp = mb->f.x;
				mb->f.x = (mb->f.x * mb->f.x) - (mb->f.y * mb->f.y);
				mb->f.y = 2 * tmp * mb->f.y;
				mb->f.x = mb->f.x + mb->f.c1;
				mb->f.y = mb->f.y + mb->f.c2;
				if ((mb->f.x * mb->f.x) + (mb->f.y * mb->f.y) > 4)
				{
					p_put(mb, mb->f.i, mb->f.j, 0xFFFFFF);
					break;
				}
				mb->f.count += 0.01;
			}
			if (mb->f.count >= 10)
					p_put(mb, mb->f.i, mb->f.j, 0x000000);
		}
	}
}

int	main(int ac, char **av)
{
	t_mother mb;

	mb.libx.mlx = mlx_init();
	if (ac > 1)
		mb.libx.win = mlx_new_window(mb.libx.mlx, 1000, 1000, av[1]);
	else
	{
		return (1);
	}
	mb.libx.img = mlx_new_image(mb.libx.mlx, 1000, 1000);
	mb.libx.addr = mlx_get_data_addr(mb.libx.img, &mb.libx.bytes_per_pixel, &mb.libx.line_length, &mb.libx.endian);
	render_img(&mb);
	mlx_put_image_to_window(mb.libx.mlx, mb.libx.win, mb.libx.img, 0, 0);
	mlx_loop(mb.libx.mlx);
	return (0);
}
