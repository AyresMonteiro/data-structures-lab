#include <iostream>
#include <fstream>
#include <vector>

#define endOfCIn -1

using namespace std;

class NonexistentFileException : public exception
{
	public:
		const char * what() const throw () {
			return "ARQUIVO INEXISTENTE\n";
		}
};

int main () {
	try {
		string input_filename;
		cout << "Digite o nome de um arquivo (com extensao):\n";

		cin >> input_filename;

		fstream file;

		// O código abaixo só funciona a partir do c++ 11
		// devido ao uso da função vector::data()
		file.open("./" + input_filename, fstream::in);

		if(!file.is_open()) throw NonexistentFileException();

		vector<char> file_content;

		char aCharacter;

		while (file.get(aCharacter)) {
			if ((aCharacter > 64 && aCharacter < 91) || (aCharacter > 97 && aCharacter < 123)) {
				file_content.push_back(aCharacter);
			}
		}
		
		cout << file_content.data() << endl;

		file.close();

		return 0;
	} catch (NonexistentFileException error) {
		cout <<	error.what();
		return 0;
	}	
}

