void lex_to_syn_tokens(){

	regex r("\\s+");

	for (glob::token t : glob:: symbol_table) {
		string n = regex_replace(t.name, r, "");

		glob::token newtoken(n, t.value);
		newtoken.line_number = t.line_number;
		newtoken.column_number = t.column_number;

		glob::symbol_table_syntax.push_back(newtoken);

	}

}

void print_symbol_table_syntax(){
	printf("\ntabela de tokens pós-adaptação\n");
	printf("----------------------------------------\n");
	cout << "[token] : [valor]\n";
	for(glob::token t : glob::symbol_table_syntax){
		string n = t.name;
		string v = t.value;
		cout << n << " : " << v << "\n";
	}
	printf("----------------------------------------\n");
}

bool build_grammar(){
	ifstream input("sintatico.in");
	/*
		Modelo de input da gramatica:
		N
		P1
		P2
		.
		.
		.
		Pn

		ex. P_i == Nonterminal k R1 R2 R3 ... Rk
	*/
	if(!input){return false;}
	int n,k;
	input >> n;
	string Nonterminal;
	vector<string> body;
	for(int i=0;i<n;i++){
		input >> Nonterminal;
		input >> k;
		body.resize(k);
		for(int j=0;j<k;j++){
			input >> body[j];
		}
		glob::G.insert_Production(Nonterminal,body);
	}
	input.close();
	return true;
}

bool build_table(){
	ifstream input("tabela.in");
	/*
		Modelo de input da tabela:
		Z -> quantidade de regras existentes na tabela
		Li Cj Rk 
		... ler Z 3-uplas
		Representam : Existe uma transição do estado Linha i Coluna J para a regra de produção Rk
		Obs: Li = string que representa Li, Cj = string que representa Cj, Rk = Numero que representa a producao a ser ativada.
		Rk = 1-based
	*/
	if(!input){return false;}
	int Z,p;
	input >> Z;
	#define pss pair<string,string>
	pss D;
	for(int i=0;i<Z;i++){
		input >> D.first >> D.second >> p;
		glob::T[D] = p;
	}
	#undef pss
	return true;
}

bool LL1_parser(){
	using namespace glob;
	stack<string> s;
	s.push("$");
	s.push("programa");
	root = new node("programa","$");

	// tokens are in symbol_table_syntax
	int i = 0;
	int r;
	#define pss pair<string,string>
	pss now;
	vector<glob::token> &tb = glob::symbol_table_syntax;
	node *atual = root;
	while(s.top() != "$"){
		if(i >= tb.size()){
			return false;
		}
		//cout << atual->value << endl;
		if(s.top() == tb[i].name){
			//cout << "MATCH: " << s.top() << " " << tb[i].name << endl;
			atual->value = tb[i].value;
			atual = atual->parent;
			atual->son++;
			while(atual->adj.size() <= atual->son && atual!=root){
				atual = atual->parent;
				atual->son++;
			}
			if(atual->adj.size() > atual->son){
				atual = atual->adj[atual->son];
			}
			s.pop();
			i++;
			continue;
		}
		now = pss(s.top(),tb[i].name);
		if(!glob::T.count(now)){
			cout << "ERRO: " << endl;
			cout << now.first << " " << now.second << "\n";
			return false;
		}
		//cout << now.first << " " << now.second << endl;
		s.pop();
		
		r = glob::T[now];
		//cout << "REGRA: " << r << endl;
		r--;
		
		vector<string> &v = glob::G.productions[r].body;
		for(int j=(int)v.size()-1; j>=0; j--){
			s.push(v[j]);
			atual->adj.push_back(new node(v[j],"$"));
			atual->adj.back()->parent = atual;
		}
		reverse(atual->adj.begin(), atual->adj.end());
		if(atual->adj.size() > 0){
			atual = atual->adj[0];
		}
		else{
			atual = atual->parent;
			atual->son++;
			while(atual->adj.size() <= atual->son && atual!=root){
				atual = atual->parent;
				atual->son++;
			}
			if(atual->adj.size() > atual->son){
				atual = atual->adj[atual->son];
			}
		}
	}
	#undef pss
	return true;
}

bool main_sin(bool verbose){

	lex_to_syn_tokens();
	
	if (verbose) print_symbol_table_syntax();

	bool ok = build_grammar();
	if(!ok) return ok;

	ok = build_table();
	if(!ok) return ok;

	ok = LL1_parser();
	return ok;
}

