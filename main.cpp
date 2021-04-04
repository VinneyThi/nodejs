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

    cout << " GETFOg" << ptrAux << endl;
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
void rot(Figura *ptrFig, double *ptrVet)
{
    ptrFig->setRot(ptrVet[0]);
    glTranslatef(ptrFig->getVetTransla()[0] + (ptrFig->getPontptr()->ptrInit->ptrValue[0]), ptrFig->getVetTransla()[1] + (ptrFig->getPontptr()->ptrInit->ptrValue[1]), 0.0);
    glRotatef((GLfloat)ptrFig->getRot(), 0.0, 0.0, 1.0);
    glTranslatef(-ptrFig->getPontptr()->ptrInit->ptrValue[0], -ptrFig->getPontptr()->ptrInit->ptrValue[1], 0.0);
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
    glRotatef((GLfloat)-90, 0.0, 0.0, 0.0);
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

void Deleteline(Pontptr *ptrPoints, const char *ptrtyp)
{
    cout << "Dentro" << endl;
    if (!ptrPoints || !ptrtyp)
        return;

    glPushMatrix();
    glOrtho(0, 600, 400, 0, -1, 1);
    glTranslatef(300.0, 200.0, 0.0);
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

void DeleteF(Figura *ptrFig)
{
    cout << "Dentro" << endl;
    if (!ptrFig)
        return;

    double *ptrAuxvetTran = ptrFig->getVetTransla();
    double *ptrAuxvetScale = ptrFig->getVetScale();

    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);

    glTranslatef(ptrFig->getVetTransla()[0] + (ptrFig->getPontptr()->ptrInit->ptrValue[0]), ptrFig->getVetTransla()[1] + (ptrFig->getPontptr()->ptrInit->ptrValue[1]), 0.0);

    glRotatef((GLfloat)ptrFig->getRot(), 0.0, 0.0, 1.0);
    glScaled(ptrAuxvetScale[0], ptrAuxvetScale[1], 0.0);
    glTranslatef(-ptrFig->getPontptr()->ptrInit->ptrValue[0], -ptrFig->getPontptr()->ptrInit->ptrValue[1], 0.0);
    glColor4ub(0, 0, 0, 255);

    //inicia desenho
    if (ptrFig->getName()[1] == 'L')
        glBegin(GL_LINE_STRIP);
    else if (ptrFig->getName()[1] == 'H')
        glBegin(GL_LINE_STRIP);
    else
        glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ptrFig->getPontptr()->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrFig->getPontptr(), i);
        if (!ptrAuxPoint)
            break;
        glVertex2f(ptrAuxPoint->ptrValue[0], ptrAuxPoint->ptrValue[1]);
    }

    glEnd();
    //fecha a matriz de desenho
    glPopMatrix();

    return;
}

