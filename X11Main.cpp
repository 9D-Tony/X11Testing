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
#include "math.h"

#include "x11window.cpp"
#include "interactables.cpp"




long getTimeInMicroseconds() 
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{
    
    uint32_t  FPS = 30;
	
    int windowWidth = 800; 
    int windowHeight = 600;
    vec2i mousePos = {};
    int testTimer = 0;
    
    SetupSimpleWindow("Testing X11",windowWidth,windowHeight);
    
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
        //XClearArea(dis,win,0,0,windowWidth,windowHeight,false);
        XSetForeground(dis,gc,0);
        XFillRectangle(dis,backBuffer,gc,0,0,windowWidth,windowHeight);
        
        //try sending event everyframe.
        XSendEvent(dis,win,false,ExposureMask,&ev);
        
        while(XPending(dis))
        {
            XNextEvent(dis, &event);
            
            if (event.type==Expose && event.xexpose.count==0) {
			//printf("Exposed window, clearing!\n")
                
            }
		
        if (event.type==KeyPress && XLookupString(&event.xkey,text,255,&key,0)==1) {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
			if (text[0]=='q') {
				printf("Closing Window!\n");
				CloseX(dis,win,gc);
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
            
            mousePos.x = event.xbutton.x;
            mousePos.y = event.xbutton.y;
            //check if mouse click was in a button
            
            
            if(checkCollision(x,y,20,20,mousePos))
            {
                printf("We got a collision back!\n");
                
            }
            
            }

            if (event.xclient.data.l[0] == wmDeleteMessage)
            {
                running = false;
            }
            
        }
        
        unsigned long end = getTimeInMicroseconds();
		XSetForeground(dis,gc,white);
		XDrawString(dis,backBuffer,gc,50,50,"hello",strlen("hello"));
		
		XSetForeground(dis,gc,blue);
        //XDrawRectangle(dis,win,gc,x,y,20,20);
        XFillRectangle(dis,backBuffer,gc,x,y,20,20);
        
        testTimer++;
        if(testTimer > 1)
        {
            x++;
            testTimer = 0;
        }
		
		lastRepaint = getTimeInMicroseconds();
        // see if this works on tinkerboard
        
		XSync(dis,true);
        XCopyArea(dis,backBuffer,win,gc,0,0,windowWidth,windowHeight,0,0);
		//TODO: need a better way    
        usleep(1000*1000 / FPS);
	}

	//clearup window stuff
    CloseX(dis,win,gc);
    
    
    return 0;
}
