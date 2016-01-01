#include <matio.h>

int main() {
	mat_t *matfp;
	const char *FILENAME = "export.mat";

	char *structname = "Test";
	const char *fieldnames[1] = { "Data"};
	const char *Datafieldnames[3] = { "name", "unit", "value" };

	//Open file
	matfp = Mat_CreateVer(FILENAME, NULL, MAT_FT_MAT5);

	size_t structdim0[2] = { 1, 3 }; // create 1 x 3 struct
	matvar_t* matstruct0 = Mat_VarCreateStruct(structname, 2, structdim0, fieldnames, 1); //main struct: Test

	//Note: Matlab starts counting at 1

	//create nested structs:

	//Test(1).Data
	char* mystring0 = "Data"; //Test(1).Data
	size_t structdim1[2] = { 1, 1 };
	matvar_t* matstruct1 = Mat_VarCreateStruct(mystring0, 2, structdim1, Datafieldnames, 3);
	Mat_VarSetStructFieldByName(matstruct0, fieldnames[0], 0, matstruct1); //save pointer into main struct - freeing matstruct1 causes a segfault at Mat_VarFree(matstruct0);

	//Test(2).Data
	char* mystring1 = "Data"; //Test(2).Data
	size_t structdim2[2] = { 1, 1 };
	matvar_t* matstruct2 = Mat_VarCreateStruct(mystring1, 2, structdim2, Datafieldnames, 3);
	Mat_VarSetStructFieldByName(matstruct0, fieldnames[0], 1, matstruct2); //save pointer into main struct - freeing matstruct2 causes a segfault at Mat_VarFree(matstruct0);

	//Test(3).Data
	char* mystring2 = "Data"; //Test(3).Data
	size_t structdim3[2] = { 1, 1 };
	matvar_t* matstruct3 = Mat_VarCreateStruct(mystring2, 2, structdim3, Datafieldnames, 3);
	Mat_VarSetStructFieldByName(matstruct0, fieldnames[0], 2, matstruct3); //save pointer into main struct - freeing matstruct3 causes a segfault at Mat_VarFree(matstruct0);


	//set struct field to value
	double mydouble = 85.85; //put into Test(1).Data.value
	size_t dim5[2] = { 1, 1 };
	matvar_t *variable = Mat_VarCreate(fieldnames[0], MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim5, &mydouble, 0);
	Mat_VarSetStructFieldByName(matstruct1, Datafieldnames[0], 0, variable);
	Mat_VarFree(variable);


	//save main struct
	Mat_VarWrite(matfp, matstruct0, MAT_COMPRESSION_NONE);
	//cleanup
	Mat_VarFree(matstruct0);


	//Close file
	Mat_Close(matfp);

	return 0;
}
