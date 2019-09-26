//autoexplanatory
void print_char_table(bool line_and_col){
	printf("tabela de caracteres\n");
	printf("----------------------------------------\n");

	for(int i=0; i<glob::char_table.size(); i++){
		char c = glob::char_table[i].character;
		int ln = glob::char_table[i].line_number;
		int cn = glob::char_table[i].column_number;
		if(line_and_col){
			printf("%c(%d)(%d)\n", c, ln, cn);
		}
		else{
			printf("%c\n", c);
		}
	}

	// int lin=glob::char_table[0].line_number;
	// int col=1;
	// printf("(linha %d)\t:", lin);
	// for(int i=0; i<glob::char_table.size(); i++){
	// 	// printf("%d colunas\n", char_table[i].size());
	// 	char c = glob::char_table[i].character;
	// 	int ln = glob::char_table[i].line_number;
	// 	int cn = glob::char_table[i].column_number;
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
			while(buffer != '\n' && !feof(glob::source_file)){
				buffer = getc(glob::source_file);
			}
		}
		//normal characters only
		else if(autm_letra(buffer) || autm_digito(buffer)){
			col++;
			glob::char_table.push_back({buffer, lin, col});
		}
		//conglomera whitespace consecutivo em um ' '
		else if(buffer == ' ' || buffer == '\t' || buffer == '\n'){
			
			if(buffer == ' '){
				glob::char_table.push_back({' ', lin, col+1});
			}
			else if(buffer == '\t'){
				glob::char_table.push_back({' ', lin, col+4});
			}
			else if(buffer == '\n'){
				glob::char_table.push_back({' ', lin, col+1});
			}

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
	// for(string a : glob::reserved_words){
	// 	if(x == a){
	// 		glob::symbol_table.push_back({x, x});
	// 		return true;
	// 	}
	// }
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

//gets the next word (until a whitespace) from the source code
string nextword(int i){
	string x;
	if(glob::char_table[i].character == ' '){
		while(!autm_letra(glob::char_table[i].character) && !autm_digito(glob::char_table[i].character)){
			i++;
		}
	}
	while(glob::char_table[i].character != ' ' && i<glob::char_table.size()){
		x += glob::char_table[i].character;
		i++;
	}
	if(x.size()==0){
		x+="$";
	}
	return convert_to_lowercase(x);
}
glob::char_pos get_char_table_pos(int i){
	if(glob::char_table[i].character == ' '){
		while(!autm_letra(glob::char_table[i].character) && !autm_digito(glob::char_table[i].character)){
			i++;
		}
	}
	return (i<glob::char_table.size() ? glob::char_table[i] : glob::char_pos('x',-1,-1));
}
//generates all tokens
bool tokenize(){
	bool got_token = false;
	bool ok = true;
	for(int i=0; i<glob::char_table.size(); ){
		string novo_token = nextword(i);
		glob::char_pos ini = get_char_table_pos(i);
		i += 1 + novo_token.size();		
		string k;
		if(
			novo_token == "vire" ||
			novo_token == "apague" ||
			novo_token == "acenda" ||
			novo_token == "aguarde" ||
			novo_token == "robo"
		  ){
		  	k = nextword(i);
			novo_token += ' ' + k;
			i += 1 + k.size();
		}
		else if(
			novo_token == "frente" ||
			novo_token == "direita" ||
			novo_token == "esquerda"
			){
			if(convert_to_lowercase(nextword(i)) == "robo"){
				k = nextword(i);
				novo_token += ' ' + k;
				i += 1 + k.size();
				k = nextword(i);
				novo_token += ' ' + k;
				i += 1 + k.size();
			}
		}
		else if(novo_token == "lampada"){
			k = nextword(i);
			novo_token += ' ' + k;
			i += 1 + k.size();

			k = nextword(i);
			novo_token += ' ' + k;
			i += 1 + k.size();
			
			k = nextword(i);
			novo_token += ' ' + k;
			i += 1 + k.size();
		}		
		if(novo_token.back() == '$'){
			cout << "ERRO, linha: " << ini.line_number << " coluna: " << ini.column_number << endl;
			return false;
		}
		cout << novo_token << endl;
		got_token = make_token(novo_token);
		if(!got_token){
			ok = false;
			glob::char_pos x = glob::char_table[i];
			printf("erro: linha %d coluna %d: palavra nao reconhecida\n", x.line_number, x.column_number);
		}
	}
	return ok;
}

//main lexical analyzer
void main_lex(){

	bool ok = true;

	ok = get_data();

	printf("\n");
	print_char_table(true);

	ok = tokenize();
	
	printf("\n");
	print_symbol_table();
}