void operacao(Figura *ptrFig, double *ptrVet, char o)
{
    if (!ptrFig || !ptrVet)
        return;

    DeleteF(ptrFig);

    glLoadIdentity();
    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);
    cout << "ddd0" << o << " vet " << ptrVet[0] << " rot " << ptrFig->getRot() << endl;
    if (o == 'r')
        ptrFig->setRot(ptrVet[0]);
    else if (o == 't')
    {
        ptrVet[0] = ptrFig->getVetTransla()[0] + ptrVet[0];
        ptrVet[1] = ptrFig->getVetTransla()[1] + ptrVet[1];
        ptrFig->setVetTrans(ptrVet);
    }
    else if (o == 's')
        ptrFig->setVetScale(ptrVet);

    double *ptrAuxvetScale = ptrFig->getVetScale();
    double *ptrAuxvetTran = ptrFig->getVetTransla();

    glTranslatef(ptrFig->getVetTransla()[0] + (ptrFig->getPontptr()->ptrInit->ptrValue[0]), ptrFig->getVetTransla()[1] + (ptrFig->getPontptr()->ptrInit->ptrValue[1]), 0.0);

    glRotatef((GLfloat)ptrFig->getRot(), 0.0, 0.0, 1.0);
    glScaled(ptrAuxvetScale[0], ptrAuxvetScale[1], 0.0);
    glTranslatef(-ptrFig->getPontptr()->ptrInit->ptrValue[0], -ptrFig->getPontptr()->ptrInit->ptrValue[1], 0.0);
    glColor4ub(0, 255, 0, 255);
    // glColor4ub(255, 20, 66, 255);

    //inicia desenho
    if (ptrFig->getName()[1] == 'L')
        glBegin(GL_LINE_STRIP);
    else if (ptrFig->getName()[1] == 'H')
        glBegin(GL_LINE_STRIP);
    else
        glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ptrFig->getPontptr()->size; i++)
    {

        Point *ptrAuxPoint = retornaPonto(ptrFig->getPontptr(), i);
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

            ptrAuxPont[0] = i <= 1 ? ptrVet[0] - l / 2 : ptrVet[0] + l / 2;
            ptrAuxPont[1] = i <= 1 ? ptrVet[1] - ((l / 2) * pow(-1, i)) : ptrVet[1] + ((l / 2) * pow(-1, i));
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
                ptrAuxPont[1] = ptrVet[1] + (sqrt(3) * l) / 6;
            }
            else
            {
                ptrAuxPont[0] = ptrVet[0];
                ptrAuxPont[1] = ptrVet[1] - (sqrt(3) * l) / 3;
            }
            setPoints(ptrPoints, ptrAuxPont, 2);
        }
    }

    glPushMatrix();

    glOrtho(0, 600, 400, 0, -1, 1);
    glTranslatef(300.0, 200.0, 0.0);
    //glRotatef((GLfloat)90.0, 0.0, 0.0, 1.0);

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

        eixoXY();

        tracoXM();
        tracoXm();
        tracoYM();
        tracoYm();
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

        else if (ptrEntrada[0] == '4')
        {
            //cout << ptrAuxFig->getPontptr()->ptrEnd->ptrValue[0] << " " << ptrAuxFig->getPontptr()->ptrEnd->ptrValue[1] << endl;
            //  cout << ptrListFIG->getFig()->getName() << " " << ptrListFIG->getSize() << " " << ptrListFIG->getFig()->getPontptr()->ptrEnd->ptrValue[1] << endl;

            char vetN1[2];
            char *vetO = new char[2];
            double vetAux[3];

            cout << "Digite nome da Fig " << endl;
            cin >> vetN1;
            cout << "Digite a operacao" << endl;
            cin >> vetO;

            cout << " aaaaa" << vetN1 << "qqqqq" << endl;
            if (vetO[0] == 'r')
            {
                cout << "Digite o angulo de rotação " << endl;
                cin >> vetAux[0];
            }
            else if (vetO[0] == 't')
            {
                cout << "Digite as coordenadas de translação " << endl;
                cin >> vetAux[0] >> vetAux[1];
            }
            else if (vetO[0] == 's')
            {
                cout << "Digite as coordenadas de escalamento " << endl;
                cin >> vetAux[0] >> vetAux[1];
            }
            else if (vetO[0] == 'x')
            {

                Pontptr *ptrAuxPont = new Pontptr;
                Pontptr *ptrAuxPontDel = new Pontptr;
                ptrAuxPontDel->size = 0;
                Point *ptrAuxPont2;
                ptrAuxPont2 = ptrListFIG->getFig(vetN1)->getPontptr()->ptrInit;
                for (int i = 0; i < ptrListFIG->getFig(vetN1)->getPontptr()->size; i++)

                {
                    double *ptrAuxV = new double[2];

                    ptrAuxV[0] = -1 * ptrAuxPont2->ptrValue[0];
                    ptrAuxV[1] = ptrAuxPont2->ptrValue[1];
                    setPoints(ptrAuxPont, ptrAuxV, 2);
                    ptrAuxV[0] *= -1;
                    setPoints(ptrAuxPontDel, ptrAuxV, 2);
                    ptrAuxPont2 = ptrAuxPont2->ptrProx;
                }
                ptrListFIG->getFig(vetN1)->setPtrListPoints(ptrAuxPont);
                Deleteline(ptrAuxPontDel, vetN1);
            }

            else if (vetO[0] == 'y')
            {

                Pontptr *ptrAuxPont = new Pontptr;
                Pontptr *ptrAuxPontDel = new Pontptr;
                ptrAuxPontDel->size = 0;
                Point *ptrAuxPont2;
                ptrAuxPont2 = ptrListFIG->getFig(vetN1)->getPontptr()->ptrInit;
                for (int i = 0; i < ptrListFIG->getFig(vetN1)->getPontptr()->size; i++)

                {
                    double *ptrAuxV = new double[2];

                    ptrAuxV[0] = ptrAuxPont2->ptrValue[0];
                    ptrAuxV[1] = -1 * ptrAuxPont2->ptrValue[1];
                    setPoints(ptrAuxPont, ptrAuxV, 2);
                    ptrAuxV[1] *= -1;
                    setPoints(ptrAuxPontDel, ptrAuxV, 2);
                    ptrAuxPont2 = ptrAuxPont2->ptrProx;
                }
                ptrListFIG->getFig(vetN1)->setPtrListPoints(ptrAuxPont);
                Deleteline(ptrAuxPontDel, vetN1);
            }

            else if (vetO[0] == 'c')
            {

                Pontptr *ptrAuxPont = new Pontptr;
                Pontptr *ptrAuxPontDel = new Pontptr;
                ptrAuxPontDel->size = 0;
                Point *ptrAuxPont2;
                cout << "Escolha o vetor de cisalhamento" << endl;
                cin >> vetAux[0] >> vetAux[1];
                ptrAuxPont2 = ptrListFIG->getFig(vetN1)->getPontptr()->ptrInit;
                for (int i = 0; i < ptrListFIG->getFig(vetN1)->getPontptr()->size; i++)

                {
                    double *ptrAuxV = new double[2];

                    ptrAuxV[0] =  ptrAuxPont2->ptrValue[0];
                    ptrAuxV[1] =  ptrAuxPont2->ptrValue[1];
                    setPoints(ptrAuxPontDel, ptrAuxV, 2);

                    ptrAuxV[0] = vetAux[0] * ptrAuxPont2->ptrValue[1] + ptrAuxPont2->ptrValue[0];
                    ptrAuxV[1] = vetAux[1] * ptrAuxPont2->ptrValue[0] + ptrAuxPont2->ptrValue[1];
                    setPoints(ptrAuxPont, ptrAuxV, 2);
                    ptrAuxPont2 = ptrAuxPont2->ptrProx;
                }
                ptrListFIG->getFig(vetN1)->setPtrListPoints(ptrAuxPont);
                Deleteline(ptrAuxPontDel, vetN1);
            }

            operacao(ptrListFIG->getFig(vetN1), vetAux, vetO[0]);
        }
        else if (ptrEntrada[0] == 'd')
        {
            //cout << ptrAuxFig->getPontptr()->ptrEnd->ptrValue[0] << " " << ptrAuxFig->getPontptr()->ptrEnd->ptrValue[1] << endl;
            //  cout << ptrListFIG->getFig()->getName() << " " << ptrListFIG->getSize() << " " << ptrListFIG->getFig()->getPontptr()->ptrEnd->ptrValue[1] << endl;

            char vetN[2];
            cout << "Digite o nome da Fig a ser deletada" << endl;
            cin >> vetN;
            //Deleteline(ptrListFIG->getFig(vetN)->getPontptr(),vetN);
            DeleteF(ptrListFIG->getFig(vetN));
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
