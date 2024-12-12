//created by 黄泽源
#include <graphics.h>
#include "../dialog.h"

int main()
{
	initgraph(640, 480);
	PIMAGE bg = newimage();
	getimage(bg, "./assets/dorm.png");
	putimage(0, 0, bg);
	getch();

	//Call functions in modules below
	showDialog("1.txt");
	//Call functions in modules above

	getch();
	closegraph();
	return 0;
}
//Append space here to force re-compile                         
