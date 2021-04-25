#include <iostream>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "func.c"
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

using namespace std;



void MouseClick (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON: printf("Botao esquerdo.");
                                                        break;
        case GLUT_RIGHT_BUTTON: printf("Botao direito.");
                                                        break;
        case GLUT_MIDDLE_BUTTON: printf("Botao do meio.");
                                                        break;
    }
    if (state == GLUT_DOWN)
        printf("Pressionado na posição: ");
    if (state == GLUT_UP)
        printf("Liberado na posição: ");
    printf("(%d, %d)\n", x,y);
}

class Figura
{

private:
    char *ptrName;
    Pontptr *ptrListPoints;
    Figura *ptrProx;
    double rot;
    double vetTransla[3];
    double vetScale[3];

public:
    Figura(const char *ptrName, Pontptr *ptrListPoints, double rot, double *ptrVetTransla, double *ptrVetScale);
    Figura(const char *ptrName, Pontptr *ptrListPoints, double *ptrVetTransla);
    Figura(const char *ptrName, Pontptr *ptrListPoints);
    ~Figura();
    void setPtrListPoints(Pontptr *ptrListPoints);
    void setRot(double rot);
    void setVetTrans(double *ptrVetAux);
    void setVetScale(double *ptrVetAux);
    void setPtrProx(Figura *ptrAux);
    double getRot();
    double *getVetTransla();
    double *getVetScale();
    const char *getName();
    Pontptr *getPontptr();
    Figura *getPtrProx();
};

Figura::Figura(const char *ptrName, Pontptr *ptrListPoints, double rot, double *ptrVetTransla, double *ptrVetScale)
{
    if (!ptrName || !ptrListPoints || !ptrVetScale || !ptrVetTransla)
        return;
    char *ptrAux = new char[4];
    for (int i = 0; i < 4; i++)
        ptrAux[i] = ptrName[i];
    this->ptrName = ptrAux;
    this->ptrProx = NULL;
    this->ptrListPoints = ptrListPoints;
    this->rot = rot;

    for (int i = 0; i < 3; i++)
        this->vetScale[i] = ptrVetScale[i];

    for (int i = 0; i < 3; i++)
        this->vetTransla[i] = ptrVetTransla[i];
}

Figura::Figura(const char *ptrName, Pontptr *ptrListPoints, double *ptrVetTransla)
{
    if (!ptrName || !ptrListPoints || !ptrVetTransla)
        return;

    char *ptrAux = new char[4];
    for (int i = 0; i < 4; i++)
        ptrAux[i] = ptrName[i];

    this->ptrProx = NULL;
    this->ptrName = ptrAux;
    this->ptrListPoints = ptrListPoints;
    this->rot = 0;

    for (int i = 0; i < 3; i++)
        this->vetScale[i] = 1;

    for (int i = 0; i < 3; i++)
        this->vetTransla[i] = ptrVetTransla[i];
}

Figura::Figura(const char *ptrName, Pontptr *ptrListPoints)
{
    if (!ptrName || !ptrListPoints)
        return;

    char *ptrAux = new char[4];
    for (int i = 0; i < 4; i++)
        ptrAux[i] = ptrName[i];

    this->ptrProx = NULL;
    this->ptrName = ptrAux;
    this->ptrListPoints = ptrListPoints;
    this->rot = 0;

    for (int i = 0; i < 3; i++)
        this->vetScale[i] = 1;

    for (int i = 0; i < 3; i++)
        this->vetTransla[i] = 0;
}

Figura::~Figura()
{
    delete[] this->ptrName;
    delete[] this->ptrListPoints;
}

void Figura::setRot(double rot)
{
    this->rot = rot;
}

void Figura::setVetScale(double *ptrVetAux)
{
    if (!ptrVetAux)
        return;
    for (int i = 0; i < 3; i++)
        this->vetScale[i] = ptrVetAux[i];
}

void Figura::setVetTrans(double *ptrVetAux)
{
    if (!ptrVetAux)
        return;
    for (int i = 0; i < 3; i++)
        this->vetTransla[i] = ptrVetAux[i];
}

