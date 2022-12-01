
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define N 10
#define M 10
#define B 30


/*	B é a qtd. de bombas, N é a largura e M é a altura 
	B deve ser no máximo uns 4/5 de N*M para o algoritmo 
	de gerar as bombas funcionar rápido.*/

#define Min(a, b) ( ((a) < (b)) ? (a) : (b) )
#define Max(a, b) ( ((a) > (b)) ? (a) : (b) )

	
char tab[N*M];
char viz[N*M];
int qviz;
char marc[N*M];

int ex[] = {0, -1, 0, 1};
int ey[] = {1, 0, -1, 0};

int ale(){
	int x = rand()%(N*M);
	if(x<0) x = -x;
	return x;
}

void geranumeros(int i,int j){
	for(int dx=-1;dx<=1;dx++){
		for(int dy=-1;dy<=1;dy++){
			if((dx==0)&&(dy==0)) continue;
			if((i+dx<0)||(i+dx>=N)||(j+dy<0)||(j+dy>=M)) continue;
			if(tab[(i+dx)*M+j+dy]!=-1) tab[(i+dx)*M+j+dy]++;
		}
	}
}

void gerabombas(){
	int bomb = B;
	int sq;
	srand(time(NULL));
	while(bomb){
		if(tab[sq = ale()]!=-1){
			bomb--;
			tab[sq] = -1;
			int i = sq/M;
			int j = sq%M;
			geranumeros(i, j);
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
			if(tab[i*M+j]==-1) r++;
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

void dfs(int x, int y){
	int c = x*M+y;
	if(viz[c]==0){
		viz[c] = 1;
		qviz++;
	}
	if(tab[c]!=0) return;
	if(marc[c]!=0) return;
	marc[c] = 1;
	
	for(int i=0;i<4;i++){
		int a = x+ex[i];
		int b = y+ey[i];
		if((a<0)||(a>=N)||(b<0)||(b>=M)) continue;
		if(marc[a*M+b]==0){
			dfs(a, b);
		}
	}
}

int acao(int x, int y){
	int c = x*M+y;
	if(tab[c]==-1){
		return -1;
	}
	if(tab[c]!=0){
		if(viz[c]==0){
			viz[c] = 1;
			qviz++;
		}
		return 0;
	}
	dfs(x, y);
	return 0;
}


void perdeu(){
	printab();
	printf("\nEstourou a bomba!\nAcabou o jogo :(\nEntre r para reiniciar\n");
}

void ganhou(){
	printf("\nParabens!\nEntre r para reiniciar\n");
}

int jogo(){
	int x, y;
	int status = 0;
	while(1){
		prinjogo();
		printf("digite as coordenadas:\n");
		int n = scanf("%d %d", &x, &y);
		if(n!=2){
			status = 1;
			break;
		}
		if(acao(x, y)){
			perdeu();
			break;
		}
		if(qviz==(N*M-B)){
			ganhou();
			break;
		}
	}
	return status;
}

void limpa(){
	for(int i=0;i<N*M;i++){
		tab[i] = 0;
		marc[i] = 0;
		viz[i] = 0;
		qviz = 0;
	}
}

int main(){

	char c;
	while(1){
		limpa();
		gerabombas();
		int status = jogo();
		if(status!=0){
			printf("deu algum erro!\n");
			break;
		}
		scanf(" %c", &c);
		if(c!='r'){
			break;
		}
	}
	
}












