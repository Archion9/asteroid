#include "raylib.h"
#include "raymath.h"

#include "asteroid.h"
#include "bullet.h"

#include <vector>
#include <algorithm>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

inline float clamp_rotation(float degree) noexcept;
float clampToScreen(float value, float min, float max) noexcept;


int main()
{

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Asteroid"); 
    //DisableCursor();
    SetTargetFPS(60);

    Image spaceImage = LoadImage("./src/textures/ship.png");
    Texture2D spaceShip = LoadTextureFromImage(spaceImage);
    UnloadImage(spaceImage);
    Rectangle spaceShipRec = {
        0.0f, 0.0f,
        static_cast<float>(spaceShip.width), static_cast<float>(spaceShip.height)};

    Rectangle destRec = {
        static_cast<float>(SCREENWIDTH) * 0.5f, static_cast<float>(SCREENHEIGHT) * 0.5f,
        static_cast<float>(spaceShip.width), static_cast<float>(spaceShip.height)};
    
    Vector2 direction;
    Vector2 position;
    
    float acc = 5.0f; //acceleration
    float speed = 0.0f; //speed of the ship
    float maxSpeed = 250.0f; //max speed that the ship can make

    float rotation = 0.0f; //rotation angle of ship
    float rotationSpeed = 200.0f; //rotation speed of ship

    float deltaTime; //GetFrameTime()

    Vector2 bulletSize = {5.0f, 5.0f};
    std::vector<Bullet> bullets;
    float bulletSpeed = 500.0f;
    float bulletOffsetMul = 0.125f;
    int bulletCol;

    //Asteroids
    float asteroidSpeed = 100.0f;
    AsteroidManager asteroidManager = {{0.0f, 0.0f}, 200.0f, asteroidSpeed, 50.0f};
    
    //user experience
    int userPoint = 0;
    int userLives = 3;


    while (!WindowShouldClose())
    {
        
        deltaTime = GetFrameTime();
        //Make sure the ship stays on the screen 
        destRec.x = clampToScreen(destRec.x, 0, static_cast<float>(SCREENWIDTH));
        destRec.y = clampToScreen(destRec.y, 0, static_cast<float>(SCREENHEIGHT));

        bulletCol = asteroidManager.Update(bullets);

        // Logic
        //under construction
        /*if(IsKeyDown(KEY_LEFT_SHIFT)){
            acc = 25.0f;
            maxSpeed = 400.0f;
        }
        else{
            acc = 5.0f;
            maxSpeed = 250.0f;
        }*/
        if(bulletCol >= 0){
            ++userPoint;
            std::swap(bullets[bulletCol], bullets.back());
            bullets.pop_back();
        }
        //controls
        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
            rotation = clamp_rotation(rotation - rotationSpeed * deltaTime);
        }
        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
            rotation = clamp_rotation(rotation + rotationSpeed * deltaTime);
        }
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
            speed += speed <= maxSpeed ? acc : 0;
            direction = { sinf(rotation * DEG2RAD), -cosf(rotation * DEG2RAD) };
            position = Vector2Scale(direction, speed * deltaTime);
            destRec.x += position.x;
            destRec.y += position.y;
        }
        else{
            speed = speed > acc ? speed - acc : 0;
            direction = { sinf(rotation * DEG2RAD), -cosf(rotation * DEG2RAD) };
            position = Vector2Scale(direction, speed * deltaTime);
            destRec.x += position.x;
            destRec.y += position.y;
        }
        //shooting
        if(IsKeyPressed(KEY_SPACE)){

            Vector2 center = {
                destRec.x - destRec.width * bulletOffsetMul,
                destRec.y - destRec.height * bulletOffsetMul
            };

            //bullets.push_back({center, direction}); good
            bullets.emplace_back(Bullet{center, direction}); // good but faster?? lixt told me to
        }
        
        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        if (!(bullets.size() <= 0))
        {            
            for (size_t i = 0; i < bullets.size(); i++)
            {   
                position = Vector2Scale(bullets[i].dir, bulletSpeed * deltaTime);
                bullets[i].pos.x += position.x;
                bullets[i].pos.y += position.y;
                
                DrawRectangleV(bullets[i].pos, bulletSize, ORANGE);
                
                if(0 > bullets[i].pos.x ||
                    static_cast<float>(SCREENWIDTH) < bullets[i].pos.x ||
                    0 > bullets[i].pos.y ||
                    static_cast<float>(SCREENHEIGHT) < bullets[i].pos.y){
                        std::swap(bullets[i], bullets.back());
                        bullets.pop_back();
                    }
                }
            }
                
        DrawTexturePro(spaceShip, spaceShipRec, destRec,
            {static_cast<float>(spaceShip.width) * 0.5f,
            (static_cast<float>(spaceShip.height) * 0.5f)}, rotation, WHITE);

        asteroidManager.Draw();
        
        DrawText(TextFormat("Points: %d",userPoint), 10, 40, 20, GREEN);
        DrawFPS(10,10);

        EndDrawing();
    }

    UnloadTexture(spaceShip);
    CloseWindow();

    return 0;
}

//Makes the ship to stay inside and goes to the other side on the screen
float clampToScreen(float value, float min, float max) noexcept {
    if(value < min)
        return value + max;
    if(value > max)
        return fmodf(value + min, max) - min;
    return value;
}

//Getting a degree and force it into an interval between 0 and 360
inline float clamp_rotation(float degree) noexcept{
    return fmodf(degree, 360); //this doesnt lose floating point data
}