void Figura::setPtrProx(Figura *ptrAux)
{
    if (!ptrAux)
        return;

    this->ptrProx = ptrAux;
}

void Figura::setPtrListPoints(Pontptr *ptrListPoints)
{
    this->ptrListPoints = ptrListPoints;
}
double Figura::getRot()
{
    return this->rot;
}

double *Figura::getVetScale()
{
    return this->vetScale;
}

double *Figura::getVetTransla()
{
    return this->vetTransla;
}

const char *Figura::getName()
{
    return this->ptrName;
}

Pontptr *Figura::getPontptr()
{
    return this->ptrListPoints;
}

Figura *Figura::getPtrProx()
{
    return this->ptrProx;
}

class LisFigDisplay
{
private:
    Figura *ptrListPointInit;
    Figura *ptrListPointEnd;
    int size;

public:
    LisFigDisplay();
    ~LisFigDisplay();
    void addFig(Figura *ptrAux);
    Figura *getFig(const char *ptrAux);
    Figura *getFig();
    int getSize();
};

LisFigDisplay::LisFigDisplay()
{
    this->ptrListPointEnd = NULL;
    this->ptrListPointInit = NULL;
    this->size = 0;
}

LisFigDisplay::~LisFigDisplay()
{
    delete[] this->ptrListPointEnd;
    delete[] this->ptrListPointInit;
}

void LisFigDisplay::addFig(Figura *ptrAux)
{
    if (!ptrAux)
        return;

    if (this->size == 0)
    {
        this->ptrListPointEnd = ptrAux;
        this->ptrListPointInit = ptrAux;
        this->size++;
    }
    else
    {
        this->ptrListPointEnd->setPtrProx(ptrAux);
        this->ptrListPointEnd = ptrAux;
        this->size++;
    }
}

Figura *LisFigDisplay::getFig(const char *ptrAux)
{
    if (!ptrAux)
        return NULL;

    
    Figura *ptrAuxList = this->ptrListPointInit;

    for (int i = 0; i < this->size; i++)
    {

        if (!ptrAuxList)
            return NULL;

        cout << "Name" << ptrAuxList->getName() << " Valor " << ptrAuxList->getPontptr()->ptrEnd->ptrValue[1] << endl;
        if (strcmp(ptrAuxList->getName(), ptrAux) == 0)
            return ptrAuxList;

        ptrAuxList = ptrAuxList->getPtrProx();
    }

    return NULL;
}

Figura *LisFigDisplay::getFig()
{
    return this->ptrListPointEnd;
}
int LisFigDisplay::getSize()
{
    return this->size;
}

void setVetAux(double *ptrAux, double *ptrVet)
{
    if (!ptrAux)
        return;

    for (int i = 0; i < 3; i++)
    {
        ptrAux[i] = ptrVet[i];
    }
}


void eixoXY()
{
    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);
    glTranslatef(300.0, 200.0, 0.0);
    glColor4ub(255, 255, 255, 0);
    glBegin(GL_LINE_LOOP);

    glVertex2f(-300.0, 0.0);
    glVertex2f(300.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);
    glTranslatef(300.0, 200.0, 0.0);
    glColor4ub(255, 255, 255, 0);
    glBegin(GL_LINE_LOOP);

    glVertex2f(0.0, 200.0);
    glVertex2f(0.0, -200.0);
    glEnd();
    glPopMatrix();
}

void tracoXM()
{
    for (int i = 0; i < 30; i++)
    {
        glPushMatrix();

        glOrtho(0, 600, 400, 0, -1, 1);
        glTranslatef(300.0, 200.0, 0.0);
        glColor4ub(0, 255, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.0 + 10 * i, 2);
        glVertex2f(0.0 + 10 * i, -2);
        glEnd();
        glPopMatrix();
    }
}

void tracoXm()
{
    for (int i = 0; i < 30; i++)
    {
        glPushMatrix();

        glOrtho(0, 600, 400, 0, -1, 1);
        glTranslatef(300.0, 200.0, 0.0);
        glColor4ub(0, 255, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.0 - 10 * i, 2);
        glVertex2f(0.0 - 10 * i, -2);
        glEnd();
        glPopMatrix();
    }
}

