#ifndef INTERACTABLES_H
#define INTERACTABLES_H

enum clickType
{
    BUTTON,
    DRAG,
    FOCUS
};

union boolType
{
    bool clicked;
    bool focused;
    bool dragged;
};

struct Clickable
{
    clickType type;
    boolType clickBoolType;
    uint32 color;
    int32 x;
    int32 y;
    int32 width;
    int32 height;
};

inline bool CollisionBasic(int32 x, int32 y, int32 width, int32 height, vec2i hitPoint);

inline bool ClickableCollision(Clickable* button, vec2i hitPoint);

void DrawRect(Clickable* clickObj, Display* dis, GC gc, Pixmap backBuffer);

void DrawDragger(Clickable* clickObj, Display* dis, GC gc, Pixmap backBuffer);

void DrawTextField(Clickable* clickObj, Display* dis, GC gc, Pixmap backBuffer);

#endif
