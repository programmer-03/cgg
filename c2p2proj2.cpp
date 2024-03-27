#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>


void drawEmoji();
void reflectEmoji();
void translateEmoji(int dx, int dy);
void scaleEmoji(float scaleFactor);
void multiplyMatrix(float mat1[][3], float mat2[][3], float result[][3]);

void scanFill(int x, int y, int fc, int bc);
void flood(int x, int y, int newc, int old);

int main() {
    int choice;
    int gd = DETECT, gm;

    initgraph(&gd, &gm, (char*)"C:/TURBOC3/BGI");
    line(325, 0, 325, 500);
    line(0, 235, 650, 235);

    drawEmoji();

    while (1) {
        printf("Menu:\n");
        printf("1. Reflect Emoji\n");
        printf("2. Translate Emoji\n");
        printf("3. Scale Emoji\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            reflectEmoji();
            break;
        case 2:
            int dx, dy;
            printf("Enter translation factors (dx dy): ");
            scanf("%d %d", &dx, &dy);
            translateEmoji(dx, dy);
            break;
        case 3:
            float scaleFactor;
            printf("Enter scale factor: ");
            scanf("%f", &scaleFactor);
            scaleEmoji(scaleFactor);
            break;
        default:
            printf("Invalid choice!\n");
        }
    }

    getch();
    closegraph();
    return 0;
}

void drawEmoji() {
    rectangle(45, 210, 290, 10);
    scanFill(50, 15, RED, WHITE);

    circle(160, 120, 40);
    circle(145, 115, 5);
    circle(177, 115, 5);
    arc(160, 118, 230, 297, 22);
    line(145, 135, 145, 137);
    line(170, 136, 170, 140);
    arc(160, 121, 230, 297, 22);
    line(177, 125, 171, 140);
    line(177, 125, 181, 140);
    arc(176, 139, 200, 355, 5);

    flood(160, 120, 14, 0);
    flood(175, 135, 3, 0);
}


void reflectEmoji() {

    int maxX = getmaxx();
    for (int x = 0; x <= maxX / 2; x++) {
        for (int y = 0; y <= getmaxy(); y++) {
            putpixel(maxX - x, y, getpixel(x, y));
        }
    }
}


void translateEmoji(int dx, int dy) {
    int maxX = getmaxx();
    int maxY = getmaxy();
    for (int x = 0; x <= maxX / 2; x++) {
        for (int y = 0; y <= maxY; y++) {
            putpixel(x + dx, y + dy, getpixel(x, y));
        }
    }
}


void scaleEmoji(float scaleFactor) {
    int maxX = getmaxx();
    int maxY = getmaxy();
    for (int x = 0; x <= maxX / 2; x++) {
        for (int y = 0; y <= maxY; y++) {
            putpixel(x * scaleFactor, y * scaleFactor, getpixel(x, y));
        }
    }
}


void flood(int x, int y, int newc, int old) {
    if (getpixel(x, y) == old) {
        putpixel(x, y, newc);
        flood(x + 1, y, newc, old);
        flood(x - 1, y, newc, old);
        flood(x, y + 1, newc, old);
        flood(x, y - 1, newc, old);
    }
}

void scanFill(int x, int y, int fc, int bc) {
    if (getpixel(x, y) != bc) return; 
    int currentX = x;
    while (getpixel(currentX, y) == bc) {
        putpixel(currentX, y, fc);
        currentX++;
    }
    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            scanFill(x + dx, y + dy, fc, bc);
        }
    }
}
