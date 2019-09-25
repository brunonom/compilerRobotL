//autoexplanatory
void print_input_as_string(bool line_and_col){
	printf("tabela de caracteres\n");
	printf("----------------------------------------\n");

	for(int i=0; i<glob::input_as_string.size(); i++){
		char c = glob::input_as_string[i].character;
		int ln = glob::input_as_string[i].line_number;
		int cn = glob::input_as_string[i].column_number;
		if(line_and_col){
			printf("%c(%d)(%d)\n", c, ln, cn);
		}
		else{
			printf("%c\n", c);
		}
	}

	// int lin=glob::input_as_string[0].line_number;
	// int col=1;
	// printf("(linha %d)\t:", lin);
	// for(int i=0; i<glob::input_as_string.size(); i++){
	// 	// printf("%d colunas\n", input_as_string[i].size());
	// 	char c = glob::input_as_string[i].character;
	// 	int ln = glob::input_as_string[i].line_number;
	// 	int cn = glob::input_as_string[i].column_number;
	// 	while(lin < ln){
	// 		printf("\n(linha %d)\t:", ln);
	// 		lin++;
	// 		col=1;
	// 	}
	// 	while(col < cn){
	// 		printf(" ");
	// 		col++;
	// 	}
	// 	if(!line_and_col){
	// 		printf("%c(%d)(%d)", c, ln, cn);
	// 	}
	// 	else{
	// 		printf("%c", c);
	// 	}
	// 	col++;
	// }

	printf("\n----------------------------------------\n");
}

//autoexplanatory
void print_symbol_table(){
	printf("tabela de tokens\n");
	printf("----------------------------------------\n");
	cout << "[token] : [valor]\n";
	for(glob::token t : glob::symbol_table){
		string n = t.name;
		string v = t.value;
		cout << n << " : " << v << "\n";
	}
	printf("----------------------------------------\n");
}

//get data from the source code
bool get_data(){

	int lin=1;
	int col=1;
	bool ok = true;
	char buffer;

	while(buffer = getc(glob::source_file)){
		
		//ignore comments
		if(buffer == '#'){
			col=0;
			lin++;
			while(buffer != '\n'){
				buffer = getc(glob::source_file);
			}
		}
		
		//normal characters only
		else if(autm_letra(buffer) || autm_digito(buffer)){
			col++;
			glob::input_as_string.push_back({buffer, lin, col});
		}
		
		//erase whitespace
		else if(buffer == ' ' || buffer == '\t' || buffer == '\n'){

			ungetc(buffer, glob::source_file);
			
			while(buffer = getc(glob::source_file)){
				if(buffer == ' '){
					col++;
				}
				else if(buffer == '\t'){
					col+=4;
				}
				else if(buffer == '\n'){
					col=0;
					lin++;
				}
				else if(buffer == 13 || buffer == -1);
				else{
					ungetc(buffer, glob::source_file);
					break;
				}
			}
		}
		
		//ignore wierd characters 
		else if(buffer == 13 || buffer == -1);
		
		//found unrecognized character so say it
		else{
			printf("erro: linha %d coluna %d: caractere nao reconhecido\n", lin, col);
			ok = false;
		}
		
		//found end of file so we got everything
		if(feof(glob::source_file)){
			return ok;
		}
	}

	//this should NEVER HAPPEN!!!
	printf("TEM ALGUMA COISA MUITO ERRADA!\n");
	return ok;
}

bool is_a_reserved_word(string x){
	for(string s : glob::reserved_words){
		if(x == s){
			return true;
		}
	}
	return false;
}

//makes a token (unfinished?)
bool make_token(string x){
	x = convert_to_lowercase(x);

	if(autm_numero(x)){
		glob::symbol_table.push_back({"numero", x});
		return true;
	}
	else if(autm_identificador(x) && !is_a_reserved_word(x)){
		glob::symbol_table.push_back({"id", x});
		return true;
	}
	else if(autm_condicao(x)){
		glob::symbol_table.push_back({"condicao", x});
		return true;
	}
	else if(autm_instrucao(x)){
		glob::symbol_table.push_back({"instrucao", x});
		return true;
	}
	else if(autm_condicional(x)){
		glob::symbol_table.push_back({"condicional", x});
		return true;
	}
	else if(autm_laco(x)){
		glob::symbol_table.push_back({"laco", x});
		return true;
	}
	else if(autm_iteracao(x)){
		glob::symbol_table.push_back({"iteracao", x});
		return true;
	}
	else if(autm_bloco(x)){
		glob::symbol_table.push_back({"bloco", x});
		return true;
	}
	else if(autm_declaracao(x)){
		glob::symbol_table.push_back({"declaracao", x});
		return true;
	}
	else if(autm_programa(x)){
		glob::symbol_table.push_back({"programa", x});
		return true;
	}
	else if(autm_sentido(x)){
		glob::symbol_table.push_back({"sentido", x});
		return true;
	}
	return false;
}

//generates all tokens
bool tokenize(){
	bool got_token = false;
	bool ok = false;
	string up_until_now = "";
	vector<bool> autm_final_states(11, false);

	up_until_now += glob::input_as_string[0].character;
	for(int i=0; i<glob::input_as_string.size(); ){
		int start = i;

		while(i - start + 1 <= 23 && !ok){
			ok = autm_sentido(up_until_now);
			ok = autm_numero(up_until_now);
			ok = autm_condicao(up_until_now);
			ok = autm_instrucao(up_until_now);
			ok = autm_condicional(up_until_now);
			ok = autm_laco(up_until_now);
			ok = autm_iteracao(up_until_now);
			ok = autm_bloco(up_until_now);
			ok = autm_declaracao(up_until_now);
			ok = autm_programa(up_until_now);
			i++;
			up_until_now += glob::input_as_string[i].character;
			up_until_now = convert_to_lowercase(up_until_now);	
			cout << up_until_now << "\n";
		}

		got_token = make_token(up_until_now);
		if(!got_token){
			ok = false;
			glob::char_pos x = glob::input_as_string[i];
			// printf("erro: linha %d coluna %d: palavra nao reconhecida\n", x.line_number, x.column_number);
			i = start;
		}

		up_until_now = "";
	}
	return ok;
}

//main lexical analyzer
void main_lex(){

	bool ok = true;

	ok = get_data();

	printf("\n");
	print_input_as_string(true);

	ok = tokenize();
	
	printf("\n");
	print_symbol_table();
}