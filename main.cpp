
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define N 20
#define M 20
#define B 50


/*	B é a qtd. de bombas, N é a largura e M é a altura 
	B deve ser no máximo uns 4/5 de N*M para o algoritmo 
	de gerar as bombas funcionar rápido.*/

#define Min(a, b) ( ((a) < (b)) ? (a) : (b) )
#define Max(a, b) ( ((a) > (b)) ? (a) : (b) )

	
	
char tab[N*M];
char viz[N*M];



int ale(){
	int x = rand()%(N*M);
	if(x<0) x = -x;
	return x;
}

void gerabombas(){
	int bomb = B;
	int sq;
	srand(time(NULL));
	while(bomb){
		if(!tab[sq = ale()]){
			bomb--;
			tab[sq] = -1;
		}
	}
}

int conta(int a){
	int i = a/N;
	int j = a%N;
	
}

//void geranumeros(){
//	for(int i=0;i<N;i++){
//		for(int j=0;j<M-1;j++){
//			if(tab[i*N+j]) continue;
//			tab[i*N+j] = conta(i*N+j);
//		}
//	}
//}

void geranumeros(){
	for(int dx=-1;dx<=1;dx++){
		for(int dy=-1;dy<=1;dy++){
			if((dx==0)&&(dy==0)) continue;
			for(int i=Max(0, -dx);i<Min(N, N-dx);i++){
				for(int j=Max(0, -dy);j<Min(M, M-dy);j++){
					int l = M*i + j;
					int k = M*(i+dx) + j+dy;
					if(tab[k]==-1) continue;
					if(tab[l]==-1) tab[k]++;
				}
			}
		}
	}
}


int printab(){
	int r=0;
	for(int i=0;i<100;i++){
		printf("\n");
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M-1;j++){
			printf("%3d ", tab[i*M+j]);
			if(tab[i*N+j]==-1) r++;
		}
		printf("%3d\n", tab[i*M+M-1]);
		printf("\n");
	}
	return r;
}




char form(int a){
	if(!viz[a]){
		return '*';
	}
	if(tab[a]==-1){
		return '<';
	}
	return '0' + tab[a];
}

int prinjogo(){
	int r=0;
	for(int i=0;i<100;i++){
		printf("\n");
	}
	
	printf("     ");
	for(int j=0;j<M;j++){
		printf("%3d ", j);
	}
	printf("\n\n");
	for(int i=0;i<N;i++){
		printf(" %3d  ", i);
		for(int j=0;j<M-1;j++){
			printf(" %c  ", form(i*M+j));
			if(tab[i*M+j]==-1) r++;
		}
		printf(" %c \n", form(i*M+M-1));
		printf("\n");
	}
	return r;
}

int acao(int x, int y){
	int c = x*M+y;
	if(tab[c]==-1){
		return -1;
	}
	if(tab[c]!=0){
		viz[c] = 1;
		return 0;
	}
	viz[c] = 1;
	return 0;
}

void perdeu(){
	printab();
	printf("\nEstourou a bomba!\nAcabou o jogo :(\n");
}

void jogo(){
	int x, y;
	while(1){
		prinjogo();
		printf("digite as coordenadas:\n");
		scanf("%d %d", &x, &y);
		if(acao(x, y)){
		perdeu();
			break;
		}
	}
}



int main(){
	
	
	gerabombas();
	geranumeros();
	
//	printf("\n\n%d\n", printab());
	jogo();
	
}













