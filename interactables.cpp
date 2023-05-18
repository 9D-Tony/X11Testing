
inline bool CollisionBasic(int32 x, int32 y, int32 width, int32 height, vec2i hitPoint)
{
    if(hitPoint.x > x &&
        hitPoint.x < (x + width) &&
        hitPoint.y > y &&
        hitPoint.y < y + height
    )
    {
        printf("Point Hit! at: %d:%d \n",hitPoint.x,hitPoint.y);
        return true;

        
    }
    
        return false;
}

inline bool ClickableCollision(Clickable* button, vec2i hitPoint)
{
    if(hitPoint.x > button->x &&
        hitPoint.x < (button->x + button->width) &&
        hitPoint.y > button->y &&
        hitPoint.y < button->y + button->height)
    {
        printf("Point Hit! at: %d:%d \n",hitPoint.x,hitPoint.y);
        return true;
        
    }
    
        return false;
}

void DrawRect(Clickable* clickObj, Display* dis, GC gc, Pixmap backBuffer)
{
    XSetForeground(dis,gc,clickObj->colour);
    
    XFillRectangle(dis,backBuffer,gc, clickObj->x,clickObj->y,clickObj->width,clickObj->height);
}

void DrawDragger(Clickable* clickObj, Display* dis, GC gc, Pixmap backBuffer)
{
    
     XSetForeground(dis,gc,clickObj->colour);
    
    XFillRectangle(dis,backBuffer,gc, clickObj->x,clickObj->y,clickObj->width,clickObj->height);
    
    XPoint points[3] = {};
    
    points[0].x = clickObj->x;
     points[0].y = clickObj->y + clickObj->height;
     
     points[1].x = clickObj->width;
    // points[1].y = clickObj->y + clickObj->height;
     
     points[2].x -= clickObj->width / 2;
    points[2].y = clickObj->height / 2;
    
    XFillPolygon(dis,backBuffer,gc,points,3,Complex, CoordModePrevious);
    
}
