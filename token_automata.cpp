//ideias ruins

bool autm_letra(char lexeme){
	lexeme = lexeme | lexeme-32;
	if('a'<=lexeme && lexeme<='z'){
		return true;
	}
	return false;
}

bool autm_digito(char lexeme){
	if('0'<=lexeme && lexeme<='9'){
		return true;
	}
	return false;
}

int char_to_pos(char c){
	if(autm_letra(c)){
		return c-'a';
	}
	return -1;
}

int digit_to_pos(char c){
	if(autm_digito(c)){
		return c-'0';
	}
	return -1;
}

int any_to_pos(char c){
	int pos = -1;
	
	pos = char_to_pos(c);
	if(pos != -1){
		return pos;
	}

	pos = digit_to_pos(c);
	if(pos != -1){
		return pos + 26;
	}

	return -1;
}

string convert_case(string x){
	for(int i=0; i<x.size(); i++){
		if(autm_letra(x[i])){
			x[i] = x[i] | x[i]-32;
		}
	}
	return x;
}
//basicos acima
//complexos abaixo

bool autm_condicao(string lexeme){
	lexeme = convert_case(lexeme);
	if(
		lexeme == "robo pronto" ||
		lexeme == "robo ocupado" ||
		lexeme == "robo parado" ||
		lexeme == "robo movimentando" ||
		lexeme == "frente robo bloqueada" ||
		lexeme == "direita robo bloqueada" ||
		lexeme == "esquerda robo bloqueada" ||
		lexeme == "lampada acesa a frente" ||
		lexeme == "lampada apagada a frente" ||
		lexeme == "lampada acesa a esquerda" ||
		lexeme == "lampada apagada a esquerda" ||
		lexeme == "lampada acesa a direita" ||
		lexeme == "lampada apagada a direita" 
		){
		return true;
	}
	return false;
}

bool autm_numero(string lexeme){
	vector< vector<int> > table;
	table = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
	int state = 0;
	for(int i=0; i<lexeme.size(); i++){
		int input = digit_to_pos(lexeme[i]);
		if(input == -1){
			return false;
		}
		int newstate = table[state][input]; 
		if(newstate < 0){
			return false;
		}
		state = newstate;
	}
	if(state == 1){
		return true;
	}
	return false;
}


bool autm_identificador(string lexeme){

	vector< vector<int> > table;
	table = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	int state = 0;
	for(int i=0; i<lexeme.size(); i++){
		int input = any_to_pos(lexeme[i]);
		if(input == -1){
			return false;
		}
		int newstate = table[state][input]; 
		if(newstate < 0){
			return false;
		}
		state = newstate;
	}
	if(state == 1){
		return true;
	}
	return false;
}

bool autm_instrucao(string lexeme){
	lexeme = convert_case(lexeme);
	if(
		lexeme == "pare" ||
		lexeme == "finalize" ||
		lexeme == "apague lampada" ||
		lexeme == "acenda lampada"
		){
		return true;
	}
	else{
		//nossa eu nao tenho a menor ideia do q to faznedo
		//nem do que eh pra fazer
	}
}



//acho q peguei o jeito da coisa so agr (palavras reservadas)
