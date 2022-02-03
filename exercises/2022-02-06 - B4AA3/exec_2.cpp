#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

#define N_VERTICES 7 // 0 1 2 3 4 5 6
#define DIR false

// busca em profundidade recursiva
void dfs(vector<vector<int>> lista, bool visitados[], int u)
{
    if (visitados[u])
    {
        return;
    }

    visitados[u] = true;

    cout << u << " ";

    for (auto v : lista[u])
    {
        if (!visitados[v])
        {
            dfs(lista, visitados, v);
        }
    }
}

int conta_vertices(int arestas[][2], int tamanho)
{
    map<int, bool> vertices;

    for (int i = 0; i < tamanho; i++)
    {
        if (vertices.find(arestas[i][0]) == vertices.end())
        {
            vertices.insert(pair<int, bool>(arestas[i][0], true));
        }

        if (vertices.find(arestas[i][1]) == vertices.end())
        {
            vertices.insert(pair<int, bool>(arestas[i][1], true));
        }
    }

    return vertices.size();
}

void busca_profundidade(vector<vector<int>> lista, int v)
{
    stack<int> auxiliar;
    int visitados[lista.size()] = {false};

    auxiliar.push(v);
    visitados[v] = true;

    while (!auxiliar.empty())
    {
        int atual = auxiliar.top();
        auxiliar.pop();

        cout << atual << " ";

        for (int i = 0; i < lista[atual].size(); i++)
        {
            int vizinho = lista[atual][i];

            if (!visitados[vizinho])
            {
                visitados[vizinho] = true;
                auxiliar.push(vizinho);
            }
        }
    }
}

void busca_largura(vector<vector<int>> lista, int v)
{
    queue<int> auxiliar;
    int visitados[lista.size()] = {false};

    auxiliar.push(v);
    visitados[v] = true;

    while (!auxiliar.empty())
    {
        int atual = auxiliar.front();

        auxiliar.pop();

        cout << atual << " ";
        for (int i = 0; i < lista[atual].size(); i++)
        {
            int vizinho = lista[atual][i];

            if (!visitados[vizinho])
            {
                visitados[vizinho] = true;
                auxiliar.push(vizinho);
            }
        }
    }
}

int main()
{
    // Conjunto de arestas
    int arestas[][2] = {
        {0, 1},
        {0, 3},
        {1, 2},
        {2, 3},
        {2, 5},
        {3, 4},
        {4, 0},
        {4, 5},
        {4, 6},
        {5, 3},
        {6, 2}};

    int V = conta_vertices(arestas, sizeof(arestas) / sizeof(int) / 2), A = 0;

    bool direcionado = DIR;

    cout << endl;
    if (direcionado)
    {
        cout << ">>> Grafo direcionado <<<" << endl;
    }
    else
    {
        cout << ">>> Grafo nao direcionado <<<" << endl;
    }

    vector<vector<int>> lista_adj(V, vector<int>());

    int tam_cj_arestas = sizeof(arestas) / sizeof(int) / 2;

    cout << "\nTamanho do conjunto de arestas: " << tam_cj_arestas << endl;
    cout << "Arestas: ";

    for (int i = 0; i < tam_cj_arestas; i++)
    {
        cout << arestas[i][0] << "-" << arestas[i][1] << " ";
        lista_adj[arestas[i][0]].push_back(arestas[i][1]);

        A++;

        if (!direcionado)
        {
            lista_adj[arestas[i][1]].push_back(arestas[i][0]);
            A++;
        }
    }

    cout << "\nNumero de arestas: " << A << endl
         << endl;

    cout << endl;
    for (int v = 0; v < V; v++)
    {
        cout << v << ": ";

        for (int i = 0; i < lista_adj[v].size(); i++)
        {
            cout << lista_adj[v][i] << " ";
        }

        cout << endl;
    }

    cout << endl
         << endl;
    cout << "Busca em largura\n";
    busca_largura(lista_adj, 0);

    cout << endl
         << endl;
    cout << "Busca em profundidade\n";
    busca_profundidade(lista_adj, 0);

    cout << endl
         << endl;
    cout << "Busca em profundidade (recursiva)\n";

    bool visitados[V] = {false};

    dfs(lista_adj, visitados, 0);

    cout << endl
         << endl;

    return 0;
}