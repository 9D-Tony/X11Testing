
Display *dis;
int screen;
Window win;
GC gc;
XFontStruct* myFont;
unsigned long black,white, red, blue;

unsigned long RGB(int r, int g, int b)
{
	return b + (g<<8) + (r <<16);
}

static  void SetupSimpleWindow(const char* titleName, int windowWidth, int windowHeight)
{
    
    dis = XOpenDisplay((char *)0);
   	screen = DefaultScreen(dis);
    
	black = BlackPixel(dis,screen),	/* get color black */
	white = WhitePixel(dis, screen);  /* get color white */
    
	red = RGB(255,0,0);
	blue = RGB(0,0,255);
    
    win = XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	windowWidth, windowHeight, 0, white, black);

	XSetStandardProperties(dis,win,titleName,"HI!",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
    
    /* create the Graphics Context */
    gc = XCreateGC(dis, win, 0,0);  
    
    XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
    
    /* clear the window and bring it on top of the other windows */
	XClearWindow(dis, win);
    
	XMapRaised(dis, win);
}

static void CloseX(Display* dis, Window win, GC gc)
{
    XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(0);	
}
