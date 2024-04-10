#include "Map.h"
#include <queue>
#include <stdio.h>

#define II std::pair<int, int>
#define mp(a, b) std::make_pair(a, b)
#define fi first
#define se second

int createdMap[33][36];
bool firstInit = true;

Map::Map() {
    if (firstInit) {
        std::ifstream file(mapFile);
        if (file) {
            for (int i = 0 ; i < MAP_HEIGHT ; ++i) {
                for (int j = 0 ; j < MAP_WIDTH ; ++j) {
                    file >> createdMap[i][j];
                }
            }
        }
    }

    for (int i = 0 ; i < MAP_HEIGHT ; ++i)
        for (int j = 0 ; j < MAP_WIDTH ; ++j)
            totalTile[i][j] = createdMap[i][j];
    trackingCross();
    findNearestCross();
    distCalc();
}

int Map::getID(int x, int y)
{
    return totalTile[x][y];
}

std::pair<int, int> Map::getNearestCross(int x, int y, int dir)
{
    return crossNearestTile[x][y][dir];
}

bool Map::isSatis(int x)
{
    return (x == 27 || x == 26 || x == 30);
}

bool Map::isWall(int x , int y) {
    if (mp(x , y) == mp(0 , 14) || mp(x , y) == mp(27 , 14)) return false;
    if (x < 1 || x > 26) return true;
    if (y < 1 || y > 29) return true;
    int tmp = totalTile[y][x];
    if (isSatis(tmp)) return false;
    else return true;
}

int Map::coinCollected(int x, int y)
{
    if (isSatis(totalTile[x][y]) && totalTile[x][y] != 30)
    {
        int ans = totalTile[x][y];
        totalTile[x][y] = 30;
        return ans;
    }
    return 0;
}

bool Map::isDirChange(int x, int y, int dir)
{
    return cross[x][y][dir];
}

void Map::trackingCross()
{
    memset(cross, false, sizeof cross);
    for (int nx = 0; nx < MAP_WIDTH; ++nx)
    {
        for (int ny = 0; ny < MAP_HEIGHT; ++ny)
        {
            if (isSatis(totalTile[ny][nx]))
            {
                if (ny - 1 >= 0 && isSatis(totalTile[ny - 1][nx]))
                    cross[ny][nx][UP] = true;
                if (ny + 1 <= 30 && isSatis(totalTile[ny + 1][nx]))
                    cross[ny][nx][DOWN] = true;
                if (nx - 1 >= 0 && isSatis(totalTile[ny][nx - 1]))
                    cross[ny][nx][LEFT] = true;
                if (nx + 1 <= 30 && isSatis(totalTile[ny][nx + 1]))
                    cross[ny][nx][RIGHT] = true;
            }
        }
    }
}

bool Map::isCross(int x, int y)
{
    int cnt = 0, cntDir = 0;
    for (int dir = 0; dir < 4; ++dir)
    {
        cnt += cross[y][x][dir];
        cntDir += ((cross[y][x][dir]) ? dir : 0);
    }
    if (cnt >= 3)
        return true;
    else if (cnt == 2)
        return !(cntDir % 2);
    else
        return false;
}

