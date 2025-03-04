/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:28:29 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/04 14:28:31 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	mouse_hook(int keycode, int x, int y, t_mother *mb)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		mb->f.max_itter *= 1.2;
	else if (keycode == 3)
		mb->f.max_itter *= 0.8;
	else if (keycode == 4)
	{
		mb->vars.zoom *= 0.9;
		mb->f.max_itter *= 1.05;
	}
	else if (keycode == 5)
	{
		mb->vars.zoom *= 1.1;
		mb->f.max_itter *= 0.95;
	}
	render_img(mb);
	mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_mother *mb)
{
	if (keycode == 65363)
		mb->f.v_shift += 0.5 * mb->vars.zoom;
	else if (keycode == 65361)
		mb->f.v_shift -= 0.5 * mb->vars.zoom;
	else if (keycode == 65362)
		mb->f.h_shift += 0.5 * mb->vars.zoom;
	else if (keycode == 65364)
		mb->f.h_shift -= 0.5 * mb->vars.zoom;
	else if (keycode == 99)
		mb->f.c_shift *= 1.25;
	else if (keycode == 65307)
		clear_data(mb);
	render_img(mb);
	mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
	return (0);
}
