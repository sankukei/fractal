/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:42:15 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/01 16:43:38 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_values(float *a, float *b, float *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int	main(int ac, char **av)
{
	t_mother	mb;

	if (ac > 1 && av[1] && !(ft_strcmp(av[1], "mandelbrot")))
		init_fractal(&mb, 1);
	else if (ac == 4 && av[1] && !(ft_strcmp(av[1], "julia")))
		init_fractal(&mb, 2);
	else
		return (write(1, "mandelbrot | julia + 'c1' + 'c2'", 33));
	init_mlx(&mb);
	setup_hooks(&mb);
	mlx_loop(mb.libx.mlx);
}
