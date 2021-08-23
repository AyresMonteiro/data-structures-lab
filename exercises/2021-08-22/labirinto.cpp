#include <iostream>
#include <fstream>
#include <exception>
#include <queue>
#include <stack>

#define MY_FILENAME_SIZE 80

typedef struct point {
	int x;
	int y;
} point;

using namespace std;

// Essa função lida com todo o processo de leitura de arquivo e
// retorna um ponteiro de caractere.
char * getContentFromFile (ifstream& file) {
	char * content = NULL;
	try {
		if (!file.is_open()) {
			cerr << "File is not open." << endl;
			return NULL;
		}

		// Ajusta o ponteiro interno do objeto para a posição
		// 0 a partir do fim do arquivo. (Logo, o coloca na
		// última posição.
		file.seekg(0, file.end);

		// Obtém o tamanho do conteúdo do arquivo a partir da
		// posição 0 até a posição do ponteiro interno do
		// objeto.
		int sizeOfContent = file.tellg();

		// Move o ponteiro interno do objeto para o início do
		// arquivo novamente.
		file.seekg(0, file.beg);

		// Não executa o processo de leitura se o tamanho do
		// arquivo for 0.
		if (sizeOfContent == 0) {
			cerr << "File is empty." << endl;
			return NULL;
		}

		// Abaixo temos o processo de leitura.

		content = new char [sizeOfContent + 1];

		file.read(content, sizeOfContent);

		content[sizeOfContent] = '\0';

		return content;
	} catch (exception e) {
		if(file.is_open()) {
			file.close();
		}

		if(content != NULL) delete[] content;

		cerr << "Error while reading file." << endl;

		return NULL;
	}
}

// Eu realmente cansei de fazer comentários. Espero que você saiba inglês,
// porque o código por si só já diz muito.
int ** generateMatrix(int matrixSize) {	
	int ** matrix = (int**) malloc(sizeof(int*) * matrixSize);

	int matrixRowController;

	for (matrixRowController = 0; matrixRowController < matrixSize; matrixRowController++) {
		matrix[matrixRowController] = (int *) malloc(sizeof(int) * matrixSize);

		int matrixColumnController;

		for(matrixColumnController = 0; matrixColumnController < matrixSize; matrixColumnController++) {
			matrix[matrixRowController][matrixColumnController] = 0;
		}
	}

	return matrix;
}

int freeMatrix(int ** matrix, int matrixSize) {
	int matrixRowController;

	for (matrixRowController = 0; matrixRowController < matrixSize; matrixRowController++) {
		free(matrix[matrixRowController]);
	}

	free(matrix);

	return 0;
}

int printMatrix(int ** matrix, int matrixSize) {
	int matrixRowController;

	for (matrixRowController = 0; matrixRowController < matrixSize; matrixRowController++) {
		int matrixColumnController;

		for(matrixColumnController = 0; matrixColumnController < matrixSize; matrixColumnController++) {
			cout << "\t" << matrix[matrixRowController][matrixColumnController];
		}

		cout << endl;
	}

	cout << endl;

	return 0;
}

int printSolutionMatrix(int ** matrix, int matrixSize) {
	int matrixRowController;

	for (matrixRowController = 0; matrixRowController < matrixSize; matrixRowController++) {
		int matrixColumnController;

		for(matrixColumnController = 0; matrixColumnController < matrixSize; matrixColumnController++) {
			cout << "\t";

			switch (matrix[matrixRowController][matrixColumnController]) {
				case -2:
					cout << "X";
					break;
				case -1:
					cout << "#";
					break;
				default:
					cout << " ";
			}
		}

		cout << endl;
	}

	cout << endl;

	return 0;
}

int * copyContentToMatrix (int ** matrix, int matrixSize, char * content) {
	int matrixRowController = 0, matrixColumnController = 0;

	cout << "Original Maze:" << endl << endl;

	for (int i = 0; content[i] != '\0'; i++) {
		if(content[i] == '\n') {
			matrixRowController++;
			matrixColumnController = 0;
			cout << endl;
			continue;
		}

		cout << "\t" << content[i];

		int value = content[i] == '#' ? -1 : 0;

		matrix[matrixRowController][matrixColumnController] = value;
		matrixColumnController++;
	}

	cout << endl;

	return 0;
}

