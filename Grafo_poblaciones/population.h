#ifndef POPULATION_H
#define POPULATION_H
#include "point.h"

struct Population
{
private:
    vector<Point> &points;
    vector<vector<int> > routes;
    vector<double> prob;
    int n; // size of the route

public:
    /** Destructor **/
    ~Population();

    /** Constructores **/
    Population(vector<Point> &_points);
    Population(int routeSize, vector<Point> &_points);
    Population(int popuSize, int routeSize, vector<Point> &_points);

    vector<vector<int> > getRoutes() const;
    int getRouteSize() const;
    vector<double> getProb() const;
    void operator=(const Population& pob);

    // OX1 tipo crossover
    void crossover(vector<int> &p1, vector<int> &p2,vector<int> &h1, vector<int> &h2);

    Population evolve();

    /**  Esta es la distancia total de i-ésimo cromosoma **/
    double getNoFitness(int);

    void order();
    void addRoute(vector<int> &nRuta);
    int getSize();

    /** Tienes que ordenar antes de llamar a este metodo **/
    vector<Point> getFirst();

    vector<int> getFirstIndexes();
    Point getPoint(int);
};

/** Algoritmo genetico **/
vector<Point> ga_tsp(vector<Point> &points);

#endif // POPULATION_H
