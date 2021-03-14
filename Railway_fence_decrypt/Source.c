#include <stdio.h>
#include <string.h>

#define BUFFER_LENGTH 256

void Decrypt(char* output, char* input, int n)
{
	int len = strlen(input);
	output[len] = 0;
	int distance = (n - 1) * 2;

	for (int outpos = 0; outpos < len; outpos += distance)
	{
		output[outpos] = *input;
		input++;
	}
	len--;
	output++;

	for (int i = 1; i < n - 1; i++)
	{
		output[0] = *input;
		input++;
		int localDistance = distance - i * 2;
		for (int i = localDistance; i < len; i += localDistance)
		{
			output[i] = *input;
			input++;
			localDistance = distance - localDistance;
		}
		output++;
		len--;
	}

	for (int outpos = 0; outpos < len; outpos += distance)
	{
		output[outpos] = *input;
		input++;
	}
}

int main()
{
	char input[BUFFER_LENGTH];
	char output[BUFFER_LENGTH];
	int n;

	gets_s(input, sizeof(input));
	scanf_s("%d", &n);
	Decrypt(output, input, n);
	puts(output);
	return 0;
}