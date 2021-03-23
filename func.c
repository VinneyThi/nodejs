
#include <stdio.h>
#include "func.h"

void setPoints(Pontptr *ptrAux, void *ptrLoad, int space)
{
  if (!(ptrAux) || !ptrLoad)
    return;

  Point *ptrAuxPoint = (Point *)malloc(sizeof(Point));
  double *ptrAuxL = (double *)malloc(sizeof(Point) * space);
  for (int i = 0; i < space; i++)
  {
    double *ptrAuxTrade = (double *)ptrLoad;
    *(ptrAuxL + i) = ptrAuxTrade[i];
  }

  ptrAuxPoint->ptrValue = ptrAuxL;
  ptrAuxPoint->ptrProx = NULL;

  if (ptrAux->size == 0)
  {

    ptrAux->ptrInit = ptrAuxPoint;
    ptrAux->ptrEnd = ptrAuxPoint;
    ptrAux->size++;
  }
  else
  {

    ptrAux->ptrEnd->ptrProx = ptrAuxPoint;
    ptrAux->ptrEnd = ptrAuxPoint;
    ptrAux->size++;
  }
}

void showPoint(double *ptrAux)
{
  double *ptrAuxD = (double *)ptrAux;
  printf("Pont %f\n", ptrAuxD[1]);
}

Point *retornaPonto(Pontptr *ptrAux, int pos)
{

  if (!ptrAux || pos > ptrAux->size)
    return NULL;

  Point *ptrBusca = ptrAux->ptrInit;
  for (int i = 0; i < pos; i++)
    ptrBusca = ptrBusca->ptrProx;


  return ptrBusca;
}