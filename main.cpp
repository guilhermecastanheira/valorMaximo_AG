//		::ALGORITMO GENÉTICO::

//o algoritmo procura o valor maximo da função f(x) = x * sin(31.41592*x) + 1.0 atraves do algoritmo genético
//o valor maximo é próximo de f(x)=2.85 na teoria

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


#define  qtdind 50
#define  probmut 100
#define  probcross 100
#define  geracao 150

using namespace std;

void mudanca_base(int popx[qtdind][22], float convx[22])
{
	int i, j;
	float x, S;

	for (i = 0; i < qtdind; i++)
	{

		S = 0.0;

		x = 21.0;

		for (j = 0; j < 22; j++)
		{

			S = S + (popx[i][j] * (pow(2.0, x)));

			x = x - 1.0;

		}

		convx[i] = S;
	}
}

void torneio(float objx[qtdind], float *v1x, float *v2x, int *pos_fntx1, int *pos_fntx2)
{
	int i, pos_fntx4[4], chave;
	float fnt[4];

	chave = 1;

	while (chave != 0)
	{
		chave = 0;

		for (int j = 0; j < 4; j++)
		{
			i = rand() % qtdind;

			fnt[j] = objx[i];
			pos_fntx4[j] = i;
		}

		for (int j = 0; j < 3;j++)
		{
			if (fnt[j] == fnt[j + 1])
			{
				chave = chave + 1;
			}
		}
	}

	for (int j = 0; j<4; j++)
	{
		cout << "finalistas: " << fnt[j] << "\t";
	}

	cout << "\n\n\n\n";



	//definindo maior 1
	for (int z = 0; z < 4; z++)
	{
		if (fnt[z]>*v1x)
		{
			*v1x = fnt[z];
			*pos_fntx1 = pos_fntx4[z];
		}

	}
	//definindo maior 2

	for (int z = 0; z < 4; z++)
	{
		if (*v1x != fnt[z])
		{
			if (fnt[z]>*v2x)
			{
				*v2x = fnt[z];
				*pos_fntx2 = pos_fntx4[z];
			}
		}
	}

}

void mutacao(int vettx[22])
{
	int p, m;

	p = rand() % 100; //definindo probabilidade

	if (p <= probmut)
	{
		m = rand() % 22;

		if (vettx[m] == 1)
		{
			vettx[m] = 0;
		}
		else
		{
			vettx[m] = 1;
		}
	}
}

void crossover(int vettx1[22], int vettx2[22])
{
	int copy_vettx1[22], copy_vettyx2[22], p, c, a;

	p = rand() % 100; //definindo probabilidade

	if (p < probcross)
	{
		//copia os vetores para usa-los como manda a teoria
		for (c = 0; c < 22; c++)
		{
			copy_vettx1[c] = vettx1[c];
			copy_vettyx2[c] = vettx2[c];
		}

		a = rand() % 22;


		for (c = a; c < 22; c++)
		{
			vettx1[c] = copy_vettyx2[c];
		}

		for (c = a; c < 22; c++)
		{
			vettx2[c] = copy_vettx1[c];
		}

	}


}

float mudanca_base_vetor(int vettw[22])
{
	int i, j;
	float S, x;


	S = 0.0;
	x = 21;


	for (j = 0; j <22; j++)
	{

		S = S + (vettw[j] * (pow(2.0, x)));
		x = x - 1;

	}

	return (S);
}




