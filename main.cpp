#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//ALGORITMO KRUSKAL CON LA ESTRUCTURA DE UNION-FIND O DISJOINT SET UNION(DSU)
class SolutionSix{
private:
    struct Edge{
        //origen, destino, peso, indice original
        int src, dst, wt, serial;
        Edge(int s, int d, int w, int n){
            src=s;
            dst=d;
            wt=w;
            serial=n;
        }
    };

    vector<int> par;
    vector<int> rank;
    //PATH COMPRESSION
    void initialize(int n){
        par=vector<int>(n); //representates lideres de cada grupo
        rank=vector<int>(n);//posicion de los conjuntos
        for(int i=0; i<n; i++){
            par[i]=i;
            rank[i]=0;
        }
    }

    void unionn(int x, int y){
        int x_rep=find(x), y_rep=find(y);
        if(x_rep==y_rep) return;
        if(rank[x_rep] < rank[y_rep]) par[x_rep]=y_rep;
        else if(rank[x_rep] > rank[y_rep]) par[y_rep]=x_rep;
        else{
            par[y_rep]=x_rep;
            rank[x_rep]++;
        }
    }

    int find(int x){ //donde cada nodo es su propio representante inicialmente
        if(x==par[x]) return x;
        par[x]=find(par[x]);
        return par[x];
    }

    //DSU IMPLEMENTATION
    vector<Edge> edge;
    static bool myCmp(Edge& e1, Edge& e2){
        return e1.wt < e2.wt;
    }

    int findMSTWt(int n, int m, int include, int exclude){
        int ret=0;
        initialize(n);
        int i, s=0;
        if(include != -1){
            Edge e=edge[include];
            unionn(e.src, e.dst);
            ret+=e.wt;
            s++;
        }
        //FINDING MST USING KRUSKAL'S ALGORITHM
        for(int i=0; s<n-1 and i<m; i++){
            if(i==exclude) continue;
            Edge e=edge[i];
            int x=find(e.src);
            int y=find(e.dst);
            if(x!=y){
                ret+=e.wt;
                unionn(x,y);
                s++;
            }
        }
        if(s<n-1) ret = 1e8;
        return ret;
    }
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        //USING KRUSKAL'S ALGORITHM
        int m=edges.size();
        for(int i=0; i<m; i++){
            //primer nodo, segundo nodo, peso, posicion 
            Edge e(edges[i][0], edges[i][1], edges[i][2], i);
            edge.push_back(e);
        }
        //ordenamiento bajo el criterio de myCmp
        sort(edge.begin(), edge.end(), myCmp);
        vector<vector<int>> ans(2);

        int mn=findMSTWt(n, m, -1, -1);
        for(int i=0; i<m; i++){
            int curr1=findMSTWt(n, m, -1, i);
            if(curr1>mn){
                ans[0].push_back(edge[i].serial);
                continue;
            }
            int curr2=findMSTWt(n, m, i, -1);
            if(curr2==mn) ans[1].push_back(edge[i].serial);
        }
        return ans;
    }
};

int main(){
    return 0;
}