#include <vector>
using namespace std;

class Individuo
{
public:
    vector<*Node> cromosoma;
    double aptitud;

    Individuo()
    {
        aptitud = 0;
    }

    Individuo(vector<*Node> gen)
    {
        int distancia = 0; ///distancia euclidiana
        cromosoma = gen;
        aptitud = 0;
        for(int j=0; j+1<cromosoma.size(); j++)
        {
            distancia = abs(cromosoma[j]->coord[0]-cromosoma[j+1]->coord[0])+abs(cromosoma[j]->coord[1]-cromosoma[j+1]->coord[1])
            aptitud += distancia;
        }
    }

    Individuo mutacion()
    {
        int x,y; ///indices que se intercambian
        Node* temp;  ///temporal para el swap
        x = rand() % cromosoma.size;
        y = rand() % cromosoma.size;
        while(y==x) /// y debe ser diferente de x
        {
            y = rand() % cromosoma.size;
        }
        Individuo nuevo(cromosoma);
        temp = nuevo.cromosoma[x]; ///esas ciudades se intercambian
        nuevo.cromosoma[x] = nuevo.cromosoma[y];
        nuevo.cromosoma[y] = temp;
        return nuevo;
    }
};

class Poblacion
{
    vector<Individuo> individuos;
};


void iniciar(int num_ciu)
{
    vector<Individuo> poblacion;
}
