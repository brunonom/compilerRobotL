//its a letter
bool autm_letra(char lexeme){
	lexeme = lexeme | 32; //maiusculo -> minusculo
	return('a'<=lexeme && lexeme<='z');
}

//its a digit
bool autm_digito(char lexeme){
	return('0'<=lexeme && lexeme<='9');
}

//convert a char into a position (for the automata)
//a=0, b=1, ..., z=26
int char_to_pos(char c){
	if(autm_letra(c)){
		return c-'a';
	}
	return -1;
}

//convert a digit into a position (for the automata)
//0=0, 1=1, ..., 9=9
int digit_to_pos(char c){
	if(autm_digito(c)){
		return c-'0';
	}
	return -1;
}

//convert a char or a digit into a position (for the automata)
//a=0, b=1, ..., z=26, 0=27, 1=28, ..., 9=36
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

//turns every letter in a string into a lowercase letter
string convert_to_lowercase(string x){
	for(int i=0; i<x.size(); i++){
		if(autm_letra(x[i])){
			x[i] = x[i] | 32;
		}
	}
	return x;
}

//its a direction
bool autm_sentido(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	if(
		lexeme == "esquerda" ||
		lexeme == "direita"
		){
		return true;
	}
	return false;
}

//its a condition sentence
bool autm_condicao(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
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

//its a number
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

//its an identifier
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

//its an instruction (unfinished)
bool autm_instrucao(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	if(
		lexeme == "mova" ||
		lexeme == "passos" ||
		lexeme == "vire para" ||
		lexeme == "pare" ||
		lexeme == "finalize" ||
		lexeme == "apague lampada" ||
		lexeme == "acenda lampada" ||
		lexeme == "aguarde ate"
		){
		return true;
	}
	return false;
}

//its a condition
bool autm_condicional(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	if(
		lexeme == "se" ||
		lexeme == "entao" ||
		lexeme == "fimse" ||
		lexeme == "senao" ||
		lexeme == "fimsenao"
		){
		return true;
	}
	return false;
}

//issa loop
bool autm_laco(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	return(
		lexeme == "enquanto" ||
		lexeme == "faca" ||
		lexeme == "fimpara"
		);
}

//issan iteration
bool autm_iteracao(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	return(
		lexeme == "repita" ||
		lexeme == "vezes" ||
		lexeme == "fimrepita"
		);
}

//issa blocc
bool autm_bloco(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	return(
		lexeme == "inicio" ||
		lexeme == "fim"
		);
}

//issa declaration
bool autm_declaracao(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	return(
		lexeme == "definainstrucao" ||
		lexeme == "como"
		);
}

//issa program
bool autm_programa(string lexeme){
	lexeme = convert_to_lowercase(lexeme);
	return(
		lexeme == "programainicio" ||
		lexeme == "execucaoinicio" ||
		lexeme == "fimexecucao" ||
		lexeme == "fimprograma"
		);
}