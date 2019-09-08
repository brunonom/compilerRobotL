#include <bits/stdc++.h>

using namespace std;

#include "global.cpp"
#include "token_automata.cpp"
#include "lexico.cpp"


int main(int argc, char** argv){

	glob::source_file = fopen(argv[1], "r");

	main_lex();

	fclose(glob::source_file);
}