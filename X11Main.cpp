// basic X11 window
#include<iostream>

//X11 for linux, should work on most
// arm based linux machines as well?
#if defined(__linux__)
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
#endif

#include<stdint.h>

Display *dis;
int screen;
Window win;
GC gc;
XFontStruct* myFont;

void close_x() {
/* it is good programming practice to return system resources to the 
   system...
*/
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(0);				
}

unsigned long RGB(int r, int g, int b)
{
	return b + (g<<8) + (r <<16);
}

long getTimeInMicroseconds() 
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{
    unsigned long black,white, red, blue;
    uint32_t  FPS = 30;

    dis = XOpenDisplay((char *)0);
   	screen = DefaultScreen(dis);
	black = BlackPixel(dis,screen),	/* get color black */
	white = WhitePixel(dis, screen);  /* get color white */
	red = RGB(255,0,0);
	blue = RGB(0,0,255);
	
    int windowWidth = 800; 
    int windowHeight = 600;
    win = XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	windowWidth, windowHeight, 0, white, black);

	XSetStandardProperties(dis,win,"My Window","HI!",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

	/* create the Graphics Context */
    gc = XCreateGC(dis, win, 0,0);        

	/* here is another routine to set the foreground and background
	   colors _currently_ in use in the window.
	*/
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);

	/* clear the window and bring it on top of the other windows */
	XClearWindow(dis, win);
    
     //XSetWindowBackgroundPixmap(dis,win,None);
    
	XMapRaised(dis, win);
	
	// TODO: seg faults here, maybe need to install custom fonts???.
	//myFont = XLoadQueryFont(dis, "-misc-fixed-medium-r-normal--9-90-75-75-c-60-iso10646-1");
	//XSetFont(dis, gc, myFont->fid);

    XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[255];		/* a char buffer for KeyPress Events */

	// have to set the wmDeleteMessage
	// don't know why this is so confusing on linux...
	Atom wmDeleteMessage = XInternAtom(dis, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dis, win, &wmDeleteMessage, 1);

	/* look for events forever... */
	bool running = true;
    
        XEvent ev;
        ev.xexpose.type = Expose;
        ev.xexpose.display = dis;
        ev.xexpose.window = win;
        ev.xexpose.x = 0;
        ev.xexpose.y - 0;
        ev.xexpose.width = 0;
        ev.xexpose.height =0;
        ev.xexpose.count  =0;
        
        int x = 20;
        int y = 20;
        
        unsigned long lastRepaint = getTimeInMicroseconds();

        while(running) {		
        /* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/

        //TODO: see if I can get to draw everyframe sucessfully with send event
        XClearArea(dis,win,0,0,windowWidth,windowHeight,false);
        
        //try sending event everyframe.
        XSendEvent(dis,win,false,ExposureMask,&ev);
		XNextEvent(dis, &event);
        
        unsigned long end = getTimeInMicroseconds();
        
		if (event.type==Expose && event.xexpose.count==0) {
		/* the window was exposed redraw it! */
			//printf("Exposed window, clearing!\n");

            
        }
		
        if (event.type==KeyPress &&
		    XLookupString(&event.xkey,text,255,&key,0)==1) {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
			if (text[0]=='q') {
				printf("Closing Window!\n");
				close_x();
			}

			if (text[0]=='s') {
				XClearWindow(dis,win);
				printf("The window has been cleared!\n");
			}

			printf("You pressed the %c key!\n",text[0]);
		}
		
		if (event.type==ButtonPress) {
		/* tell where the mouse Button was Pressed */
			printf("You pressed a button at (%i,%i)\n",
			event.xbutton.x,event.xbutton.y);
            
            //check if mouse click was in a button
            
            
            
		}

        if (event.xclient.data.l[0] == wmDeleteMessage)
		{
            running = false;
		}
		
		XSetForeground(dis,gc,blue);
        XDrawRectangle(dis,win,gc,x,y,20,20);
        XFillRectangle(dis,win,gc,x,y,20,20);
        x++;
		
		lastRepaint = getTimeInMicroseconds();
        // see if this works on tinkerboard
        
		XSync(dis,true); //at moment sync is disposing of all other messages, 
		//TODO: need a better way    
        usleep(1000*1000 / FPS);
	}

	//clearup window stuff
	close_x();
    
    
    return 0;
}
