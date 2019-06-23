# Examples for MAT File I/O Library (MATIO)


### Basics

#### Header
```cpp
#include <matio.h>
```

#### Create MAT file

```cpp
const char *filename = "myfile.mat";
mat_t *matfp = NULL; //matfp contains pointer to MAT file or NULL on failure
matfp = Mat_CreateVer(filename, NULL, MAT_FT_MAT5); //or MAT_FT_MAT4 / MAT_FT_MAT73
//don't forget to close file with Mat_Close(matfp);
```

#### Create and save variables ([saveVariable.cpp](https://github.com/NJannasch/matio-examples/blob/master/Examples/saveVariable.cpp))

- String

```cpp
char* fieldname = "MyStringVariable";
char* mystring = "Text";
size_t dim[2] = { 1, sizeof(mystring)/sizeof(mystring[0]) };
matvar_t *variable = Mat_VarCreate(fieldname, MAT_C_CHAR, MAT_T_UTF8, 2, dim, mystring, 0);
Mat_VarWrite(matfp, variable, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
Mat_VarFree(variable);
```

- Integer

```cpp
char* fieldname = "MyIntegerVariable";
int myinteger = 42;
size_t dim[2] = { 1, 1 };
matvar_t *variable = Mat_VarCreate(fieldname, MAT_C_INT32, MAT_T_INT32, 2, dim, &myinteger, 0);
Mat_VarWrite(matfp, variable, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
Mat_VarFree(variable);
```


- Double

```cpp
char* fieldname = "MyDoubleVariable";
double mydouble = 4.2;
size_t dim[2] = { 1, 1 };
matvar_t *variable = Mat_VarCreate(fieldname, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim, &mydouble, 0);
Mat_VarWrite(matfp, variable, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
Mat_VarFree(variable);
```


- Complex double

```cpp
char* fieldname = "MyComplexDoubleVariable";
double real = 4.2;
double imag = 1.5;
mat_complex_split_t mycomplexdouble = {&real, &imag};
size_t dim[2]={ 1, 1 };
matvar_t *variable = Mat_VarCreate(fieldname, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim, &mycomplexdouble, MAT_F_COMPLEX);
Mat_VarWrite(matfp,variable, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
Mat_VarFree(variable);
```


- Bool

```cpp
char* fieldname = "MyBoolVariable";
bool mybool = true;
size_t dim[2] = { 1, 1 };
matvar_t *variable = Mat_VarCreate(fieldname, MAT_C_INT16, MAT_T_INT16, 2, dim, &mybool, MAT_F_LOGICAL);
Mat_VarWrite(matfp, variable, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
Mat_VarFree(variable);
```

#### Create and save arrays ([nDimensionalArray.cpp](https://github.com/NJannasch/matio-examples/blob/master/Examples/nDimensionalArray.cpp))

- 1-D

```cpp
const int first = 3; //rows
int array1d[first]= { 0 };

// fill 1d array
for (int i = 0; i < first; i++)
	array1d[i] = (i + 1);

// write
char* fieldname1d = "array1d";
size_t dim1d[1] = { first };
matvar_t *variable1d = Mat_VarCreate(fieldname1d, MAT_C_INT32, MAT_T_INT32, 1, dim1d, &array1d, 0); //rank 1
Mat_VarWrite(matfp, variable1d, MAT_COMPRESSION_NONE);
Mat_VarFree(variable1d);

```

- 2-D (Matrix)

```cpp
const int second = 4; //columns
int array2d[first][second] = { 0 };

// fill 2d array
for (int i = 0; i < first; i++)
	for (int j = 0; j < second; j++)
		array2d[i][j] = (i + 1) * (j + 1);

// write
char* fieldname2d = "array2d";
size_t dim2d[2] = { first, second };
matvar_t *variable2d = Mat_VarCreate(fieldname2d, MAT_C_INT32, MAT_T_INT32, 2, dim2d, &array2d, 0); //rank 2
Mat_VarWrite(matfp, variable2d, MAT_COMPRESSION_NONE);
Mat_VarFree(variable2d);
```

- 3-D

