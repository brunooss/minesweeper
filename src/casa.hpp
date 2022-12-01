#ifndef CASA_HPP
#define CASA_HPP

#include <vector>

class Casa{
	public:
		bool isBomba() const;
		bool isBandeira() const;
		bool isRevelada() const;
		int getContagem() const;
		void setBandeira(bool estado);
		void setRevelada(bool estado);
		virtual void contarVizinhos(int lin, int col, std::vector<std::vector<Casa*>> casas);
	
	protected:
		bool bomba;
		bool bandeira;
		bool revelada;
		int contagem;
};

#endif