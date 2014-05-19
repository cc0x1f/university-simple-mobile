#include "../header/Helper.h"

void Helper::printMatrix(glm::mat4 matrix) {
	int row, column;
	
	printf("\n---------------------------------------\n");
	for (row=0; row<4; row++) {
		for(column=0; column<4; column++)
			printf("%f\t", matrix[column][row]);
		printf("\n");
	}
	printf("---------------------------------------\n");
}
