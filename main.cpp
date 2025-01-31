#include <iostream>
#include <stack>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Point{
    int x, y;
};

// Un punto global para ordenar los puntos con referencia al primer punto usado en el método qsort()
Point p0;

// Función utilizada para encontrar el punto superior en el stack
// Complejidad en el tiempo: O(1)
Point point_in_top(stack<Point> & S){
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// Función para intercambiar dos puntos
// Complejidad en el tiempo: O(1)
void swap(Point &p1, Point &p2){
    Point temp = p1;
    p1 = p2;
    p2 = temp;

}

// Función para devolver el cuadrado de la distancia entre p1 y p2
// Complejidad en el tiempo: O(1)
int square_distance(Point p1, Point p2){
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

/**
* Para encontrar la orientación del triplete ordenado (p, q, r).
* Se regresan los siguientes valores 
* 0, si p,q son colineales
* 1, sentido horario
* 2, sentido antihorario
* Complejidad en el tiempo: O(1)
 */
 int orientation(Point p, Point q, Point r){
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    // colineal
    if (val == 0){
        return 0; 
    }
    // horario o antihorario
    return (val > 0) ? 1: 2; 
 }

 // Función para ordenar una matriz de puntos con respecto al primer punto
 // Complejidad en el tiempo: O(1) por comparación
 int compare(const void *vp1, const void *vp2){
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // Buscar la orientación
    int ori = orientation(p0, *p1, *p2);
    if (ori == 0){
        return (square_distance(p0, *p2) >= square_distance(p0, *p1)) ? -1 : 1;
    }
    return (ori == 2) ? -1: 1;
 }

 // Imprime el casco convexo de un set de n puntos
 /**
 * Complejidad en el tiempo:
 * Encontrar el punto más bajo: O(n)
 * Ordenar los puntos por angulo polar: O(n Log n)
 * Escanear y hacer el casco convexo: O(n)
 * Complejidad en el tiempo: O(n Log n)
  */
 void convex_hull(Point points[], int n){

     // Se encuentra el punto más bajo
     int ymin = points[0].y, min = 0;
     for (int i=1; i < n; i++){
        int y = points[i].y;

        // Se elije el punto más bajo o el más a la izquierda en caso de empate
        if (( y < ymin ) || (ymin == y && points[i].x < points[min].x)){
            ymin = points[i].y, min = i;
            }

     }


     // Se coloca el punto más bajo en la primera posición
     swap(points[0], points[min]);

     /**
     * Se ordenan n-1 puntos con respecto a la primera posición. Un punto p1 viene antes de p2 en la salida ordenada si p2 tiene un
     * angulo polar más grande (en dirección sentido antihorario) que p1.
      */
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);

    /**
    * Si dos o más puntos hacen el mismo angulo con p0, se quitan todas menos la que este más alejada de p0. Se busca mantener el 
    * punto más alejado al final cuando más de un punto tiene el mismo angulo.
     */
    int m = 1; // Se inicializa el tamaño del array modificado
    for (int i=1; i < n; i++){

        // Se avanza en i mientras el angulo de i con i+1 sea el mismo con respecto a p0
        while( i < n-1 && orientation(p0, points[i], points[i + 1]) == 0){
            i++;
        }
        points[m] = points[i];
        m++; // Se actualiza el tamaño del array
    }

    // Si el array modificado de puntos tiene menos de 3, no es posible un casco convexo
    if ( m < 3) return;

    // Se crea un empty stack y se pushean los primeros tres puntos
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Se procesan los n-3 puntos restantes
    for (int i=3; i < m; i++){

        // Se quita el de hasta arriba mientras el angulo formado por los puntos point_in_top, top y points[i] haga un giro que no
        // sea a la izquierda
        while (S.size() > 1 && orientation(point_in_top(S), S.top(), points[i]) != 2){
            S.pop();
        }
        S.push(points[i]);
    }

    // Se imprimen los puntos de salida
    vector<Point> arr;
    while (!S.empty()){
        arr.push_back(S.top());
        S.pop();
    }

    for (int i = arr.size() - 1; i >= 0; i--){
        cout << arr[i].x  << " "<< arr[i].y << endl;
    }
 }

// Función main para echar a andar el algoritmo de Graham's Scan
// Complejidad en el tiempo: O(n Log n) por el ordenamiento de los puntos
 int main(){
    int n;
    cout << "Dame el número de n puntos (vértices): ";
    cin >> n;

    Point *points = new Point[n];

    cout << "Ingresa los puntos (vértices) en el formato (x y): " << endl;
    for (int i = 0; i < n; i++){
        cin >> points[i].x >> points[i].y;
    }
    cout << "Salida: " << endl;
    convex_hull(points, n);
    delete[] points;
    return 0;

 }
 