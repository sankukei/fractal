void	draw_line(int x1, int y1, int x2, int y2)
{

}

void	pyta(t_pyta a, t_pyta b, int iter)
{
	// IMPLEMENTER DRAW LINE
	(void)a;
	(void)b;
	
	t_pyta	c;
	t_pyta	d;
	t_pyta	e;

	c.x = b.x - (a.y - b.y);
	c.y = b.y - (b.x - a.x);
	d.x = a.x - (a.y - b.y);
	d.y = a.y - (b.x - a.x);
	e.x = d.x + (b.x - a.x - (a.y - b.y)) / 2;
	e.y = d.y + (b.x - a.x + a.y - b.y) / 2;

	if (iter > 0)
	{
		
	}

}

void	init_pyta(int iter, double side)
{
	t_pyta	a;
	t_pyta	b;
	(void)iter;
	a.x = 6 * side / 2 - side / 2;
	a.y = 4 * side;
	b.x = 6 * side / 2 - side / 2;
	b.y = 4 * side;

	iter = 10;
	pyta(a, b);
}