int map(int y, int x, int ** matrix, int matrixSize, queue<point>& pointQueue) {
	int mappedCount = 0;
	for (int i = -1; i < 2; i++) {
		// Se a coordenada do eixo das ordenadas ultrapassa
		// os limites da matriz, apenas aumente a coordenada.
		if(y + i < 0 || y + i >= matrixSize) continue;

		for (int j = -1; j < 2; j++) {
			// Se a coordenada do eixo das abscissas ultrapassa
			// os limites da matriz, apenas aumente a coordenada.
			if (x + j < 0 || x + j >= matrixSize) continue;

			// Excluí posições não-adjacentes.
			if (i == j || i == (j * -1)) continue;

			// Se o ponto já foi mapeado ou é uma parade, não há
			// por quê remapear.
			if (matrix[y + i][x + j] != 0) continue;
			
			// Mapeie o ponto com o número do passo.
			matrix[y + i][x + j] = matrix[y][x] + 1;

			point newPoint;
			newPoint.x = x + j;
			newPoint.y = y + i;
			pointQueue.push(newPoint);
			mappedCount++;
		}
	}

	return mappedCount;
}

// Deixando bem claro que o nome só vai em português porque eu quero seguir
// a descrição da atividade, mas que tá feio, tá.
int anotar(int x, int y, int ** matrix, int matrixSize) {
	// Inicializa o ponto inicial (entrada).
	point entrance;
	entrance.x = x;
	entrance.y = y;

	matrix[y][x] = 1;

	// Inicializa a fila.
	queue<point> pointQueue;

	// Insere o ponto inicial na fila.
	pointQueue.push(entrance);

	while(!pointQueue.empty()) {
		int x = pointQueue.front().x, y = pointQueue.front().y;

		pointQueue.pop();

		map(y, x, matrix, matrixSize, pointQueue);
	}

	return 0;
}

point searchForLesser (int ** matrix, int matrixSize, point current) {
	int y = current.y, x = current.x;

	int lesser = matrix[y][x];

	for (int i = -1; i < 2; i++) {
		if(y + i < 0 || y + i >= matrixSize) continue;

		for (int j = -1; j < 2; j++) {
			if (x + j < 0 || x + j >= matrixSize) continue;
			if (i == j || i == (j * -1)) continue;
			if (matrix[y + i][x + j] == -1) continue;

			if(matrix[y + i][x + j] < lesser) {
				lesser = matrix[y + i][x + j];
				current.x = x + j;
				current.y = y + i;
			}
		}
	}

	return current;
}

int extrair (int exitX, int exitY, int ** matrix, int matrixSize) {
	stack<point> pointStack;

	point exit;
	exit.x = exitX;
	exit.y = exitY;

	pointStack.push(exit);

	if (matrix[pointStack.top().y][pointStack.top().x] == 0) return 0;
	if (matrix[pointStack.top().y][pointStack.top().x] == -1) return 0;

	while (matrix[pointStack.top().y][pointStack.top().x] != 1) {
		int value = matrix[pointStack.top().y][pointStack.top().x];

		point pointToCompare;

		pointToCompare.x = pointStack.top().x;
		pointToCompare.y = pointStack.top().y;
 
		point lesserPoint = searchForLesser(matrix, matrixSize, pointToCompare);

		if(value > matrix[lesserPoint.y][lesserPoint.x]) {
			pointStack.push(lesserPoint);
		} else {
			matrix[pointStack.top().y][pointStack.top().x] = value + 1;
			pointStack.pop();
		}
	}

	while (!pointStack.empty()) {
		int y = pointStack.top().y, x = pointStack.top().x;
		matrix[y][x] = -2;
		pointStack.pop();	
	}

	return 0;
}


int main () {
	int matrixSize = 0;

	cout << "Insert matrix size:" << endl;

	cin >> matrixSize;
	
	int ** matrix = generateMatrix(matrixSize);

	char * filename = new char [MY_FILENAME_SIZE];

	cout << "Insert filename:" << endl;

	cin >> filename;

	ifstream file;

	file.open(filename);

	char * fileContent = getContentFromFile(file);

	file.close();
	
	delete[] filename;

	if (fileContent == NULL) {
		cout << "The system could not read the file." << endl;

		return 0;
	}
	
	copyContentToMatrix(matrix, matrixSize, fileContent);
	
	delete[] fileContent;

	cout << "Maze on Matrix:" << endl << endl;

	printMatrix(matrix, matrixSize);

	int entranceX, entranceY, exitX, exitY;

	cout << "Insert entrance's x (start count by 0):" << endl;
	cin >> entranceX;
	cout << "Insert entrance's y (start count by 0):" << endl;
	cin >> entranceY;

	anotar(entranceX, entranceY, matrix, matrixSize);
	
	cout << "Mapped Maze:" << endl << endl;

	printMatrix(matrix, matrixSize);

	cout << "Insert exit's x (start count by 0):" << endl;
	cin >> exitX;
	cout << "Insert exit's y (start count by 0):" << endl;
	cin >> exitY;

	extrair(exitX, exitY, matrix, matrixSize);

	cout << "Shortest path:" << endl << endl;

	printSolutionMatrix(matrix, matrixSize);

	freeMatrix(matrix, matrixSize);

	return 0;
}

