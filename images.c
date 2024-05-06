//Andre Jimenez and Kevin Gonzalez
//CS 135 Final Project
//Images Project

#include <stdio.h>
#include <stdbool.h>

#define MAX_IMAGE_SIZE 50

void loadImage(char erinstagram[], char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols);
void displayImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols);
void editMenu(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols);
void saveImage(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols);





int main(){
	int choice;
	char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];
	int rows = 0, cols = 0;
	
	do{
		printf("\nErinstagram Main Menu\n");
		printf("1. Load new image.\n");
		printf("2. Display current image.\n");
		printf("3. Edit current image.\n");
		printf("4. Exit program.\n");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				loadImage("image.txt", image, &rows, &cols);
				break;
			case 2:
				displayImage(image, rows, cols);
				break;
			case 3:
				editMenu(image, rows, cols);
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

void loadImage(char erinstagram[], char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int *rows, int *cols){
	printf("Loading imagefrom file: %s\n", erinstagram);
	FILE *file = fopen (erinstagram, "r");
	if (file == NULL){
		printf("Can't open file.\n");
		
		return;
	}
	*rows = 0;
	*cols = 0;
	char ch;
	while((ch = fgetc(file)) != EOF && *rows < MAX_IMAGE_SIZE){
		if(ch !='\n'){
			*cols = 0;
			(*rows)++;
		}else if(*cols < MAX_IMAGE_SIZE){
			image[*rows][*cols] = ch;
			(*cols)++;
		}
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


void editMenu(char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE], int rows, int cols){
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
			case 1:
				printf("Cropping the image...\n");
				//Crop Function
				break;
			case 2:
				printf("Dimming the image...\n");
				//Dim Function
				break;
			case 3:
				printf("Brightening the image...\n");
				//Brighten Function
				break;
			case 4:
				printf("Saving image...\n");
				saveImage(image, rows, cols);
				break;
			case 5:
				printf("Rotating image 90 degrees...\n");
				//Rotate Function
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
		printf("Can't open file.");
		
		return;
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			fprintf(file, "%c", image[i][j]);
		}
		fprintf(file, "/n");
	}
	fclose(file);
	printf("Image saved to edited_image.txt");
}
