#include "header.h"

void	p_put(t_mother *mb, int x, int y, int color)
{
	char	*dst;

	dst = mb->libx.addr + (y * mb->libx.line_length + x
			* (mb->libx.bytes_per_pixel / 8));
	*(unsigned *)dst = color;
}

int	color_picker(int count, t_mother *mb)
{
	float	clr;
	int		red;
	int		blue;
	int		green;

	clr = (float)count / mb->f.max_itter;
	red = (int)(9 * clr * clr * clr * (1 - clr) * 255);
	green = (int)(15 * clr * clr * (1 - clr) * (1 - clr) * 255);
	blue = (int)(8.5 * clr * (1 - clr) * (1 - clr) * (1 - clr) * 255);
	return ((red << 16) | (green << 8) | blue);
}

void	calculate1(t_mother *mb)
{
	if (mb->vars.choice == 1)
	{
		mb->f.x = (rescale(mb->f.i, 1000, -2, 0.47)
				* mb->vars.zoom + mb->f.v_shift);
		mb->f.y = (rescale(mb->f.j, 1000, 1.12, -1.12)
				* mb->vars.zoom + mb->f.h_shift);
		mb->f.c1 = mb->f.x;
		mb->f.c2 = mb->f.y;
	}
	else
	{
		mb->f.x = (rescale(mb->f.i, 1000, -2, 2)
				* mb->vars.zoom + mb->f.v_shift);
		mb->f.y = (rescale(mb->f.j, 1000, 2, -2)
				* mb->vars.zoom + mb->f.h_shift);
		mb->f.c1 = mb->f.julia_c1;
		mb->f.c2 = mb->f.julia_c2;
	}
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
					break ;
				}
				mb->f.count += 1;
			}
			if (mb->f.count >= mb->f.max_itter)
				p_put(mb, mb->f.i, mb->f.j, 0x000000);
		}
	}
	return (0);
}
