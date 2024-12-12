//created by ª∆‘Û‘¥&≈·ÀºÁ˘
#include"character.h"

void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer);

int main()
{
	initgraph(640, 480);
	CHARACTER rabbit;
	rabbit.img = newimage();
	rabbit.state = RUN;
	rabbit.frame = 1;
	PIMAGE background = newimage();
	PIMAGE buffer = newimage(640, 480);
	getimage(background, "../../bit-adventure/assets/ROAD3.0.png");
	getimage(rabbit.img, "../../bit-adventure/assets/rabbit1.1.png");
	rabbit.height = 50;
	refresh(rabbit, background, buffer);

	while (1)
	{
		action(&rabbit);
		if (keyDetect(&rabbit, 2))
		{
			delimage(rabbit.img);
			delimage(background);
			closegraph();
			break;
		}
		refresh(rabbit, background, buffer);
		rabbit.frame++;
		delay_ms(50);
	}
	closegraph();
}

void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbit.img, rabbit.x, Y(rabbit), BLACK);
	putimage(buffer, 0, 0, 640 - SPEED, 480, background, SPEED, 0);
	putimage(buffer, 640 - SPEED, 0, SPEED, 480, background, 0, 0);
	putimage(background, 0, 0, buffer);
}