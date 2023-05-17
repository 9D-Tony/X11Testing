
inline bool checkCollision(int32 x, int32 y, int32 width, int32 height, vec2i hitPoint)
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


void DrawInteractables()
{
    
    
}
