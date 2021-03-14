#include <stdio.h>
#include <Windows.h>

#define STRING_SIZE 256

void Encrypt(unsigned char* text, unsigned char* key, char* shifrtext)
{
	int keylen = strlen(key);
	int textlen = strlen(text);
	for (int i = 0; i < textlen; i++)
	{
		shifrtext[i] = (unsigned char)'а' + (text[i] + key[i % keylen] - 2 * (unsigned char)'а') % 32;
	}
	shifrtext[textlen] = '\0';
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char key[STRING_SIZE];
	printf("Введите ключ(ру, ниж): ");
	gets_s(key, STRING_SIZE);


	char text[STRING_SIZE];
	printf("Введите шифруемый текст(ру, ниж): ");
	gets_s(text, STRING_SIZE);

	char shifrtext[STRING_SIZE];
	Encrypt(text, key, shifrtext);
	printf("Зашифрованный текст: %s\n", shifrtext);


	return 0;
}