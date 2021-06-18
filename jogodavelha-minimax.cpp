#include<bits/stdc++.h>
#define sz(x) ((int)x.size())

const int inf = INT_MAX;

using namespace std;

bool acabou = false;
int jogadas = 0;

char Final(char tab[3][3])
{
	for(int i = 0;i<3;i++)
	{
		if(tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2] && tab[i][0] != '-')
		{
			return tab[i][0];
		}
		if(tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i] && tab[0][i] != '-')
		{
			return tab[0][i];
		}
	}
	if(tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2] && tab[0][0] != '-')
		{
			return tab[0][0];
		}

	if(tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0] && tab[0][2] != '-')
		{
			return tab[0][2];
		}
	if(jogadas > 8)
		return 'e';
	return 'C';
}

int custo(char c)
{
	if(c == 'X')return -1;
	if(c == 'O')return 1;
	return 0;
}

int minimax(char tab[3][3],int profundidade,char jogador)
{
	char ganhador = Final(tab);
	if(ganhador != 'C')
		return custo(ganhador);

	if(jogador == 'O')
	{
		int melhor = -inf;
		for(int i = 0;i<3;i++)
		{ 
			for(int j = 0;j<3;j++)
			{
				if(tab[i][j] == '-')
				{
					tab[i][j] = 'O';
					int pontos = minimax(tab,profundidade + 1,'X');
					tab[i][j] = '-';
					melhor = max(melhor,pontos);
				}
			}
		}
		return melhor;
	}else
	{
		int melhor = inf;
		for(int i = 0;i<3;i++)
		{
			for(int j = 0;j<3;j++)
			{
				if(tab[i][j] == '-')
				{
					tab[i][j] = 'X';
					int pontos = minimax(tab,profundidade + 1,'O');
					tab[i][j] = '-';
					melhor = min(melhor,pontos);
				}
			}
		}
		return melhor;
	}
}

void print(char tab[3][3])
{
	cout<<"-------------"<<endl;
	for(int i = 0;i<3;i++)
	{
		for(int j = 0;j<3;j++)
		{
			cout<<tab[i][j]<<"     ";
		}
		cout<<endl<<endl;
	}
	cout<<"-------------"<<endl<<endl;

}

int main()
{
	
	char tabuleiro[3][3];
	memset(tabuleiro,'-',3*3);
	
	char eu = 'X',ia = 'O';
	bool vez = false;
	while(!acabou && jogadas < 9)
	{
		if(vez)
		{
			print(tabuleiro);
			int x,y;
			cout<<"x,y:";
			cin>>x>>y,x--,y--;
			if(x < 0 || y < 0 || x > 2 || y > 2 || tabuleiro[x][y] != '-')
			{
				cout<<"jogada invalida\n";
				continue;
			}
			
			tabuleiro[x][y] = eu;
			vez = false;
			if(Final(tabuleiro) == 'X')
			{
				acabou = true;
				cout<<"JOGADOR VENCEU\n";
			}
			jogadas++;
		}else
		{
			int melhor = -inf;
			int x,y;
			for(int i = 0;i<3;i++)
			{
				for(int j = 0;j<3;j++)
				{
					if(tabuleiro[i][j] == '-')
						{
						tabuleiro[i][j] = ia;
						int valor = minimax(tabuleiro,0,eu);
						tabuleiro[i][j] = '-';
						if(valor > melhor)
						{
							melhor = valor;
							x = i;
							y = j;
						}
					}
				}
			}
			tabuleiro[x][y] = ia;
			vez = true;
			if(Final(tabuleiro) == 'O'){acabou = true;
			cout<<"IA VENCEU\n";
			}
			jogadas++;
		}
		
		
	}
	if(jogadas == 9)cout<<"Empate\n";
	print(tabuleiro);
	
	

}


	
	

	
	
