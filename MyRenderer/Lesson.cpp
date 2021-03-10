#include "Lesson.h"

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	for (float t = 0.; t < 1.; t += .01)
	{
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		image.set(x, y, color);
	}
}//效率低

void line1(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	for (int x = x0; x < x1; x++)
	{
		float t = (x - x0) / (float)(x1 - x0);//算出来目前走了路长的几分之几
		int y = y0 * (1. - t) + y1 * t;//展开来和上面那个函数一样
		image.set(x, y,color);
	}
}

void line2(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	bool steep = false;
	//如果x的宽度小于y的宽度，说明是陡峭的
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	for (int x = x0; x < x1; x++)
	{
		float t = (x - x0) / (float)(x1 - x0);
		float y = y0 * (1. - t) + y1 * t;
		if (steep)
		{
			image.set(y, x, color);
		}else
		{
			image.set(x, y, color);
		}
	}
}

void line3(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	bool step = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		step = true;
	}
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror = abs(dy / dx);
	float error = 0;

	int y = y0;
	for (int x = x0; x < x1; x++)
	{
		if (step)
		{
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}

		error += derror;
		if (error > .5)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= 1;
		}
	}
}

void lineFinal(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	bool step = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		step = true;
	}
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror2 = abs(dy)*2;
	float error2 = 0;

	int y = y0;
	for (int x = x0; x < x1; x++)
	{
		if (step)
		{
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}

		error2 += derror2;
		if (error2 > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx*2;
		}
	}
}