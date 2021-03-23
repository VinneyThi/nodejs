 #define _func_H
 #ifndef _func_H
 #endif




 typedef struct Point
{
 struct Point *ptrProx;
  double *ptrValue;
}Point;


 typedef struct Pontptr
{
  Point *ptrInit;
    Point *ptrEnd;
    int size;
  
}Pontptr;


void quadrado(void *ptrPoints);

void setPoints(Pontptr *ptrAux, void *ptrLoad, int space);

void showPoint(double *ptrAux);


Point *retornaPonto(Pontptr *ptrAux, int pos);





