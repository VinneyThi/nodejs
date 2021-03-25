#include <iostream>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "func.c"
#include <math.h>
#include <unistd.h>
using namespace std;

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
    ~Figura();
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
        this->vetScale[i] = 0;

    for (int i = 0; i < 3; i++)
        this->vetTransla[i] = ptrVetTransla[i];
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

Figura *line(Pontptr *ptrPoints, int l1)
{

    if (!ptrPoints)
        return NULL;
    std::string ptrName = " ";

    ptrName = std::to_string(l1) + "L";

    double *ptrVetTra = new double[3];
    double vetAux[3] = {300.0, 200.0, 0.0};

    setVetAux(ptrVetTra, vetAux);
    Figura *ptrAuxF = new Figura(ptrName.c_str(), ptrPoints, ptrVetTra);

    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);
    glTranslatef(300.0, 200.0, 0.0);

    glColor4ub(255, 20, 66, 255);

    //inicia desenho

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < ptrPoints->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrPoints, i);
        if (!ptrAuxPoint)
            break;
        glVertex2f(ptrAuxPoint->ptrValue[0], ptrAuxPoint->ptrValue[1]);
    }

    glEnd();
    //fecha a matriz de desenho
    glPopMatrix();

    return ptrAuxF;
}

Figura *lineR(Pontptr *ptrPoints, int l1)
{

    if (!ptrPoints)
        return NULL;
    std::string ptrName = " ";

    ptrName = std::to_string(l1) + "L";

    double *ptrVetTra = new double[3];
    double vetAux[3] = {300.0, 200.0, 0.0};

    setVetAux(ptrVetTra, vetAux);

    Figura *ptrAuxF = new Figura(ptrName.c_str(), ptrPoints, ptrVetTra);

    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);
    glTranslatef(300.0, 200.0, 0.0);
    glRotatef((GLfloat)-90, 0.0, 0.0,0.0);
    glColor4ub(255, 20, 66, 255);

    //inicia desenho

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ptrPoints->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrPoints, i);
        if (!ptrAuxPoint)
            break;
        glVertex2f(ptrAuxPoint->ptrValue[0], ptrAuxPoint->ptrValue[1]);
    }

    glEnd();
    //fecha a matriz de desenho
    glPopMatrix();

    return ptrAuxF;
}

void Deleteline(Pontptr *ptrPoints, char *ptrtyp)
{
    cout << "Dentro" << endl;
    if (!ptrPoints || !ptrtyp)
        return;

    glPushMatrix();
    glOrtho(0, 600, 400, 0, -1, 1);
   // glTranslatef(300.0, 200.0, 0.0);
    //glRotatef((GLfloat)-90, 0.0, 0.0,0.0);
    glColor4ub(0, 0, 0, 255);

    //inicia desenho
    if (ptrtyp[1] == 'L')
        glBegin(GL_LINE_STRIP);
    else if (ptrtyp[1] == 'H')
        glBegin(GL_LINE_STRIP);
    else
        glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ptrPoints->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrPoints, i);
        if (!ptrAuxPoint)
            break;
        glVertex2f(ptrAuxPoint->ptrValue[0], ptrAuxPoint->ptrValue[1]);
    }

    glEnd();
    //fecha a matriz de desenho
    glPopMatrix();

    return;
}

