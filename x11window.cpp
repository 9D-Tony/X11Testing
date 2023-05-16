
Display *dis;
int screen;
Window win;
GC gc;
XFontStruct* myFont;


void SetupWindow(Display* dis, Window win, GC gc, char* titleName)
{
    
    
}

void CloseX(Display* dis, Window win, GC gc)
{
    XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(0);	
}
