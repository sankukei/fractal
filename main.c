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

void	my_mlx_pixel_put(t_mother *mb, int x, int y, int color)
{
	char	*dst;

	dst = mb->libx.addr + (y * mb->libx.line_length + x * (mb->libx.bytes_per_pixel / 8));
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
	init_values(&mb->frac.i, &mb->frac.j, &mb->frac.count, &mb->frac.max_itter);
	while (mb->frac.i++ < mb->vars.screen_width)
	{
		while (mb->frac.j++ < mb->vars.screen_height)
		{
			mb->frac.count = 0;
			mb->frac.x = rescale(mb->frac.i, 1000, -2, 2);
			mb->frac.y = rescale(mb->frac.j, 1000, -2, 2);
			mb->frac.c1 = mb->frac.x;
			mb->frac.c2 = mb->frac.y;
			while (mb->frac.count <= 10)
			{
				tmp = mb->frac.x;
				mb->frac.x = (mb->frac.x * mb->frac.x) - (mb->frac.y * mb->frac.y);
				mb->frac.y = 2 * tmp * mb->frac.y;
				mb->frac.x = mb->frac.x + mb->frac.c1;
				mb->frac.y = mb->frac.y + mb->frac.c2;
				if ((mb->frac.x * mb->frac.x) + (mb->frac.y * mb->frac.y) > 4)
				{
					my_mlx_pixel_put(mb->libx.img, mb->frac.i, mb->frac.j, 0xFFFFFF);
					break;
				}
				mb->frac.count += 0.01;
			}
			if (mb->frac.count >= 10)
					my_mlx_pixel_put(mb->libx.img, mb->frac.i, mb->frac.j, 0x000000);
		}
		mb->frac.j = 0;
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
		write(1, "no", 2);
		return (1);
	}
	mb.libx.img = mlx_new_image(mb.libx.mlx, 1000, 1000);
	mb.libx.addr = mlx_get_data_addr(mb.libx.img, &mb.libx.bytes_per_pixel, &mb.libx.line_length, &mb.libx.endian);
	render_img(&mb);
	mlx_put_image_to_window(mb.libx.mlx, mb.libx.win, mb.libx.img, 0, 0);
	mlx_loop(mb.libx.mlx);
	return (0);
}
