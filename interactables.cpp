
inline static bool checkCollision(int x, int y, int width, int height, vec2i hitPoint)
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
