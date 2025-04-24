#ifndef ASTEROID_H
#define ASTEROID_H

#include "include.hpp"

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



#endif