void tracoYM()
{
    for (int i = 0; i < 30; i++)
    {
        glPushMatrix();

        glOrtho(0, 600, 400, 0, -1, 1);
        glTranslatef(300.0, 200.0, 0.0);
        glColor4ub(0, 255, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(2, 0 + 10 * i);
        glVertex2f(-2, 0 + 10 * i);
        glEnd();
        glPopMatrix();
    }
}

void tracoYm()
{
    for (int i = 0; i < 30; i++)
    {
        glPushMatrix();

        glOrtho(0, 600, 400, 0, -1, 1);
        glTranslatef(300.0, 200.0, 0.0);
        glColor4ub(0, 255, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(2, 0 - 10 * i);
        glVertex2f(-2, 0 - 10 * i);
        glEnd();
        glPopMatrix();
    }
}


Figura * curva(Pontptr *ptrPoints, int l1, double *ptrVetCor)
{
      if (!ptrPoints )
        return NULL;
    
     Figura *ptrAuxF;
    std::string ptrName = " ";
    if(l1 >= 0)
    {  
        ptrName = std::to_string(l1) + "C";
        ptrAuxF = new Figura(ptrName.c_str(), ptrPoints);
        
    }
    SDL_GL_SwapBuffers();

    eixoXY();
    tracoYM();
    tracoYm();
    tracoXM();
    tracoXm();

   GLfloat vetcurva[9][3];

    for (int i = 0; i < ptrPoints->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrPoints, i);
        if (!ptrAuxPoint)
            break;
       
       vetcurva[i][0] = ptrAuxPoint->ptrValue[0] ;
       vetcurva[i][1] = ptrAuxPoint->ptrValue[1] ;
       vetcurva[i][2] = 0;
    }

    printf("Tam %d\n",ptrPoints->size);
    for(int j=0 ; j < ptrPoints->size ; j++)
    {
        printf(" vet %d %f %f\n",j,vetcurva[j][0],vetcurva[j][1]);

    }
    
    
glMap1f(GL_MAP1_VERTEX_3, 0.0, 1, 3, ptrPoints->size, &vetcurva[0][0]);
	// Ativa gera��o de coordenadas

        
	glEnable(GL_MAP1_VERTEX_3);
	float delta = 1.0/(float)100;

	// Tra�a a curva

    
    if(ptrVetCor)
        for(int i = 0 ; i < 3 ; i++)
        {
                float radnv = rand() % 150 ;
                ptrVetCor[i] = (ptrVetCor[i] + radnv)  < 255.0 ? (ptrVetCor[i] + radnv) : ( ptrVetCor[i] +radnv);
        }

        
    if(ptrVetCor)
        glColor4ub(ptrVetCor[0], ptrVetCor[1], ptrVetCor[2], 0);
    else
        glColor4ub(0, 0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for(float f = 0; f<=1.01; f+=delta)
		glEvalCoord1f(f);
	glEnd();

    glPointSize(5.0);
  glBegin(GL_POINTS);
  for (int  i = 0; i < ptrPoints->size; i++)
   { 
     glVertex3fv(&vetcurva[i][0]);
      
  }
  glEnd();


SDL_GL_SwapBuffers();

return ptrAuxF;

}



void DeleteF(Figura *ptrFig)
{
    cout << "Dentro" << endl;
    if (!ptrFig)
        return;

    double *ptrAuxvetTran = ptrFig->getVetTransla();
    double *ptrAuxvetScale = ptrFig->getVetScale();

    

    
    for (int i = 0; i < ptrFig->getPontptr()->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrFig->getPontptr(), i);
        if (!ptrAuxPoint)
            break;
        glVertex2f(ptrAuxPoint->ptrValue[0], ptrAuxPoint->ptrValue[1]);
    }
    curva(ptrFig->getPontptr(), -1, {});

    glEnd();

    return;
}

int main(int argc, char  *argv[])
{
    Figura *ptrAuxFig;
    Pontptr *ptrPoints2 = new (Pontptr);
    Pontptr *ptrPoints3 = new (Pontptr);
    ptrPoints2->size = 0;
    ptrPoints3->size = 0;

    LisFigDisplay *ptrListFIG = new LisFigDisplay();
    int l1 = 0;
    int rl = 0;
    int tamFig = 0;

    char *ptrEntrada = new char[240];
    double *ptrEntradaP;
    double bufferCor[3] = {255.0,0.0,0.0};
    SDL_Init(SDL_INIT_EVERYTHING);

    //Memoria

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Nome da janela e icone

    SDL_WM_SetCaption("Primeira janela SDL", NULL);

    //Tamanho da janela

    SDL_SetVideoMode(600, 400, 32, SDL_OPENGLBLIT); // possivel pau


    glClearColor(0, 0, 0, 0);

    //2D
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

    // LOGICA
    eixoXY();
    tracoYM();
    tracoYm();
    tracoXM();
    tracoXm();
    SDL_GL_SwapBuffers();

    bool flagEx = true;
    SDL_Event eventUser;
    glutInit(&argc,argv);
    glutMouseFunc(MouseClick);
      Pontptr *ptrPoints = new (Pontptr);
     ptrPoints->size = 0;
    while (flagEx)
    {

        //Render

        glClear(GL_DEPTH_BUFFER_BIT); //limpa o buffer de cor
                                      //Inicializa matriz para desenhar
                                      //line(ptrPoints);
                                      //   line(ptrPoints2);
                                      //double cent[2] = {200, 200};
                                      //  regularLine(ptrPoints3, cent, 100, "t"); // fazer retornar um ponteiro para linkar a lista de ponstos



        while (SDL_PollEvent(&eventUser))
        {
            if (eventUser.type == SDL_QUIT)
                flagEx = false;

            else if (eventUser.type == SDL_KEYUP && eventUser.key.keysym.sym == SDLK_ESCAPE)
                flagEx = false;
            else if (eventUser.type == SDL_KEYUP && eventUser.key.keysym.sym == SDLK_KP_ENTER)
            {
                   if(tamFig >= 5)
                    {   printf("Numero limite maximo\n");
                        delete ptrPoints;
                        ptrPoints = new (Pontptr);
                        ptrPoints->size = 0;
                        break ;
                    }

                    if(ptrPoints->size > 9 || ptrPoints->size < 3 )
                    {
                        printf("Quantidades de pontos invalidos\n");
                        delete ptrPoints;
                        ptrPoints = new (Pontptr);
                        ptrPoints->size = 0;
                        break;
                    }
                    if(ptrPoints->size % 2 == 0)
                    {
                        printf("Quantidades de pontos não impar\n");
                        delete ptrPoints;
                        ptrPoints = new (Pontptr);
                        ptrPoints->size = 0;
                        break;
                    }   
                ptrAuxFig = curva(ptrPoints, ++l1 ,bufferCor);
                tamFig++;
                ptrListFIG->addFig(ptrAuxFig);
                ptrPoints = new (Pontptr);
                ptrPoints->size = 0;
            }
                

            else if (eventUser.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x,y;
                  
                        
                        if(eventUser.button.button == SDL_BUTTON_LEFT )
                            {
                             
                                SDL_GetMouseState(&x, &y);
                                printf("x %d y %d \n",x-300,-y + 200);
                                ptrEntradaP = new double[2];
                                ptrEntradaP[0] = (x - 300) /300.0;
                                ptrEntradaP[1] = -1.0*(y - 200 )/200.0;
                                if ( ptrPoints->size > 0 && ptrEntradaP[0] == ptrPoints->ptrEnd->ptrValue[0])
                                    {
                                        printf("Entrada Invalida\n");
                                        delete ptrPoints;
                                        ptrPoints = new (Pontptr);
                                        ptrPoints->size = 0;
                                        break;
                                    }
                                setPoints(ptrPoints, ptrEntradaP, 2);
                                
                                
                                
                            }
                }

            else if (eventUser.type == SDL_KEYUP && eventUser.key.keysym.sym == SDLK_d)
            {

                char vetN[2];
                cout << "Digite o nome da Fig a ser deletada" << endl;
                cin >> vetN;
                DeleteF(ptrListFIG->getFig(vetN));
                tamFig--;
            }
              
       
        } 
        // desabilita animação
    }

    SDL_Quit();
    return 0;
}
