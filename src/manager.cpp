#include "asteroid.hpp"

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
