#include <matio.h>

int main() {
	mat_t *matfp = NULL;
	const char *FILENAME = "export.mat";
	
	const int first = 4; //rows
    const int second = 4; //columns
	
	//Open file
	matfp = Mat_CreateVer(FILENAME, NULL, MAT_FT_MAT5);
	
	//#################################################
	
	//#########
	// 2d array
    int array2d[first][second] = { 0 };
 
    // fill 2d array
    for (int i = 0; i < first; i++)
        for (int j = 0; j < second; j++)
            array2d[i][j] = i * j;

	// write
	char* fieldname2d = "array2d";
	size_t dim2d[2] = { first, second };
	matvar_t *variable2d = Mat_VarCreate(fieldname2d, MAT_C_INT32, MAT_T_INT32, 2, dim2d, &array2d, 0); //rank 2
	Mat_VarWrite(matfp, variable2d, MAT_COMPRESSION_NONE);
	Mat_VarFree(variable2d);

	//#########
	// 3d array
	const int third = 4;
	int array3d[first][second][third] = { 0 };

	// fill 3d array
	for (int i = 0; i < first; i++)
		for (int j = 0; j < second; j++)
			for (int k = 0; k < third; k++)
				array3d[i][j][k] = i * j * k;

	// write
	char* fieldname3d = "array3d";
	size_t dim3d[3] = { first, second, third };
	matvar_t *variable3d = Mat_VarCreate(fieldname3d, MAT_C_INT32, MAT_T_INT32, 3, dim3d, &array3d, 0); //rank 3
	Mat_VarWrite(matfp, variable3d, MAT_COMPRESSION_NONE);
	Mat_VarFree(variable3d);

	//#########
	// 4d array
	const int fourth = 4;
	int array4d[first][second][third][fourth] = { 0 };

	// fill 4d array
	for (int i = 0; i < first; i++)
		for (int j = 0; j < second; j++)
			for (int k = 0; k < third; k++)
				for (int l = 0; l < fourth; l++)
					array4d[i][j][k][l] = i * j * k *l;

	// write
	char* fieldname4d = "array4d";
	size_t dim4d[4] = { first, second, third, fourth };
	matvar_t *variable4d = Mat_VarCreate(fieldname4d, MAT_C_INT32, MAT_T_INT32, 4, dim4d, &array4d, 0); //rank 4
	Mat_VarWrite(matfp, variable4d, MAT_COMPRESSION_NONE);
	Mat_VarFree(variable4d);
	
	//for N dimensional array create:
	//int arrayNd
	//create:
	//size_t dimNd[N] = {...};
	//and select rank N in Mat_VarCreate:                 | |
	//Mat_VarCreate(fieldnameNd, MAT_C_INT32, MAT_T_INT32, N, dimNd, &arrayNd, 0);
	//                                                    | |
	//#################################################
	
	//Close file
	Mat_Close(matfp);
	
	return 0;
}