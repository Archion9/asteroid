#include "raymath.h"

#ifndef BULLET_H
#define BULLET_H

struct Bullet
{
    Vector2 pos;
    Vector2 dir;
    Vector2 size = { 5.0f, 5.0f };
};

#endif