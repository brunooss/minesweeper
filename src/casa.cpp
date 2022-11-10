#include "casa.hpp"

bool Casa::isBomba() const{
	return this->bomba;
}

bool Casa::isBandeira() const{
	return this->bandeira;
}

bool Casa::isRevelada() const{
	return this->revelada;
}

int Casa::getContagem() const{
	return this->contagem;
}

void Casa::setBandeira(bool estado){
	this->bandeira = estado;
}

void Casa::setRevelada(bool estado){
	this->revelada = estado;
}

void Casa::setContagem(int contagem){
	this->contagem = contagem;
}

void Casa::contarVizinhos(int lin, int col, std::vector<std::vector<Casa*>> casas){
	
}