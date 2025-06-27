#ifndef TYPES_H
#define TYPES_H
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct
{
	Display *display;
	Window root;
	Window window;
	XWindowAttributes window_attributes;
	XEvent event;
} WinManager;

typedef struct
{
	int x;
	int y;
} Point;

typedef struct
{
	int x;
	int y;
	unsigned int width;
	unsigned int height;
} Rectangle;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	char *color;
	int	len;
}Rgb;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int tolerance;
}Tolerance;

typedef struct
{
	Rgb color;
	int height;
	int width;
}Rgb_pattern;

#endif
