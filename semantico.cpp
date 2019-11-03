
bool check_ids(){
	for(auto id : glob::id_frequency){
		if(id.second > 1){
			cout << "Identificador duplicado : " << id.first << endl;
			return false;
		}
		//cout << id.first << " " << id.second << endl;
	}
	return true;
}


bool check_SemanticRule2and3(){
	#define left 0
	#define right 1
	#define none 2
	vector<glob::token> &tab = glob::symbol_table;
	int n = tab.size();
	int last_turn = none;
	for(int i=0;i<n;i++){
		string x = tab[i].value;
		if(x=="vire para"){
			string y = tab[i+1].value;
			if(y=="esquerda" && last_turn == right){
				cout << "Vire Para direita seguido de Vire Para esquerda." << endl;
				return false;
			}
			else if(y=="direita" && last_turn == left){
				cout << "Vire Para esquerda seguido de Vire Para direita." << endl;
				return false;
			}
			last_turn = (y=="direita" ? right : left);
		}
		if(x=="mova"){
			// estrutura obrigatoria : "mova numero passos aguardeate robopronto"
			// enumerando temos :         i    i+1   i+2      i+3        i+4 
			if(i+3 >= n or tab[i+3].value != "aguarde ate" or tab[i+4].value != "robo pronto" ){
				cout << "Falta Aguarde Ate Robo Pronto após mova n passos." << endl;
				return false;
			}
			return true;
		}
	}
	#undef left
	#undef right
	#undef none
	return true;
}

bool main_sem(bool verbose){
	// ids iguais
	bool ok = check_ids();
	if(!ok) return ok;

	// Declarações Vire Para imediatamente subseqüentes tenham sentidos diferentes.
	// Apos instrucao "Mova n" tem que ter "Aguarde ate robo pronto"
	ok &= check_SemanticRule2and3();
	
	return ok;
}