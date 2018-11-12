#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct funcionarios{
	int id;
	char nome[50];
	char funcao[50];
	float salario;
	int horas;
};

struct denso{
	int id;
	int posicao;
};

struct funcao{
	char nome[50];
	int lista[100];
	int total;
};

int carregar(funcionarios funcionario[]);

void indiceDenso(funcionarios funcionario[], denso indice[], int max);
int alfabetico(funcionarios funcionario[], int indice[], int max);
int indiceFuncao(funcionarios funcionario[], int tabelaInvertida[], int pri, int result, funcao trabalho[], int tot);
int odenarIndice(funcionarios funcionario[], int indice[], int max);

int busca(int chave,funcionarios funcionario[], int tot);
void escrever(funcionarios funcionario[], int result);

void ordenaFuncIndice(funcionarios funcionario[], denso indice[], funcao trabalho[], int tot);
void ordenaFuncao(funcionarios funcionario[], funcao trabalho[],int tot);
int existe(char funcaoo[], funcao trabalho[], int result);
int valida(int i,funcionarios funcionario[], int max);
int norepeat(int posicao, funcao trabalho);

void imprimirIndice(funcionarios funcionario[], denso ordenado[], int max);
void imprimirAlfa(funcionarios funcionario[], int alfa[], int max, int pri);
void imprimir(funcionarios funcionario[]);
void imprimirFuncao(funcionarios funcionario[], funcao trabalho[], int max, int tot);

