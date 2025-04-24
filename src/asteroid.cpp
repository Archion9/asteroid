#include "asteroid.hpp"


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