int main()
{
	int pop[qtdind][22], i, j, pos_fnt1, pos_fnt2, vett_1[22], vett_2[22], pos_f = 0, pos_obj, pos_obj2, copiavett1[22], copiavett2[22], vet1[22], vet2[22];
	float conv[qtdind], obj[qtdind], v1, v2, vobj1, vobj2, v2novo2, v1novo1, maior_otz, f[qtdind], menor_obj, menor_obj2, objp[4], m1, m2, mobj1, mobj2, vf1, vf2;

	srand(static_cast<unsigned int> (time(NULL)));


	//DEFININDO POPULAÇÃO INICIAL

	/*int vettest[22] = { 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 };

	for (int z = 0; z < 22; z++)
	{
	pop[0][z] = vettest[z];
	}

	float Z = mudanca_base_vetor(vettest);
	cout << "Valor max" << Z << endl;
	*/
	for (i = 0; i<qtdind; i++)
	{

		for (j = 0; j<22; j++)
		{

			pop[i][j] = rand() % 2;

		}
	}

	for (i = 0; i < qtdind; i++){
		cout << "\n Ind " << i;
		for (j = 0; j < 22; j++)
		{
			cout << "\t" << pop[i][j];

		}
		cout << "\t FO: " << obj[i];

	}

	//JOGANDO NA FUNÇÃO OBJETIVO
	for (i = 0; i < qtdind; i++)
	{

		mudanca_base(pop, conv);

		obj[i] = -1.0 + ((conv[i] * 3.0) / 4194303.0);
	}

	//CALCULANDO A FUNCAO f(x)

	for (i = 0; i < qtdind; i++)
	{
		f[i] = obj[i] * sin(31.41592*obj[i]) + 1.0;
	}

	cout << "\n\n\n";
	cout << "\n\n\n";

	/*maior_otz = f[0];

	for (i = 0; i < qtdind; i++)
	{
	if (maior_otz < f[i])
	{
	maior_otz = f[i];
	pos_f = i;
	}
	}
	*/
	//FAZENDO AS GERAÇÕES
	for (int k = 0; k <= geracao; k++)
	{
		cout << "\n\n\n";

		v1 = -1;
		v2 = -1;
		pos_fnt1 = 0.0;
		pos_fnt2 = 0.0;
		menor_obj = f[0];
		menor_obj2 = f[0];
		pos_obj = 0;
		pos_obj2 = 0;
		vobj1 = -1;
		vobj2 = -1;
		v1novo1 = -1;
		v2novo2 = -1;
		pos_f = 0;
		m1 = -1;
		m2 = -1;
		mobj1 = -1;
		mobj2 = -1;
		maior_otz = -1;

		for (int z = 0; z < qtdind; z++)
		{
			if (f[z] < menor_obj)
			{
				menor_obj = f[z];
				pos_obj = z;
			}
		}

		for (int z = 0; z < qtdind; z++)
		{
			if (f[z] != menor_obj)
			{
				if (f[z] < menor_obj2)
				{
					menor_obj2 = f[z];
					pos_obj2 = z;
				}
			}
		}


		for (int z = 0; z < 22; z++)
		{
			copiavett1[z] = pop[pos_obj][z];
			copiavett2[z] = pop[pos_obj2][z];
		}


		cout << "copiavett1 ::  ";
		for (int z = 0; z < 22; z++)
		{
			cout << copiavett1[z] << "\t";
		}

		cout << "\n\n";
		cout << "copiavett2 ::  ";
		for (int z = 0; z < 22; z++)
		{
			cout << copiavett2[z] << "\t";
		}

		cout << "\n\n\n";


		//TORNEIO
		torneio(obj, &v1, &v2, &pos_fnt1, &pos_fnt2);

		cout << "finalista 1::  " << v1 << endl;

		cout << "finalista 2::  " << v2 << endl;


		//IDENTIFICANDO V1 E V2 PELA POSIÇÃO E PEGANDO O VETOR NA POPULAÇÃO INICIAL
		for (j = 0; j < 22; j++)
		{
			vett_1[j] = pop[pos_fnt1][j];
			vett_2[j] = pop[pos_fnt2][j];
		}

		cout << "vett_1:   ";
		for (int z = 0; z < 22; z++)
		{
			cout << vett_1[z] << "\t";
		}

		cout << "\n\n";
		cout << "vett_2:   ";

		for (int z = 0; z < 22; z++)
		{
			cout << vett_2[z] << "\t";
		}

		cout << "\n\n\n";


		//REALIZANDO CROSSOVER 
		crossover(vett_1, vett_2);

		//Após crossover:

		vobj1 = mudanca_base_vetor(vett_1);
		v1novo1 = -1.0 + ((vobj1 * 3) / 4194303.0);
		vf1 = v1novo1 * sin(31.41592*v1novo1) + 1.0;

		vobj2 = mudanca_base_vetor(vett_2);
		v2novo2 = -1.0 + ((vobj2 * 3) / 4194303.0); //objetivo
		vf2 = v2novo2 * sin(31.41592*v2novo2) + 1.0; //fç

		cout << "vett_1:   ";

		for (int z = 0; z < 22; z++)
		{
			cout << vett_1[z] << "\t";
		}

		cout << "\n\n";

		cout << "vett_2:   ";

		for (int z = 0; z < 22; z++)
		{
			cout << vett_2[z] << "\t";
		}

		cout << "\n\n\n";

		//REALIZANDO MUTAÇÃO 

		mutacao(vett_1);
		mutacao(vett_2);

		vobj1 = mudanca_base_vetor(vett_1);
		v1novo1 = -1.0 + ((vobj1 * 3) / 4194303.0);
		vf1 = v1novo1 * sin(31.41592*v1novo1) + 1.0;

		vobj2 = mudanca_base_vetor(vett_2);
		v2novo2 = -1.0 + ((vobj2 * 3) / 4194303.0);
		vf2 = v2novo2 * sin(31.41592*v2novo2) + 1.0;

		cout << "vett_1:   ";

		for (int z = 0; z < 22; z++)
		{
			cout << vett_1[z] << "\t";
		}

		cout << "\n\n";
		cout << "vett_2:   ";

		for (int z = 0; z < 22; z++)
		{
			cout << vett_2[z] << "\t";
		}

		cout << "\n\n\n";

		float result[4] = { menor_obj, menor_obj2, vf1, vf2 };
		float objp[4] = { obj[pos_obj], obj[pos_obj2], v1novo1, v2novo2 };

		for (i = 0; i < 22; i++)
		{
			vet1[i] = 0;
			vet2[i] = 0;
		}

		for (int z = 0; z < 4; z++)
		{
			if (m1 < result[z])
			{
				m1 = result[z];
				mobj1 = objp[z];

				if (z == 0)
				{
					for (i = 0; i < 22; i++)
					{
						vet1[i] = copiavett1[i];
					}
				}

				if (z == 1)
				{
					for (i = 0; i < 22; i++)
					{
						vet1[i] = copiavett2[i];
					}
				}

				if (z == 2)
				{
					for (i = 0; i < 22; i++)
					{
						vet1[i] = vett_1[i];
					}
				}

				if (z == 3)
				{
					for (i = 0; i < 22; i++)
					{
						vet1[i] = vett_2[i];
					}
				}
			}
		}

		for (int z = 0; z < 4; z++)
		{
			if (m1 != result[z])
			{
				if (m2 < result[z])
				{
					m2 = result[z];
					mobj2 = objp[z];

					if (z == 0)
					{
						for (i = 0; i < 22; i++)
						{
							vet2[i] = copiavett1[i];
						}
					}

					if (z == 1)
					{
						for (i = 0; i < 22; i++)
						{
							vet2[i] = copiavett2[i];
						}
					}

					if (z == 2)
					{
						for (i = 0; i < 22; i++)
						{
							vet2[i] = vett_1[i];
						}
					}

					if (z == 3)
					{
						for (i = 0; i < 22; i++)
						{
							vet2[i] = vett_2[i];
						}
					}
				}
			}
		}

		cout << "vet1:   ";

		for (int z = 0; z < 22; z++)
		{
			cout << vet1[z] << "\t";
		}

		cout << "\n\n";
		cout << "vet2:   ";

		for (int z = 0; z < 22; z++)
		{
			cout << vet2[z] << "\t";
		}


		for (j = 0; j < 22; j++)
		{
			pop[pos_obj][j] = vet1[j];
			pop[pos_obj2][j] = vet2[j];
		}

		//JOGANDO NA FUNÇÃO OBJETIVO
		for (i = 0; i < qtdind; i++)
		{

			mudanca_base(pop, conv);

			obj[i] = -1.0 + ((conv[i] * 3.0) / 4194303.0);
		}

		//CALCULANDO A FUNCAO f(x)

		for (i = 0; i < qtdind; i++)
		{
			f[i] = obj[i] * sin(31.41592*obj[i]) + 1.0;
		}


		for (i = 0; i < qtdind; i++)
		{
			if (maior_otz < f[i])
			{
				maior_otz = f[i];
				pos_f = i;
			}
		}



		cout << "Geracao: " << k << endl;
		cout << "Valor em x::     " << obj[pos_f] << endl;
		cout << "Maior valor da funcao f(x)::     " << maior_otz << endl;
		cout << "\n\nPopulacao";


		for (i = 0; i < qtdind; i++){
			cout << "\nInd " << i;
			for (j = 0; j < 22; j++)
			{
				cout << "\t" << pop[i][j];

			}
			cout << "\tFO: " << obj[i];

		}


	}




	return 0;

}



