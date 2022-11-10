#include "tabuleiro.hpp"
#include <iostream>
#include <vector>

void printTabuleiro(Tabuleiro tabuleiro){
	int lin = tabuleiro.getNLinhas();
	int col = tabuleiro.getNColunas();
	std::vector<std::vector<Casa*>> casas = tabuleiro.getCasas();
	
	std::cout << std::endl;
	
	for (int i = 0; i < lin; i++){
		for (int j = 0; j < col; j++){
			if (casas[i][j]->isRevelada()){
				if (casas[i][j]->isBomba()){
					std::cout << "B ";
				} else{
					std::cout << casas[i][j]->getContagem() << " ";
				}
			} else{
				std::cout << "* ";
			}
		}
		
		std::cout << std::endl;
	}
}

void printTabuleiroRevelado(Tabuleiro tabuleiro){
	int lin = tabuleiro.getNLinhas();
	int col = tabuleiro.getNColunas();
	std::vector<std::vector<Casa*>> casas = tabuleiro.getCasas();
	
	std::cout << std::endl;
	
	for (int i = 0; i < lin; i++){
		for (int j = 0; j < col; j++){
			if (casas[i][j]->isBomba()){
				std::cout << "B ";
			} else{
				std::cout << casas[i][j]->getContagem() << " ";
			}
		}
		
		std::cout << std::endl;
	}
	
	std::cout << std::endl;
}

int main(){
	int nLin, nCol, bombas;
	
	std::cout << "Digite o numero de linhas: ";
	std::cin >> nLin;
	
	std::cout << "Digite o numero de colunas: ";
	std::cin >> nCol;
	
	std::cout << "Digite o numero de bombas: ";
	std::cin >> bombas;
	
	Tabuleiro tabuleiro(nCol, nLin, bombas);
	//printTabuleiro(tabuleiro);
	
	int lin, col;
	
	std::cout << "\nDigite a linha (1 a " << nLin << "): ";
	std::cin >> lin;
	lin--;
	
	std::cout << "Digite a coluna (1 a " << nCol << "): ";
	std::cin >> col;
	col--;
	
	tabuleiro.criarTabuleiro(lin, col);
	printTabuleiroRevelado(tabuleiro);
	std::vector<std::vector<Casa*>> casas = tabuleiro.getCasas();
	casas[lin][col]->setRevelada(true);
	tabuleiro.setCasas(casas);
	printTabuleiro(tabuleiro);
	
	while (1){
		
		std::cout << "\nDigite a linha (1 a " << nLin << "): ";
		std::cin >> lin;
		lin--;
		std::cout << "Digite a coluna (1 a " << nCol << "): ";
		std::cin >> col;
		col--;
		
		std::vector<std::vector<Casa*>> casas = tabuleiro.getCasas();
		tabuleiro.revelarCasas(lin, col);
		tabuleiro.setCasas(casas);
		printTabuleiro(tabuleiro);
		
		if (tabuleiro.checarDerrota(lin, col)){
			std::cout << "\nVoce perdeu!" << std::endl;
			break;
		} else if (tabuleiro.checarVitoria()){
			std::cout << "\nVoce venceu!" << std::endl;
			break;
		}
	}
}