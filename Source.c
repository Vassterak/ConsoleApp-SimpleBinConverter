#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_LENGHT 64

void initial(char* str)
{
	str[0] = '\0';
	printf("If your input is longer than %d characters, overflow chars will be ignored.\n", MAX_MESSAGE_LENGHT - 1);
	printf("Enter ASCII message to transform it to binary code: ");

	strcpy_s(str, MAX_MESSAGE_LENGHT, fgets(str, MAX_MESSAGE_LENGHT, stdin));
}

void convert_each_char(char letter, int arrayIndex, int* strOut)
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

void loop_throught_message(char* str, int* strOutput)
{
	//int* strOutput = malloc(strlen(str) * 8 * sizeof(int));
	for (size_t i = 0; i < strlen(str); i++)
		convert_each_char(str[i], i, strOutput);
}

void print_message(int messageLenght, int* strOutput)
{
	for (int i = 0; i < messageLenght; i++)
	{
		for (int j = 0; j < 8; j++)
			printf("%d", strOutput[i * 8 + j]);
		printf("\n");
	}
	printf("--------------------------------------\n");
}

void save_to_file(int messageLenght, int* dataToWrite)
{
	printf("Your binary output is saved to file named: binaryOutput.txt\n");

	FILE* outputFile;
	fopen_s(&outputFile,"binaryOutput.txt", "w+");

	if (outputFile != NULL)
	{
		for (int i = 0; i < messageLenght; i++)
		{
			for (int j = 0; j < 8; j++)
				fprintf(outputFile, "%d", dataToWrite[i * 8 * j]);
			fputs("\n", outputFile);
		}
		fclose(outputFile);
	}
	else
		printf("Unable to create a file.\n");
}

int new_conversion()
{
	printf("Would you like to convert next text to binary y/n.\n");
	/*
	char detectNewConversion[2] = "";
	fgets(detectNewConversion, 1, stdin);
	if (detectNewConversion[0] == 89)
		return 0;
	else*/
		return 1;
}

int main()
{
	int isNew = 1;
	int* strOutput = NULL;

	char inputMesssage[MAX_MESSAGE_LENGHT]; //user text
	initial(inputMesssage); //save the message from user input
	int messageLenght = strlen(inputMesssage) -1;

	strOutput = (int*) malloc(messageLenght * 8 * sizeof(int)); //create array used to store output values
	printf("Your message lenght: %d\n", messageLenght);
	loop_throught_message(inputMesssage, strOutput);
	print_message(messageLenght, strOutput);

	while (1)
	{
		initial(inputMesssage); //save the message from user input
		int messageLenght = strlen(inputMesssage) - 1;

		printf("Your message lenght: %d\n", messageLenght);

		strOutput = realloc(strOutput, messageLenght * 8 * sizeof(int)); //change allocated memory, IDK NOT WORKING IDK HOW TO FIX IT...
		
		loop_throught_message(inputMesssage, strOutput);
		print_message(messageLenght, strOutput);

		//save_to_file(messageLenght, strOutput);

		//free(strOutput[0]);
		free(strOutput);
	}

	return 0;
}