Figura *regularLine(Pontptr *ptrPoints, double *ptrVet, double l, char *ptrType, int r1)
{

    if (!ptrPoints || !ptrType)
        return NULL;

    std::string ptrName = " ";

    ptrName = std::to_string(r1) + "R";
    //inicia desenho

    if (ptrType[0] == 'q')

    {
        for (int i = 0; i < 4; i++)
        {
            double *ptrAuxPont = new double[2];

            if (!ptrAuxPont)
                return NULL;

            ptrAuxPont[0] = i <= 1 ? ptrVet[0] - l : ptrVet[0] + l;
            ptrAuxPont[1] = i <= 1 ? ptrVet[1] - ((l)*pow(-1, i)) : ptrVet[1] + ((l)*pow(-1, i));
            setPoints(ptrPoints, ptrAuxPont, 2);
        }
    }
    else if (ptrType[0] == 'h')
    {
        for (int i = 0; i < 6; i++)
        {
            double *ptrAuxPont = new double[2];

            if (!ptrAuxPont)
                return NULL;

            if (i != 5 && i != 2)
            {

                ptrAuxPont[0] = i == 0 || i == 4 ? ptrVet[0] - l / 2 : ptrVet[0] + l / 2;
                ptrAuxPont[1] = i == 3 || i == 0 ? ptrVet[1] - ((sqrt(3) * (l / 2)) * pow(-1, i)) : ptrVet[1] + ((sqrt(3) * (l / 2)) * pow(-1, i));
                cout << ptrAuxPont[1] << endl;
            }
            else
            {

                ptrAuxPont[0] = i == 2 ? ptrVet[0] + l : ptrVet[0] - l;
                ptrAuxPont[1] = ptrVet[1];
            }
            setPoints(ptrPoints, ptrAuxPont, 2);
        }
    }

    else if (ptrType[0] == 't')

    {
        for (int i = 0; i < 3; i++)
        {
            double *ptrAuxPont = new double[2];

            if (!ptrAuxPont)
                return NULL;

            if (i != 1)
            {
                ptrAuxPont[0] = i == 0 ? ptrVet[0] - l / 2 : ptrVet[0] + l / 2;
                ptrAuxPont[1] = ptrVet[1] + (sqrt(3) * l) / 4;
            }
            else
            {
                ptrAuxPont[0] = ptrVet[0];
                ptrAuxPont[1] = ptrVet[1] - (sqrt(3) * l) / 2;
            }
            setPoints(ptrPoints, ptrAuxPont, 2);
        }
    }

    // glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);
    glTranslatef(300.0, 200.0, 0.0);
    glColor4ub(255, 20, 66, 255);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < ptrPoints->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrPoints, i);
        if (!ptrAuxPoint)
            break;
        glVertex2f(ptrAuxPoint->ptrValue[0], ptrAuxPoint->ptrValue[1]);
    }

    double *ptrVetTra = new double[3];
    double vetAux[3] = {300.0, 200.0, 0.0};

    setVetAux(ptrVetTra, vetAux);

    Figura *ptrAuxF = new Figura(ptrName.c_str(), ptrPoints, ptrVetTra);

    //fecha a matriz de desenho
    glEnd();

    glPopMatrix();

    return ptrAuxF;
}

