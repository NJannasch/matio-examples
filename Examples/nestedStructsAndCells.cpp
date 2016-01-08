#include <matio.h>

int main() {
	mat_t *matfp;
	const char *FILENAME = "export.mat";

	char *structname = "Test";
	const char *fieldnames[1] = { "Data" };
	const char *Datafieldnames[2] = { "double", "cell" };

	//Open file
	matfp = Mat_CreateVer(FILENAME, NULL, MAT_FT_MAT73);

	size_t structdim0[2] = { 1, 2 }; // create 1 x 2 struct
	matvar_t *matstruct0 = Mat_VarCreateStruct(structname, 2, structdim0, fieldnames, 1);

	size_t structdim1[2] = { 1, 1 };
	matvar_t *matstruct1 = Mat_VarCreateStruct(NULL, 2, structdim1, Datafieldnames, 2);
	Mat_VarSetStructFieldByName(matstruct0, fieldnames[0], 0, matstruct1); // set Test(1).Data

	size_t structdim2[2] = { 1, 1 };
	matvar_t *matstruct2 = Mat_VarCreateStruct(NULL, 2, structdim2, Datafieldnames, 2);
	Mat_VarSetStructFieldByName(matstruct0, fieldnames[0], 1, matstruct2); // set Test(2).Data



	size_t outercelldim[2] = { 1, 2 };
	matvar_t *outercell = Mat_VarCreate(NULL, MAT_C_CELL, MAT_T_CELL, 2, outercelldim, NULL, 0); //create outer cell

	double mydouble1 = 42.2;
	double mydouble2 = 142.2;
	size_t innercelldim[2] = { 1, 2 };
	size_t doubledim[2] = { 1, 1 };
	matvar_t *cells[2]; //create cell data
	cells[0] = Mat_VarCreate(NULL, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, doubledim, &mydouble1, 0);
	cells[1] = Mat_VarCreate(NULL, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, doubledim, &mydouble2, 0);

	matvar_t *innercell = Mat_VarCreate(NULL, MAT_C_CELL, MAT_T_CELL, 2, innercelldim, cells, 0); //create inner cell
	Mat_VarSetCell(outercell, 0, innercell); //set inner cell

	size_t structdim3[2] = { 1, 1 };
	matvar_t *matstruct3 = Mat_VarCreateStruct(NULL, 2, structdim3, Datafieldnames, 2);
	Mat_VarSetCell(outercell, 1, matstruct3); // set struct into outer cell

	Mat_VarSetStructFieldByName(matstruct1, Datafieldnames[1], 0, outercell); //set outer cell into struct


	//save main struct
	Mat_VarWrite(matfp, matstruct0, MAT_COMPRESSION_ZLIB);
	//cleanup
	Mat_VarFree(matstruct0);
	//Close file
	Mat_Close(matfp);

	return 0;
}