int main ()
{

	funcionarios funcionario[100];
	denso indice[100];
	funcao trabalho[15], trabalhoIndice[15];
	int i, result, tabelaInvertida[100], pri, opcao, chave, tot = 0;
	int buscar, tabelaInvIndice[100], priIndice;
	
	result = carregar(funcionario);
							indiceDenso(funcionario, indice, result);
							pri = alfabetico(funcionario, tabelaInvertida, result);
							priIndice = odenarIndice(funcionario, tabelaInvIndice, result);
							tot = indiceFuncao(funcionario,tabelaInvertida, pri, result, trabalho,0);
							tot = indiceFuncao(funcionario,tabelaInvIndice, priIndice, result, trabalhoIndice,0);
	
	do
	{	
		printf("Escolha uma opcao:\n");
		printf("1- Consultar um registro\n");
		printf("2- Alterar campos de um registro\n");
		printf("3- Eliminar registro de um arquivo\n");
		printf("4- Inserir um registro no arquivo\n");
		printf("5- Visualizar informacoes\n");
		printf("0- Sair\n");
		scanf("%i", &opcao);
		
		switch(opcao)
		{
			case 1:
				printf("Digite a chave: ");
				scanf("%i", &chave);
				buscar = busca(chave, funcionario, result);
				if(buscar!=-1)
				{
					printf("Funcionario %i encontrado:\n", funcionario[buscar].id);
					printf("Nome:   \t%s\n", funcionario[buscar].nome);
					printf("Funcao: \t%s\n", funcionario[buscar].funcao);
					printf("Salario:\tR$%.2f\n", funcionario[buscar].salario);
					printf("Horas:  \t%i\n", funcionario[buscar].horas);
				}
				else
					printf("Chave nao encontrada\n");
				break;
			case 2:
				printf("Digite a chave: ");
				scanf("%i", &chave);
				buscar = busca(chave, funcionario, result);
				if(buscar!=-1)
				{
					do{
						printf("Digite o campo a ser mudado:\n");
						printf("1- Nome\n2- Funcao\n3- Salario\n4- Horas\n0- Sair\n");
						scanf("%i", &chave);
						switch(chave)
						{
							case 1:
								gets(funcionario[buscar].nome);
								pri = alfabetico(funcionario, tabelaInvertida, result);
								priIndice = odenarIndice(funcionario, tabelaInvIndice, result);
								tot = indiceFuncao(funcionario,tabelaInvertida, pri, result, trabalho,0);
								tot = indiceFuncao(funcionario,tabelaInvIndice, priIndice, result, trabalhoIndice,0);
								break;
							case 2:
								pri = alfabetico(funcionario, tabelaInvertida, result);
								priIndice = odenarIndice(funcionario, tabelaInvIndice, result);
								tot = indiceFuncao(funcionario,tabelaInvertida, pri, result, trabalho,0);
								tot = indiceFuncao(funcionario,tabelaInvIndice, priIndice, result, trabalhoIndice,0);
								gets(funcionario[buscar].funcao);
								break;
							case 3:
								printf("Digite o novo salario: ");
								scanf("%f", &funcionario[buscar].salario);
								break;
							case 4:
								printf("Atualize as horas de trabalho: ");
								scanf("%i", &funcionario[buscar].horas);
								break;
							case 0:
								printf("Registrando alteracoes...\n");
								break;
							default:
								printf("Opcao nao encontrada.\n");
								break;	
						}
						escrever(funcionario, result);
					}while(chave!=0);
				}
				else
					printf("Chave nao encontrada\n");
				break;
			case 3:
				printf("Digite a chave: ");
				scanf("%i", &chave);
				indiceDenso(funcionario, indice, result);
				pri = alfabetico(funcionario, tabelaInvertida, result);
				priIndice = odenarIndice(funcionario, tabelaInvIndice, result);
				tot = indiceFuncao(funcionario,tabelaInvertida, pri, result, trabalho,0);
				tot = indiceFuncao(funcionario,tabelaInvIndice, priIndice, result, trabalhoIndice,0);
				buscar = busca(chave, funcionario, result);
				if(buscar!=-1)
				{
					for(i=buscar; i < result-1; i++)
					{
						strcpy(funcionario[i].funcao, funcionario[i+1].funcao);
						strcpy(funcionario[i].nome, funcionario[i+1].nome);
						funcionario[i].horas = funcionario[i+1].horas;
						funcionario[i].id = funcionario[i+1].id;
						funcionario[i].salario = funcionario[i+1].salario;
					}
					result--;
					escrever(funcionario, result);
					indiceDenso(funcionario, indice, result);
					pri = alfabetico(funcionario, tabelaInvertida, result);
					priIndice = odenarIndice(funcionario, tabelaInvIndice, result);
					tot = indiceFuncao(funcionario,tabelaInvertida, pri, result, trabalho,0);
					tot = indiceFuncao(funcionario,tabelaInvIndice, priIndice, result, trabalhoIndice,0);
					printf("Registro eliminado com sucesso.\n");
				}
				else
					printf("Chave nao encontrada\n");
				break;
			case 4:
				do{
					printf("Digite uma chave de 4 digitos para o novo registro:\n");
					getchar();
					scanf("%i", &i);
				}while(valida(i, funcionario, result)==0);
				funcionario[result].id = i;
				printf("Digite o nome do funcionario:\n");
				getchar();
				gets(funcionario[result].nome);
				printf("Digite a funcao do funcionario:\n");
				gets(funcionario[result].funcao);
				printf("Digite o salario do funcionario:\n");
				scanf("%f", &funcionario[result].salario);
				printf("Digite as horas de trabalho do funcionario:\n");
				scanf("%i", &funcionario[result].horas);
				result++;
				escrever(funcionario, result);
				indiceDenso(funcionario, indice, result);
				pri = alfabetico(funcionario, tabelaInvertida, result);
				priIndice = odenarIndice(funcionario, tabelaInvIndice, result);
				tot = indiceFuncao(funcionario,tabelaInvertida, pri, result, trabalho,0);
				tot = indiceFuncao(funcionario,tabelaInvIndice, priIndice, result, trabalhoIndice,0);

				printf("Insercao feita com sucesso\n");
				break;
			case 5:
							indiceDenso(funcionario, indice, result);
							pri = alfabetico(funcionario, tabelaInvertida, result);
							priIndice = odenarIndice(funcionario, tabelaInvIndice, result);
							tot = indiceFuncao(funcionario,tabelaInvertida, pri, result, trabalho,0);
							tot = indiceFuncao(funcionario,tabelaInvIndice, priIndice, result, trabalhoIndice,0);
				do{
						printf("Digite a opcao desejada:\n");
						printf("1- Ordenado por chave\n2- Ordenado por nome\n3- Funcao ordenada por chave\n4- Funcao ordenado por nome\n5- Desordenado\n0- Sair\n");
						scanf("%i", &chave);
						switch(chave)
						{
							case 1:
								imprimirIndice(funcionario, indice, result);
								printf("\n");
								break;
							case 2:
								imprimirAlfa(funcionario, tabelaInvertida, result, pri);
								printf("\n");
								break;
							case 3:
								imprimirFuncao(funcionario, trabalhoIndice, result, tot);
								printf("\n");
								break;
							case 4:
								imprimirFuncao(funcionario, trabalho, result, tot);
								printf("\n");
								break;
							case 5:
								imprimir(funcionario);
								printf("\n");
								break;
							case 0:
								printf("Encerrando\n");
								break;
							default:
								printf("Opcao nao encontrada.\n");
								break;	
						}
					}while(chave!=0);
				break;
			case 0:
				printf("Encerrando...\n");
				break;
		}
		
	}while(opcao!=0);
    return 0;
}

int valida(int i,funcionarios funcionario[], int max)
{
	int j;
	for(j=0; j<max; j++)
	{
		if(funcionario[j].id==i)
		return 0;
	}
	return 1;
}

