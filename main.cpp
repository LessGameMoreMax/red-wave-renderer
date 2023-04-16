#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Fail to initialize" << endl;
        return 0;
    }
    cout << "Succeed to initialize" << endl;
    SDL_Quit();
    return 0;
}
