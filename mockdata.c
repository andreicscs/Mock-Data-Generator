#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxStringLength 30 // The length must match that at which the records have been written

#define maxChoices 4


int getRandomNumber(int min, int max);
char* randomStringFromFile(const char *FileName);

int main() {
	

    // Seed the random number generator with the current time
    srand(time(NULL));
    
    // Open the txt file for writing CSV records
    FILE *fileWriteRecords = fopen("GeneratedMockData.txt", "w");
    if (fileWriteRecords == NULL) {
        perror("Error opening file");
        return 1;
    }
    

	// Let the user choose which fields to use and in which order
	printf("Generate mock data:\n");
    printf("1. Names\n");
    printf("2. Surnames\n");
    printf("3. Genders\n");
    printf("4. Ages\n");
    printf("Enter the numbers of the fields you want to generate in the desired order (e.g., 1 2 3 4): ");
    
    int choices[maxChoices]; // An array to store user choices
    int numChoices = 0;

    int choice;
     while (1) {
        int scanfResult = scanf("%d", &choice);
        if (scanfResult == 1) {
            if (choice == 0) {
                break; // Exit the loop when the user enters 0
            }
            if (numChoices < 4) {
                choices[numChoices++] = choice;
                if (numChoices == 4) {
                    printf("You've reached the maximum number of choices (4).\n");
                    break;
                }
            }
             printf("Enter the next field number or press '0' to finish: ");
        } else {
            // Invalid input, clear the input buffer
            while (getchar() != '\n');
            printf("Invalid choice. Please enter valid numbers (1-4), or '0' to finish: ");
        }
    }

	
    // Create variables to store generated data for each field
    char* namesData;
    char* surnamesData;
    char* gendersData;
    int agesData;
    
    
	int nRecords=0;
	printf("enter how many records to generate: ");
	scanf("%d",&nRecords);
	
	// First row to explain fields.
	for (int y = 0; y < numChoices; y++) {
	    switch (choices[y]) {
	        case 1:
	            fprintf(fileWriteRecords,"name");
	            if(y!=numChoices-1)fprintf(fileWriteRecords,",");
				
	            break;
	        case 2:
	            fprintf(fileWriteRecords,"surname");
	            if(y!=numChoices-1)fprintf(fileWriteRecords,",");
	            break;
	        case 3:
	            fprintf(fileWriteRecords,"gender");
	            if(y!=numChoices-1)fprintf(fileWriteRecords,",");
	            break;
	        case 4:
	            fprintf(fileWriteRecords,"age");
	            if(y!=numChoices-1)fprintf(fileWriteRecords,",");
	            break;
	        default:
	            break;
	    }
	}
    fprintf(fileWriteRecords,"\n");
    
    // Generate the records
	for(int i=0;i<nRecords;i++){
	    // Generate data based on user's choices and order
    	for (int y = 0; y < numChoices; y++) {
	        switch (choices[y]) {
	            case 1:
	                namesData = randomStringFromFile("names.dat");
	                fprintf(fileWriteRecords,"%s",namesData);
	                if(y!=numChoices-1)fprintf(fileWriteRecords,",");// put a comma only if it's not the last field.
					
	                break;
	            case 2:
	                surnamesData = randomStringFromFile("surnames.dat");
	                fprintf(fileWriteRecords,"%s",surnamesData);
	                if(y!=numChoices-1)fprintf(fileWriteRecords,",");
	                break;
	            case 3:
	                gendersData = randomStringFromFile("genders.dat");
	                fprintf(fileWriteRecords,"%s",gendersData);
	                if(y!=numChoices-1)fprintf(fileWriteRecords,",");
	                break;
	            case 4:
	                agesData=getRandomNumber(1,101);
	                fprintf(fileWriteRecords,"%d",agesData);
	                if(y!=numChoices-1)fprintf(fileWriteRecords,",");
	                break;
	            default:
	                break;
	        }
    	}
    	if(i<nRecords-1)fprintf(fileWriteRecords,"\n");// Only go to a new line if it's not the last record
	}
	
    printf("Mock data has been Generated successfully\n");
    
	
    
	// Close the file
	fclose(fileWriteRecords);
	
	//free allocated variables
	free(namesData);
    free(surnamesData);
    free(gendersData);
    //free(agesData); 
    
	return 0;
}


char* randomStringFromFile(const char *FileName){
    char* string = (char*)malloc((maxStringLength + 1) * sizeof(char)); // +1 for the '\0'
    
    // Open the binary file containing names
    FILE *file = fopen(FileName, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Calculate the number of records in the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    long numRecords = fileSize / maxStringLength;
    

    // Generate a random record index
    long randomIndex = rand() % numRecords;
    
    // Seek to the random record
    fseek(file, randomIndex * maxStringLength, SEEK_SET);

    // Read a name record from the file

    if (fread(string, maxStringLength, 1, file) != 1) {
        printf("Error reading string from file.\n");
        fclose(file);
        return NULL;
    }

    // Close the file
    fclose(file);

	return string;
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max+1 - min); // Generates a random age between 0 and 100
}




