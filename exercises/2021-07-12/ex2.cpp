#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define endOfCIn -1

using namespace std;

class NonexistentFileException : public exception
{
	public:
		const char * what() const throw () {
			return "ARQUIVO INEXISTENTE\n";
		}
};

bool isNotPunctuationMark(char c) {
	char punctuationMarks[] = "!@#$%*()-+='\"\\|,.;:/?[]{}";

	return find(
		begin(punctuationMarks),
		end(punctuationMarks),
		c
	) == end(punctuationMarks);
}


int main () {
	try {
		string input_filename;
		cout << "Digite o nome de um arquivo (com extensao):\n";

		cin >> input_filename;

		fstream file;
 
		file.open("./" + input_filename, fstream::in);

		if(!file.is_open()) throw NonexistentFileException();

		vector<vector<char>> file_content(1, vector<char>());

		char aCharacter;

		int i = 0;

		while (file.get(aCharacter)) {
			if(aCharacter == ' ' || aCharacter == '\n') {
				vector<char> newVector;
				file_content.push_back(newVector);
				file_content[i].push_back('\0');
				i++;
				continue;
			}

			// Como "sinais de pontuação" é meio vago, vou
			// ignorar somente os caracteres descritos na função
			// isNotPunctuationMark
			if (isNotPunctuationMark(aCharacter)) {
				file_content[i].push_back(aCharacter);
			}
		}

		vector<vector<char>>::reverse_iterator rI =
			file_content.rbegin();

		while (rI != file_content.rend()) {
			// O ponteiro para o qual o iterador reverso inicial
			// aponta vem depois do ponteiro do iterador final
			// normal, portanto é aconselhável diminui-lo antes do
			// seu uso inicial, ao invés de diminui-lo ao final de
			// cada loop.
			// Ps: Aumentar um iterador reverso diminui seu
			// ponteiro. Malandragens do C++.
			++rI;

			// O código abaixo só funciona a partir do c++ 11
			// devido ao uso da função vector::data()
			cout << rI->data() << endl;
		}

		file.close();

		return 0;
	} catch (NonexistentFileException NonexistentFileError) {
		cout <<	NonexistentFileError.what();
		return 0;
	} catch (exception otherError) {
		cout << otherError.what();
		return 0;
	}
}

