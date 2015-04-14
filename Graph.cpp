#include "Graph.h"
#include <vector>
#include <queue>
#include <iostream>
#include <climits>

using namespace std;

Graph::Graph()
{
    n = 0;
}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].distID<<":";
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(j<vertices[i].adj.size()-1)
            {
                cout<<vertices[i].adj[j].v->name<<"***";
            }
            else
                cout<<vertices[i].adj[j].v->name;
        }
        cout<<endl;
    }

}

void Graph::BFTraversal(string startingCity) {
    queue<vertex*> bfq;
    vertex v;
    int i = 0;
    for(i=0; i<vertices.size();i++) {
        if (startingCity==vertices[i].name) {
            v = vertices[i];
            break;
        }
    }
    //cout<<v.name<<endl;
    vertices[i].visited = true;
    if(vertices[i].distID == -1)
    {
        n++;
        vertices[i].distID = n;
        bfq.push(&vertices[i]);

        while (!bfq.empty()) {
            v = *bfq.front();
            bfq.pop();
            for(i=0;i<v.adj.size();i++) {
                if (v.adj[i].v->visited==false) {
                    v.adj[i].v->visited = true;
                    bfq.push(v.adj[i].v);
                    //cout<<v.adj[i].v->name<<endl;
                    v.adj[i].v->distID = n;
                }
            }
        }
    }

}


void Graph::BFSearch(string startCity, string finCity)
{
    bool flag = 0;
    queue<vertex*> bfq;
    vector<string> path;
    vertex v;
    vertex destination;
    int i = 0;
    bool flgDest=0;
    bool strtFlg=0;
    for(int j=0; j<vertices.size(); j++)
    {
        vertices[j].visited = false;
    }

    for(i=0; i<vertices.size();i++) {
        if (startCity==vertices[i].name) {
            v = vertices[i];
            strtFlg = 1;
            break;
        }
    }

    for(int z=0; z<vertices.size();z++) {
        if (finCity==vertices[z].name) {
            destination = vertices[z];
            flgDest=1;
            break;
        }
    }

    if(flgDest && v.distID == -1 && strtFlg){
      cout<<"Please identify the districts before checking distances"<<endl;
      return;
     }
     if(!strtFlg || !flgDest){
      cout<<"One or more cities doesn\'t exist"<<endl;
      return;
     }
     //cout<<v.distID<<" "<<v.name<<endl;
     //cout<<destination.distID<<" "<<destination.name<<endl;
     if(v.distID != destination.distID){
      cout<<"No safe path between cities"<<endl;
      return;
     }

    v.visited = true;

    bfq.push(&vertices[i]);
    path.push_back(v.name);

    while (!bfq.empty() && flag == 0) {
        v = *bfq.front();
        bfq.pop();
        for(i=0;i<v.adj.size();i++) {
            if (v.adj[i].v->visited==false) {
                if(v.adj[i].v->name == finCity)
                {
                    flag = 1;
                    path.push_back(v.adj[i].v->name);
                    break;
                }
                else
                {
                    v.adj[i].v->visited = true;
                    bfq.push(v.adj[i].v);

                    path.push_back(v.adj[i].v->name);
                }

            }
        }
    }


    cout<<path.size()-1;
    for(int k=0; k<path.size(); k++)
    {
        cout<<","<<path[k];
    }
    cout<<endl;



    //My Failed, pathetic attempt
    /*for(int i=1; i<15; i++)
    {
        vertices[i].visited = false;
    }
    vertices[0].visited = true;
    qVertex qv;
    qv.dist = 0;
    qv.path[0] = &vertices[0];

    vector<qVertex> que;
    que.push_back(qv);
    vector<vertex*> dumbPath;
    int dumbDist;

    //while Q not empty
    while(!que.empty())
    {
        qv = que.back();
        //for each adjacent vertex on the last vertex of path...
        for(int j=0; j<qv.path.back()->adj.size(); j++)
        {
            if(qv.path.back()->adj[j].v->visited == false)
             {
                dumbPath = qv.path;
                qv.path.back()->adj[j].v->visited = true;
                dumbDist = qv.dist + 1;
                dumbPath.push_back(qv.path.back()->adj[j].v);
                qVertex temp;
                temp.path = dumbPath;
                temp.dist = dumbDist;
                if(qv.path.back()->adj[j].v->name == finCity)
                {
                    cout<<temp.dist;
                }
                else
                {
                    que.push_back(temp);
                }
            }
        }
    }
    cout<<"it didn't work"<<endl;*/
}


void Graph::shortDistance(string starting, string destination)
{
    bool flgDest=0;
    bool strtFlg=0;
    int i=0;
    vertex v;
    vertex destined;

    for(i=0; i<vertices.size();i++) {
        if (starting==vertices[i].name) {
            v = vertices[i];
            strtFlg = 1;
            break;
        }
    }

    for(int z=0; z<vertices.size();z++) {
        if (destination==vertices[z].name) {
            destined = vertices[z];
            flgDest=1;
            break;
        }
    }

    if(flgDest && v.distID == -1 && strtFlg){
      cout<<"Please identify the districts before checking distances"<<endl;
      return;
     }
     if(!strtFlg || !flgDest){
      cout<<"One or more cities doesn\'t exist"<<endl;
      return;
     }
     //cout<<v.distID<<" "<<v.name<<endl;
     //cout<<destined.distID<<" "<<destined.name<<endl;
     if(v.distID != destined.distID){
      cout<<"No safe path between cities"<<endl;
      return;
     }

    for(int i=0; i<vertices.size(); i++)
    {
        vertices[i].visited = false;
        vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;
    }

    vector<vertex*> solved;
    vertex* s = new vertex; //starting
    vertex* d = new vertex; //destination
    //Find 's'
    for(int j=0; j<vertices.size(); j++)
    {
        if(vertices[j].name == starting)
        {
            s = &vertices[j];
        }
        if(vertices[j].name == destination)
        {
            d = &vertices[j];
        }
    }

    s->visited = true;
    s->distance = 0;
    solved.push_back(s);
    int dist = 0;
    int minDist = 0;
    vertex* minVertex;
    vertex* minPrev;
    //Find 'd' which equals vertices[k]

    while(d->visited == false)
    {
        minDist = INT_MAX;
        //for each u in solved:
        for(int l=0; l<solved.size(); l++)
        {
            for(int k=0; k<solved[l]->adj.size(); k++)
            {
                if(solved[l]->adj[k].v->visited == false)
                {
                    dist = solved[l]->distance + solved[l]->adj[k].weight;
                    if(dist < minDist)
                    {
                        solved[l]->adj[k].v->distance = dist;
                        minDist = dist;
                        minVertex = solved[l]->adj[k].v;
                        minPrev = solved[l];
                    }
                }
            }
        }
        //update solved and add minVertex
        minVertex->previous = minPrev;
        solved.push_back(minVertex);
        minVertex->visited = true;
    }

    /*cout<<"Shortest Path"<<endl;


    */
    cout<<minDist<<",";
    vector<string> path;
    vertex* xing = d;

    while(xing != NULL)
    {
        path.push_back(xing->name);
        xing=xing->previous;
    }

    int z = path.size()-1;
    //print current location deal (path deal is backwards)
    cout<<path[z];
    for(int y=z-1; y>=0; y--)
    {
        cout<<","<<path[y];
    }
    cout<<endl;

}
