#include <iostream> 
#include <SDL.h> 
#include <vector>
#define WINDOW_WIDTH 1000 

using namespace std;


void it_horizontalLine(SDL_Renderer* render, int x, int y, int lenght) {
    if (lenght < 0) {
        x += lenght;
        if (x < 0)
            x = 0;
        lenght *= -1;
    }
    for (int n1 = 0; n1 < lenght; n1++) {
        SDL_RenderDrawPoint(render, x + n1, y);
    }
    SDL_RenderPresent(render);
}


void it_verticalLine(SDL_Renderer* render, int x, int y, int lenght) {
    if (lenght < 0) {
        y += lenght;
        if (y < 0)
            y = 0;
        lenght *= -1;
    }
    for (int n1 = 0; n1 < lenght; n1++) {
        SDL_RenderDrawPoint(render, x, y + n1);
    }
    SDL_RenderPresent(render);
}


void it_verticalDiagram(SDL_Renderer* render, vector<int>vect) {
    it_horizontalLine(render, 0, 600, 1000);
    int lenght = 1000 / vect.size();
    for (int n1 = 0; n1 < vect.size(); n1++) {
        it_verticalLine(render, lenght * n1, 600, (vect[n1] * vect.size()));
        it_horizontalLine(render, lenght * n1, 600 + (vect[n1] * 5), lenght);
        it_verticalLine(render, lenght * n1, 600 + (vect[n1] * vect.size()), -1 * (vect[n1] * vect.size()));
    }
    SDL_RenderPresent(render);
}


void it_horizontalDiagram(SDL_Renderer* render, vector<int>numbers) {

}


int main(int argc, char* args[])
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    //SDL_RenderDrawPoint(renderer, 499, 499);
    //it_verticalLine(renderer, 499, 499, -100);
    //it_horizontalLine(renderer, 499, 499, 100);
    it_verticalDiagram(renderer, { 1, 5, 12, 25 });
    SDL_Delay(30000);
    SDL_Quit();
    return 0;
}