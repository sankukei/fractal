/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:19:09 by leothoma          #+#    #+#             */
/*   Updated: 2025/02/20 02:19:10 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

typedef struct	s_vars
{
	int	screen_width;
	int	screen_height;

	float	x1;
	float	x2;
	float	y1;
	float	y2;
	float	zoom;

} t_vars;

typedef struct	s_fractal
{
	float	max_itter;

	double	x;
	double	y;
	double	c1;
	double	c2;

	float	i;
	float	j;
	float	count;

	double	tmp;

} t_fractal;

typedef struct	s_libx
{
	void	*mlx;
	void	*win;
	void	*img;

	int	bytes_per_pixel;
	int	line_length;
	int	endian;

	char	*addr;
} t_libx;

typedef struct	s_motherboard
{
	 t_vars	vars;
	 t_fractal f;
	 t_libx	libx;
	
} t_mother;

#endif
