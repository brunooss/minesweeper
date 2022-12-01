#include "casa.hpp"

# retorna bomba
bool Casa::isBomba() const{
	return this->bomba;
}

# retorna bandeira
bool Casa::isBandeira() const{
	return this->bandeira;
}

# retorna revelada
bool Casa::isRevelada() const{
	return this->revelada;
}

# retorna contagem
int Casa::getContagem() const{
	return this->contagem;
}

# atualiza o valor de bandeira passado por parâmetro
void Casa::setBandeira(bool estado){
	this->bandeira = estado;
}

# atualiza o valor de revelada passado por parâmetro
void Casa::setRevelada(bool estado){
	this->revelada = estado;
}

# atribui o número de vizinhos com bomba à variável contagem
void Casa::contarVizinhos(int lin, int col, std::vector<std::vector<Casa*>> casas){
	
}