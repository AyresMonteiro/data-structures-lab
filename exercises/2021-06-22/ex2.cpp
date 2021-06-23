#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class NonexistentFileException : public exception
{
	public:
		const char * what() const throw () {
			return "ARQUIVO INEXISTENTE\n";
		}
};

bool isConsonant(char content_char) {
	char consonants[] = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
	
	return find(begin(consonants), end(consonants), content_char) != end(consonants);
}

int main () {
	char * file_content = NULL;
	try {
		string input_filename;
		cout << "Digite o nome de um arquivo (com extensao):\n";

		cin >> input_filename;

		fstream file;

		// Lendo arquivo no modo de entrada (r)
		file.open("./" + input_filename, fstream::in);

		if(file.is_open()) {
			// Procurando posicao do EOF do arquivo e movendo o ponteiro interno do objeto para tal
			file.seekg(0, file.end);

			// Obtendo o tamanho do arquivo ate o fim (conforme setado pela instrucao anterior)
			int length = file.tellg();	
		
			// Movendo o ponteiro interno do objeto file para o inicio
			file.seekg(0, file.beg);
		
			file_content = new char [length];

			file.read(file_content, length);
		
			if (file) {
				for (int i = 0; i < length; i++) {
					if(isConsonant(file_content[i])) cout << file_content[i];
				}
			}

			file.close();

			// "Desalocando" memória
			delete[] file_content;
		} else {
			// Lancando excecao caso o arquivo nao tenha sido aberto
			throw NonexistentFileException();
		}

		cout << "\n";

		return 0;
	} catch (NonexistentFileException error) {
		// "Desaloca" memória se o ponteiro estiver apontando para algo diferente de nulo
		if (file_content != NULL) delete[] file_content;
		cout <<	error.what();
		return 0;
	}	
}

