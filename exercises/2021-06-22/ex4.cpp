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

bool isLetter(char content_char) {
	char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	return find(begin(letters), end(letters), content_char) != end(letters);
}

int main () {
	fstream file;
	fstream new_file;
	char * file_content = NULL;
	try {
		string input_filename;
		cout << "Digite o nome de um arquivo (com extensao):\n";

		cin >> input_filename;

		// Lendo arquivo no modo de entrada (r, read)
		file.open("./" + input_filename, fstream::in);
		
		// Lendo arquivo no modo de saída (o, out)
		new_file.open("./result_" + input_filename, fstream::out);

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
					if(isLetter(file_content[i])) file_content[i] += 1;
					new_file << file_content[i];
				}
				
			}

			file.close();
			new_file.close();

			// "Desalocando" memória
			delete[] file_content;
		} else {
			// Lancando excecao caso o arquivo nao tenha sido aberto
			throw NonexistentFileException();
		}

		return 0;
	} catch (NonexistentFileException error) {
		if(new_file.is_open()) new_file.close();
		// "Desaloca" memória se o ponteiro estiver apontando para algo diferente de nulo
		if (file_content != NULL) delete[] file_content;
		cout <<	error.what();
		return 0;
	}	
}

