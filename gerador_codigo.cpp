ofstream produto;
glob::node *last_node = nullptr;
int id_loop = 0;
int id_while = 0;
stack<int> loop_id, while_id;
stack<string> conditions;
bool aguardeate = 0;
bool enquanto = 0;
bool definainstrucao = 0;
bool se = 0;
int se_id = 0;
bool zzz = false;
string instr;
void dfs(glob::node *atual, int depth){
	cout << atual->nome << " " << atual->value << " " << depth << endl;
	if(atual->nome == "fimse"){
		produto << "jmp endif_" << se_id << endl;
		zzz = true;
		produto << "false_" << se_id << ":" << endl;
	}
	else if(zzz && (atual->nome != "x1" && atual->nome != "x2" && atual->nome != "x3")){
		zzz = false;
		if(atual->nome!="senao") produto << "endif_" << se_id << ":" << endl; 
	}
	if(atual->nome == "id"){
		if(last_node->nome == "definainstrucao"){
			if(definainstrucao){
				produto << "ret" << endl;
				produto << instr << " endp" << endl << endl;
			}
			produto << atual->value << " proc\n";
			instr = atual->value;
			definainstrucao = true;
		}
		else{
			produto << "call " << atual->value << "\n";
		}
	}
	else if(atual->nome == "numero"){
		if(last_node->nome == "mova"){
			produto << "push cx" << endl;
			produto << "mov cx, " << atual->value << "\n";
			produto << "loop_" << id_loop << ":\n";
			produto << "call move_forward \n";
			produto << "loop loop_" << id_loop << "\n";
			produto << "pop cx" << endl;
			id_loop++;
		}
		else{
			produto << "push cx" << endl;
			produto << "mov cx, " << atual->value << "\n";
			produto << "loop_" << id_loop << ":\n";
			loop_id.push(id_loop);
			id_loop++;
		}
	}
	else if(atual->nome == "fimrepita"){
		if(loop_id.empty()){
			cout << "ERRO NA GERACAO, SEM FECHAMENTO DE LOOP" << endl;
			exit(0);
		}
		else{
			produto << "loop loop_" << loop_id.top() << endl;
			produto << "pop cx" << endl;
			loop_id.pop();
		}
	}
	else if(atual->nome == "aguardeate"){
		aguardeate = true;
		produto << "while_" << id_while << ":" << endl;
	}
	else if(last_node != nullptr && last_node->nome == "condicao"){
		if(aguardeate){
			aguardeate = false;
			produto << "call " << atual->nome << endl;
			produto << "cmp bx, 0" << endl;
			produto << "je while_" << id_while++ << endl; 
		}
		else if(enquanto){
			enquanto = false;
			conditions.push(atual->nome);
		}
		else if(se){
			se = false;
			produto << "call " << atual->nome << endl;
			produto << "cmp bx,0" << endl;
			produto << "je false_" << ++se_id << endl;
		}
	}
	else if(atual->nome == "enquanto"){
		enquanto = true;
		produto << "while_" << id_while <<":" << endl;
		while_id.push(id_while);
		id_while++;
	}
	else if(atual->nome == "fimpara"){
		if(conditions.empty() or while_id.empty()){
			cout << "ERRO NA GERACAO, SEM CONDICAO" << endl;
			exit(0);
		}
		else{
			produto << "call " << conditions.top() << endl;
			conditions.pop();
			produto << "cmp bx, 1" << endl;
			produto << "je while_" << while_id.top() << endl;
			while_id.pop();
		}
	}
	else if(last_node != nullptr && last_node->nome == "instrucao"){
		if(atual->nome == "pare" or atual->nome=="finalize" or 
		   atual->nome=="apaguelampada" or atual->nome=="acendalampada")
			produto << "call " << atual->nome << endl;
	}
	else if(atual->nome == "esquerda"){
		produto << "call turn_left" << endl;
	}
	else if(atual->nome == "direita"){
		produto << "call turn_right" << endl;
	}
	else if(atual->nome == "execucaoinicio"){
		if(definainstrucao){
			produto << "ret" << endl;
			produto << instr << " endp" << endl << endl;
			definainstrucao = false;
		}
	}
	else if(atual->nome == "se"){
		se = true;
	}
	else if(atual->nome == "fimsenao"){
		produto << "endif_" << se_id << ":" << endl; 
	}
	if(atual->nome != "x1" && atual->nome != "x2" && atual->nome != "x3")
		last_node = atual;
	for(int i=0;i<atual->adj.size();i++)
		dfs(atual->adj[i],depth+1);
}


bool gera_codigo(){
	produto = ofstream(glob::source_file_name.substr(0,(int)glob::source_file_name.size() - 4) + ".asm", ofstream::out);
	ifstream base("base.asm");
	string linha;
	int lat = 0;
	while(getline(base,linha)){
		produto << linha << endl;
		lat++;
		if(lat == 37){
			break;
		}
	}
	//produto << "era pra sair no loop\n";
	dfs(glob::root,0);
	// termina arquivo (constroi funcoes basicas e termina o loop principal)
	while(getline(base,linha))
		produto << linha << endl;
	base.close();
	return true;
	
}

bool main_gerador(bool verbose){
	bool a = gera_codigo();
	produto.close();
	return true;
}
