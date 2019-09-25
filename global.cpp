namespace glob{

	//to know every char in the spurce code and its location
	struct char_pos{
		char character;
		int line_number;
		int column_number;

		char_pos(char c, int ln, int cn){
			character = c;
			line_number = ln;
			column_number = cn;
		}

		const bool operator==(const char_pos &b){
			return
			character == b.character && 
			line_number == b.line_number && 
			column_number == b.column_number;
		}
	};

	//tokens
	struct token{
		string name;
		string value;
		
		token(string n, string v){
			name = n; value = v;
		}
	};

	//the source file
	FILE * source_file;

	//every char and its position in the source code
	vector<char_pos> input_as_string;
	vector< vector<char_pos> > char_table;
	
	//symbol table
	vector<token> symbol_table;

	//reserved words
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
		"apaguelampada",
		"acendalampada",
		"aguardeate",
		"robopronto",
		"roboocupado",
		"roboparado",
		"robomovimentando",
		"frenterobobloqueada",
		"direitarobobloqueada",
		"esquerdarobobloqueada",
		"lampadaacesaafrente",
		"lampadaapagadaafrente",
		"lampadaacesaaesquerda",
		"lampadaapagadaaesquerda",
		"lampadaacesaadireita",
		"lampadaapagadaadireita",
		"esquerda",
		"direita"
	};
}