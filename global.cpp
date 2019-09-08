namespace glob{

	struct char_pos{
		char character;
		int line_number;
		int column_number;

		char_pos(char c, int ln, int cn){
			character = c;
			line_number = ln;
			column_number = cn;
		}
	};

	bool equal_char_pos(char_pos a, char_pos b){
		return a.character == b.character && a.line_number == b.line_number && a.column_number == b.column_number;
	}

	struct token{
		string name;
		string value;
		
		token(string n, string v){
			name = n; value = v;
		}
	};

	FILE * source_file;
	vector<char_pos> char_table;
	char buffer;

	//q porra eh essa aqui mds to usando crack
	// token tk_programa = token("programa", "");
	// token tk_declaracao = token("declaracao", "");
	// token tk_bloco = token("bloco", "");
	// token tk_comando = token("comando", "");
	// token tk_iteracao = token("iteracao", "");
	// token tk_laco = token("laco", "");
	// token tk_condicional = token("condicional", "");
	// token tk_instrucao = token("instrucao", "");
	// token tk_condicao = token("condicao", "");
	// token tk_identificador = token("identificador", "");
	// token tk_numero = token("numero", "");
	// token tk_letra = token("letra", "");
	// token tk_digito = token("digito", "");
	// token tk_sentido = token("sentido", "");

	vector<string> reserved_words = {
		"programainicio",
		"execucaoinicio",
		"fimexecucao",
		"fimprograma",
		"definainstrucao",
		"como",
		"inicio",
		"fim",
		"repita",
		"vezes",
		"fimrepita",
		"enquanto",
		"faca",
		"fimpara",
		"se",
		"entao",
		"fimse",
		"senao",
		"fimsenao",
		"mova",
		"passos",
		"vire para",
		"pare",
		"finalize",
		"apague lampada",
		"acenda lampada",
		"aguarde ate",
		"robo pronto",
		"robo ocupado",
		"robo parado",
		"robo movimentando",
		"frente robo bloqueada",
		"direita robo bloqueada",
		"esquerda robo bloqueada",
		"lampada acesa a frente",
		"lampada apagada a frente",
		"lampada acesa a esquerda",
		"lampada apagada a esquerda",
		"lampada acesa a direita",
		"lampada apagada a direita",
		"esquerda",
		"direita"
	};

	vector<token> symbol_table;

	void prints(string s){
		for(char c : s){
			printf("%c", c);
		}
	}
}