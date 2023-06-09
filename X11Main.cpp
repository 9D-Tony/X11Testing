

// basic X11 window
#include<iostream>

//X11 for linux, work on linux arm machines?
#if defined(__linux__)
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
    #include <unistd.h>
    #include <sys/mman.h>
#endif

//compiler definition for arm, needed if doing any SIMD or
// arm thread work.
#if defined(__arm__)
    #define COMPILER "ARM\n"
#else
    #define COMPILER "x86\n"
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
    printf(COMPILER);
    
    int windowWidth = 800; 
    int windowHeight = 600;
    vec2i mousePos = {};
    int testTimer = 0;
    int resizeTimer = 0;
    int windowX, windowY;
    bool windowChange = false;
    
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
    bool mouseHeldDown = false;
        
    int32 x = 20;
    int32 y = 20;
        
    uint32 lastRepaint = getTimeInMicroseconds();

    Clickable button01 = {};
    button01.type = BUTTON;
     button01.clickBoolType.clicked = false;
    button01.color = red;
    button01.width = 40;
    button01.height = 20;
    button01.x = 60;
    button01.y = 80;
    
    Clickable dragger01 = {};
    dragger01.type = DRAG;
    dragger01.clickBoolType.dragged = false;
    dragger01.color = RGB(134,135,134);
    dragger01.width = 10;
    dragger01.height = 10;
    dragger01.x = 120;
    dragger01.y = 80;
    
    Clickable textField = {};
    textField.type = FOCUS;
    textField.clickBoolType.focused = false;
    textField.color = RGB(134,135,134);
    textField.width = 140;
    textField.height = 35;
    textField.x = 140;
    textField.y = 120;
    
        while(running) {		
        /* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/

        //background clear color
        XSetForeground(dis,gc,0);
        
        XFillRectangle(dis,backBuffer,gc,0,0,windowWidth,windowHeight);
        
        while(XPending(dis))
        {
            //make sure all events are handled.
            XNextEvent(dis, &event);
            
            //TODO: is the expose event even relivant anymore?
            if (event.type==Expose && event.xexpose.count==0)
            {
                printf("Expose Event!\n");
            }
            
            // Window resize
             if(event.type == ConfigureNotify)
            {
                
                if((windowHeight != event.xconfigure.height || windowWidth != event.xconfigure.width) 
                    && windowX == event.xconfigure.x && windowY == event.xconfigure.y)
                {
                    
                    windowWidth = event.xconfigure.width;
                    windowHeight = event.xconfigure.height;
                    windowChange = true;
                    
                }else
                {
                    windowX = event.xconfigure.x;
                    windowY = event.xconfigure.y;
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
            
            if (event.type==ButtonPress) {
                
            /* tell where the mouse Button was Pressed */
                printf("You pressed a button at (%i,%i)\n",
                event.xbutton.x,event.xbutton.y);
                
                mousePos.x = event.xbutton.x;
                mousePos.y = event.xbutton.y;
                
                // mouse button events:
                // button 1 left mouse
                // button 2 middle mouse
                // button 3 right mouse
                // button 4 scroll up mouse
                // button 5 scroll down mouse
                if(event.xbutton.button == Button1)
                {
                    mouseHeldDown = true;
                    //check if mouse click was in a button
                    if(CollisionBasic(x,y,20,20,mousePos))
                    {
                        printf("We got a collision back!\n");
                    }
                    
                    if(ClickableCollision(&button01,mousePos))
                    {
                        printf("We got a collision back!\n");
                        x = 0;
                    }
                    
                    if(ClickableCollision(&dragger01,mousePos))
                    {
                        printf("We got a collision back!\n");
                        x = 0;
                    }
                }
            }
            
             if (event.type==ButtonRelease)
             {
                 
                 // TODO: find out why release doesn't always fire.
                 
                 mousePos.x = event.xbutton.x;
                mousePos.y = event.xbutton.y;
                if(event.xbutton.button == Button1)
                {
                    mouseHeldDown = false;
                }
            }

            // if X clicked on window
            if (event.xclient.data.l[0] == wmDeleteMessage)
            {
                running = false;
            }
        }
        
        if(windowChange)
        {
            //if window changed recreate backbuffer  
            ResizeBackbuffer(windowWidth,windowHeight);
            windowChange = false;
        }
        
        uint32 end = getTimeInMicroseconds();
        
        Window child, root;
        int win_x, win_y, root_x, root_y = 0;
        uint32 mask = 0;
        
        XQueryPointer(dis,win,&child,&root,&win_x,&win_y,&root_x,&root_y,&mask);
        
        mousePos.x = root_x;
        mousePos.y = root_y;
        
         if(mouseHeldDown && CollisionBasic(x,y,20,20,mousePos))
        {
            x = root_x;
        }
        
        if(mouseHeldDown && ClickableCollision(&textField,mousePos) && textField.type == FOCUS)
        {
            printf("text field hit\n");
            textField.clickBoolType.focused = true;
        }
        
         if(x + 20 <= windowWidth)
        {
            x += 1;
        }
        
        //Drawing
		XSetForeground(dis,gc,white);
		XDrawString(dis,backBuffer,gc,50,50,"hello",strlen("hello"));
		
		XSetForeground(dis,gc,blue);
        XFillRectangle(dis,backBuffer,gc,x,y,20,20);
        
        DrawRect(&button01,dis,gc,backBuffer);
        DrawDragger(&dragger01,dis,gc,backBuffer);
        DrawTextField(&textField,dis,gc,backBuffer);
		
		lastRepaint = getTimeInMicroseconds();
        
		XSync(dis,false);
        
        //backbuffer
        XCopyArea(dis,backBuffer,win,gc,0,0,windowWidth,windowHeight,0,0);
        
		//TODO: need a better way, measure how long the frame took and wait the extra milliseconds if it was fast.    
        usleep(1000*1000 / FPS);
	}

	
	//clearup window stuff
    CloseX(dis,win,gc);
    
    
    return 0;
}
