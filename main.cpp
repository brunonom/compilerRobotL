#include <bits/stdc++.h>

using namespace std;

#include "global.cpp"
#include "token_automata.cpp"
#include "lexico.cpp"
#include "sintatico.cpp"
#include "semantico.cpp"
#include "gerador_codigo.cpp"
int main(int argc, char* argv[]){

	bool ok = false;
	bool verbose = false;
	glob::source_file = NULL;

	if(argc == 1){
		printf("./[executavel] -h para ajuda\n");
		return 0;
	}

	for(int i=0; i<argc; i++){
		if(strcmp(argv[i], "-s") == 0){
			glob::source_file = fopen(argv[i+1], "r");
			glob::source_file_name = argv[i+1];
		}
		if(strcmp(argv[i], "-v") == 0){
			verbose = true;
		}
		if(strcmp(argv[i], "-h") == 0){
			printf("Ajuda: ./[executavel] [argumentos]\n");
			printf("argumentos:\n");
			printf("    -s [arquivo]    para passar o arquivo de entrada\n");
			printf("    -v              para observar as estruturas criadas detalhadamente\n");
			printf("    -h              para ver este menu de ajuda\n");
			return 0;
		}
	}

	if(glob::source_file == NULL){
		printf("Arquivo de entrada invalido\n");
		return 0;
	}
	else{
		ok = main_lex(verbose);
	}

	if(ok){
		ok = main_sin(verbose);
	}
	else{
		printf("Compilacao finalizada com erros lexicos\n");
		return 0;
	}


	if(ok){
		ok = main_sem(verbose);
	}
	else{
		printf("Compilacao finalizada com erros sintaticos\n");
		return 0;
	}


	if(ok){
		ok = main_gerador(verbose);
	}
	else{
		printf("Compilacao finalizada com erros semânticos.\n");
		return 0;
	}

	if(ok){
		printf("Compilacao finalizada sem erros\n");
	}
	else{
		// a gnt q lute
		printf("Compilacao finalizada com erros na geração de código.");
	}

	return 0;
}