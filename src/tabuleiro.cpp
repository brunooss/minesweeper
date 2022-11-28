#include "tabuleiro.hpp"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

Tabuleiro::Tabuleiro(int dificuldade){
	switch (dificuldade){
		case 1:
			this->nLinhas = 8;
			this->nColunas = 8;
			this->bombas = 8;
			break;
		case 2:
			this->nLinhas = 12;
			this->nColunas = 12;
			this->bombas = 25;
			break;
		case 3:
			this->nLinhas = 18;
			this->nColunas = 18;
			this->bombas = 80;
			break;
	}
	
	this->bandeiras = 0;
	this->casasReveladas = 0;
}

int Tabuleiro::getNLinhas(){
	return this->nLinhas;
}

int Tabuleiro::getNColunas(){
	return this->nColunas;
}

int Tabuleiro::getBombas(){
	return this->bombas;
}

int Tabuleiro::getBandeiras(){
	return this->bandeiras;
}

std::vector<std::vector<Casa*>> Tabuleiro::getCasas(){
	return this->casas;
}

void Tabuleiro::setCasas(std::vector<std::vector<Casa*>> casas){
	this->casas = casas;
}

void Tabuleiro::criarTabuleiro(int lin, int col){
	std::vector<std::vector<Casa*>> casas;
	std::vector<std::vector<bool>> tabBombas = this->gerarBombas(lin, col);
	
	for (int i = 0; i < this->getNLinhas(); i++){
		std::vector<Casa*> linha;
		
		for (int j = 0; j < this->getNColunas(); j++){
			if (tabBombas[i][j]){
				Casa* bomba = new Bomba();
				linha.push_back(bomba);
			} else{
				Casa* vazia = new Vazia();
				linha.push_back(vazia);
			}
		}
		
		casas.push_back(linha);
	}
	
	this->casas = casas;
	this->contagemTabuleiro();
}

void Tabuleiro::contagemTabuleiro(){
	for (int i = 0; i < this->nLinhas; i++){
		for (int j = 0; j < this->nColunas; j++){
			if (!this->casas[i][j]->isBomba()){
				this->casas[i][j]->contarVizinhos(i, j, this->casas);
			}
		}
	}
}

bool Tabuleiro::checarDerrota(int lin, int col){
	return this->casas[lin][col]->isBomba();
}

bool Tabuleiro::checarVitoria(){
	return (this->nLinhas * this->nColunas - this->bombas == this->casasReveladas);
}

std::vector<std::vector<bool>> Tabuleiro::gerarBombas(int lin, int col){
	srand(time(NULL));
	std::vector<std::vector<bool>> tabBombas;
	
	for (int i = 0; i < this->nLinhas; i++){
		std::vector<bool> linha;
		
		for (int j = 0; j < this->nColunas; j++){
			linha.push_back(false);
		}
		
		tabBombas.push_back(linha);
	}
	
	for (int i = 0; i < this->bombas; i++){
		int rLin, rCol;
		
		while (1){
			rLin = rand() % (this->nLinhas);
			rCol = rand() % (this->nColunas);
			if (rLin != lin or rCol != col){
				if (!tabBombas[rLin][rCol]){
					break;
				}
			}
		}
		
		tabBombas[rLin][rCol] = true;
	}
	
	return tabBombas;
}

void Tabuleiro::revelarCasas(int lin, int col){
	if (checarDerrota(lin, col)){
		for (int i = 0; i < this->nLinhas; i++){
			for (int j = 0; j < this->nColunas; j++){
				if (casas[i][j]->isBomba()){
					casas[i][j]->setRevelada(true);
				}
			}
		}
	} else if (this->casas[lin][col]->getContagem() == 0){
		//TODO: DFS
		this->dfs(lin, col);
	} else{
		casas[lin][col]->setRevelada(true);
		this->casasReveladas++;
	}
}

void Tabuleiro::registrarPartida(){
	std::fstream file;
	file.open("src/partidas.txt", std::ios::app);
	
	std::vector<std::vector<Casa*>> casas = this->casas;
	std::string registro, binario, temp, strDecimal, vitoria;
	int nCasas = this->nLinhas * this->nColunas, decimal, dificuldade;
	int operacoes = nCasas / 15 + (nCasas % 15 != 0);
	
	switch(this->nLinhas){
		case 8:
			dificuldade = 1;
			break;
		case 12:
			dificuldade = 2;
			break;
		case 18:
			dificuldade = 3;
			break;
	}
	
	if (this->checarVitoria()){
		vitoria = "1";
	} else{
		vitoria = "0";
	}
	
	for (std::vector<Casa*> linha : casas){
		for (Casa* casa : linha){
			binario += std::to_string(casa->isBomba()) + std::to_string(casa->isRevelada());
		}
	}
	
	file << dificuldade << std::endl << binario << std::endl << vitoria << std::endl;
	file.close();
}

