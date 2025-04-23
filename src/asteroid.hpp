#include "raymath.h"
#include "raylib.h"
#include "bullet.hpp"

#include <iostream>

#include <vector>

#ifndef ASTEROID_H
#define ASTEROID_H

//On the Asteroid class you can chain the setter functions to be convenient to use
class Asteroid
{

private:
    Vector2 center; //Circle's center point 
    float direction; //Direction that is supposed to be between 0 and 360 degree
    float speed; //Speed (pixel/second)
    float radius; //Circle's radius

    int split;
public:
    // Asteroid(Vector2 center, float direction, float radius); //Constructor
    Asteroid(Vector2 center, float direction, float speed, float radius); //Constructor
    //~Asteroid(); //Destructor (Compiler handling it)

    int Update(std::vector<Bullet> bullets); //Updating the physics of the bullet 
    
    Vector2 GetCenter();
    float GetSpeed();
    float GetDirection();
    float GetRadius();
    int GetSplit();

    Asteroid& SetCenter(Vector2 center);
    Asteroid& SetRadius(float radius);
    Asteroid& SetSpeed(float speed);
    Asteroid& SetDirection(float direction);
    Asteroid& SetSplit(int split);
    
    
};

/*Asteroid::Asteroid(Vector2 center, float direction, float radius) 
{
    this->center = center;
    this->direction = direction;
    this->radius = radius;
    this->speed = 100.0f; //default speed
}*/
Asteroid::Asteroid(Vector2 center, float direction, float speed, float radius) 
{
    this->center = center;
    this->direction = direction;
    this->radius = radius;
    this->speed = speed;
    this->split = 1;
}

int Asteroid::Update(std::vector<Bullet> bullets){

    
    for (size_t i = 0; i < bullets.size(); i++)
    {
        if(CheckCollisionCircleRec(this->center, this->radius, {bullets[i].pos.x, bullets[i].pos.y, bullets[i].size.x, bullets[i].size.y})){
            return i;
        }
    }
    
    // Getting the direction vector and scaling it with a speed and deltatime
    this->SetCenter(this->center +
        Vector2Scale( { sinf(this->direction * DEG2RAD),
            -cosf(this->direction * DEG2RAD) },
        this->speed * GetFrameTime()))
    .SetCenter( { Wrap(this->center.x, 0, GetScreenWidth()),
        Wrap(this->center.y, 0, GetScreenHeight()) } );
    return -1;
}

Vector2 Asteroid::GetCenter(){
    return this->center;
}

float Asteroid::GetDirection(){
    return this->direction;
}

float Asteroid::GetSpeed(){
    return this->speed;
}

float Asteroid::GetRadius(){
    return this->radius;
}
int Asteroid::GetSplit(){
    return this->split;
}


Asteroid& Asteroid::SetCenter(Vector2 center){
    this->center = center;
    return *this;
}
Asteroid& Asteroid::SetRadius(float radius){
    this->radius = radius;
    return *this;
}
Asteroid& Asteroid::SetDirection(float direction){
    this->direction = direction;
    return *this;
}
Asteroid& Asteroid::SetSpeed(float speed){
    this->speed = speed;
    return *this;
}
Asteroid& Asteroid::SetSplit(int split){
    this->split = split;
    return *this;
}

class AsteroidManager
{
private:
    std::vector<Asteroid> manager;
    int maxSplit = 3;
public:
    AsteroidManager(Vector2 center, float direction, float speed, float radius);
    //~AsteroidManager();
    int Update(std::vector<Bullet> bullets);
    void Draw();
};

AsteroidManager::AsteroidManager(Vector2 center, float direction, float speed, float radius)
{ 
    manager.push_back({center, direction, speed, radius});
}

int AsteroidManager::Update(std::vector<Bullet> bullets){

    for (size_t i = 0; i < manager.size(); i++)
    {
        int collision = manager[i].Update(bullets);
        if(collision >= 0){

            if(manager[i].GetSplit() < maxSplit){   
                manager.push_back({ manager[i].GetCenter(), manager[i].GetDirection() - 120.0f, manager[i].GetSpeed(), manager[i].GetRadius() * 0.5f });
                manager.back().SetSplit(manager[i].GetSplit()+1);
                manager.push_back({ manager[i].GetCenter(), manager[i].GetDirection() + 120.0f, manager[i].GetSpeed(), manager[i].GetRadius() * 0.5f });
                manager.back().SetSplit(manager[i].GetSplit()+1);
            }

            std::swap(manager[i], manager.back());
            manager.pop_back();
            return collision;
        }
    }
    return -1;
}

void AsteroidManager::Draw(){
    for (size_t i = 0; i < manager.size(); i++)
    {
        DrawCircleLinesV(manager[i].GetCenter(), manager[i].GetRadius(), RED);
    }
}

#endif