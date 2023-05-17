#ifndef INTERACTABLES_H
#define INTERACTABLES_H

enum clickType
{
    BUTTON,
    DRAG,
    CLICK
};

struct clickable
{
    clickType type;
    uint32 colour;
    int32 x;
    int32 y;
    int32 width;
    int32 height;
};

inline bool checkCollision(int32 x, int32 y, int32 width, int32 height, vec2i hitPoint);

#endif
