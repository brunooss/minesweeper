#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

#include "vazia.hpp"
#include "bomba.hpp"
#include <vector>

class Tabuleiro{
	private:
		int nLinhas, nColunas, bombas, bandeiras, casasReveladas;
		std::vector<std::vector<Casa*>> casas;
	
	public:
		Tabuleiro(int dificuldade);
		int getNLinhas();
		int getNColunas();
		int getBombas();
		int getBandeiras();
		std::vector<std::vector<Casa*>> getCasas();
		void setCasas(std::vector<std::vector<Casa*>> casas);
		void criarTabuleiro(int lin, int col);
		void contagemTabuleiro();
		bool checarDerrota(int lin, int col);
		bool checarVitoria();
		std::vector<std::vector<bool>> gerarBombas(int lin, int col);
		int gerarRandInt();
		void revelarCasas(int lin, int col);
		void registrarPartida();
		void lerPartidas();
		void reiniciarTabuleiro(int dificuldade, int lin, int col);
		void printTabuleiro();
		void dfs(int lin, int col);
};

#endif