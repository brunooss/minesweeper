#ifndef VAZIA_HPP
#define VAZIA_HPP

#include "casa.hpp"

class Vazia: public Casa{
	public:
		Vazia();
		void contarVizinhos(int lin, int col, std::vector<std::vector<Casa*>> casas) override;
};

#endif