void Tabuleiro::lerPartidas(){
	std::fstream file;
	file.open("src/partidas.txt", std::ios::in);
	
	std::string linha, nomeDif;
	std::vector<std::string> dificuldades, tabuleiros, vitorias;
	int i = 0, dificuldade;
	
	while (std::getline(file, linha)){
		if (linha == "\n"){
			continue;
		}
		
		if (i == 0){
			dificuldades.push_back(linha);
		} else if (i == 1){
			tabuleiros.push_back(linha);
		} else if (i == 2){
			vitorias.push_back(linha);
			i = -1;
		}
		
		i++;
	}
	
	file.close();
	
	for (int i = 0; i < dificuldades.size(); i++){
		dificuldade = stoi(dificuldades[i]);
		
		if (dificuldade == 1){
				nLinhas = 8;
				nColunas = 8;
				nomeDif = "facil";
				this->nLinhas = 8;
				this->nColunas = 8;
				this->bombas = 8;
		} else if (dificuldade == 2){
				nLinhas = 12;
				nColunas = 12;
				nomeDif = "media";
				this->nLinhas = 12;
				this->nColunas = 12;
				this->bombas = 25;
		} else if (dificuldade == 3){
				nLinhas = 18;
				nColunas = 18;
				nomeDif = "difícil";
				this->nLinhas = 18;
				this->nColunas = 18;
				this->bombas = 80;
		}
		
		int nCasas = nLinhas * nColunas;
		std::string registro = tabuleiros[i], bits;
		std::vector<std::vector<Casa*>> casas;
		
		for (int j = 0; j < nLinhas; j++){
			std::vector<Casa*> linha;
			
			for (int k = 0; k < nColunas; k++){
				Casa* casa;
				int index = j * nColunas + k;
				bits = registro.substr(2 * index, 2);
				
				if (bits[0] == '1'){
					casa = new Bomba();
				} else{
					casa = new Vazia();
				}
				
				casa->setRevelada(bits[1] == '1');
				linha.push_back(casa);
			}
			
			casas.push_back(linha);
		}
		
		this->casas = casas;
		this->contagemTabuleiro();
		std::cout << "\nPartida " << i + 1 << " (" << nLinhas << "x" << nColunas << "): " << std::endl;
		this->printTabuleiro();
		std::cout << std::endl;
	}
}

void Tabuleiro::reiniciarTabuleiro(int dificuldade, int lin, int col){
	for (std::vector<Casa*> linha : this->casas){
		for (Casa* casa : linha){
			delete casa;
		}
		
		linha.clear();
	}
	
	switch (dificuldade){
		case 1:
			this->nLinhas = 8;
			this->nColunas = 8;
			this->bombas = 8;
			break;
		case 2:
			this->nLinhas = 12;
			this->nColunas = 12;
			this->bombas = 25;
			break;
		case 3:
			this->nLinhas = 18;
			this->nColunas = 18;
			this->bombas = 80;
			break;
	}
	
	this->criarTabuleiro(lin, col);
}

void Tabuleiro::printTabuleiro(){
	std::cout << std::endl;
	
	for (int i = 0; i < nLinhas; i++){
		for (int j = 0; j < nColunas; j++){
			if (this->casas[i][j]->isRevelada()){
				if (this->casas[i][j]->isBomba()){
					std::cout << "B ";
				} else{
					std::cout << this->casas[i][j]->getContagem() << " ";
				}
			} else{
				std::cout << "* ";
			}
		}
		
		std::cout << std::endl;
	}
}

int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int dy[] = {1, 1, 1, 0, -1, -1, -1, 0};
void Tabuleiro::dfs(int lin, int col){

	Casa* atual = casas[lin][col];
	
	if(atual->isRevelada()){
		return;
	}
	
	atual->setRevelada(true);
	casasReveladas++;
	
	if(atual->getContagem()>0){
		return;
	}
	
	for(int i=0;i<8;i++){
		
		int linviz = lin + dx[i];
		int colviz = col + dy[i];
		
		if((linviz>=nLinhas)||(linviz<0)){
			continue;
		}
		
		if((colviz>=nColunas)||(colviz<0)){
			continue;
		}
		
		dfs(linviz, colviz);		
	}
}