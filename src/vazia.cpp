#include "vazia.hpp"

#include <iostream>

Vazia::Vazia(){
	this->bomba = false;
	this->bandeira = false;
	this->revelada = false;
}

void Vazia::contarVizinhos(int lin, int col, std::vector<std::vector<Casa*>> casas){
	this->contagem = 0;
	
	int contagem = 0, nLinhas = casas.size(), nColunas = casas[0].size();

	for (int i = -1; i <= 1; i++){
		
		if ((lin == 0 and i == -1) or (lin == nLinhas - 1 and i == 1)){
			continue;
		}
		
		for (int j = -1; j <= 1; j++){
			if ((col == 0 and j == -1) or (col == nColunas - 1 and j == 1)){
				continue;
			}
			
			if (casas[lin + i][col + j]->isBomba()){
				contagem++;
			}
		}
	}

	this->contagem = contagem;
}