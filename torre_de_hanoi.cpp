#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio2.h>
#include<unistd.h>
#include<time.h> 
#include<math.h>

#include "bootstrapAntigo.h"
#include "TADPilhaM2.h"

/*
ANDRESSA DINIZ, RA: 262318644
GUILHERME HORTA, RA: 262319144
*/


//STRUCT PARA AUXILIAR NAS MOVIMENTAÇÕES ENTRE AS PILHAS
struct TpTorre
{
	int origem, destino, aux;
};



char menuPrincipal(void)
{
    consolePrintf("topo", "rosa_claro", 2, "TORRE DE HANOI");
    consolePrintf("esquerda", "branco", 0, "[A] Jogar manual");
    consolePrintf("esquerda", "branco", 1, "[B] Jogar automatico");
    consolePrintf("esquerda", "branco", 2, "[C] Infos sobre o jogo");
    consolePrintf("esquerda", "branco", 5, "[ESC] - Encerrar");
    gotoxy(4, 15);
	
	return toupper(getche()); 
}
//FUNÇÃO QUE EXIBE AS PILHAS PARA O USUARIO
void mostrarPilhas(TpPilhaM2 pm, int contO, int contD, int contA)
{
	int l, c, i=0;
	//EXIBIÇÃO DAS PILHAS
	if(pilhaVazia(pm,0))
	{
		c=5;
		for(i=0; i<10; i++)
		{
			gotoxy(10,c);
			printf("   |");
			c++;
		}
		gotoxy(10,c);
		textcolor(GREEN);
		printf("HASTE 1");
		textcolor(WHITE);
	}
	else
	{
		c=5;
		for(i=0; i<10-contO; i++)
		{
			gotoxy(10,c);
			printf("   |");
			c++;
		}
		while(!pilhaVazia(pm,0))
		{
			gotoxy(10,c);
			printf("   %d",retirar(pm,0));
			c++;
		}
		gotoxy(10,c);
		textcolor(GREEN);
		printf("HASTE 1");
		textcolor(WHITE);
	}
	
	if(pilhaVazia(pm,1))
	{
		c=5;
		for(i=0; i<10; i++)
		{
			gotoxy(30,c);
			printf("   |");
			c++;
		}
		gotoxy(30,c);
		textcolor(GREEN);
		printf("HASTE 2");
		textcolor(WHITE);
	}
	else
	{
		c=5;
		for(i=0; i<10-contA; i++)
		{
			gotoxy(30,c);
			printf("   |");
			c++;
		}
		while(!pilhaVazia(pm,1))
		{
			gotoxy(30,c);
			printf("   %d",retirar(pm,1));
			c++;
		}
		gotoxy(30,c);
		textcolor(GREEN);
		printf("HASTE 2");
		textcolor(WHITE);
	}
	
	if(pilhaVazia(pm,2))
	{
		c=5;
		for(i=0; i<10; i++)
		{
			gotoxy(50,c);
			printf("   |");
			c++;
		}
		gotoxy(50,c);
		textcolor(GREEN);
		printf("HASTE 3");
		textcolor(WHITE);
	}
	else
	{
		c=5;
		for(i=0; i<10-contD; i++)
		{
			gotoxy(50,c);
			printf("   |");
			c++;
		}
		while(!pilhaVazia(pm,2))
		{
			gotoxy(50,c);
			printf("   %d",retirar(pm,2));
			c++;
		}
		gotoxy(50,c);
		textcolor(GREEN);
		printf("HASTE 3");
		textcolor(WHITE);
	}
}

//FUNÇÃO QUE COLOCA A QUANTIADE DE DISCO NA PILHA 1
void colocarDisco(TpPilhaM2 &pm, int qtdeDisco)
{
	int i=0, disco = qtdeDisco;
	
	while(i<qtdeDisco)
	{
		inserir(pm,disco,0);
		disco--;
		i++;
	}
}

