//autoexplanatory
void print_char_table(){
	// printf("%d linhas\n", char_table.size());
	for(int i=0; i<glob::char_table.size(); i++){
		// printf("%d colunas\n", char_table[i].size());
		char c = glob::char_table[i].character;
		int ln = glob::char_table[i].line_number;
		int cn = glob::char_table[i].column_number;
		printf("%c(%d)(%d)\n", c, ln, cn);
	}
}

//autoexplanatory
void print_symbol_table(){
	for(glob::token t : glob::symbol_table){
		string n = t.name;
		string v = t.value;
		
		cout << n << "(" << v << ")\n";
	}
}

//get data from the source code
bool get_data(){

	int lin=1;
	int col=1;
	bool everything_is_ok = true;

	while(glob::buffer = getc(glob::source_file)){
		//ignore comments
		if(glob::buffer == '#'){
			while(glob::buffer != '\n'){
				glob::buffer = getc(glob::source_file);
			}
			col=0;
			lin++;
		}
		//checks for invalid characters
		else if(autm_letra(glob::buffer) || autm_digito(glob::buffer)){
			glob::char_table.push_back({glob::buffer, lin, col});
		}
		//endline -> reset columns and goes to new line
		else if(glob::buffer == '\n'){
			col=0;
			lin++;
		}
		//tab -> skip 4 columns
		else if(glob::buffer == '\t'){
			col+=3;
		}
		//ignore spaces and wierd characters 
		else if(glob::buffer == 13 || glob::buffer == ' ' || glob::buffer == -1);
		//found unrecognized character so say it
		else{
			printf("erro: linha %d coluna %d: caractere nao reconhecido\n", lin, col);
			everything_is_ok = false;
		}
		col++;

		//found end of file so we got everything
		if(feof(glob::source_file)){
			return everything_is_ok
		}
	}

	//this should NEVER HAPPEN!!!
	printf("TEM ALGUMA COISA MUITO ERRADA!\n");
	return everything_is_ok;
}

//makes a token (unfinished?)
bool make_token(string x){
	x = convert_case(x);
	for(string a : glob::reserved_words){
		if(x == a){
			glob::symbol_table.push_back({x, x});
			return true;
		}
	}
	if(autm_numero(x)){
		glob::symbol_table.push_back({"numero", x});
		return true;
	}
	if(autm_identificador(x)){
		glob::symbol_table.push_back({"id", x});
		return true;
	}
	return false;
	//falta oq msm?
}

//gets the next word (until a whitespace) from the source code
string nextword(int begin){
	int copy = begin;
	int forward = begin +1;
	string x;
	x += glob::char_table[copy].character;
	while(
		glob::char_table[forward].column_number-glob::char_table[copy].column_number <= 1 && 
		glob::char_table[copy].line_number == glob::char_table[forward].line_number
		){
		x += glob::char_table[forward].character;
		copy++;
		forward++;
	}
	return x;
}

//generates all tokens
void tokenize(){
	bool got_token = false;
	string up_until_now = "";
	for(int i=0; i<glob::char_table.size(); i++){
		up_until_now += nextword(i);
		i += nextword(i).size()-1;		
		up_until_now = convert_case(up_until_now);
		
		if(
			up_until_now == "vire" ||
			up_until_now == "apague" ||
			up_until_now == "acenda" ||
			up_until_now == "aguarde" ||
			up_until_now == "robo"
			){
			up_until_now += nextword(i);
			i += nextword(i).size();
			glob::prints(up_until_now);
			printf("\n");
		}
		else if(
			up_until_now == "frente" ||
			up_until_now == "direita" ||
			up_until_now == "esquera"
			){
			if(convert_case(nextword(i)) == "robo"){
				up_until_now += nextword(i);
				i += nextword(i).size();
				glob::prints(up_until_now);
			printf("\n");
				up_until_now += nextword(i);
				i += nextword(i).size();
				glob::prints(up_until_now);
			printf("\n");
			}
		}
		else if(up_until_now == "lampada"){
			up_until_now += nextword(i);
			i += nextword(i).size();
			glob::prints(up_until_now);
			printf("\n");
			up_until_now += nextword(i);
			i += nextword(i).size();
			glob::prints(up_until_now);
			printf("\n");
			up_until_now += nextword(i);
			i += nextword(i).size();
			glob::prints(up_until_now);
			printf("\n");
			up_until_now += nextword(i);
			i += nextword(i).size();
			glob::prints(up_until_now);
			printf("\n");
		}
		

		got_token = make_token(up_until_now);
		if(!got_token){
			glob::char_pos x = glob::char_table[i];
			printf("erro: linha %d coluna %d: palavra nao reconhecida\n", x.line_number, x.column_number);
		}

		up_until_now = "";
	}
}

//main lexical analyzer
void main_lex(){

	glob::char_pos x = get_data();
	
	if(!glob::equal_char_pos(x, {-1, -1, -1})){
		printf("erro: linha %d coluna %d: caractere nao reconhecido\n", x.line_number, x.column_number);
	}

	// print_char_table();

	tokenize();

	print_symbol_table();
}