#include "game.h"
#define WINDOW_WIDTH 1000
// поле 

class Enemy {
public:
    int moveX = 5;
    int moveY = 5;
};


class Player {
public:
    int posX, posY, score = 0;
    Player (int x, int y) {
        posX = x;
        posY = y;
    }

    void setPos(int x, int y) {
        posX = x;
        posY = y;
    }
    void getPos(int& x, int& y) {
        x = posX;
        y = posY;
    }
};


bool collideTiles(int x, int y, vector <vector <char>> field, int move){
    if (move == 1) {
        if (y - 1 < 0 or y - 1 > field.size())
            return false;
        else if (field[y - 1][x] != '0')
            return false;
    }
    else if (move == 2) {
        if (y + 1 >= field.size() or y + 1 < 0)
            return false;
        else if (field[y + 1][x] != '0')
            return false;
    }
    else if (move == 3) {
        if (x - 1 < 0 or x - 1 >= field[0].size())
            return false;
        else if (field[y][x - 1] != '0')
            return false;
    }
    else if (move == 4) {
        if (x + 1 >= field.size() or x + 1 < 0)
            return false;
        else if (field[y][x + 1] != '0')
            return false;
    }
    return true;
}
/*
1 - up
2 - down
3 - left
4 - right
*/


void drawPlayer(int x, int y, SDL_Renderer* render) {
    SDL_SetRenderDrawColor(render, 255, 255, 0, 0);
    drawRect(render, x, y, 50);
    SDL_RenderPresent(render);
}


void drawRect(SDL_Renderer* render, int x, int y, int lenght) {
    for (int n1 = y; n1 < y + lenght; n1++)
        for (int n2 = x; n2 < x + lenght; n2++)
            SDL_RenderDrawPoint(render, n2, n1);

}


void drawMap(SDL_Renderer* render, const vector<vector<char>> field) {
    for (int nY = 0; nY < field.size(); nY++) {
        for (int nX = 0; nX < field[0].size(); nX++) {
            if (field[nY][nX] != '0') {
                if (field[nY][nX] == '1')
                    SDL_SetRenderDrawColor(render, 0, 255, 0, 0);
            //            else if (field[nY][nX] == 'p')
            //                SDL_SetRenderDrawColor(render, 255, 0, 255, 0);
                if (field[nY][nX] == 'e')
                    SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
                drawRect(render, (nX * 50), (nY * 50), 50);
                SDL_RenderPresent(render);
            }
        }
    }
    SDL_RenderPresent(render);
}


void changeLevelData(int level, vector <vector <char>>& field) {
    string way, line;
    vector <char>text;
    if (level == 1) way = "level1.txt";
    if (level == 2) way = "level2.txt";
    if (level == 3) way = "level3.txt";
    ifstream dataFile(way);
    field.clear();
    while (getline(dataFile, line)) {
        text.clear();
        for (auto n1 : line) {
            text.push_back(n1);
        }
        field.push_back(text);
    }
}


void getPos(int& x, int& y, vector <vector <char>> field) {
    for (int n1 = 0; n1 < field.size(); n1++) {
        for (int n2 = 0; n2 < field[0].size(); n2++) {
            if (field[n1][n2] == 'p') { x = n2; y = n1; }
        }
    }
}


int main(int argc, char* args[])
{
    vector <vector <char>> field = {};
    int posX, posY, x ,y;
    changeLevelData(1, field);
    getPos(posX, posY, field);
    Player player(posX, posY);
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event* even = new SDL_Event();
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH - 100, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    bool done = false;
    x = posX * 50;
    y = posY * 50;
    while (!done) {
        drawMap(renderer, field);
        drawPlayer(x, y, renderer);
        while (SDL_PollEvent(even)) {
            if (even->type == SDL_QUIT) done = true;
            switch (even->key.keysym.scancode) {
            case SDL_SCANCODE_S:
                if (collideTiles(x / 50, y / 50, field, 2) == false) break;
                y += 5;
                break;
            case SDL_SCANCODE_W:
                if (collideTiles(x / 50, y / 50, field, 1) == false) break;
                y -= 5;
                break;
            case SDL_SCANCODE_A:
                if (collideTiles(x / 50, y / 50, field, 3) == false) break;
                x -= 5;
                break;
            case SDL_SCANCODE_D:
                if (collideTiles(x / 50, y / 50, field, 4) == false) break;
                x += 5;
                break;
            }
        }
        /*
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > 999) x = 999;
        if (y > 999) y = 999;
        */
        //cout << x << '\n';
        //cout << y << '\n';
        //SDL_Delay(600);
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return 0;
}
/*
1 - up
2 - down
3 - left
4 - right
*/