//FUNÇÃO DO JOGO MANUAL
void manual(TpPilhaM2 &pm)
{
	int qtdeDisco, i=0, valor, movimento=0, op;
	int origem, contO, contD, contA;
	TpTorre t;
	//x=linha | y=coluna
	gotoxy(35,8);
	printf("Quantidade de discos (MIN:3 - MAX:10): ");
	scanf("%d",&qtdeDisco);
	if(qtdeDisco >=3 && qtdeDisco <= 10)
	{
		clrscr();
		//o jogo começa sempre na haste 0
		t.origem = 0;
		
		//colocando a quantidade de disco na haste de inicio
		colocarDisco(pm,qtdeDisco);
		
		//EXIBIÇÃO DAS PILHAS
		contO=qtdeDisco;
		contD=0;
		contA=0;
		mostrarPilhas(pm,contO,contD,contA);

		do
		{
			textcolor(WHITE);
			gotoxy(1,22);
			printf("MENSAGEM: ");
			
			gotoxy(1,18);
			printf("De qual torre deseja mover o disco? (1, 2 ou 3): ");
			scanf("%d",&t.origem);
			t.origem--;
			gotoxy(1,19);
			printf("Para qual torre deseja mover o disco? (1, 2 ou 3): ");
			scanf("%d",&t.destino);
			t.destino--;
			if(t.origem != t.destino)
			{
				if((t.destino >= 0 && t.destino <= 2) && (t.origem >= 0  && t.origem <= 2))
				{
					//VALIDAÇÃO PARA FAZER AS MOVIMENTAÇÕES
		       		if(pilhaVazia(pm,t.destino))
		       		{
						inserir(pm,retirar(pm,t.origem),t.destino);
						textcolor(GREEN);
						gotoxy(11,22);
		       			printf("Movido da haste: %d \t Para haste: %d",t.origem+1,t.destino+1);
		       			movimento++;
		       			
		       			//PARA FAZER A MOLDURA
		       			if(t.origem == 0 && t.destino == 1)
		       			{
		       				contO--; //origem
		       				contA++; //auxiliar
		       			}
		       			else
		       			if(t.origem == 0 && t.destino == 2)
		       			{
		       				contO--; //origem
		       				contD++; //destino
		       			}
		       			else
		       			if(t.origem == 1 && t.destino == 0)
		       			{
		       				contA--; //auxiliar
		       				contO++; //origem
		       			}
		       			else
		       			if(t.origem == 2 && t.destino == 0)
		       			{
		       				contD--; //destino
		       				contO++; //origem
		       			}
		       			else
		       			if(t.origem == 1 && t.destino == 2)
		       			{
		       				contA--; //auxiliar
		       				contD++; //destino
		       			}
		       			else
		       			if(t.origem == 2 && t.destino == 1)
		       			{
		       				contD--; //destino
		       				contA++; //auxiliar
		       			}
		       		}
		       		else
					if(elementoTopo(pm,t.origem) < elementoTopo(pm,t.destino))
					{
						inserir(pm,retirar(pm,t.origem),t.destino);
						textcolor(GREEN);
						gotoxy(11,22);
		       			printf("Movido da haste: %d \t Para haste: %d",t.origem+1,t.destino+1);
						movimento++;
						
						//PARA FAZER A MOLDURA
		       			if(t.origem == 0 && t.destino == 1)
		       			{
		       				contO--; //origem
		       				contA++; //auxiliar
		       			}
		       			else
		       			if(t.origem == 0 && t.destino == 2)
		       			{
		       				contO--; //origem
		       				contD++; //destino
		       			}
		       			else
		       			if(t.origem == 1 && t.destino == 0)
		       			{
		       				contA--; //auxiliar
		       				contO++; //origem
		       			}
		       			else
		       			if(t.origem == 2 && t.destino == 0)
		       			{
		       				contD--; //destino
		       				contO++; //origem
		       			}
		       			else
		       			if(t.origem == 1 && t.destino == 2)
		       			{
		       				contA--; //auxiliar
		       				contD++; //destino
		       			}
		       			else
		       			if(t.origem == 2 && t.destino == 1)
		       			{
		       				contD--; //destino
		       				contA++; //auxiliar
		       			}
					}
					else
					{
						textcolor(RED);
						gotoxy(11,22);
						printf("Erro! Nao foi possivel realizar o movimento!");
					}
					//VOLTANDO PARA COR PADRÃO DO PROGRAMA
					textcolor(WHITE);	
					
					//AQUI ESTAVA A EXIBIÇÃO DAS PILHAS
				}
				else
				{
					textcolor(RED);
					gotoxy(11,22);
					printf("Erro! Voce digitou uma haste que nao existe! Digite novamente...");
					textcolor(WHITE);
				}
			}
			else
			{
				textcolor(RED);
				gotoxy(11,22);
				printf("Erro! Nao e possivel mover para mesma haste!");
				textcolor(WHITE);
			}
			getch();
			clrscr();
					
			//EXIBIÇÃO DAS PILHAS
			mostrarPilhas(pm,contO,contD,contA);
			
			//VERIFICANDO SE A PESSOA GANHOU
			if(pilhaVazia(pm,0) && pilhaVazia(pm,1)) //ALTERADO PARA GANHAR NA PILHA 3
			{
				textcolor(WHITE);
				gotoxy(1,22);
				printf("MENSAGEM: ");
			 	textcolor(13);
			 	gotoxy(11,22);
				printf("PARABENS VOCE GANHOU!");
				textcolor(WHITE);
			}
		}while(!(pilhaVazia(pm,0) && pilhaVazia(pm,1))); //ALTERADO PARA GANHAR NA PILHA 3
		 textcolor(WHITE);
		 gotoxy(1,20);
		 printf("Total de movimentos: %d",movimento);
	}
	else
	{
		textcolor(WHITE);
		gotoxy(1,22);
		printf("MENSAGEM: ");
		textcolor(RED);
		gotoxy(11,22);
		printf("Erro! Quantidade de disco invalida!");
		textcolor(WHITE);
	}
}

