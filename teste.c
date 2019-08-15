#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//testa se o "p" e o "q" é primo vendo o resto de todos os numeros ate a raiz quadrada do numero.

long long ehprimo(long long p)
{
	long long i;
	double j;
	j = sqrt(p);
	for(i = 2; i <= j; i++){
		if(p%i == 0)
			return 0;
	}
	return 1;
}

//calcula o mdc do possivel "e" pelo modo de divisoes suscessivas.
long long mdc(long long phi, long long e)
{
	if (phi % e == 0)
	{
		return e;
	}else{
		mdc(e, phi % e);
	}
}

//da sujestões de possiveis "e" sendo testado na função mdc até um total de tres sugestões.
int escolheE(long long phi){
	int cont = 0;
	for(long long e = 10; e < phi; e++){
		if(mdc(phi, e) == 1){
			printf("Uma sugestoes de 'e' : %llu\n", e);
			if (cont == 2)
			{
				return 0;
			}
			cont++;
		}
	}
}

//Calcula a forma reduzida de a^e módulo n, usando a expansao binaria do expoente.
long potencia(long long m, long long e, long long n){
long long A = m, P = 1, E = e;
	while(1){
		//Chegou ao fim da expansao, retorna o P.
		if(E == 0){
			return P;
		}
		//Se o expoente e impar.
		else if(E%2 != 0){
			//Realizamos a reducao modulo n de cada uma das multpilicacoes.
			P = (A * P)%n;
			E = (E-1)/2;
		}
		//Se o expoente e par.
		else{
			E = E/2;
		}
		//Obtem a sequencia de potencias.
		A = (A*A)%n;
	}
}

//Euclides estendido que retorna o "d" que é inverso de "e" mod phi.
long long euclidesEstendido(long long a, long long b){
	long long resto, quo;
	long long xB = 1, yB = 0;
	long long x = 0, y = 1;
	long long alpha, beta, phi;
	phi = a;
	resto = a;
	while(resto != 0){
		//Calcula o resto e o quociente de uma divisão.
		if(a >= 0){
			quo = 0;
			resto = a;
			while(resto >= b){
				resto -= b;
				quo = quo + 1;
			}
		}
		a = b;
		b = resto;
		if(resto > 0){
			alpha = xB - quo *x;
			beta = yB - quo * y;
			xB = x;
			yB = y;
			x = alpha;
			y = beta;
		}
	}
	if(beta < 0){
		beta = phi + beta;
	}
return beta;
}

int main()
{
  long long p,q,e,phi,n,d;
  int escolha,verdade,smsCifrada[500];
	char smsOriginal[500];
  char alfabeto[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
	char maiusculo[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
  printf("\n===========================\nEscolha o que quer fazer :\n0. parar o programa\n1. Gerar chave publica\n2.Criptografar\n3.Descriptografar\n===========================\n\n");
  scanf("%d",&escolha);
  if (escolha == 0)
  {
    return 0;
  }
  if (escolha == 1)
  {
    printf("digite o primeiro numero primo :\n");
    scanf("%llu",&p);
    verdade = ehprimo(p);
    if (verdade == 0)
    {
      printf("voce nao digitou um primo\n");
      return 0;
    }
    printf("digite o segundo numero primo :\n");
    scanf("%llu",&q);
    verdade = ehprimo(q);
    if (verdade == 0)
    {
      printf("voce nao digitou um primo\n");
      return 0;
    }
    n = p * q;
    phi = (p-1)*(q-1);
    escolheE(phi);
    printf("digite um expoente e relativamente primo a (%llu-1)*(%llu-1) :\n",p,q);
    scanf("%llu",&e);
		printf("a chave publica é [%llu,%llu]\n\n",e,n);
		FILE *file;
		file = fopen("chave publica.txt", "w");
		fprintf(file, "a chave publica é [%llu,%llu]",e,n);
		fclose(file);
    main();
  }
  if (escolha == 2)
  {
    printf("digite a mensagem a criptografar :\n");
    scanf("\n");
    fgets(smsOriginal, 500, stdin);
    int contador = 0,i,j = 0;
    printf("digite a chave publica :\n");
    scanf("%llu %llu",&e,&n);
		printf("\n");
		//criptografa a mensagem.
		while(j < strlen(smsOriginal))
		{
			for(i = 0;i < 27;i ++)
			{
				if(alfabeto[i] == smsOriginal[j] || maiusculo[i] == smsOriginal[j])
				{
					//potencia, nesse caso transforma o numero refrente a letra em um numero alto relacionado ao "e" e o "n".
					smsCifrada[j] = potencia(i,e,n);
					printf("%d ",smsCifrada[j]);
					FILE *file;
					file = fopen("criptografado.txt", "a");
					fprintf(file, "%d ",smsCifrada[j]);
					fclose(file);
				}
			}
			j++;
		}
		printf("\n\n");
   main();
  }
	if (escolha == 3)
	{
		printf("digite o p:\n");
		scanf("%llu",&p);
		printf("digite o q:\n");
		scanf("%llu",&q);
		printf("digite o e:\n");
		scanf("%llu",&e);
		n = p * q;
    phi = (p-1)*(q-1);
		//calcula o inverso multiplicativo do "e".
		d = euclidesEstendido(phi, e);
		int j,i = 0,contador = 0;
		FILE *file;
		file = fopen("criptografado.txt","r");
		while(fscanf(file,"%d",&smsCifrada[i]) != EOF)
		{
			contador += 1;
			i++;
		}
			fclose(file);

			for(i=0;i<contador;i++)
			{
				//potencia transforma o numero criptografado no numero original,atravez do "d" que é o inverso multiplicativo do "e" e o "n".
				smsCifrada[i] = potencia(smsCifrada[i], d, n);
				//esse for printa as letras correspondetes ao numero.
				for(j=0;j<27;j++)
				{
					if(smsCifrada[i] == j)
					{
						printf("%c",alfabeto[j]);
						FILE *file;
						file = fopen("descriptografado.txt", "a");
						fprintf(file, "%c",alfabeto[j]);
						fclose(file);
					}
			  }
			}
			printf("\n");
	}
}
