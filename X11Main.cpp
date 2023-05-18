// basic X11 window
#include<iostream>

//X11 for linux, should work on most
// arm based linux machines as well?
#if defined(__linux__)
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
    #include <unistd.h>
    #include <sys/mman.h>
#endif

#include <assert.h>
#include<stdint.h>

typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;

// .h files
#include "math.h"
#include "memory.cpp"
#include "interactables.h"

// .cpp files
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
    uint32  FPS = 30;
    
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
        
    int32 x = 20;
    int32 y = 20;
        
    uint32 lastRepaint = getTimeInMicroseconds();

    clickable button01 = {};
    button01.colour = red;
    button01.width = 40;
    button01.height = 20;
    button01.x = 80;
    button01.y = 80;
    
        while(running) {		
        /* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/

        //TODO: see if I can get to draw everyframe sucessfully with send event
        //XClearArea(dis,win,0,0,windowWidth,windowHeight,false);
        XSetForeground(dis,gc,0);
        XFillRectangle(dis,backBuffer,gc,0,0,windowWidth,windowHeight);
        
        while(XPending(dis))
        {
            //make sure all events are handled.
            XNextEvent(dis, &event);
            
            //TODO: is the expose event even relivant anymore?
            if (event.type==Expose && event.xexpose.count==0)
            {
                //printf("Expose Event!\n");
            }
            
            // if window resize
             if(event.type == ConfigureNotify)
            {
                if(windowWidth != event.xconfigure.width)
                {
                    windowWidth = event.xconfigure.width;
                }
                
                if(windowHeight != event.xconfigure.height)
                {
                    windowHeight = event.xconfigure.height;
                }
            }
            
            
            //TODO: only handles ascii keys for the time being
            if (event.type==KeyPress && XLookupString(&event.xkey,text,255,&key,0)==1) {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
                printf("keycode of pressed key: %x\n",event.xkey.keycode);
                
                if (text[0]=='q') 
                {
                    printf("q key pressed!\n");
                }
                
                if(event.xkey.keycode == 0x09) // escape Key
                {
                    printf("Escape key pressed, closing window!\n");
                    CloseX(dis,win,gc);
                }
                
                printf("You pressed the %c key!\n",text[0]);
            }
            
            if (event.type==ButtonPress || event.type==ButtonRelease) {
                
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
                
                
                if(checkCollision(button01.x,button01.y,button01.width,button01.height,mousePos))
                {
                    printf("We got a collision back!\n");
                }
            
            }

            // if X clicked on window
            if (event.xclient.data.l[0] == wmDeleteMessage)
            {
                running = false;
            }
        }
        
        uint32 end = getTimeInMicroseconds();
        
        //Drawing
		XSetForeground(dis,gc,white);
		XDrawString(dis,backBuffer,gc,50,50,"hello",strlen("hello"));
		
		XSetForeground(dis,gc,blue);
        XFillRectangle(dis,backBuffer,gc,x,y,20,20);
        
        DrawInteractable(&button01,dis,gc,backBuffer);
        
        if(x + 20 < windowWidth)
        {
            x += 2;
        }
		
		lastRepaint = getTimeInMicroseconds();
        // see if this works on tinkerboard
        
		XSync(dis,true);
        XCopyArea(dis,backBuffer,win,gc,0,0,windowWidth,windowHeight,0,0);
        
		//TODO: need a better way, measure how long the frame took and wait the extra milliseconds if it was fast.    
        usleep(1000*1000 / FPS);
	}

	
	//clearup window stuff
    CloseX(dis,win,gc);
    
    
    return 0;
}