int main(int argc, char const *argv[])
{
    Figura *ptrAuxFig;
    Pontptr *ptrPoints2 = new (Pontptr);
    Pontptr *ptrPoints3 = new (Pontptr);
    ptrPoints2->size = 0;
    ptrPoints3->size = 0;

    LisFigDisplay *ptrListFIG = new LisFigDisplay();
    int l1 = 0;
    int rl = 0;

    char *ptrEntrada = new char[240];
    double *ptrEntradaP;

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

    glClearColor(1, 1, 1, 1);

    //2D
    glMatrixMode(GL_MODELVIEW); //Atribui a projeção da matrix atual
    glLoadIdentity();           //Habilita desenho geometrico
    glDisable(GL_DEPTH_TEST);   // Desabilita o 3D

    // LOGICA

    bool flagEx = true;
    SDL_Event eventUser;

    while (flagEx)
    {

        //Render

        glClear(GL_DEPTH_BUFFER_BIT); //limpa o buffer de cor
                                      //Inicializa matriz para desenhar
                                      //line(ptrPoints);
                                      //   line(ptrPoints2);
                                      //double cent[2] = {200, 200};
                                      //  regularLine(ptrPoints3, cent, 100, "t"); // fazer retornar um ponteiro para linkar a lista de ponstos

        glPushMatrix();

        glOrtho(0, 600, 400, 0, -1, 1);
        glTranslatef(300.0, 200.0, 0.0);
        glColor4ub(255, 255, 255, 255);
        glBegin(GL_LINE_LOOP);

        glVertex2f(-300.0, 0.0);
        glVertex2f(300.0, 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix();

        glOrtho(0, 600, 400, 0, -1, 1);
        glTranslatef(300.0, 200.0, 0.0);
        glColor4ub(255, 255, 255, 255);
        glBegin(GL_LINE_LOOP);

        glVertex2f(0.0, 200.0);
        glVertex2f(0.0, -200.0);
        glEnd();
        glPopMatrix();
        SDL_GL_SwapBuffers();

        cout << "Escolha a operação " << endl
             << "1- Desenho livre " << endl
             << "2- Desenho livre Regular  " << endl
             << "3 -Poligonos Regulares" << endl
             << "4- Operações em Poligonos" << endl
             << "ESC- Para sair" << endl;

        cin >> ptrEntrada;

        if (ptrEntrada[0] == '1')
        {

            Pontptr *ptrPoints = new (Pontptr);
            ptrPoints->size = 0;
            cout << "Passe os pontos de entrada e para finalizar passe f" << endl;

            while (ptrEntrada[0] != 'f')
            {

                ptrEntradaP = new double[2];
                cin >> ptrEntradaP[0] >> ptrEntradaP[1] >> ptrEntrada[0];
                setPoints(ptrPoints, ptrEntradaP, 2);
            }
            ptrAuxFig = line(ptrPoints, ++l1);
            ptrListFIG->addFig(ptrAuxFig);
            //  cout << ptrListFIG->getFig()->getName() << " " << ptrListFIG->getSize() << " " << ptrListFIG->getFig()->getPontptr()->ptrEnd->ptrValue[1] << endl;

            //cout << ptrListFIG->getFig("3L")->getName() <<" " << ptrListFIG->getSize() << " " << ptrListFIG->getFig("3L")->getPontptr()->ptrEnd->ptrValue[1] << endl;
        }
        else if (ptrEntrada[0] == '2')
        {

            Pontptr *ptrPoints = new (Pontptr);
            ptrPoints->size = 0;
            cout << "Passe os pontos de entrada e para finalizar passe f" << endl;

            while (ptrEntrada[0] != 'f')
            {

                ptrEntradaP = new double[2];
                cin >> ptrEntradaP[0] >> ptrEntradaP[1] >> ptrEntrada[0];
                setPoints(ptrPoints, ptrEntradaP, 2);
            }
            ptrAuxFig = lineR(ptrPoints, ++l1);
            ptrListFIG->addFig(ptrAuxFig);
            //  cout << ptrListFIG->getFig()->getName() << " " << ptrListFIG->getSize() << " " << ptrListFIG->getFig()->getPontptr()->ptrEnd->ptrValue[1] << endl;

            //cout << ptrListFIG->getFig("3L")->getName() <<" " << ptrListFIG->getSize() << " " << ptrListFIG->getFig("3L")->getPontptr()->ptrEnd->ptrValue[1] << endl;
        }
        else if (ptrEntrada[0] == '3')
        {
            cout << "Passe o ponto central, tamanho da aresta e  a classe de Poligono" << endl;
            ptrEntradaP = new double[2];
            double aresta = 0;
            cin >> ptrEntradaP[0] >> ptrEntradaP[1] >> aresta >> ptrEntrada[0];
            Pontptr *ptrPoints = new (Pontptr);
            ptrPoints->size = 0;
            cout << ptrEntradaP[0] << " " << ptrEntradaP[1] << aresta << "" << ptrEntrada[0] << endl;
            ptrAuxFig = regularLine(ptrPoints, ptrEntradaP, aresta, ptrEntrada, ++rl);
            ptrListFIG->addFig(ptrAuxFig);
        }

        else if (ptrEntrada[0] == 'd')
        {
            //cout << ptrAuxFig->getPontptr()->ptrEnd->ptrValue[0] << " " << ptrAuxFig->getPontptr()->ptrEnd->ptrValue[1] << endl;
            //  cout << ptrListFIG->getFig()->getName() << " " << ptrListFIG->getSize() << " " << ptrListFIG->getFig()->getPontptr()->ptrEnd->ptrValue[1] << endl;

            char vetN[2];
            cout << "Digite o nome da Fig a ser deletada" << endl;
            cin >> vetN;

            Deleteline(ptrListFIG->getFig(vetN)->getPontptr(), vetN);
        }
        SDL_GL_SwapBuffers();
        usleep(15000);
        while (SDL_PollEvent(&eventUser))
        {
            if (eventUser.type == SDL_QUIT)
                flagEx = false;

            else if (eventUser.type == SDL_KEYUP && eventUser.key.keysym.sym == SDLK_ESCAPE)
                flagEx = false;
        } // desabilita animação
    }

    SDL_Quit();
    return 0;
}
