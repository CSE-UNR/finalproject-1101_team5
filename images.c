//Andre Jimenez and Kevin Gonzalez
//CS 135 Final Project
//Images Project

#include <stdio.h>
#include <stdbool.h>

#define MAX_IMAGE_SIZE 50

void loadImage(char erinstagram[], char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols);
void displayImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols);
void editMenu(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols);
void saveImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols);

void cropImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols, int startRow, int endRow, int startCol, int endCol);
void dimImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols, double factor);
void brightenImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols, double factor);
void rotateImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols);

int main(){
	int choice;
	char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];
	int rows = 0, cols = 0;
	char filename[] = "image.txt";
	
	do{
		printf("\nErinstagram Main Menu\n");
		printf("1. Load new image.\n");
		printf("2. Display current image.\n");
		printf("3. Edit current image.\n");
		printf("4. Exit program.\n");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				loadImage(filename, image, &rows, &cols);
				break;
			case 2:
				displayImage(image, rows, cols);
				break;
			case 3:
				editMenu(image, &rows, &cols);
				break;
			case 4:
				printf("Exiting the program.");
				break;
			default:
				printf("Invalid choice. Please pick from the options above. (1-4)");
		}
	}while(choice != 4);
	
	return 0;
}

void loadImage(char filename[], char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols){
	printf("Loading imagefrom file: %s\n", filename);
	FILE *file = fopen (filename, "r");
	if (file == NULL){
		printf("Can't open file.\n");
		
		return;
	}
	*rows = 0;
	*cols = 0;
	char line[MAX_IMAGE_SIZE];
	while(fgets(line, MAX_IMAGE_SIZE, file) != NULL && *rows < MAX_IMAGE_SIZE){
		int len = 0;
		while(line[len] != '\0' && line[len] != '\n' && len < MAX_IMAGE_SIZE - 1){
			len++;
		}
		for(int i = 0; i < len; i++){
			image[*rows][i] = line[i];
		}
		for(int i = len; i < *cols; i++){
			image[*rows][i] = '\0';
		}
		if(len > *cols){
			*cols = len;
		}
		(*rows)++;
	}
	fclose(file);
}

void displayImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols){
	printf("Displaying current image\n");
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("%c", image[i][j]);
		}
		printf("\n");
	}
}


void editMenu(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols){
	int choice;
	
	do{
		printf("\nErinstagram Edit Menu\n");
		printf("1. Crop\n");
		printf("2. Dim\n");
		printf("3. Brighten\n");
		printf("4. Save Image\n");
		printf("5. Rotate Image 90 Degress\n");
		printf("6. Back To Main Menu\n");
		scanf("%d", &choice);
		
		switch(choice){
			case 1: {
				printf("Cropping the image...\n");
				 int startRow, endRow, startCol, endCol;
                		printf("Enter start row and end row: ");
                		scanf("%d %d", &startRow, &endRow);
                		printf("Enter start column and end column: ");
                		scanf("%d %d", &startCol, &endCol);
                		cropImage(image, rows, cols, startRow, endRow, startCol, endCol);
                		break;
            		}
			
			case 2: {
				printf("Dimming the image...\n");		
                		double dimFactor;
               			printf("Enter dimming factor (between 0 and 1): ");
               			scanf("%lf", &dimFactor);
                		dimImage(image, *rows, *cols, dimFactor);
                		break;
          	 	}
			
			case 3: {
				printf("Brightening the image...\n");
				double brightenFactor;
                		printf("Enter brightening factor (> 1): ");
                		scanf("%lf", &brightenFactor);
               	 		brightenImage(image, *rows, *cols, brightenFactor);
                		break;
			}
			
			case 4:
				printf("Saving image...\n");
				saveImage(image, *rows, *cols);
				break;
			case 5:
				printf("Rotating image 90 degrees...\n");
				rotateImage(image, rows, cols);
				break;
			case 6:
				printf("Returning to Main Menu...\n");
				break;
			default:
				printf("Invalid choice. Please pick from the options above. (1-6)");
		}
	}while(choice != 6);
}

void saveImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols){
	FILE *file = fopen("edited_image.txt", "w");
	if(file == NULL){
		printf("Can't open file.\n");
		
		return;
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			fprintf(file, "%c", image[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
	printf("Image saved to edited_image.txt\n");
}

void cropImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols, int startRow, int endRow, int startCol, int endCol) {
    int newRows = endRow - startRow + 1;
    int newCols = endCol - startCol + 1;

    char croppedImage[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];

 	for (int i = startRow; i <= endRow && i < *rows && i - startRow < newRows; i++) {
        for (int j = startCol; j <= endCol && j < *cols && j - startCol < newCols; j++) {
            croppedImage[i - startRow][j - startCol] = image[i][j];
        }
    }

    *rows = newRows;
    *cols = newCols;
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            image[i][j] = croppedImage[i][j];
        }
    }
}

void dimImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols, double factor) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] *= factor;
        }
    }
}

void brightenImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols, double factor) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] *= factor;
        }
    }
}

void rotateImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols) {
char rotatedImage[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];
for( int i = 0; i < *rows; i++) {
	for(int j = 0; j < *cols; j++) {
		rotatedImage[j][*rows - 1 - i] = image[i][j];
	}
}

int turn = *rows;
*rows = *cols;
*cols = turn;

for( int i = 0; i < *rows; i++) {
	for( int j = 0; j < *cols; j++) {
		image[i][j] = rotatedImage[i][j];
	}
}
