#include <iostream>
#include<SDL/SDL.h>


int main(int argc, char const *argv[])
{

SDL_Init(SDL_INIT_EVERYTHING);

std::cout << "teste" << std::endl;
SDL_Delay(5000);
SDL_Quit();
    return 0;
}