int indiceFuncao(funcionarios funcionario[], int tabelaInvertida[], int pri, int result, funcao trabalho[], int tot)
{
	int i, ind;
	for(i = pri; i!=-1; i)
	{
		ind = existe(funcionario[i].funcao, trabalho, tot);
		if(ind!=-1)
		{
			trabalho[ind].lista[trabalho[ind].total] = i;
			trabalho[ind].total++;
		}
		else
		{
			strcpy(trabalho[tot].nome, funcionario[i].funcao);
			trabalho[tot].lista[0] = i;
			trabalho[tot].total = 1;
			tot++;	
		}
		i = tabelaInvertida[i];		
	}
	return tot;
}

void ordenaFuncIndice(funcionarios funcionario[], denso indice[], funcao trabalho[], int tot)
{
	int i, ind;
	for(i = 0; i < tot; i++)
	{
		ind = existe(funcionario[indice[i].posicao].funcao, trabalho, tot);
		
		if(ind!=-1)
		{
			if(norepeat(indice[i].posicao, trabalho[ind])==1)
			{
				trabalho[ind].lista[trabalho[ind].total] = indice[i].posicao;
				trabalho[ind].total++;
			}
		}
		else
		{
			strcpy(trabalho[tot].nome, funcionario[indice[i].posicao].funcao);
			trabalho[tot].lista[0] = indice[i].posicao;
			trabalho[tot].total = 1;
			tot++;	
		}
	}
}

int norepeat(int posicao, funcao trabalho)
{
	int i;
	for(i=0; i< trabalho.total; i++)
	{
		if(posicao == trabalho.lista[i])
			return 0;
	}
	return 1;
}

int odenarIndice(funcionarios funcionario[], int indice[], int max)
{
	int i, j, k, pri = 0, prii, ordenada = 0, aux[100];
	for (i = 1; i < max; i++) { 
	   if(funcionario[pri].id > funcionario[i].id)
	   		pri = i;
	}
	aux[0] = pri;
	prii = pri;
	for (i = 0; i < max; i++)
	{ 
		aux[i]=0;
		for (j = 0; j < max; j++)
		   if(funcionario[i].id > funcionario[j].id)
		   		aux[i]++;
	}
	
	for (i = 1; i < max; i++) 
	{   
       for (j = 0; j< max; j++) 
       { 
           if(i==aux[j])
           	{
		   		indice[pri] = j;
		   		pri = j;
		   		j = max;
			}
       } 
   	}
   	indice[pri]=-1;
	
	return prii;
}

int existe(char funcaoo[], funcao trabalho[], int result)
{
	int i;
	for(i=0; i<result; i++)
	{
		if(strcmp(funcaoo, trabalho[i].nome)==0)
			return i;
	}
	return -1;
}

void escrever(funcionarios funcionario[], int result)
{
	FILE* fp;
	fp = fopen ("Funcionarios.dat", "wb");
	fwrite(&funcionario[0], sizeof(struct  funcionarios), result, fp);      
    fclose(fp);
}

int busca(int chave,funcionarios funcionario[], int tot)
{
	int i;
	
	for(i=0; i<tot; i++)
	{
		if(chave == funcionario[i].id)
			return i;
	}
	return -1;
}

void indiceDenso(funcionarios funcionario[], denso indice[], int max)
{
	int i, chave, j, aux; 
	
	for(i = 0; i < max; i++)
	{
		indice[i].id = funcionario[i].id;
		indice[i].posicao = i;
	}
	
   	for (i = 1; i < max; i++) 
	{ 
       chave = indice[i].id; 
       j = i-1; 
  
       while (j >= 0 && indice[j].id > chave) 
       { 
           indice[j+1].id= indice[j].id;
           aux = indice[j+1].posicao;
		   indice[j+1].posicao = indice[j].posicao;
		   indice[j].posicao = aux;
           j = j-1; 
       } 
       indice[j+1].id = chave; 
   	}
}

int carregar(funcionarios funcionario[])
{
	FILE* fp;
	fp = fopen ("Funcionarios.dat", "rb");
	int result, i;
	result = fread (&funcionario[0], sizeof(struct  funcionarios), 100, fp);
      
      fclose(fp);
      return result;
}

int alfabetico(funcionarios funcionario[], int indice[], int max)
{
	int i, j, k, pri = 0, prii, ordenada = 0, aux[100];
	for (i = 1; i < max; i++) { 
	   if(strcmp(funcionario[pri].nome, funcionario[i].nome)>0)
	   		pri = i;
	}
	aux[0] = pri;
	prii = pri;
	for (i = 0; i < max; i++)
	{ 
		aux[i]=0;
		for (j = 0; j < max; j++)
		   if(strcmp(funcionario[i].nome, funcionario[j].nome)>0)
		   		aux[i]++;

	}
	
	for (i = 1; i < max; i++) 
	{   
       for (j = 0; j< max; j++) 
       { 
           if(i==aux[j])
           	{
		   		indice[pri] = j;
		   		pri = j;
		   		j = max;
			}
       } 
   	}
   	indice[pri]=-1;
	
	return prii;
}

