//autoexplanatory
void print_char_table(bool line_and_col){
	printf("tabela de caracteres\n");
	printf("----------------------------------------\n");
	int lin=glob::char_table[0].line_number;
	int col=1;
	printf("(linha %d)\t:", lin);
	for(int i=0; i<glob::char_table.size(); i++){
		// printf("%d colunas\n", char_table[i].size());
		char c = glob::char_table[i].character;
		int ln = glob::char_table[i].line_number;
		int cn = glob::char_table[i].column_number;
		while(lin < ln){
			printf("\n(linha %d)\t:", ln);
			lin++;
			col=1;
		}
		while(col < cn){
			printf(" ");
			col++;
		}
		if(line_and_col){
			printf("%c(%d)(%d)", c, ln, cn);
		}
		else{
			printf("%c", c);
		}
		col++;
	}
	printf("\n----------------------------------------\n");
}

//autoexplanatory
void print_symbol_table(){
	printf("tabela de tokens\n");
	printf("----------------------------------------\n");
	for(glob::token t : glob::symbol_table){
		string n = t.name;
		string v = t.value;
		cout << n << "(" << v << ")\n";
	}
	printf("----------------------------------------\n");
}

//get data from the source code
bool get_data(){

	int lin=1;
	int col=1;
	bool ok = true;

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
			ok = false;
		}
		col++;

		//found end of file so we got everything
		if(feof(glob::source_file)){
			return ok;
		}
	}

	//this should NEVER HAPPEN!!!
	printf("TEM ALGUMA COISA MUITO ERRADA!\n");
	return ok;
}

//makes a token (unfinished?)
bool make_token(string x){
	x = convert_to_lowercase(x);
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
bool tokenize(){
	bool got_token = false;
	bool ok = true;
	string up_until_now = "";
	for(int i=0; i<glob::char_table.size(); ){
		up_until_now += nextword(i);
		i += nextword(i).size();		
		up_until_now = convert_to_lowercase(up_until_now);
		
		if(
			up_until_now == "vire" ||
			up_until_now == "apague" ||
			up_until_now == "acenda" ||
			up_until_now == "aguarde" ||
			up_until_now == "robo"
			){
			up_until_now += ' ' + nextword(i);
			i += nextword(i).size();
		}
		else if(
			up_until_now == "frente" ||
			up_until_now == "direita" ||
			up_until_now == "esquera"
			){
			if(convert_to_lowercase(nextword(i)) == "robo"){
				up_until_now += ' ' + nextword(i);
				i += nextword(i).size();
				up_until_now += ' ' + nextword(i);
				i += nextword(i).size();
			}
		}
		else if(up_until_now == "lampada"){
			up_until_now += ' ' + nextword(i);
			i += nextword(i).size();
			up_until_now += ' ' + nextword(i);
			i += nextword(i).size();
			up_until_now += ' ' + nextword(i);
			i += nextword(i).size();
			up_until_now += ' ' + nextword(i);
			i += nextword(i).size();
		}
		

		got_token = make_token(up_until_now);
		if(!got_token){
			ok = false;
			glob::char_pos x = glob::char_table[i];
			printf("erro: linha %d coluna %d: palavra nao reconhecida\n", x.line_number, x.column_number);
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
	print_char_table(false);

	ok = tokenize();
	
	printf("\n");
	print_symbol_table();
}