//FUNÇÃO QUE EXIBE AS PILHAS PARA O USUARIO
void mostrarPilhasAuto(TpPilhaM2 pm)
{
	int l=3, c, i=0;
	//EXIBIÇÃO DAS PILHAS
	if(pilhaVazia(pm,0))
	{
		printf("\nHASTE vazia!"); 
		printf("\nHASTE 1\n");
	}
	else
	{
		exibir(pm,0);
		printf("\nHASTE 1\n");
	}
			
	if(pilhaVazia(pm,1))
	{
		printf("\nHaste vazia!");
		printf("\nHASTE 2\n");
	}
	else
	{
		exibir(pm,1);
		printf("\nHASTE 2\n");
	}
	if(pilhaVazia(pm,2))
	{
		printf("\nHaste vazia!");
		printf("\nHASTE 3\n");
	}
	else
	{
		exibir(pm,2);
		printf("\nHASTE 3\n");
	}
}

//FUNÇÃO QUE MOVE O AUTOMATICO
void moverAutomatico(TpPilhaM2 &pm, int origem, int destino)
{
	if(pilhaVazia(pm,origem) && !pilhaVazia(pm,destino))
	{
		inserir(pm,retirar(pm,destino),origem);
	}
		
	else
	if(!pilhaVazia(pm,origem) && pilhaVazia(pm,destino))
	{
		inserir(pm,retirar(pm,origem),destino);
	}
		
	else
	if(elementoTopo(pm,origem) > elementoTopo(pm,destino))
	{
		inserir(pm,retirar(pm,destino),origem);
	}
		
	else
	{
		inserir(pm,retirar(pm,origem),destino);
	}
}