void imprimir(funcionarios funcionario[])
{
	FILE* fp;
	fp = fopen ("Funcionarios.dat", "rb");
	int result, i;
	result = fread (&funcionario[0], sizeof(struct  funcionarios), 100, fp);
	
	printf("Nome\t\t\t id\t Salario\t Funcao\t\t Horas trabalhadas\n");
	for (i=0; i<result; i++)
      {
      	if(strlen(funcionario[i].nome)>15)
      	{
      		if(strcmp(funcionario[i].funcao, "CEO")!=0)
      			printf("%s\t %i\t R$%.2f\t %s\t %i\n", funcionario[i].nome, funcionario[i].id, funcionario[i].salario, funcionario[i].funcao, funcionario[i].horas);
      		else
      			printf("%s\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[i].nome, funcionario[i].id, funcionario[i].salario, funcionario[i].funcao, funcionario[i].horas);
     	}
      	else
      	{
      		if(strcmp(funcionario[i].funcao, "CEO")!=0)
      			printf("%s\t\t %i\t R$%.2f\t %s\t %i\n", funcionario[i].nome, funcionario[i].id, funcionario[i].salario, funcionario[i].funcao, funcionario[i].horas);
      		else
      			printf("%s\t\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[i].nome, funcionario[i].id, funcionario[i].salario, funcionario[i].funcao, funcionario[i].horas);
      	}
      }
      
      fclose(fp);
}

void imprimirIndice(funcionarios funcionario[], denso ordenado[], int max)
{
	printf("Nome\t\t\t id\t Salario\t Funcao\t\t Horas trabalhadas\n");
	int i, j;
	for (i=0; i<max; i++)
    {
    	j = ordenado[i].posicao;
    	if(strlen(funcionario[j].nome)>15)
    	{
    		if(strcmp(funcionario[j].funcao, "CEO")!=0)
				printf("%s\t %i\t R$%.2f\t %s\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
			else
				printf("%s\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
		}
    	else
		{
			if(strcmp(funcionario[j].funcao, "CEO")!=0)
    			printf("%s\t\t %i\t R$%.2f\t %s\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
    		else
    			printf("%s\t\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
    	}
    }
}


void imprimirFuncao(funcionarios funcionario[], funcao trabalho[], int max, int tot)
{
	printf("Nome\t\t\t id\t Salario\t Funcao\t\t Horas trabalhadas\n");
	int j, i, k;
	
	for(i=0; i<tot; i++)
	for (j=0; j < trabalho[i].total; j++)
    {
    	k = trabalho[i].lista[j];
    	if(strlen(funcionario[k].nome)>15)
    	{
    		if(strcmp(funcionario[k].funcao, "CEO")!=0)
				printf("%s\t %i\t R$%.2f\t %s\t %i\n", funcionario[k].nome, funcionario[k].id, funcionario[k].salario, funcionario[k].funcao, funcionario[k].horas);
			else
				printf("%s\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[k].nome, funcionario[k].id, funcionario[k].salario, funcionario[k].funcao, funcionario[k].horas);
		}
    	else
		{
			if(strcmp(funcionario[k].funcao, "CEO")!=0)
    			printf("%s\t\t %i\t R$%.2f\t %s\t %i\n", funcionario[k].nome, funcionario[k].id, funcionario[k].salario, funcionario[k].funcao, funcionario[k].horas);
    		else
    			printf("%s\t\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[k].nome, funcionario[k].id, funcionario[k].salario, funcionario[k].funcao, funcionario[k].horas);
    	}
    }
}

void imprimirAlfa(funcionarios funcionario[], int alfa[], int max, int pri)
{
	printf("Nome\t\t\t id\t Salario\t Funcao\t\t Horas trabalhadas\n");
	int j;
	
	j = alfa[pri];
	
	for (j=pri; j!=-1; j)
    {
    	
    	if(strlen(funcionario[j].nome)>15)
    	{
    		if(strcmp(funcionario[j].funcao, "CEO")!=0)
				printf("%s\t %i\t R$%.2f\t %s\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
			else
				printf("%s\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
		}
    	else
		{
			if(strcmp(funcionario[j].funcao, "CEO")!=0)
    			printf("%s\t\t %i\t R$%.2f\t %s\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
    		else
    			printf("%s\t\t %i\t R$%.2f\t %s\t\t %i\n", funcionario[j].nome, funcionario[j].id, funcionario[j].salario, funcionario[j].funcao, funcionario[j].horas);
    	}
    	j = alfa[j];
    }
}
