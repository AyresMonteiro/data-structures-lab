#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

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

bool consegue_chegar(vector<vector<int>> lista, int v_inicial, int v_final)
{
    queue<int> auxiliar;

    int visitados[lista.size()] = {false};

    auxiliar.push(v_inicial);
    visitados[v_inicial] = true;

    while (!auxiliar.empty())
    {
        int atual = auxiliar.front();

        if (atual == v_final)
        {
            return true;
        }

        auxiliar.pop();

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

    return false;
}

bool eh_conexo(vector<vector<int>> lista)
{
    int n_vertices = lista.size();

    vector<bool> checados(n_vertices, false);

    for (int i = 0; i < n_vertices; i++)
    {
        for (int j = 0; j < n_vertices; j++)
        {
            if (!checados[j])
            {
                if (!consegue_chegar(lista, i, j))
                {
                    return false;
                }
            }
        }

        checados[i] = true;
    }

    return true;
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

    bool direcionado = false;

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

    cout << "O grafo em questao eh conexo? " << (eh_conexo(lista_adj) ? "Sim" : "Nao") << endl;

    int arestas_s_c[][2] = {
        {0, 1},
        {0, 2},
        {2, 5},
        {4, 3},
        {3, 6}};

    int
        v_s_c = conta_vertices(
            arestas_s_c,
            sizeof(arestas_s_c) / sizeof(int) / 2),
        a_s_c = 0;

    int direcionado_s_c = false;

    cout << endl
         << endl;

    if (direcionado_s_c)
    {
        cout << ">>> Grafo direcionado <<<" << endl;
    }
    else
    {
        cout << ">>> Grafo nao direcionado <<<" << endl;
    }

    vector<vector<int>> lista_adj_s_c(V, vector<int>());

    int tam_cj_arestas_s_c = sizeof(arestas_s_c) / sizeof(int) / 2;

    cout << "\nTamanho do conjunto de arestas (segundo conjunto): " << tam_cj_arestas_s_c << endl;
    cout << "Arestas (segundo conjunto): ";

    for (int i = 0; i < tam_cj_arestas_s_c; i++)
    {
        cout << arestas_s_c[i][0] << "-" << arestas_s_c[i][1] << " ";
        lista_adj_s_c[arestas_s_c[i][0]].push_back(arestas_s_c[i][1]);

        a_s_c++;

        if (!direcionado)
        {
            lista_adj_s_c[arestas_s_c[i][1]].push_back(arestas_s_c[i][0]);
            a_s_c++;
        }
    }

    cout << "\nNumero de arestas (segundo conjunto): " << a_s_c << endl
         << endl;

    cout << endl;
    for (int v = 0; v < V; v++)
    {
        cout << v << ": ";

        for (int i = 0; i < lista_adj_s_c[v].size(); i++)
        {
            cout << lista_adj_s_c[v][i] << " ";
        }

        cout << endl;
    }

    cout << endl
         << "O grafo em questao eh conexo? " << (eh_conexo(lista_adj_s_c) ? "Sim" : "Nao") << endl;

    cout << endl
         << endl;

    return 0;
}