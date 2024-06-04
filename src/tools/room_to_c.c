#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100

typedef enum tagSECTION
{
	SECTION_HEADER,
	SECTION_KEY,
	SECTION_TILES,
} SECTION;

/// @brief Reads up to 100 chars including a null char from a file.
/// @param file The file to read from.
/// @param buffer A buffer that should be 100 chars long.
/// @return If the end of file was reached.
int readWord(FILE *file, char* buffer)
{
	int result = fscanf(file, "%99s", buffer);
	return result == EOF;
}

int main(int argc, char *argv[])
{
	char *inputPath;
	char *outputPath;
	FILE *inputFile;
	SECTION section = SECTION_HEADER;
	//size_t inputFileSize;
	//char *inputFileContent;
	//size_t x;
	// Get arguments
	if (argc != 3)
	{
		printf("Invalid argument count. Syntax: room_to_c <input path> <output path>.\n");
		return 1;
	}
	inputPath = argv[1];
	outputPath = argv[2];
	// Open file
	inputFile = fopen(inputPath, "r");
	if (inputFile == NULL)
	{
		printf("Error opening file %s.\n", inputPath);
		return 1;
	}
	// For each statement
	while (1)
	{
		char inputWord[MAX_WORD_LENGTH];
		int result;
		// Read first word of line
		result = readWord(inputFile, inputWord);
		if (result) break;
		printf("%s\n", inputWord);
	}
	return 0;
}