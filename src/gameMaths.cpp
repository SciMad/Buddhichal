#include "../header/gameMaths.h"

int pos(int x, int y){
	if (x>=0 && x<=7 && y<=7 && y>=0)   return (y*8+x);	else return 99;
}
int x(int position){
	if (position<0 && position>63) return 99;
	//if ((position+1)%8==0) return 8; else return (position+1)%8; 			//For 1,1 based system
	if ((position+1)%8==0) return 8-1; else return ((position+1)%8)-1;		//For 0,0 based system
}
int y(int position){
	if (position<0 && position>63) return 99;
	//return (position/8)+1;		//For 1,1 based grid
	return (position/8);			//For 0,0 based grid
}

vector2d::vector2d(float a, float b){
    this->x = a;
    this->y =b;
}

vector3d::vector3d(float a, float b, float c){
    this->x = a;
    this->y = b;
    this->z = c;
}
