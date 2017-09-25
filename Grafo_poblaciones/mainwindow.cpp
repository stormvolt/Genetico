#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::graphicsNode(int tam,int size) //tam es el numero de nodos
{
    int matrix[2]={size,size};
    g =new Graph(matrix);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush redBrush(Qt::yellow);
    QPen outlinePen(Qt::black);

    g->randomInsert(scene,redBrush,outlinePen,tam);

    /* AQUI EMPIEZA LA PARTE DEL ALGORITMO GENETICO */
    int punto_a[2]; //punto para los search node
    int punto_b[2]; //punto para los search node
    int punto_inicio[2]; //primer punto del recorrido
    ios_base::sync_with_stdio(true);//incializamos el random
    srand ( unsigned ( time(0) ) );
    vector<Point> points;
    /** Leemos el grafo **/
    int x, y;
    for(int i=0; i < g->nStatic.size(); i++)
    {
        x = g->nStatic[i]->coord[0];
        y = g->nStatic[i]->coord[1];
        points.push_back( Point(x,y) );
    }
    vector<Point> result = ga_tsp( points );

    punto_inicio[0] = result[0].x; //guardamos el primer punto del camino
    punto_inicio[1] = result[0].y;

    for(int i = 0; i < result.size()-1; i++)
    {
        punto_a[0] = result[i].x;
        punto_a[1] = result[i].y;
        punto_b[0] = result[i+1].x;
        punto_b[1] = result[i+1].y;
        g->insertEdge(0, punto_a, punto_b); //insertamos aristas de la solucion
        //Dibujamos la arista
        scene->addLine(punto_a[1]*10,punto_a[0]*10,
                       punto_b[1]*10,punto_b[0]*10,
                       outlinePen);

    }
    //Cerramos el camino
    g->insertEdge(0, punto_b, punto_inicio);
    scene->addLine(punto_b[1]*10,punto_b[0]*10,
                   punto_inicio[1]*10,punto_inicio[0]*10,
                   outlinePen);

    /* AQUI TERMINA LA PARTE DEL ALGORITMO GENETICO */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString n,tam;
    n=ui->n_nodes->text();
    tam=ui->n_tam->text();
    graphicsNode(n.toInt(),tam.toInt());
}
