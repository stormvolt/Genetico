#include "graph.h"

int distanciaEuclidiana(int *A, int *B){
    return abs(A[0]-B[0])+abs(A[1]-B[1]);
}

void printVectorNodo(vector<Node*>V){
    for(int x=0;x<V.size();x++){
        V[x]->printNode();
        cout<<" ";
    }
    cout<<endl;
}

Node*globalTemp;
/* Implementacion grafo */
Graph::Graph(int*tam){
    size[0]=tam[0];
    size[1]=tam[1];
    vector<vector<Node*> > A(tam[0], vector<Node*>(tam[1],NULL));
    nodes= A;
}

bool Graph::checkDimension(int*A,int*B){ //A es el tamaño de la matriz, y B es el tamaño a comprobar
    return (A[0]>B[0] and A[1]>B[1]);
}

void Graph::randomInsert(QGraphicsScene * scene,QBrush redBrush,QPen outlinePen,int total){
    int x,y;
    srand (time(NULL));
    for (int i = 0; i < total; i++) {
        x=rand() % size[0];
        y=rand() % size[1];
        int coord[2]={x,y};
        scene->addEllipse(coord[1]*len,coord[0]*len,10,10,outlinePen,redBrush);
        insertNode(coord);     
    }
    cout<<endl;
}

Node* Graph::searchNode(int *pos){
    Node* resp=NULL;
    if(checkDimension(size,pos))
        resp=nodes[pos[0]][pos[1]];
    return resp;
}

Edge* Graph::searchEdge(int *nA, int *nB){
    Edge* resp=NULL;
    Node* nodeA=searchNode(nA);
    Node* nodeB=searchNode(nB);
    if(nodeA!=NULL and nodeB!=NULL){
        resp=nodeA->shareEdge(nodeB);
    }
    return resp;
}

bool Graph::insertNode(int *posNode){
    int positionBase[2]={0,0};
    if(searchNode(posNode)==NULL){
        Node* tempNode=new Node(posNode);
        nodes[posNode[0]][posNode[1]]=tempNode;
        /* Insercion a nStatic ordenado*/
        Node* tempAnterior=NULL;
        int size=nStatic.size();
        if(size>0)
            tempAnterior=nStatic[nStatic.size()-1];
        while(size!=0 and distanciaEuclidiana(posNode,positionBase)<distanciaEuclidiana(tempAnterior->coord,positionBase)){
            size--;
            tempAnterior=nStatic[size-1];
        }

        nStatic.insert(nStatic.begin()+size,tempNode);
        /*Solo usado para cuadricular*/

        tempNode->printNode();
        return true;
    }
    return false;
}

bool Graph::insertEdge(int peso,int *nA, int *nB){
    Node* nodeA=searchNode(nA);
    Node* nodeB=searchNode(nB);
    if(nodeA!=NULL and nodeB!=NULL and nodeA->shareEdge(nodeB)==NULL and nodeA!=nodeB){
        Edge* tempEdge=new Edge(peso,nodeA,nodeB);
        nodeA->edges.push_back(tempEdge);
        nodeB->edges.push_back(tempEdge);
        return true;
    }
    else{

        return false;

    }
}
bool Graph::deleteEdge(int *nA, int *nB){
    Edge* edgeTemp;
    Node* nodeA=searchNode(nA);
    Node* nodeB=searchNode(nB);
    if(nodeA!=NULL and nodeB!=NULL){
        edgeTemp=nodeA->shareEdge(nodeB);
        if(edgeTemp!=NULL){
            edgeTemp->autoRemove();
            return true;
        }
        else
            return false;
    }
}

bool Graph::deleteNode(int *coordNode) { //Falta aun
    Node* temp=searchNode(coordNode);
    if(temp!=NULL){
        temp->deleteEdges();
        nodes[coordNode[0]][coordNode[1]]=NULL;
        delete(temp);
    }
}

void Graph::print() {
    for(int x=0;x<nodes.size();x++){
        cout<<x;
        if(x<10)
            cout<<":   ";
        if(x>=10 and x<100)
            cout<<":  ";
        if(x>=100)
            cout<<": ";

        for (int y = 0; y <nodes[0].size();y++) {
            Node*temp=nodes[x][y];
            if(temp!=NULL){
                cout<<"*";
            }
            else{
                cout<<"-";
            }
        }
        cout<<endl;
    }
}

void Graph::printStatic(){
    for(int x=0;x<nStatic.size();x++){
        nStatic[x]->printNode();
        if(nStatic[x]->edges.size()>0){
            cout<<"aristas: ";
            nStatic[x]->printEdges();
        }
        cout<<endl;
    }
}

void Graph::colorNode(QGraphicsScene *scene,QPen outlinePen, QBrush ini, QBrush fin, int *x, int *y)
{
    Node *inicio=searchNode(x);
    Node *final=searchNode(y);
    scene->addEllipse(inicio->coord[1]*len,inicio->coord[0]*len,10,10,outlinePen,ini);
    scene->addEllipse(final->coord[1]*len,final->coord[0]*len,10,10,outlinePen,fin);
}

void Graph::delVisit()
{
    for (int i = 0; i < nStatic.size(); i++) {
        nStatic[i]->visit=false;
    }
}

void Graph::delColor(QGraphicsScene * scene,QBrush redBrush,QPen outlinePen)
{
    for (int i = 0; i < nStatic.size(); i++) {
        scene->addEllipse(nStatic[i]->coord[1]*len,nStatic[i]->coord[0]*len,10,10,outlinePen,redBrush);
        for (int j = 0; j < nStatic[i]->edges.size();j++) {
            Node * belong=nStatic[i]->edges[j]->whoBelongEdge(nStatic[i]);
            scene->addLine(nStatic[i]->coord[1]*len,nStatic[i]->coord[0]*len,
                           belong->coord[1]*len,belong->coord[0]*len,
                           outlinePen);
        }
    }
}
