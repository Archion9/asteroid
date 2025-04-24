#ifndef BULLET_H
#define BULLET_H
#include "include.hpp"

struct Bullet
{
    Vector2 pos;
    Vector2 dir;
    Vector2 size = { 5.0f, 5.0f };
};

#endif