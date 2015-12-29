#include <matio.h>

int main() {
	mat_t *matfp;
	const char *FILENAME = "myfile.mat";

	//Open file
	matfp = Mat_CreateVer(FILENAME, NULL, MAT_FT_MAT5);

	//string
	char* fieldname1 = "MyStringVariable";
	char* mystring = "Text";
	size_t dim1[2] = { 1, sizeof(mystring)/sizeof(mystring[0]) };
	matvar_t *variable1 = Mat_VarCreate(fieldname1, MAT_C_CHAR, MAT_T_UTF8, 2, dim1, mystring, 0);
	Mat_VarWrite(matfp, variable1, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB

	//integer
	char* fieldname2 = "MyIntegerVariable";
	int myinteger = 42;
	size_t dim2[2] = { 1, 1 };
	matvar_t *variable2 = Mat_VarCreate(fieldname2, MAT_C_INT32, MAT_T_INT32, 2, dim2, &myinteger, 0);
	Mat_VarWrite(matfp, variable2, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB

	//double
	char* fieldname3 = "MyDoubleVariable";
	double mydouble = 4.2;
	size_t dim3[2] = { 1, 1 };
	matvar_t *variable3 = Mat_VarCreate(fieldname3, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim3, &mydouble, 0);
	Mat_VarWrite(matfp, variable3, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB

	//complex double
	char* fieldname4 = "MyComplexDoubleVariable";
	double real = 4.2;
	double imag = 1.5;
	mat_complex_split_t mycomplexdouble = { &real, &imag };
	size_t dim4[2] = { 1, 1 };
	matvar_t *variable4 = Mat_VarCreate(fieldname4, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim4, &mycomplexdouble, MAT_F_COMPLEX);
	Mat_VarWrite(matfp, variable4, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB

	//bool
	char* fieldname5 = "MyBoolVariable";
	bool mybool = true;
	size_t dim5[2] = { 1, 1 };
	matvar_t *variable5 = Mat_VarCreate(fieldname5, MAT_C_INT16, MAT_T_INT16, 2, dim5, &mybool, MAT_F_LOGICAL);
	Mat_VarWrite(matfp, variable5, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
	
	//Close file
	Mat_Close(matfp);
	return 0;
}