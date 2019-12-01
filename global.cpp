namespace glob{

	//to know every char in the source code and its location
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
		int line_number;
		int column_number;
		token(string n, string v){
			name = n; value = v;
		}
	};

	struct grammar{
		struct production{
			string nonterminal;
			vector<string> body;
			production(string nonterminal, vector<string> &body) : nonterminal(nonterminal), body(body) {}
		};
		vector<production> productions;
		void insert_Production(string nonterminal, vector<string> &body){
			productions.push_back(production(nonterminal,body));
		}
	};
	
	// grammar to be built in syntactic analysis.
	grammar G;
	
	// map used for table transitions in syntactic analysis.
	#define pss pair<string,string>
	map<pss,int> T;
	#undef pss

	//counts frequency of each id
	map<string,int> id_frequency;

	//the source file
	FILE * source_file;
	string source_file_name;


	//every char and its position in the source code
	vector<char_pos> char_table;
	
	//symbol tables
	vector<token> symbol_table;
	vector<token> symbol_table_syntax;

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
		"vire",
		"para",
		"pare",
		"finalize",
		"apague",
		"acenda",
		"aguarde",
		"ate",
		"robo",
		"pronto",
		"ocupado",
		"parado",
		"movimentando",
		"frente",
		"direita",
		"esquerda",
		"bloqueada",
		"lampada"
		"acesa",
		"apagada",
		"a"
		"$"
	};
	
	struct node{
		vector< node* > adj;
		node *parent = nullptr;
		string value;
		string nome;
		int son = 0;
		node(string x,string y){
			nome = x;
			value = y;

		}
	};

	node *root;
}

