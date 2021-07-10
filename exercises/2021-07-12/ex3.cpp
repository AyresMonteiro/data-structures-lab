#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class NonexistentFileException : public exception
{
	public:
		const char * what() const throw () {
			return "ARQUIVO INEXISTENTE\n";
		}
};

bool isNotPunctuationMark(char c) {
	char punctuationMarks[] = "!@#$%*()-+='\"\\|,.;:/?[]{} \n";

	return find(
		begin(punctuationMarks),
		end(punctuationMarks),
		c
	) == end(punctuationMarks);
}

char * reverseCharVector(vector<char> vec) {
	// A função vector::data() está inclusa a partir do C++11
	// versões anteriores não comportarão seu uso
	char * charPointer = vec.data();

	int i = vec.size();

	char * newCharPointer = new char[i];
	
	newCharPointer[--i] = '\0';
	
	while(*charPointer != '\0') {
		--i;
		newCharPointer[i] = *charPointer;
		++charPointer;
	}

	return newCharPointer;
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
			if(
				(aCharacter == ' ' ||
				aCharacter == '\n') &&
				file_content[i].size() != 0
			) {
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

		// Deleta o ultimo array caso esse esteja vazio (Em caso do
		// arquivo ter uma quebra de linha no final)

		if((file_content.end() - 1)->size() == 0) {
			file_content.pop_back();
		}

		vector<vector<char>>::iterator it =
			file_content.begin();

		while (it != file_content.end()) {
			char * reversedString = reverseCharVector(*it);
			cout << reversedString;
			delete[] reversedString;

			it++;

			// Não coloca espaço depois da última palavra
			if(it != file_content.end()) cout << ' ';
		}

		cout << endl;

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

