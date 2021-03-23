#include <iostream>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"

int main(int argc, char const *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    //Memoria

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    


    //Nome da janela e icone

    SDL_WM_SetCaption("Primeira janela SDL",NULL);

    //Tamanho da janela

    SDL_SetVideoMode(600,400,32,SDL_OPENGL);

    glClearColor(1,1,1,1);


    glViewport(0,0,600,400);

    //Sombra da janela
    glShadeModel(GL_SMOOTH);

    //2D
    glMatrixMode(GL_PROJECTION); //Atribui a projeção da matrix atual
    glLoadIdentity();//Habilita desenho geometrico
    glDisable(GL_DEPTH_TEST); // Desabilita o 3D

// LOGICA

    bool flagEx = true;
    SDL_Event eventUser; 
    while (flagEx)
    {
       while (SDL_PollEvent(&eventUser))
       {
          if(eventUser.type == SDL_QUIT)
            flagEx = false;

           else if (eventUser.type == SDL_KEYUP && eventUser.key.keysym.sym == SDLK_F10)
                flagEx = false; 
       }


    //Render

    glClear(GL_DEPTH_BUFFER_BIT); //limpa o buffer de cor
    //Inicializa matriz para desenhar
    glPushMatrix();

    glOrtho(0,600,400,0,-1,1);

    glColor4ub(255,20,66,255);

    //inicia desenho

    glBegin(GL_POLYGON);

    glVertex2f(50,50);
    glVertex2f(50,325);
    glVertex2f(400,325);
    glVertex2f(500,195);
    glVertex2f(400,50);
    glEnd();
//fecha a matriz de desenho
    glPopMatrix();



    SDL_GL_SwapBuffers(); // desabilita animação


        
    }
    



    SDL_Quit();
        return 0;
}

