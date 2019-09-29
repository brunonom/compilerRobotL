#include <bits/stdc++.h>

using namespace std;

#include "global.cpp"
#include "token_automata.cpp"
#include "lexico.cpp"


int main(int argc, char** argv){

	glob::source_file = fopen(argv[1], "r");
	bool ok;
	if(argc == 2){
		ok = main_lex(true);
	}
	else if(argc==3){
		bool z = false;
		if(argv[2][0] == 'y') z = true;
		ok = main_lex(z);
	}
	else{
		cout << "Modo de utilização: ./executavel [arquivo].txt y/n(opcional)";
		return 0;
	}
	fclose(glob::source_file);
	if(ok){
		cout << "Compilação finalizada sem erros." << endl;
	}
}