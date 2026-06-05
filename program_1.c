#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WIDTH 80
#define MAX_HEIGHT 25
#define MAX_OBJECTS 50

typedef enum {
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} ShapeType;

typedef struct {
    int id;
    ShapeType type;
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int radius;
    char stroke;
    char fill;
} Object;

static char canvas[MAX_HEIGHT][MAX_WIDTH];
static Object objects[MAX_OBJECTS];
static int object_count = 0;

void init_canvas(void) {
    for (int y = 0; y < MAX_HEIGHT; ++y) {
        for (int x = 0; x < MAX_WIDTH; ++x) {
            canvas[y][x] = ' ';
        }
    }
}

void display_canvas(void) {
    printf("\n");
    for (int x = 0; x < MAX_WIDTH + 2; ++x) putchar('-');
    putchar('\n');
    for (int y = 0; y < MAX_HEIGHT; ++y) {
        putchar('|');
        for (int x = 0; x < MAX_WIDTH; ++x) {
            putchar(canvas[y][x]);
        }
        putchar('|');
        putchar('\n');
    }
    for (int x = 0; x < MAX_WIDTH + 2; ++x) putchar('-');
    putchar('\n');
}

void set_pixel(int x, int y, char ch) {
    if (x >= 0 && x < MAX_WIDTH && y >= 0 && y < MAX_HEIGHT) {
        canvas[y][x] = ch;
    }
}

void draw_line(const Object *obj) {
    int x0 = obj->x1;
    int y0 = obj->y1;
    int x1 = obj->x2;
    int y1 = obj->y2;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        set_pixel(x0, y0, obj->stroke);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
