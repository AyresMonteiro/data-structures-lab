#include <iostream>
#include <fstream>

using namespace std;

int main () {
	cout << "Digite qualquer coisa (aperte ENTER para terminar de digitar):\n";

	fstream file;

	// Lendo arquivo no modo de saida (append, a)
	file.open("./ex3.txt", fstream::app);

	if(file.is_open()) {
		string user_words;
		getline(cin, user_words);
		file << user_words;

		file.close();
	}

	return 0;
}

