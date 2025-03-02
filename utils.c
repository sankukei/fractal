#include "header.h"

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
	int		i;
	int		y;
	double	res1;
	double	res2;
	int		neg;

	neg = 1;
	res1 = 0;
	res2 = 0;
	i = 0;
	y = 0;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (str[i] && str[i] != '.')
		res1 = (res1 * 10) + str[i++] - 48;
	i++;
	while (str[i] && ++y)
		res2 = (res2 * 10) + str[i++] - 48;
	while (y-- > 0)
		res2 /= 10;
	return ((res1 + res2) * neg);
}

double	rescale(float val, double in_max, double out_min, double out_max)
{
	return (out_min + (val * (out_max - out_min) / in_max));
}

int	clear_data(t_mother *mb)
{
	mlx_clear_window(mb->libx.mlx, mb->libx.win);
	mlx_destroy_image(mb->libx.mlx, mb->libx.img);
	mlx_destroy_window(mb->libx.mlx, mb->libx.win);
	mlx_destroy_display(mb->libx.mlx);
	mlx_loop_end(mb->libx.mlx);
	free(mb->libx.mlx);
	exit(0);
	return (1);
}
