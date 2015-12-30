#include <matio.h>

int main() {
	mat_t *matfp;
	const char *FILENAME = "export.mat";

	char *structname = "Data";
	const char *fieldnames[3] = { "name","unit","value" };

	//Open file
	matfp = Mat_CreateVer(FILENAME, NULL, MAT_FT_MAT5);

	size_t structdim[2] = { 1, 2 }; // create 1x2 struct
	matvar_t* matstruct = Mat_VarCreateStruct(structname, 2, structdim, fieldnames, 3); //main struct: Data

	//Note: Matlab starts counting at 1
	
	//first row in 'Data'
	char* mystring0 = "Speed"; //Data(1).name
	size_t dim0[2] = { 1, 5 };
	matvar_t *variable0 = Mat_VarCreate(fieldnames[0], MAT_C_CHAR, MAT_T_UTF8, 2, dim0, mystring0, 0);
	Mat_VarSetStructFieldByName(matstruct, fieldnames[0], 0, variable0); //0 for first row
	Mat_VarFree(variable0);

	char* mystring1 = "km/h"; //Data(1).unit
	size_t dim1[2] = { 1, 4 };
	matvar_t *variable1 = Mat_VarCreate(fieldnames[1], MAT_C_CHAR, MAT_T_UTF8, 2, dim1, mystring1, 0);
	Mat_VarSetStructFieldByName(matstruct, fieldnames[1], 0, variable1); //0 for first row
	Mat_VarFree(variable1);

	double mydouble0 = 42.3;  //Data(1).value
	size_t dim2[2] = { 1, 1 };
	matvar_t *variable2 = Mat_VarCreate(fieldnames[2], MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim2, &mydouble0, 0);
	Mat_VarSetStructFieldByName(matstruct, fieldnames[2], 0, variable2); //0 for first row
	Mat_VarFree(variable2);


	//second row
	char* mystring3 = "Angle"; //Data(2).name
	size_t dim3[2] = { 1, 5 };
	matvar_t *variable3 = Mat_VarCreate(fieldnames[0], MAT_C_CHAR, MAT_T_UTF8, 2, dim3, mystring3, 0);
	Mat_VarSetStructFieldByName(matstruct, fieldnames[0], 1, variable3); //1 for second row
	Mat_VarFree(variable3);

	char* mystring4 = "degree"; //Data(2).unit
	size_t dim4[2] = { 1, 6 };
	matvar_t *variable4 = Mat_VarCreate(fieldnames[1], MAT_C_CHAR, MAT_T_UTF8, 2, dim4, mystring4, 0);
	Mat_VarSetStructFieldByName(matstruct, fieldnames[1], 1, variable4); //1 for second row
	Mat_VarFree(variable4);

	double mydouble1 = 85.85; //Data(2).value
	size_t dim5[2] = { 1, 1 };
	matvar_t *variable5 = Mat_VarCreate(fieldnames[2], MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim5, &mydouble1, 0);
	Mat_VarSetStructFieldByName(matstruct, fieldnames[2], 1, variable5); //1 for second row
	Mat_VarFree(variable5);


	//save main struct
	Mat_VarWrite(matfp, matstruct, MAT_COMPRESSION_NONE);
	//cleanup
	Mat_VarFree(matstruct);


	//Close file
	Mat_Close(matfp);

	return 0;
}
