#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxStringLength 30
#define bufferLength 100

int main() {


    //converte una lista di stringhe da file, in una lista su un file binario, per permettere l'utilizzo di fseek.
    
    // Change to the file name of the file you want to convert
    char fileTxt[]="names.txt";
    
    // Change to the file name of the output file
    char fileDat[]="nomi.dat";
    
    
    
    // Open the txt file for reading
    FILE *fileRead = fopen(fileTxt, "r");
    if (fileRead == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Open the binary file for writing
    FILE *fileWrite = fopen(fileDat, "wb");
    if (fileWrite == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    
    // Array of strings to write to the file
    char strings[bufferLength][maxStringLength];
    
    
    // Write each string to the file
    int i=0;
    int j=0;
    while (fscanf(fileRead, "%s", strings[i])>0) {
        i++;
        if(i==bufferLength){
            for(j=0;j<bufferLength;j++){
                if (fwrite(strings[j], sizeof(char), maxStringLength, fileWrite) != maxStringLength) {
                    printf("Error writing name to file.\n");
                    fclose(fileWrite);
                    
                }
            }
            i=0;
        }
    }
    for(int j=0;j<i;j++){
        if (fwrite(strings[j], sizeof(char), maxStringLength, fileWrite) != maxStringLength) {
            printf("Error writing string to file.\n");
            fclose(fileWrite);
            
        }
    }
    printf("wrote successfully\n");
    // Close the file
    fclose(fileRead);
    fclose(fileWrite);
    
    
	return 0;
}