```cpp
const int third = 5;
int array3d[first][second][third] = { 0 };

// fill 3d array
for (int i = 0; i < first; i++)
	for (int j = 0; j < second; j++)
		for (int k = 0; k < third; k++)
			array3d[i][j][k] = (i + 1) * (j + 1) * (k + 1);

// write
char* fieldname3d = "array3d";
size_t dim3d[3] = { first, second, third };
matvar_t *variable3d = Mat_VarCreate(fieldname3d, MAT_C_INT32, MAT_T_INT32, 3, dim3d, &array3d, 0); //rank 3
Mat_VarWrite(matfp, variable3d, MAT_COMPRESSION_NONE);
Mat_VarFree(variable3d);
```

- N-D

```cpp
// for N dimensional array create:
int arrayNd[first][second][third][...][N] = { 0 };

// fill Nd array
// ...

// write
char* fieldnameNd = "arrayNd";
size_t dimNd[N] = {first, second, third, ..., N};
matvar_t *variableNd = Mat_VarCreate(fieldnameNd, MAT_C_INT32, MAT_T_INT32, N, dimNd, &arrayNd, 0); //rank N
Mat_VarWrite(matfp, variableNd, MAT_COMPRESSION_NONE);
Mat_VarFree(variableNd);
```

#### Create and save structs ([saveStruct.cpp](https://github.com/NJannasch/matio-examples/blob/master/Examples/saveStruct.cpp))

- 1 x 1 struct

```cpp
//Create a 1 x 1 struct 'Data' with fields: name, unit, value
char *structname = "Data";
const char *fieldnames[3] = { "name","unit","value" };
size_t structdim[2] = { 1, 1 }; // create 1 x 1 struct
//main struct: Data with 3 fields
matvar_t* matstruct = Mat_VarCreateStruct(structname, 2, structdim, fieldnames, 3); 
char* mystring = "Speed";
size_t dim[2] = { 1, 5 }; //string dimension
matvar_t *variable = Mat_VarCreate(fieldnames[0], MAT_C_CHAR, MAT_T_UTF8, 2, dim, mystring, 0);
Mat_VarSetStructFieldByName(matstruct, fieldnames[0], 0, variable); //insert in Data.name
Mat_VarWrite(matfp, matstruct, MAT_COMPRESSION_NONE);
Mat_VarFree(matstruct);
```

- 1 x n struct

```cpp
//Create a 1 x n struct 'Data' with fields: name, unit, value
char *structname = "Data";
const char *fieldnames[3] = { "name","unit","value" };
size_t structdim[2] = { 1, n }; // create 1 x n struct
//main struct: Data with 3 fields
matvar_t* matstruct = Mat_VarCreateStruct(structname, 2, structdim, fieldnames, 3); 
char* mystring = "Speed";
size_t dim[2] = { 1, 5 }; //string dimension
matvar_t *variable = Mat_VarCreate(fieldnames[0], MAT_C_CHAR, MAT_T_UTF8, 2, dim, mystring, 0);
Mat_VarSetStructFieldByName(matstruct, fieldnames[0], p, variable); //insert Data(p).name (1 <= p <= n)
Mat_VarWrite(matfp, matstruct, MAT_COMPRESSION_NONE);
Mat_VarFree(matstruct);
```

- nested struct

```cpp
char *structname = "Test";
const char *fieldnames[1] = { "Data"};
size_t structdim0[2] = { 1, p }; // create 1 x p struct
matvar_t* matstruct0 = Mat_VarCreateStruct(structname, 2, structdim0, fieldnames, 1); //main struct: Test
char* mystring0 = "Data";
const char *Datafieldnames[3] = { "name", "unit", "value" };
size_t structdim1[2] = { 1, 1 };
matvar_t* matstruct1 = Mat_VarCreateStruct(mystring0, 2, structdim1, Datafieldnames, 3);
//Set Test(p).Data (1 <= p <= n)
Mat_VarSetStructFieldByName(matstruct0, fieldnames[0], p, matstruct1);
Mat_VarWrite(matfp, matstruct0, MAT_COMPRESSION_NONE);
Mat_VarFree(matstruct0);
```

----------


> **About matio:**
> 
> matio is an open-source library for reading and writing MATLAB MAT files. 
> 
> Further information on http://sourceforge.net/projects/matio/ or on https://github.com/tbeu/matio
> 
> - For file compression please compile matio with zlib
> [http://zlib.net](http://zlib.net)
> 
> - For file version 7.3 please compile matio with HDF-5
> [https://www.hdfgroup.org/HDF5/release/obtain5.html](https://www.hdfgroup.org/HDF5/release/obtain5.html)
