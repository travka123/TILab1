#include <stdio.h>
#include <Windows.h>

#define STRING_SIZE 256

void Decrypt(char* shifrtext, unsigned char* key, char* text)
{
	int keylen = strlen(key);
	int shifrtextlen = strlen(shifrtext);
	int mincolumnpos = 0;

	for (int i = 0; i < keylen; i++)
	{
		if (key[i] < key[mincolumnpos])
		{
			mincolumnpos = i;
		}
	}

	int lastmincolumpos;
	do {

		for (int i = mincolumnpos; i < shifrtextlen; i += keylen)
		{
			text[i] = *(shifrtext++);
		}

		lastmincolumpos = mincolumnpos;
		for (int i = 0; i < keylen; i++)
		{
			if ((key[i] > key[lastmincolumpos]) && ((mincolumnpos == lastmincolumpos) || (key[i] < key[mincolumnpos])))
			{
				mincolumnpos = i;
			}
			else if ((key[i] == key[lastmincolumpos]) && (i > lastmincolumpos))
			{
				mincolumnpos = i;
				break;
			}
		}
	} while (mincolumnpos != lastmincolumpos);
	text[shifrtextlen] = '\0';
}

int CheckKey(char* key)
{
	char used[256];
	memset(used, 0, sizeof(used));
	for (int i = 0; i < strlen(key); i++)
	{
		if (used[key[i]] == 1)
		{
			return 0;
		}
		else
		{
			used[key[i]] = 1;
		}
	}
	return 1;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char key[STRING_SIZE];
	printf("Введите ключ: ");
	gets_s(key, STRING_SIZE);

	
		char shifrtext[STRING_SIZE];
		printf("Введите зашифрованный текст: ");
		gets_s(shifrtext, STRING_SIZE);

		char text[STRING_SIZE];
		Decrypt(shifrtext, key, text);
		printf("Расшифрованный текст: %s\n", text);
	

	return 0;
}