#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "SDL.h"

// Feat: add enum to differentiate between 4 obstacles in the game
enum ObstacleNumber{
    NoObstacle=0,
    Obstacle_1,
    Obstacle_2,
    Obstacle_3,
    Obstacle_4
};

// Feat: add class Obstacle to encapsulate the functionality of adding obstacles in case of difficult game mode
class Obstacle{

public:
    // Feat: constructor 
    Obstacle(int gridWidth, int gridHeight);
    // Feat: destructor    
    ~Obstacle(){};
    // Feat: get the obstacle body points
    std::vector<SDL_Point> GetObstacleBody() const;
    // Feat: getter/setter to obstacles count private member
    int  GetObstacleCount();
    void SetObstacleCount(const int obstacleCount);
    // Feat: add an obstacle
    void CreateObstacle();
    // Feat: Remove the obstacles body and reset the obstacles count
    void RemoveObstacle();
    // Feat: check if the cell is occupied by an obstacle
    bool ObstacleCell(int x, int y);
    static const int MAX_OBSTACLE_COUNT{Obstacle_4};

private:
    // Feat: 1D vector of obstacle body grid points 
    std::vector<SDL_Point> _obstacleBody;
    int _gridWidth;
    int _gridHeight;
    // Feat: number of obstacles added
    int _obstacleCount{NoObstacle};
    // Feat: obstacle body is of length 4 cells
    const int _ObstacleLength{4};
    // Feat: 2D vector that will hold the positions of the 4 obstacles on the grid
    std::vector<std::vector<SDL_Point>> initialObstaclePoints;
};
#endif /*OBSTACLE_H*/