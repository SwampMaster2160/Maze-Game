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
	FILE *outputFile;
	SECTION section = SECTION_HEADER;
	unsigned tileRow = 0;
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
	// Create and open output file
	outputFile = fopen(outputPath, "w");
	if (outputFile == NULL)
	{
		printf("Error creating output file %s.\n", outputPath);
		return 1;
	}
	// Include main.h
	fprintf(outputFile, "#include \"../src/main.h\"\n");
	// For each statement
	while (1)
	{
		char inputWord[MAX_WORD_LENGTH];
		size_t inputWordLenth;
		int result;
		// Read first word of line
		result = readWord(inputFile, inputWord);
		if (result || inputWord[0] == 0) break;
		inputWordLenth = strlen(inputWord);
		// Process section words
		if (inputWordLenth != 16 && inputWord[0] == '#')
		{
			// Change section
			char *sectionName = inputWord + 1;
			if (strcmp(sectionName, "head") == 0) section = SECTION_HEADER;
			else if (strcmp(sectionName, "key") == 0) section = SECTION_KEY;
			else if (strcmp(sectionName, "tiles") == 0) section = SECTION_TILES;
			else
			{
				printf("Unknown section %s.\n", sectionName);
				return 1;
			}
			// Make sure we dont change section while processing a map layout
			if (tileRow != 0 && tileRow != 16)
			{
				printf("Map must have 16 rows.\n");
				return 1;
			}
			// Reset the map row we are processing
			tileRow = 0;
			// Write a comment for the section
			fprintf(outputFile, "// %s\n", sectionName);
			// Define '.' as TILE_NULL by default.
			if (section == SECTION_KEY) fprintf(outputFile, "#define RTC_TILE_LETTER_%hhu TILE_NULL\n", '.');
			// Next word
			continue;
		}
		// Process other words depending on what section we are in
		switch (section)
		{
		case SECTION_HEADER:
			// a "name" word is the room name
			if (strcmp(inputWord, "name") == 0)
			{
				result = readWord(inputFile, inputWord);
				if (result)
				{
					printf("Error reading room name.\n");
					return 1;
				}
				fprintf(outputFile, "#define RTC_ROOM_NAME %s\n", inputWord);
			}
			else
			{
				printf("Invalid word in header.\n");
				return 1;
			}
			break;
		case SECTION_KEY:
			// The tile letter should be 1 char long
			if (inputWordLenth != 1)
			{
				printf("Tile letter name must be 1 char long.\n");
				return 1;
			}
			// Add code line
			{
				char tileLetter = inputWord[0];
				result = readWord(inputFile, inputWord);
				if (result)
				{
					printf("Error reading tile name.\n");
					return 1;
				}
				fprintf(outputFile, "#define RTC_TILE_LETTER_%hhu %s\n", tileLetter, inputWord);
			}
			break;
		case SECTION_TILES:
			// Make sure the row is 16 chars long
			if (inputWordLenth != 16)
			{
				printf("Map row must be 16 chars long.\n");
				return 1;
			}
			// If we are processing the first line, add the array definition
			if (tileRow == 0) fprintf(outputFile, "const TILE RTC_ROOM_NAME[16][16] = {\n");
			// Make sure the room is not more than 16 rows long
			if (tileRow > 15)
			{
				printf("Map must have 16 rows.\n");
				return 1;
			}
			// Add code for each line to the output file
			fprintf(outputFile, "\t{\n");
			{
				unsigned x;
				for (x = 0; x < 16; x++) fprintf(outputFile, "\t\tRTC_TILE_LETTER_%hhu,\n", inputWord[x]);
			}
			fprintf(outputFile, "\t},\n");

			tileRow++;
			// If we are on the last line, end the array
			if (tileRow == 16) fprintf(outputFile, "};\n");
			break;
		}
	}
	// Clean up
	fclose(inputFile);
	fflush(outputFile);
	fclose(outputFile);
	return 0;
}