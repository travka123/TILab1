#include <stdio.h>
#include <Windows.h>
#include "Lattice.h"

void Decrypt(char *shifrtext, int* lattice, const int width)
{
	int* latticeTurn[4];

	latticeTurn[0] = lattice;
	for (int i = 1; i < 4; i++)
	{
		latticeTurn[i] = GetTurnedLattice(latticeTurn[i - 1], width);
	}

	int length = strlen(shifrtext);
	char* dectyptedstring = (char*)malloc(length + 1);
	dectyptedstring[length] = '\0';
	char* pstr = dectyptedstring;


	int tcount = 0;
	int size = width * width;
	while (TRUE)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (!*pstr)
				{
					printf("�������������� �����: %s\n", dectyptedstring);
					return 0;
				}
				if (latticeTurn[i][j])
				{
					*pstr = shifrtext[tcount * size + j];
					pstr++;
				}
			}
		}
		tcount++;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size;
	int* lattice = GetLattice(&size);
	if (lattice == NULL)
	{
		printf("�� ������� ��������� �������\n");
		return -1;
	}
	printf("������� ���������\n");

	if (!CheckLattice(lattice, size))
	{
		printf("������� �� ���������\n");
		return -1;
	}

	printf("����� ��� �����������: ");
	char text[256];
	gets_s(text, 256);

	Decrypt(text, lattice, size);

	return 0;
}