void Map::findNearestCross()
{
    // UP CROSS
    for (int nx = 0; nx < MAP_WIDTH; ++nx)
    {
        // border top
        crossNearestTile[0][nx][UP] = mp(-1, -1);
        for (int ny = 1; ny < MAP_HEIGHT; ++ny)
        {
            if (isWall(nx, ny))
                crossNearestTile[ny][nx][UP] = mp(-1, -1);
            else
            {
                if (crossNearestTile[ny - 1][nx][UP] != mp(-1, -1))
                    cross[ny][nx][UP] = cross[ny - 1][nx][UP];
                if (isCross(nx, ny - 1))
                    crossNearestTile[ny][nx][UP] = mp(nx, ny - 1);
            }
        }
    }
    // DOWN CROSS
    for (int nx = 0; nx < MAP_WIDTH; ++nx)
    {
        // border bottom
        crossNearestTile[MAP_HEIGHT - 1][nx][DOWN] = mp(-1, -1);
        for (int ny = MAP_HEIGHT - 2; ny >= 0; --ny)
        {
            if (isWall(nx, ny))
                crossNearestTile[ny][nx][DOWN] = mp(-1, -1);
            else
            {
                if (crossNearestTile[ny + 1][nx][DOWN] != mp(-1, -1))
                    cross[ny][nx][DOWN] = cross[ny + 1][nx][DOWN];
                if (isCross(nx, ny + 1))
                    crossNearestTile[ny][nx][DOWN] = mp(nx, ny + 1);
            }
        }
    }
    // LEFT CROSS
    for (int ny = 0; ny < MAP_HEIGHT; ++ny)
    {
        crossNearestTile[ny][0][LEFT] = mp(-1, -1);
        for (int nx = 1; nx < MAP_WIDTH; ++nx)
        {
            if (isWall(nx, ny))
                crossNearestTile[ny][nx][LEFT] = mp(-1, -1);
            else
            {
                if (crossNearestTile[ny][nx - 1][LEFT] != mp(-1, -1))
                    cross[ny][nx][LEFT] = cross[ny][nx - 1][LEFT];
                if (isCross(nx - 1, ny))
                    crossNearestTile[ny][nx][LEFT] = mp(nx - 1, ny);
            }
        }
    }
    // RIGHT CROSS
    for (int ny = 0; ny < MAP_HEIGHT; ++ny)
    {
        crossNearestTile[ny][0][RIGHT] = mp(-1, -1);
        for (int nx = MAP_WIDTH - 1; nx >= 0; --nx)
        {
            if (isWall(nx, ny))
                crossNearestTile[ny][nx][RIGHT] = mp(-1, -1);
            else
            {
                if (crossNearestTile[ny][nx + 1][RIGHT] != mp(-1, -1))
                    cross[ny][nx][RIGHT] = cross[ny][nx + 1][RIGHT];
                if (isCross(nx + 1, ny))
                    crossNearestTile[ny][nx][RIGHT] = mp(nx + 1, ny);
            }
        }
    }
}

void Map::distCalc()
{
    int Row[4] = {0, 0, -1, 1};
    int Col[4] = {1, -1, 0, 0};
    int distance[MAP_HEIGHT][MAP_WIDTH];
    bool visited[MAP_HEIGHT][MAP_WIDTH];
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            if (isWall(i, j))
                continue;
            if (mp(i, j) == mp(0, 14) || mp(i, j) == mp(27, 14))
                continue;
            for (int oDir = 0; oDir < 4; ++oDir)
            {
                int nx = i + Row[oDir];
                int ny = j + Col[oDir];
                if (isWall(nx, ny))
                    continue;
                memset(visited, false, sizeof visited);
                distance[ny][nx] = 0;
                visited[ny][nx] = true;
                std::queue<std::pair<std::pair<int, int>, int>> nodeQueue;
                nodeQueue.push(std::make_pair(std::make_pair(ny, nx), oDir));
                while (!nodeQueue.empty())
                {
                    int nextX = nodeQueue.front().fi.se;
                    int nextY = nodeQueue.front().fi.fi;
                    int currentDir = nodeQueue.front().se;
                    nodeQueue.pop();

                    if (mp(nextX, nextY) == mp(0, 14) || mp(nextX, nextY) == mp(27, 14))
                        continue;
                    for (int nextIdDir = 0; nextIdDir < 4; ++nextIdDir)
                    {
                        int a = nextX + Row[nextIdDir];
                        int b = nextY + Col[nextIdDir];
                        if ((oDir + nextIdDir) % 2 == 0 && oDir != nextIdDir)
                            continue;
                        if (isWall(a, b)) continue;
                        if (!visited[b][a]) {
                            visited[b][a] = true;
                            distance[b][a] = distance[nextY][nextX] + 1;
                            nodeQueue.push(std::make_pair(std::make_pair(b , a) , nextIdDir));
                        }
                    }
                }
                for (int i = 0 ; i < MAP_WIDTH ;  ++i){
                    for (int j = 0 ; j < MAP_HEIGHT ; ++j){
                        dist[ny][nx][j][i][oDir] = distance[j][i];
                    }
                }
            }
        }
    }
    // std::cout << "Render map successfully" << std::endl;
}
