#include "tabuleiro.hpp"
#include <iostream>
#include <vector>


# imprime no terminal o tabuleiro passado por parâmetro, com todas as casas reveladas
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
}

# recebe como input a dificuldade e as casas a serem "clicadas", mostrando o tabuleiro depois de cada jogada
int main(){
	int dificuldade;
	bool fim = false;
	std::string espacos(14, ' ');
	
	std::cout << "Dificuldades: 1 - facil (8x8)\n" << espacos << "2 - media (12x12)\n" << espacos << "3 - dificil (18x18)" << std::endl << std::endl;
	
	do{
		std::cout << "Qual a dificuldade desejada? ";
		std::cin >> dificuldade;
	} while (dificuldade < 1 or dificuldade > 3);
	
	Tabuleiro tabuleiro(dificuldade);
	int lin, col, nLin = tabuleiro.getNLinhas(), nCol = tabuleiro.getNColunas();
	
	std::cout << "\nDigite a linha (1 a " << nLin << "): ";
	std::cin >> lin;
	lin--;
	
	std::cout << "Digite a coluna (1 a " << nCol << "): ";
	std::cin >> col;
	col--;
	
	tabuleiro.criarTabuleiro(lin, col);
	//printTabuleiroRevelado(tabuleiro);
	tabuleiro.revelarCasas(lin, col);
	tabuleiro.printTabuleiro();
	
	if (tabuleiro.checarDerrota(lin, col)){
		std::cout << "\nVoce perdeu!" << std::endl;
		fim = true;
	} else if (tabuleiro.checarVitoria()){
		std::cout << "\nVoce venceu!" << std::endl;
		fim = true;
	}
	
	char resposta;
	
	while (1){
		while (!fim){
			
			std::cout << "\nDigite a linha (1 a " << nLin << "): ";
			std::cin >> lin;
			lin--;
			std::cout << "Digite a coluna (1 a " << nCol << "): ";
			std::cin >> col;
			col--;
			
			tabuleiro.revelarCasas(lin, col);
			tabuleiro.printTabuleiro();
			
			if (tabuleiro.checarDerrota(lin, col)){
				std::cout << "\nVoce perdeu!" << std::endl;
				fim = true;
			} else if (tabuleiro.checarVitoria()){
				std::cout << "\nVoce venceu!" << std::endl;
				fim = true;
			}
		}
		
		std::cout << "\nDeseja salvar a partida? (s/n) ";
		std::cin >> resposta;
		if (resposta == 's'){
			tabuleiro.registrarPartida();
			std::cout << "Partida salva!" << std::endl;
		}

		std::cout << "\nDeseja reiniciar a partida? (s/n) ";
		std::cin >> resposta;
		
		if (resposta == 's'){
			std::cout << "\nDificuldades: 1 - facil (8x8)\n" << espacos << "2 - media (12x12)\n" << espacos << "3 - dificil (18x18)" << std::endl;
			
			do{
				std::cout << "\nQual a dificuldade desejada? ";
				std::cin >> dificuldade;
			} while (dificuldade < 0 or dificuldade > 3);
			
			if (dificuldade == 1){
				nLin = 8;
				nCol = 8;
			} else if (dificuldade == 2){
				nLin = 12;
				nCol = 12;
			} else{
				nLin = 18;
				nCol = 18;
			}
			
			std::cout << "\nDigite a linha (1 a " << nLin << "): ";
			std::cin >> lin;
			lin--;
			std::cout << "Digite a coluna (1 a " << nCol << "): ";
			std::cin >> col;
			col--;
			
			tabuleiro.reiniciarTabuleiro(dificuldade, lin, col);
			tabuleiro.revelarCasas(lin, col);
			tabuleiro.printTabuleiro();
			fim = false;
		} else{
			std::vector<std::vector<Casa*>> casas = tabuleiro.getCasas();
			
			for (std::vector<Casa*> linha : casas){
				for (Casa* casa : linha){
					delete casa;
				}
			}
			
			casas.clear();
			tabuleiro.setCasas(casas);
			break;
		}
	}
}