//SIMULAÇÃO AUTOMATICA
void automatico(TpPilhaM2 &pm)
{
    int i, qtdeDisco, auxiliar, contO, contD, contA, retorno;
    int movimentosTotal;
    TpTorre t;
    
    t.origem = 0;
    t.aux = 1;
    t.destino = 2;
    
    //PEGANDO A QUANTIADE DE DISCO QUE VAI SER MOVIMENTADO
    
    printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
    scanf("%d",&qtdeDisco);
    clrscr();
    
    if(qtdeDisco >= 3 && qtdeDisco <= 10)
    {
    	//CALCULANDO A QUANTIDADE TOTAL DE MOVIMENTOS PARA FINALIZAR AS MOVIMENTAÇÕES
    	movimentosTotal = pow(2, qtdeDisco) - 1;
    	
    	//SE O NUMERO DE DISCO ESCOLHIDO FOR PAR DESTINO E AUXILAR TROCAM O PAPEL
		if(qtdeDisco % 2 == 0)
		{
		    auxiliar = t.destino;
		    t.destino = t.aux;
		    t.aux = auxiliar;
		}
		
		//INSERINDO OS DISCO DENTRO A PILHA ORIGEM
		colocarDisco(pm,qtdeDisco);
		
		//mostrando pilha inicial para o usuario
		//EXIBIÇÃO DAS PILHAS
		mostrarPilhasAuto(pm);
		getch();
			
		i=1;
		while(i <= movimentosTotal)
		{
			clrscr();
		    if(i%3 == 1) //HASTE 1
		    	moverAutomatico(pm,t.origem,t.destino);
		    	
			else
			if(i%3 == 2) //HASTE 2
				moverAutomatico(pm,t.origem,t.aux);

			else
			if(i%3 == 0) //HASTE 3
				moverAutomatico(pm,t.aux,t.destino);
			
			textcolor(3);
			printf("\n%d.o MOVIMENTACAO\n",i);
			textcolor(WHITE);
			mostrarPilhasAuto(pm);
			
			if(pilhaVazia(pm,0) && pilhaVazia(pm,1))
			{
				textcolor(GREEN);
				printf("\nAutomatico finalizado!\n");
				textcolor(WHITE);
				printf("\nMovimentacoes: %d\n",movimentosTotal);
			}
				
		    i++; //CONTATOR PARA ENCERRAR QUANDO BATER A QUANTIDADE DE PASSOS TOTAL
		    Sleep(1000); //PODE USAR O SLEEP OU GETCH
		    //getch();
		    //system("cls");
		}
	}
	else
	{
		gotoxy(1,1);
		printf("MENSAGEM: ");
		textcolor(RED);
		gotoxy(11,1);
		printf("Erro! Quantidade de disco invalida");
		textcolor(WHITE);
	}
}

//FUNÇÃO QUE MOSTRA AS INFORMAÇÕES E REGRAS DO JOGO
void informacoes(void)
{
	char op;
	do{
		system("cls");
		consolePrintf("topo", "verde", 0, "Informacoes sobre Jogo:");
		consolePrintf("esquerda", "branco", 0, "[ESQ] Voltar");
		consolePrintf("direita", "branco", 0, "O jogo Torre de Hanoi, consiste em tres hastes, sendo o objetivo");
		consolePrintf("direita", "branco", 1, "transferir todos os discos da primeira haste para a terceira,");
		consolePrintf("direita", "branco", 2, "utilizando a segunda haste como auxiliar. As regras determinam");
		consolePrintf("direita", "branco", 3, "que apenas um disco pode ser movido por vez, e que nao eh");
		consolePrintf("direita", "branco", 4, "permitido colocar um disco maior sobre um menor");
		gotoxy(4, 15);
        op = toupper(getche());
        system("cls");
	}while(op!=27);	
	
}

int main(void)
{
	char op;
	int qtdeDisco, i=0, destino, valor;
	
	//pilha para maniupulação
	TpPilhaM2 pm;
	
	do
	{
		//3 é quantidade fixa de pilha que vamos ter, mudando apenas a quantidade de valores dentro delas
		inicializar(pm,3); //0, 1, 2
		clrscr();

		op = menuPrincipal();
		
		switch(op)
		{
			case 'A':
				manual(pm);
				
				break;
				
			case 'B':
				automatico(pm);
				
				break;
			
			case 'C':
				//COLOCAR AS REGRAS E INFORMAÇÕES DO JOGO AQUI PARA O USUARIO
				//já criei a função, só colocar os conteúdo dentro
				informacoes();
				
				break;
				
			case 27:
				printf("\nJogo encerrado!\n"); //pode colocar na parte de mensagem do jogo
		}
		getch();
	}while(op != 27);
	
	return 0;
}
