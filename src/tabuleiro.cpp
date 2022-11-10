#include "tabuleiro.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

Tabuleiro::Tabuleiro(int nLin, int nCol, int bombas){
	this->nLinhas = nLin;
	this->nColunas = nCol;
	this->bombas = bombas;
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
			rCol = rand() % (this->nLinhas);
			
			if (rLin != lin and rCol != col){
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
		//TODO: algoritmo minimax
		casas[lin][col]->setRevelada(true);
		this->casasReveladas++;
	} else{
		casas[lin][col]->setRevelada(true);
		this->casasReveladas++;
	}
}