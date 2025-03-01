#include "header.h"

void	init_fractal(t_mother *mb, int choice)
{
	if (choice == 1)
		mb->vars.choice = 1;
	else
		mb->vars.choice = 0;
	mb->vars.zoom = 1;
	mb->f.v_shift = 0;
	mb->f.h_shift = 0;
	mb->f.max_itter = 100;
	mb->vars.screen_height = 1000;
	mb->vars.screen_width = 1000;
}

void	init_mlx(t_mother *mb)
{
	mb->libx.mlx = mlx_init();
	mb->libx.win = mlx_new_window(mb->libx.mlx, 1000, 1000, "fractal");
	mb->libx.img = mlx_new_image(mb->libx.mlx, 1000, 1000);
	mb->libx.addr = mlx_get_data_addr(mb->libx.img,
			&mb->libx.bytes_per_pixel, &mb->libx.line_length, &mb->libx.endian);
	render_img(mb);
	mlx_put_image_to_window(mb->libx.mlx, mb->libx.win, mb->libx.img, 0, 0);
}

void	setup_hooks(t_mother *mb)
{
	mlx_hook(mb->libx.win, 2, 1L << 0, key_hook, mb);
	mlx_mouse_hook(mb->libx.win, mouse_hook, mb);
	mlx_hook(mb->libx.win, 17, 0, clear_data, mb);
}
