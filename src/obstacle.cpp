#include "obstacle.h"
#include <iostream>

// Feat: Obstacle Class functions Definitions
// Feat: using initialization list in the constructor
Obstacle::Obstacle(int gridWidth, int gridHeight): _gridWidth(gridWidth), _gridHeight(gridHeight) {

    // initialize the initialobstaclepoints to 0,0
    std::vector<SDL_Point> p{{0,0},{0,0},{0,0},{0,0}};
    for(int i=0; i<_ObstacleLength+1 ; i++)
            initialObstaclePoints.push_back(p);

    // add the 4 obstacles body points in the following grid positions (upper middle, lower middle, left middle, right middle)
    for(int i=0; i<_ObstacleLength+1 ; i++)
    {
        initialObstaclePoints[Obstacle_1][i]= {((gridWidth-1)/2)+i,0};
        initialObstaclePoints[Obstacle_2][i]={((gridWidth-1)/2)+i,gridHeight-1};
        initialObstaclePoints[Obstacle_3][i]={0,((gridHeight-1)/2)+i};
        initialObstaclePoints[Obstacle_4][i]={gridWidth-1,((gridHeight-1)/2)+i};
    }}

// Feat: get the obstacle body points
std::vector<SDL_Point> Obstacle::GetObstacleBody() const{
    return _obstacleBody;
}

// Feat: getter/setter to obstacles count private member
int Obstacle::GetObstacleCount(){
    return _obstacleCount;
}


void Obstacle::SetObstacleCount(const int obstacleCount)
{
    _obstacleCount = obstacleCount;
}

// Feat: Add an obstacle to the obstacle body and increase the obstacle count
void Obstacle::CreateObstacle(){

    _obstacleCount++;

    switch (_obstacleCount)
    {
        case Obstacle_1:
            for(const SDL_Point &p : initialObstaclePoints[Obstacle_1])
            {
                _obstacleBody.push_back(p);
            }
            break;
        
        case Obstacle_2:
            for(const SDL_Point &p : initialObstaclePoints[Obstacle_2])
            {
                _obstacleBody.push_back(p);
            }
            break;

        case Obstacle_3:
            for(const SDL_Point &p : initialObstaclePoints[Obstacle_3])
            {
                _obstacleBody.push_back(p);
            }
            break;

        case Obstacle_4:
            for(const SDL_Point &p : initialObstaclePoints[Obstacle_4])
            {
                _obstacleBody.push_back(p);
            }
            break;
    
        default:
            break;
    }
}

// Feat: clear the obstacle body points to remove all obstacles
void Obstacle::RemoveObstacle(){
    _obstacleBody.clear();
    SetObstacleCount(NoObstacle);
}

// Feat: check if the cell is occupied by an obstacle
bool Obstacle::ObstacleCell(int x, int y)
{
    for(const SDL_Point &p : _obstacleBody)
    {
        if(p.x == x && p.y == y)
            return true;
    }
    return false;
}