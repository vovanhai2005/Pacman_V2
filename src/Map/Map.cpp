#include "Map.h"
#include <queue>

typedef std::pair<int, int> II;
#define mp(a , b) std::make_pair(a , b)
#define fi first
#define se second

bool firstInit = true;
int premanMap[31][28];
int color[31][28];

Map::Map() {
    if (firstInit) {
        std::ifstream file(mapFile);
        if (file) {
            for (int i = 0; i < MAP_HEIGHT; ++i) {
                for (int j = 0; j < MAP_WIDTH; ++j) {
                    file >> premanMap[i][j];
                    if (premanMap[i][j] > 31 || premanMap[i][j] < 0) {
                        Console->Status("Wrong Tile!");
                        return;
                    }
                }
            }
            Console->Status("Map read successfully!");
        }
        else Console->Status("Error reading file!");
    }

    for (int i = 0; i < MAP_HEIGHT; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
            totalTile[i][j] = premanMap[i][j];

    trackingCross();
    findNearestCross();
    distCalc();
}

int Map::getID(int x, int y) {
    return totalTile[y][x];
}

std::pair<int, int> Map::getNearestCross(int x, int y, int dir) {
    return crossNearestTile[y][x][dir];
}

bool Map::isWall(std::pair<int, int> tileID) {
    if (tileID == II(0, 14) || tileID == II(27, 14)) return false;
    if (tileID.first < 1 || tileID.first > 26) return true;
    if (tileID.second < 1 || tileID.second > 29) return true;
    return totalTile[tileID.second][tileID.first] != 26 && totalTile[tileID.second][tileID.first] != 30 && totalTile[tileID.second][tileID.first] != 27;
}

bool Map::isCross(int x, int y) {
    int cnt = 0;
    if (cross[y][x][UP]) ++cnt;
    if (cross[y][x][RIGHT]) ++cnt;
    if (cross[y][x][DOWN]) ++cnt;
    if (cross[y][x][LEFT]) ++cnt;
    if (cnt >= 3) return true;
    if (cnt == 2) {
        if (cross[y][x][UP] && cross[y][x][DOWN]) return false;
        if (cross[y][x][LEFT] && cross[y][x][RIGHT]) return false;
        return true;
    }
    return false;
}

bool Map::isDirChange(int x, int y, int newDir) {
    return cross[y][x][newDir];
}

bool Map::isWallBehind(std::pair<int, int> Cross, int newDir) {
    if (newDir == UP) Cross.second -= 1;
    else if (newDir == DOWN) Cross.second += 1;
    else if (newDir == RIGHT) Cross.first += 1;
    else Cross.first -= 1;
    return isWall(Cross);
}

void Map::trackingCross() {
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int dir = 0; dir < 4; ++dir) cross[y][x][dir] = false;

            if (totalTile[y][x] != 26 && totalTile[y][x] != 27 && totalTile[y][x] != 30) continue;

            if (y > 0  && (totalTile[y - 1][x] == 26 || totalTile[y - 1][x] == 27 || totalTile[y - 1][x] == 30)) cross[y][x][0] = true;
            if (y < 30 && (totalTile[y + 1][x] == 26 || totalTile[y + 1][x] == 27 || totalTile[y + 1][x] == 30)) cross[y][x][2] = true;
            if (x > 0  && (totalTile[y][x - 1] == 26 || totalTile[y][x - 1] == 27 || totalTile[y][x - 1] == 30)) cross[y][x][3] = true;
            if (x < 27 && (totalTile[y][x + 1] == 26 || totalTile[y][x + 1] == 27 || totalTile[y][x + 1] == 30)) cross[y][x][1] = true;
        }
    }
}

void Map::findNearestCross() {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        crossNearestTile[y][0][LEFT] = II(-1, -1);
        for (int x = 1; x < MAP_WIDTH; ++x) {
            crossNearestTile[y][x][LEFT] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (crossNearestTile[y][x - 1][LEFT] != II(-1, -1)) crossNearestTile[y][x][LEFT] = crossNearestTile[y][x - 1][LEFT];
                if (isCross(x - 1, y)) crossNearestTile[y][x][LEFT] = II(x - 1, y);
            }
        }

        crossNearestTile[y][MAP_WIDTH - 1][RIGHT] = II(-1, -1);
        for (int x = MAP_WIDTH - 2; x >= 0; --x) {
            crossNearestTile[y][x][RIGHT] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (crossNearestTile[y][x + 1][RIGHT] != II(-1, -1)) crossNearestTile[y][x][RIGHT] = crossNearestTile[y][x + 1][RIGHT];
                if (isCross(x + 1, y)) crossNearestTile[y][x][RIGHT] = II(x + 1, y);
            }
        }
    }

    for (int x = 0; x < MAP_WIDTH; ++x) {
        crossNearestTile[0][x][UP] = II(-1, -1);
        for (int y = 1; y < MAP_HEIGHT; ++y) {
            crossNearestTile[y][x][UP] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (crossNearestTile[y - 1][x][UP] != II(-1, -1)) crossNearestTile[y][x][UP] = crossNearestTile[y - 1][x][UP];
                if (isCross(x, y - 1)) crossNearestTile[y][x][UP] = II(x, y - 1);
            }
        }

        crossNearestTile[MAP_HEIGHT - 1][x][DOWN] = II(-1, -1);
        for (int y = MAP_HEIGHT - 2; y >= 0; --y) {
            crossNearestTile[y][x][DOWN] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (crossNearestTile[y + 1][x][DOWN] != II(-1, -1)) crossNearestTile[y][x][DOWN] = crossNearestTile[y + 1][x][DOWN];
                if (isCross(x, y + 1)) crossNearestTile[y][x][DOWN] = II(x, y + 1);
            }
        }
    }
}

void Map::distCalc() {
    int Row[4] = {0, 0, -1, 1};
    int Col[4] = {1, -1, 0, 0};
    int distance[MAP_HEIGHT][MAP_WIDTH];
    bool visited[MAP_HEIGHT][MAP_WIDTH];
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            if (isWall(mp(i , j))) continue;
            if (mp(i, j) == mp(0, 14) || mp(i, j) == mp(27, 14)) continue;
            for (int oDir = 0; oDir < 4; ++oDir)
            {
                int nx = i + Row[oDir];
                int ny = j + Col[oDir];
                if (isWall(mp(nx , ny))) continue;
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
                        if ((oDir + nextIdDir) % 2 == 0 && oDir != nextIdDir) continue;
                        if (isWall(mp(a, b))) continue;
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

int Map::coinCollected(int pacmanTileX , int pacmanTileY) {
    if (totalTile[pacmanTileY][pacmanTileX] == 26) {
        totalTile[pacmanTileY][pacmanTileX] = 30;
        return 26;
    }
    if (totalTile[pacmanTileY][pacmanTileX] == 27) {
        totalTile[pacmanTileY][pacmanTileX] = 30;
        return 27;
    }
    return 0;
}

int Map::getDist(std::pair<int, int> start, std::pair<int, int> end, int startDir) {
    if (isWall(end)) return (start.first - end.first) * (start.first - end.first) + (start.second - end.second) * (start.second - end.second);
    else {
        if (dist[start.second][start.first][end.se][end.first][startDir] == -1)
            return (start.first - end.first) * (start.first - end.first) + (start.second - end.second) * (start.second - end.second);
        else return dist[start.second][start.first][end.se][end.first][startDir];
    }
}

void Map::reset() {
    for (int i = 0; i < MAP_HEIGHT; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
            totalTile[i][j] = premanMap[i][j];
}
