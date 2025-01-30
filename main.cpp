#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point{
    int x, y;
};

// Un punto global para sortear los puntos con referencia al primer punto usado en el método qsort()
Point p0;

// Función utilizada para encontrar el punto superior en el stack
Point point_in_top(stack<Point> & S){
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// Función para intercambiar dos puntos
void swap(Point &p1, Point &p2){
    Point temp = p1;
    p1 = p2;
    p2 = temp;

}

// Función para devolver el cuadrado de la distancia entre p1 y p2
int square_distance(Point p1, Point p2){
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

/**
* Para encontrar la orientación del triplete ordenado (p, q, r).
* Se regresan los siguientes valores 
* 0, si p,q son colineales
* 1, sentido horario
* 2, sentido antihorario
 */
 int orientation(Point p, Point q, Point r){
    int val = (q.y . p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    // colineal
    if (val == 0){
        return 0; 
    }
    // horario o antihorario
    return (val > 0) ? 1: 2; 
 }
 