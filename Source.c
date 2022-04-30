#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_LENGHT 128

void get_user_input(char* str)
{
	printf("If your input is longer than %d characters, overflow chars will be ignored.\n", MAX_MESSAGE_LENGHT - 1);
	printf("Enter ASCII message to transform it to binary code: ");
	strcpy_s(str, MAX_MESSAGE_LENGHT, fgets(str, MAX_MESSAGE_LENGHT, stdin)); //copy user input into 
}

void convert_char_to_binary(char letter, int arrayIndex, int* strOut)
{
	unsigned char workaround = letter; //char is signed by default so bitshift to left -> overflow to negative values. For fix we use unsigned char
	for (size_t i = 0; i < 8; i++)
	{
		if ((workaround & 0x80) != 0)
			strOut[arrayIndex * 8 + i] = 1;
		else
			strOut[arrayIndex * 8 + i] = 0;

		workaround = workaround << 1;
	}
}

void loop_thr_msg(char* str, int* strOutput)
{
	for (size_t i = 0; i < strlen(str)-1; i++) // -1 because ignore last ASCII(DEC 10, new line)
		convert_char_to_binary(str[i], i, strOutput);
}

void print_convert_msg(int messageLenght, int* strOutput)
{
	for (int i = 0; i < messageLenght-1; i++) // -1 because ignore last ASCII(DEC 10, new line)
	{
		for (int j = 0; j < 8; j++)
			printf("%d", strOutput[i * 8 + j]);
		printf("\n");
	}
}

void save_to_file(int messageLenght, int* dataToWrite)
{
	char userAnswer;
	do
	{
		printf("PS: if you already saved a file now it will be replaced! Be careful.\n");
		printf("Would you like to save the new file? y/n ");

		scanf(" %c", &userAnswer); 
		getchar(); // the getchar() is necessary because the fgets will thing that user input is new line.

	} while (tolower(userAnswer) != 'y' && tolower(userAnswer) != 'n');

	if (userAnswer == 'n')
		return;

	printf("Your binary output is saved to file named: binaryOutput.txt\n");

	FILE* outputFile;
	fopen_s(&outputFile,"binaryOutput.txt", "w+");

	if (outputFile != NULL)
	{
		for (int i = 0; i < messageLenght-1; i++)
		{
			for (int j = 0; j < 8; j++)
				fprintf(outputFile, "%d", dataToWrite[i * 8 + j]);
			fputs("\n", outputFile);
		}
		fclose(outputFile);
	}
	else
		printf("Unable to create a file.\n");
	printf("\n");
}

int main()
{
	char inputMesssage[MAX_MESSAGE_LENGHT]; //user text input is saved here
	int messageLenght;

	int * strOutput = (int*) calloc(8, sizeof(int)); //allocate some memory (size Will be dynamically changed by user input lenght)

	while (1)
	{
		get_user_input(inputMesssage); //save the message from user input
		messageLenght = strlen(inputMesssage);

		printf("New message lenght: %d\n", messageLenght);

		strOutput = (int*) realloc(strOutput, (messageLenght * 8 * sizeof(int))); //change allocated memory
		if (strOutput == NULL) //Check if memory reallocation was successful
		{
			printf("Memory allocation failed\n");
			break;
		}
		
		loop_thr_msg(inputMesssage, strOutput);
		print_convert_msg(messageLenght, strOutput);
		save_to_file(messageLenght, strOutput);
	}

	free(strOutput);
	return 0;
}
