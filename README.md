# Examples for MAT File I/O Library (MATIO)


###Basics

####Header
```cpp
#include <matio.h>
```

####Create MAT file

```cpp
const char *filename = "myfile.mat";
mat_t *matfp = NULL; //matfp contains pointer to MAT file or NULL on failure
matfp = Mat_CreateVer(FILENAME,NULL,MAT_FT_MAT5); //or MAT_FT_MAT4 / MAT_FT_MAT73
//dont forget to close file with Mat_Close(matfp);
```

####Create and save variables ([saveVariable.cpp](https://github.com/NJannasch/matio-examples/blob/master/Examples/saveVariable.cpp))

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


####Create and save structs ([saveStruct.cpp](https://github.com/NJannasch/matio-examples/blob/master/Examples/saveStruct.cpp))

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
Mat_VarFree(variable);
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
Mat_VarFree(variable);
Mat_VarWrite(matfp, matstruct, MAT_COMPRESSION_NONE);
Mat_VarFree(matstruct);
```


----------


> **About matio:**
> 
> matio is an open-source library for reading and writing MATLAB MAT files. 
> 
> Further information on http://sourceforge.net/projects/matio/ or on its fork https://github.com/tbeu/matio
> 
> - For file compression please compile matio with zlib
> [http://zlib.net](http://zlib.net)
> 
> - For file version 7.3 please compile matio with HDF-5
> [https://www.hdfgroup.org/HDF5/release/obtain5.html](https://www.hdfgroup.org/HDF5/release/obtain5.html)

----------
