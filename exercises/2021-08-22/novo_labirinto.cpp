#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

typedef struct Point
{
	int x, y;
} Point;

using namespace std;

void imprimir_matriz(vector<vector<int>> matriz)
{
	for (int i = 0; i < matriz.size(); i++)
	{
		for (int j = 0; j < matriz[0].size(); j++)
		{
			cout << matriz[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void imprimir_matriz(vector<vector<char>> matriz)
{
	for (int i = 0; i < matriz.size(); i++)
	{
		for (int j = 0; j < matriz[0].size(); j++)
		{
			cout << matriz[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<int>> ler(string nome_do_arquivo)
{
	int linhas = 0, contador_de_barra_n;
	char c;
	ifstream file(nome_do_arquivo, ifstream::in);

	while (!file.eof())
	{
		file.get(c);

		if (c == '\n' && contador_de_barra_n == 0)
		{
			linhas++;
			contador_de_barra_n++;
		}
		else
		{
			contador_de_barra_n = 0;
		}
	}

	file.clear();
	file.seekg(0);

	vector<vector<int>> matriz(linhas, vector<int>(linhas, -1));

	for (int i = 0; i < linhas && file.good(); i++)
	{
		for (int j = 0; j < linhas && file.good(); j++)
		{
			file.get(c);

			if (c != '#')
			{
				matriz[i][j] = 0;
			}
		}

		// capturando \n
		file.get();
	}

	file.close();

	return matriz;
}

vector<Point> pontos_adjacentes(const Point &p, vector<vector<int>> &labirinto)
{
	int m = labirinto.size(), n = labirinto[0].size();
	vector<Point> adjacentes;

	// Se a coordenada y - 1 não está fora dos limites e não é uma parede (-1),
	// adicione-a ao vetor
	if (!(p.y - 1 < 0) && labirinto[p.y - 1][p.x] != -1)
	{
		adjacentes.push_back({x : p.x, y : p.y - 1});
	}

	// Se a coordenada y + 1 não está fora dos limites e não é uma parede (-1),
	// adicione-a ao vetor
	if (!(p.y + 1 >= m) && labirinto[p.y + 1][p.x] != -1)
	{
		adjacentes.push_back({x : p.x, y : p.y + 1});
	}

	// Se a coordenada x - 1 não está fora dos limites e não é uma parede (-1),
	// adicione-a ao vetor
	if (!(p.x - 1 < 0) && labirinto[p.y][p.x - 1] != -1)
	{
		adjacentes.push_back({x : p.x - 1, y : p.y});
	}

	// Se a coordenada x + 1 não está fora dos limites e não é uma parede (-1),
	// adicione-a ao vetor
	if (!(p.x + 1 >= n) && labirinto[p.y][p.x + 1] != -1)
	{
		adjacentes.push_back({x : p.x + 1, y : p.y});
	}

	return adjacentes;
};

void anotar(vector<vector<int>> &labirinto)
{
	queue<Point> fila;

	fila.push({x : 0, y : 1});

	// "Abre" a posição inicial
	labirinto[1][0] = 0;

	while (!fila.empty())
	{
		Point p = fila.front();
		int valor_do_ponto = labirinto[p.y][p.x];

		vector<Point> pontos = pontos_adjacentes(p, labirinto);

		for (int i = 0; i < pontos.size(); i++)
		{
			if (labirinto[pontos[i].y][pontos[i].x] == 0)
			{
				labirinto[pontos[i].y][pontos[i].x] = valor_do_ponto + 1;

				fila.push({x : pontos[i].x, y : pontos[i].y});
			}
		}

		fila.pop();
	}

	// Marca a posição inicial como uma parede, "fechando" ela
	labirinto[1][0] = -1;
}

vector<vector<char>> extrair(vector<vector<int>> labirinto)
{
	stack<Point> pilha;
	int m = labirinto.size(), n = labirinto[0].size();

	// Inicializando matriz de caracteres
	vector<vector<char>> mapa_extraido(m, vector<char>(n, '#'));

	// Inserindo espaços vazios na matriz de caracteres
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (labirinto[i][j] != -1)
			{
				mapa_extraido[i][j] = ' ';
			}
		}
	}

	Point p = {x : n - 2, y : m - 2};

	pilha.push(p);

	while (!pilha.empty() && !(pilha.top().y == 1 && pilha.top().x == 1))
	{
		const Point ponto = pilha.top();

		vector<Point> adjacentes = pontos_adjacentes(pilha.top(), labirinto);

		Point menor = {x : ponto.x, y : ponto.y};

		for (int i = 0; i < adjacentes.size(); i++)
		{
			if (labirinto[adjacentes[i].y][adjacentes[i].x] < labirinto[menor.y][menor.x])
			{
				menor = {x : adjacentes[i].x, y : adjacentes[i].y};
			}
		}

		if (labirinto[menor.y][menor.x] < labirinto[ponto.y][ponto.x])
		{
			pilha.push(menor);
		}
		else
		{
			labirinto[ponto.y][ponto.x] += 1;
			pilha.pop();
		}
	}

	while (!pilha.empty())
	{
		mapa_extraido[pilha.top().y][pilha.top().x] = 'X';
		pilha.pop();
	}

	return mapa_extraido;
}

int main()
{
	string nome_do_arquivo;

	cout << "Digite o nome do arquivo: ";

	cin >> nome_do_arquivo;

	vector<vector<int>> l = ler(nome_do_arquivo);

	imprimir_matriz(l);
	anotar(l);
	imprimir_matriz(l);
	imprimir_matriz(extrair(l));
}
