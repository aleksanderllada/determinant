/*Arquivo determinant.h, contém as declarações das funções necessárias
  Programado por: Aleksander Luiz Lada Arruda                         */

#define     FILE_FALSE      -23.5943
#define     WRONG_SIZE     -93.2348

void PrintMatrix(double **getmatrix, short int matrixsize);
void TestResult(int result);
bool CheckExistence(char *filename);
bool SaveMatrix(double **mtos, short int matrixsize, char *matrixname, double matrixdeterminant);
bool LoadMatrix(char *matrixname);
bool ListMatrix();
bool DeleteMatrix(char *matrixname);
bool Help();
double LaPlace(double **getmatrix, short int matrixsize, bool isMain, bool showCalcs);
double LoadFrom(char *matrixfile);
