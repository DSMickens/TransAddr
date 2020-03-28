/**
* TO DO
* 
* Change write files names to name of input file - .txt + needsAdded/needsDeleted
* valgrind
*
*
*
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
*
*/
typedef struct area_code {
    int code;
    char* city;
} AREA_CODE;

/*
*
*/
typedef struct TransEntry {
	bool hasDest;
	int code;
} TRANS_ENTRY;	
	

AREA_CODE area_code[430];
FILE * needsAdded;
FILE * needsDeleted;

/*
*
*/
void printAreaCodes()
{
	for (int i = 0; i < 430; i++){
    	printf("%d %s\n", area_code[i].code, area_code[i].city);
    }
}

/*
*
*/
void freeAreaCodes()
{
    
    for (int i = 0; i < 430; i++){
		free(area_code[i].city);
	}
}

/*
*
*/
void extractAreaCodes()
{
	FILE * codes_file = fopen("Area_Codes.txt", "r");
    
    for (int i = 0; i < 430; i++){
    	  char* cityName = (char*) malloc(30 * sizeof(char)); 
    	  int codeNum;
          fscanf(codes_file, "%d %[^\n]s\n", &codeNum, cityName); 
          area_code[i].code = codeNum;
          area_code[i].city = cityName;
          
          printf("%d\n", area_code[i].code);
    }
}

/*
*
*/
void extractTransEntry(char* fileName)
{
	FILE * trans_entry_file = fopen(fileName, "r");
	
	int lineCount = 0;
	while (!feof(trans_entry_file)){
	
		lineCount++;
	
		char* addrCheck = (char*) malloc(4 * sizeof(char));
		int officeAreaCode;
		int codeNum;
		char* excessNums = (char*) malloc(4 * sizeof(char));
		char* destCheck = (char*) malloc(4 * sizeof(char));
		char* leftovers = (char*) malloc(70 * sizeof(char));
		
		fscanf(trans_entry_file, "%4s %3d %3d%[^A-Z] %s %[^\n]\n",
			   addrCheck, &officeAreaCode, &codeNum, excessNums, destCheck, leftovers);
		
		printf("%s\n", destCheck);
		TRANS_ENTRY officeEntry = {.hasDest = false};
		if (strcmp(destCheck, "DEST") == 0)
		    officeEntry.hasDest = true;
		officeEntry.code = codeNum;
		
		printf("%d\n", officeEntry.code);
		
		bool isValidEntry = false;
		if (officeEntry.hasDest){
			for (int i = 0; i < 430; i++){
				if (officeEntry.code == area_code[i].code)
					isValidEntry = true;
			}
		}
		if (!isValidEntry){
			fprintf(needsDeleted, "Line: %d %4s %3d %3d%s %s %s\n", lineCount,
			    		addrCheck, officeAreaCode, codeNum, excessNums, destCheck, leftovers);
		}
			
		   
		if (codeNum == 800 || codeNum == 822 || codeNum == 833 || codeNum == 844 ||
			codeNum == 855 || codeNum == 866 || codeNum == 877 || codeNum == 888)
		{
			if (strcmp(destCheck, "DEST") != 0 && strcmp(destCheck, "TSCP") != 0
			    && strcmp(destCheck, "SSAC") != 0)
			{
			    fprintf(needsAdded, "Line: %d %4s %3d %3d%s %s %s\n", lineCount,
			    		addrCheck, officeAreaCode, codeNum, excessNums, destCheck, leftovers);
			}
		}
		
		/*printf("Line: %d %4s %3d %3d%s %s %s\n", lineCount,
			    addrCheck, officeAreaCode, codeNum, excessNums, destCheck, leftovers);*/
		
		// Freeing all allocated memory for each line
		free(addrCheck);
		free(excessNums);
		free(destCheck);
		free(leftovers);
	}
}
	
/*
*
*/
int commandLineErrorHandling(int argc)
{	
	if (argc < 2){
        printf("Not enough parameters, make sure to include one file name.\n");
        return 1;
    }
    if (argc > 2){
    	printf("Too many parameters, make sure to include only one file names.\n");
    	return 1;
    }
    return 0;
}

/*
*
*/
void openWriteFiles()
{
    needsAdded = fopen("needsAdded.txt", "w");
    needsDeleted = fopen("needsDeleted.txt", "w");
}
/*
*
*/
int main(int argc, char* argv[])
{
    if (commandLineErrorHandling(argc) == 1) {return 1;}
    
    openWriteFiles();
    
    extractAreaCodes();
    
    //printAreaCodes();
    
    extractTransEntry(argv[1]);
    
    freeAreaCodes();
    
    return 0;
}
