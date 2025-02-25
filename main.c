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

void	init_values(float *a, float *b, float *c, float *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int     color_picker(float count)
{
        if (count <= 0.01)
                return (0xffffff);
        if (count < 0.02)
                return (0xf9fff5);
        else if (count < 0.05)
                return (0xffffff);
        else if (count < 0.1)
                return (0x00ff00);
        else if (count < 0.5)
                return (0xff00ff);
        else
                return (0x0000ff);
}

double	rescale(float val, double in_max, double out_min, double out_max)
{
	return (out_min + (val * (out_max - out_min) / in_max));
}

int	render_img(t_mother *mb)
{
	double tmp;

	tmp = 0;
	init_values(&mb->f.i, &mb->f.j, &mb->f.count, &mb->f.max_itter);
	while (mb->f.i++ < mb->vars.screen_width)
	{
		mb->f.j = 0;
		while (mb->f.j++ < mb->vars.screen_height)
		{
			mb->f.count = 0;
			mb->f.x = rescale(mb->f.i, 1000, -2, 2) / mb->vars.zoom;
			mb->f.y = rescale(mb->f.j, 1000, 2, -2) / mb->vars.zoom;
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
					p_put(mb, mb->f.i, mb->f.j, color_picker(mb->f.count));
					break;
				}
				mb->f.count += 0.01;
			}
			if (mb->f.count >= 10)
					p_put(mb, mb->f.i, mb->f.j, color_picker(mb->f.count));
		}
	}
	return (0);
}

int	mouse_hook(int keycode, t_mother *mb)
{
	mb->vars.zoom *= 2;
	render_img(mb);
	mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	if (keycode == 4)
	{
		(void)mb;
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_mother mb;
	mb.vars.zoom = 2;

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
	mlx_key_hook(mb.libx.win, mouse_hook, &mb);
	mlx_put_image_to_window(mb.libx.mlx, mb.libx.win, mb.libx.img, 0, 0);
	mlx_loop(mb.libx.mlx);
	return (0);
}
