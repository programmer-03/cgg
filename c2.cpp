#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

void translate(int *x, int *y, int tx, int ty) {
    *x += tx;
    *y += ty;
}

void scaleEmoji(int *x, int *y, int *scale, int s) {
    *x+=155;
    *y+=155;
    *scale *= s;
}

void reflectEmoji(int *x, int *y, int axis, int maxX, int maxY) {
    if (axis == 1) {
	// Reflect along X-axis
	*y = maxY - *y;
    } else if (axis == 2) {
	// Reflect along Y-axis
	*x = maxX - *x;
    }
}

void rotateEmoji(int *x, int *y, int *angle) {
    float PI = 3.14;
    float rad = (*angle * PI) / 180.0;

    int rotatedX = *x * cos(rad) - *y * sin(rad);
    int rotatedY = *x * sin(rad) + *y * cos(rad);

    *x = rotatedX;
    *y = rotatedY;
}

void drawEmoji(int x, int y, int scale) {
    // Draw face
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    circle(x, y, 60 * scale);
    floodfill(x, y, YELLOW);

    // Draw right eyes
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    circle(x - 25 * scale, y - 15 * scale, 7 * scale); // left eye
    floodfill(x - 25 * scale, y - 15 * scale, BLACK);

    // Draw left eye
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    circle(x + 25 * scale, y - 15 * scale, 7 * scale); // left eye
    floodfill(x + 25 * scale, y - 15 * scale, BLACK);

    // Draw mouth (smile) as an arc
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 1, 3);
    arc(x + 5, y - 12 * scale, 230, 297, 38 * scale); // Drawing the smile as an arc
    
    
     setcolor(LIGHTCYAN);
    setlinestyle(SOLID_LINE, 1, 3);
    line(x + 25 * scale, y * scale, x + 20 * scale, y + 25 * scale);
    line(x + 26 * scale, y * scale, x + 22 * scale, y + 25 * scale);
    line(x + 26 * scale, y * scale, x + 25 * scale, y + 26 * scale);
    line(x + 26 * scale, y * scale, x + 28 * scale, y + 25 * scale);
    line(x + 26 * scale, y * scale, x + 31 * scale, y + 25 * scale);
    line(x + 26 * scale, y * scale, x + 31 * scale, y + 25 * scale);
    arc(x + 26, y + 25 * scale, 200, 355, 5 * scale); // Drawing the smile as an arc
	floodfill(x + 26 * scale, y + 23 * scale, LIGHTCYAN);
		
}





void shearEmoji(int *x, int *y, int shx, int shy, int pivotX, int pivotY) {
    int newX = (*x+50)+ shx * (*y - pivotY);
    int newY = (*y+50) + shy * (*x - pivotX);

    *x = newX;
    *y = newY;
}

void scanLineFill(int x1, int y1, int x2, int y2, int color) {
    int i, j;
    for (i = y1; i <= y2; i++) {
	for (j = x1; j <= x2; j++) {
	    putpixel(j, i, color);
	}
    }
}

int main() {
    int gd = DETECT, gm;
    int x = 155, y = 155, scale = 1;
    int tx, ty, s, shx, shy, angle;
    int choice, i, j;
    int maxX, maxY, axis;
    int rotated_x, rotated_y;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    setcolor(CYAN);
    maxX = getmaxx();
    maxY = getmaxy();
    setcolor(YELLOW);
    line(320, 1, 320, 470);
    line(1, 240, 640, 240);
    rectangle(80, 80, 230, 230);
   
    scanLineFill(80, 80, 230, 230, WHITE);
    drawEmoji(x, y, scale);

	while (1) {

    printf("Enter your choice:\n1. Translate\n2. Scale\n3. Reflect\n4. Shear\n5. Rotate\n6. Exit\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
	printf("Enter translation factors (tx, ty): ");
	scanf("%d%d", &tx, &ty);
	cleardevice();
	translate(&x, &y, tx, ty);
	scanLineFill(80+tx,80+ty,230+tx,230+ty,WHITE);
	rectangle(80 + tx, 80 + ty, 230 + tx, 230 + ty);
	drawEmoji(x, y, scale);


	setcolor(WHITE);
	line(320, 1, 320, 470);
	line(1, 240, 640, 240);
	break;
    case 2:
	printf("Enter scaling factor: ");
	scanf("%d", &s);
	cleardevice();
	scaleEmoji(&x, &y, &scale, s);
	
	scanLineFill(80*scale,80*scale,230*scale,230*scale,WHITE);
	rectangle(80*scale,80*scale,230*scale,230*scale);

	drawEmoji(x, y, scale);
	
	break;
    case 3:

	printf("About:\n1. X-axis\n2. Y-axis\n");
	scanf("%d", &axis);
	

	if (axis == 1) {
	   
	    rectangle(80, maxY - 230, 230, maxY - 80); // Draw reflected square
	    for (i = x - 80 * scale; i <= x + 80 * scale; i++) {
		for (j = y - 80 * scale; j <= y + 80 * scale; j++) {
		    putpixel(i, maxY - j, getpixel(i, j));
		}
	    }
	}
 
	  else if (axis == 2) {

	    rectangle(maxX - 230, 80, maxX - 80, 230); // Draw reflected square
	    for (i = x - 80 * scale; i <= x + 80 * scale; i++) {
		for (j = y - 80 * scale; j <= y + 80 * scale; j++) {
		    putpixel(maxX - i, j, getpixel(i, j));
		}
	    }
	} else {
	    printf("Invalid choice.");
	}
	break;
    case 4:
	printf("Enter shearing factors (shx, shy): ");
	scanf("%d%d", &shx, &shy);
	cleardevice();
	drawEmoji(1 * maxX / 4, maxY / 4, 1); 

	for (x = 0; x <= maxX; x++) {
	    for (y = 0; y <= maxY; y++) {
		int px = x, py = y;                               
		shearEmoji(&px, &py, shx, shy, maxX / 2, maxY / 2); 
		putpixel(px, py, getpixel(x, y));                 
	    }
	}
	setcolor(WHITE);
	line(320, 1, 320, 470);
	line(1, 240, 640, 240);

	break;
    case 5:
	printf("Enter rotation angle (in degrees): ");
	scanf("%d", &angle);
	cleardevice();
	
	for(i=80;i<=230;i++){
		for(j=80;j<=230;j++){
			rotated_x=155+(i-155)*cos(angle*M_PI/180)-(j-155)*sin(angle*M_PI/180);
			rotated_y=155+(i-155)*sin(angle*M_PI/180)+(j-155)*cos(angle*M_PI/180);
			putpixel(rotated_x,rotated_y,WHITE);
		}
	}
	drawEmoji(x,y,scale);
	
	setcolor(WHITE);
	line(320,1,320,470);
	line(1,240,640,240);

	break;
    case 6:
	exit(0);
    }
}
    getch();
    closegraph();
    return 0;
}
