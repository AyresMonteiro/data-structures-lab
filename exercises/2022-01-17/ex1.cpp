// [2,5 pontos] Implementar uma função que, dada a lista de adjacências de um
// grafo e um vértice inicial, gere uma numeração com o nível dos vértices na
// busca em largura, conforme exemplo a seguir. O nível de um vértice pode ser
// pensado como a distância do respectivo vértice para o vértice que originou a
// busca, ou seja, o caminho com o menor número de arestas entre os dois
// vértices. No exemplo do grafo acima, considerando que o vértice inicial seja
// o vértice 0 (portanto estando no nível 0), temos a seguinte rotulação dos
// níveis de cada vértice: 0 (0), 1 (2), 2 (3), 3 (1), 4 (1), 5 (2) onde i (j)
// representa o vértice i visitado e o nível j do vértice. Faça um programa para
// testar a função partindo de cada vértice.

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct Numeracao
{
	int first, second;
} Numeracao;

typedef struct Adjacencia
{
	int indice, linhas;
} Adjacencia;

typedef queue<Adjacencia> Adjacencias;
typedef vector<Adjacencias> ListaDeAdjacencias;
typedef vector<Numeracao> Numeracoes;
typedef vector<bool> ListaDeVisitas;

void imprimirAdj(Adjacencias adj)
{
	while (!adj.empty())
	{
		cout << adj.front().indice << " ";

		adj.pop();
	}

	cout << endl;
}

Numeracoes extrairNumeracoes(
	ListaDeAdjacencias lista,
	ListaDeVisitas visitas,
	int verticeInicial)
{
	Numeracoes numeracoes;

	numeracoes.push_back({first : verticeInicial, second : 0});

	visitas[verticeInicial] = true;

	Adjacencias adjacencias = lista[verticeInicial];
	Adjacencias novasAdjacencias;

	while (!(novasAdjacencias.empty() && adjacencias.empty()))
	{
		while (!adjacencias.empty())
		{
			Adjacencia atual = adjacencias.front();

			visitas[atual.indice] = true;
			numeracoes.push_back({first : atual.indice, second : atual.linhas});

			Adjacencias maisAdjacencias = lista[atual.indice];

			while (!maisAdjacencias.empty())
			{
				Adjacencia atualDiferente = maisAdjacencias.front();

				if (!visitas[atualDiferente.indice])
				{
					atualDiferente.linhas = atual.linhas + 1;
					novasAdjacencias.push(atualDiferente);
				}

				maisAdjacencias.pop();
			}

			adjacencias.pop();
		}

		novasAdjacencias.swap(adjacencias);
	}

	return numeracoes;
}

int main()
{
	ListaDeAdjacencias lista;

	Adjacencias adj1;

	adj1.push({indice : 3, linhas : 1});
	adj1.push({indice : 4, linhas : 1});

	lista.push_back(adj1);

	Adjacencias adj2;

	adj2.push({indice : 2, linhas : 1});
	adj2.push({indice : 4, linhas : 1});

	lista.push_back(adj2);

	Adjacencias adj3;

	adj3.push({indice : 1, linhas : 1});
	adj3.push({indice : 5, linhas : 1});

	lista.push_back(adj3);

	Adjacencias adj4;

	adj4.push({indice : 0, linhas : 1});

	lista.push_back(adj4);

	Adjacencias adj5;

	adj5.push({indice : 0, linhas : 1});
	adj5.push({indice : 1, linhas : 1});
	adj5.push({indice : 5, linhas : 1});

	lista.push_back(adj5);

	Adjacencias adj6;

	adj6.push({indice : 2, linhas : 1});
	adj6.push({indice : 4, linhas : 1});

	lista.push_back(adj6);

	ListaDeVisitas visitas(6, false);
	Numeracoes extraidas = extrairNumeracoes(lista, visitas, 0);

	for (Numeracao extraida : extraidas)
	{
		cout << extraida.first << ": " << extraida.second << endl;
	}

	return 0;
}
