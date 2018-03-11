/*Arquivo determinant.cpp, contém as definições das funções necessárias
  Programado por: Aleksander Luiz Lada Arruda
  Este código é open-source, e a modificação do mesmo é livre, desde que
  se preserve o nome do programador.*/

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "math.h"
#include "determinant.h"
#include "windows.h"
#include "string.h"
#include "conio.h"

using namespace std;

void PrintMatrix(double **getmatrix, short int matrixsize)
{
     int c1 = 0, c2 = 0;
     while(c1<matrixsize)
     {
           c2=0;
           while(c2<matrixsize)
           {
                 if(c2==0)
                 cout << "\nLinha " << c1+1 << "| ";

                 cout << getmatrix[c1][c2] << " ";
                 c2++;
           }
           c1++;
     }
}

void TestResult(int result)
{
     if(result == EOF)
     {
               cout << "Erro na gravacao.\n";
     }
}

bool CheckExistence(char *filename)
{
    FILE *archive;
    if(archive = fopen(filename, "r"))
    {
        fclose(archive);
        return true;
    }
    return false;
}

bool SaveMatrix(double **mtos, short int matrixsize, char *matrixname, double matrixdeterminant)
{
    int counterl = 0, counterc = 0, result;
    char name[16];
    char get;
    FILE *matrix;
    FILE *determin;
    strcpy(name, matrixname);
    strcat(name, ".dat");

    while(CheckExistence(name)==true)
    {
        cout << "Uma matriz com esse nome ja existe salva, deseja sobrescreve-la?\n[S]im [N]ao [C]ancelar\n";
        while(true)
        {
            get = getch();
            if(get == 's')
            {
                    break;
            }
            if(get == 'n')
            {
                cout << "Digite outro nome para a matriz: ";
                cin.getline(matrixname, 11);
                strcpy(name, matrixname);
                strcat(name, ".dat");
                break;
            }
            if(get == 'c')
            {
                return false;
                break;
            }
        }
        if(get == 's')
        break;
    }

    matrix = fopen(name, "wt");
    determin = fopen("determinant.dat", "a");

    if(matrix == NULL)
        return false;
    if(determin == NULL)
        return false;

    fprintf(matrix, "%d\n", matrixsize);
    while(true)
    {
               result = fprintf(matrix, "%g ", mtos[counterl][counterc]);
               TestResult(result);
               counterc++;
               if(counterc == matrixsize)
               {
                           counterc = 0;
                           result = fprintf(matrix, "\n");
                           TestResult(result);
                           counterl++;
                           if(counterl == matrixsize)
                           {
                                       break;
                           }
               }
    }
    result = fprintf(matrix, "%g\n", matrixdeterminant);
    TestResult(result);
    result = fprintf(determin, "%s\n", matrixname);
    TestResult(result);
    fclose(matrix);
    fclose(determin);
    return true;
 }

bool LoadMatrix(char *matrixname)
{
    FILE *matrix;
    char name[16];
    char line[1000];
    int counter;
    short int matrixsize;
    counter = 0;
    strcpy(name, matrixname);
    strcat(name, ".dat");
    if(CheckExistence(name)==true)
    {
        matrix = fopen(name, "rt");
        fscanf(matrix, "%d", &matrixsize);
        if(matrixsize<=15)
        {
            cout << "Matriz " << matrixsize << "x" << matrixsize;
            while(counter<=matrixsize)
            {
                fgets(line, 1000, matrix);
                cout << line;
                counter++;
            }
            fgets(line, 1000, matrix);
            cout << line;
            fclose(matrix);
            return true;
        }
        else
        {
            cout << "O tamanho da matriz e superior a 15x15.\n";
            fclose(matrix);
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool ListMatrix()
{
    bool check;
    char cmp[10];
    char archive[10];
    int counter = 0;
    check = CheckExistence("determinant.dat");
    if(check==false)
        return false;
    FILE *list;
    list = fopen("determinant.dat", "rt");
    while(!feof(list))
    {
        strcpy(cmp, archive);
        fgets(archive, 10, list);
        if(strcmp(cmp, archive) != 0)
            cout << archive;
        counter++;
    }
    fclose(list);
    if(counter<=1)
        return false;
    return true;
}

bool DeleteMatrix(char *matrixname)
{
    char filename[15];
    char dtor[10];
    char check[10];

    FILE *determin;
    FILE *temp;
    determin = fopen("determinant.dat", "rt");
    temp = tmpfile();

    strcpy(filename, matrixname);
    strcat(filename, ".dat");
    if(CheckExistence(filename)==false)
        return false;
    remove(filename);

    while(!feof(determin))
    {
        strcpy(check, dtor);
        fscanf(determin, "%s", dtor);
        if(strcmp(check, dtor) != 0) //ANTI-BUG
            fprintf(temp, "%s\n", dtor);
    }

    fclose(determin);
    remove("determinant.dat");

    determin = fopen("determinant.dat", "wt");
    fseek(temp, 0, SEEK_SET);

    while(!feof(temp))
    {
        strcpy(check, dtor);
        fscanf(temp, "%s", dtor);
        if(strcmp(check, dtor) != 0 && strcmp(dtor, matrixname) != 0)
            fprintf(determin, "%s\n", dtor);
    }

    fclose(temp);
    fclose(determin);
    return true;
}

bool Help()
{
       bool check;
       check = CheckExistence("help.bin");
       if(check==false)
           return false;
       char str[100];
       FILE *pHelp;
       pHelp = fopen("help.bin", "r");
       while(!feof(pHelp))
       {
           fgets(str, 100, pHelp);
           cout << str;
       }
       return true;
}

double LaPlace(double **getmatrix, short int matrixsize, bool isMain, bool showCalcs)
{
    //Para matriz 1x1, o próprio elemento é a determinante.
    if(matrixsize==1)
    {
        return getmatrix[0][0];
    }
    //Para matriz 2x2, retorna-se a determinante.
    if(matrixsize==2)
    {
        if(showCalcs==true)
        {
            cout << "\nMatriz 2x2:";
            PrintMatrix(&*getmatrix, matrixsize);
        }

        double determin = getmatrix[0][0]*getmatrix[1][1] - getmatrix[0][1]*getmatrix[1][0];
        if(showCalcs==true)
        {
            cout << "de determinante igual a " << determin << ".\n";
            getch();
        }

        return determin;
    }
    /*PARA MATRIZES ACIMA DE 2x2*/
    //É criada uma matriz menor para transcrevê-la, seguindo o Teorema de Laplace.
    short int sendsize;
    sendsize = matrixsize-1;
    double **sendmatrix = new double*[sendsize];
    for(int counter=0; counter<sendsize; counter++)
        sendmatrix[counter] = new double[sendsize];

    //Elemento analisado, Linha do elemento, Coluna do elemento
    int exElement = 0, elementLine, elementColumn, scannedLine, scannedColumn;
    double det; //Determinante
    double result = 0; //Resultado final, incluindo o Co-Fator

    if(showCalcs==true)
    {
        cout << "+--------------------------------------------------+\n";
        cout << "Matriz " << matrixsize << "x" << matrixsize << ":\n";
        PrintMatrix(&*getmatrix, matrixsize);
    }

    if(showCalcs==true)
    {
        if(isMain==true)
                cout << "\n\nAnalisando a matriz principal...\n";
            else
                cout << "\n\nAnalisando a matriz derivada...\n";

        cout << "Criadas " << matrixsize << " matrizes " << sendsize << "x" << sendsize << ":\n";
        getch();
    }

    while(exElement<matrixsize) //Enquanto não examinar todos os elementos da matriz
    {
        elementLine = 1;
        elementColumn = 0;
        scannedLine = 0;
        scannedColumn = 0;

        while(elementLine<matrixsize) //Enquanto não examinar todas as linhas da matriz
        {
            scannedColumn = 0;
            elementColumn = 0;
            while(elementColumn<matrixsize) //Enquanto não examinar todas as colunas da matriz
            {
                if(elementColumn==exElement)
                {
                    elementColumn++;
                }
                if(elementColumn==matrixsize)
                {
                    break;
                }
                sendmatrix[scannedLine][scannedColumn] = getmatrix[elementLine][elementColumn]; //Transcreve a matriz
                scannedColumn++;
                elementColumn++;
            }
            scannedLine++;
            elementLine++;
        }

        //Envia a matriz para a função determinant e calcula o CoFator.
        det = getmatrix[0][exElement]*pow(-1, exElement+2)*LaPlace(&*sendmatrix, sendsize, false, showCalcs);
        result+=det; //Soma o CoFator do elemento a result.
        exElement++;
    }

    if(showCalcs==true)
    {
        cout << "\nFim dos calculos da matriz " << matrixsize << "x" << matrixsize << ".\n";
        cout << "Calculando CoFator; Calculando determinante;\n";
        if(isMain==false)
        {
            cout << "Retornando determinante " << result << " para a matriz de derivacao " << matrixsize+1 << "x" << matrixsize+1 << ".\n";
            getch();
        }
        else
        {
            cout << "Retornando determinante final.\n";
        }
    }
    return result; //Retorna o resultado.
}

double LoadFrom(char *matrixfile)
{
    bool check;
    char get;
    char file[15];
    strcpy(file, matrixfile);
    strcat(file, ".txt");
    check = CheckExistence(file);

    if(check==false) //Verifica se o arquivo existe.
        return FILE_FALSE;

    FILE *pMatrix;
    short int matrixsize = 0;
    pMatrix = fopen(file, "rt");
    fscanf(pMatrix, "%*s%*s%d", &matrixsize); //Recebe o tamanho da matriz.

    if(matrixsize<=0)
        return WRONG_SIZE;

    cout << "Calculando a determinante da matriz...\n";

    double **fmatrix = new double*[matrixsize];

        for(int counter=0; counter<matrixsize; counter++) //Cria a matriz com alocação dinâmica.
            fmatrix[counter] = new double[matrixsize];

    /*Comentário do programador:
    Porque cria a matriz com alocação dinâmica, sendo que se tem o valor do tamanho da matriz desejada?
    Pelo fato de que uma matriz bidimensional criada com alocação dinâmica, é um ponteiro que aponta para outro,
    e uma matriz criada sem alocação dinâmica, é um array bidimensional.
    A função determinant só recebe endereços de memória, e não matrizes inteiras.*/

    int counterl = 0, counterc;
    float holder; //fscanf() só lê float, não double. Nesse caso, não podemos usar a matriz double como argumento da fscanf, pois haverá um erro na conversão das variáveis.
    fscanf(pMatrix, "%*s");
    while(counterl<matrixsize)
    {
           counterc=0;
           while(counterc<matrixsize)
           {

                 fscanf(pMatrix, "%f", &holder);
                 fmatrix[counterl][counterc]=holder;
                 counterc++;
           }
           counterl++;
    }

    double result;
    result = LaPlace(&*fmatrix, matrixsize, true, false);
    cout.precision(4);
    cout <<  "Matriz " << matrixsize << "x" << matrixsize << " de determinante " << result << " carregada !\n";

    if(matrixsize<=15)
    {
        cout << "Deseja imprimir a matriz (s/n)?\n";

        while(get!='n' || get != 's')
        {
            get = getch();
            if(get == 'n')
            {
                break;
            }
            if(get == 's')
            {
                PrintMatrix(&*fmatrix, matrixsize);
                break;
            }
        }
    }

    cout << "\nDeseja salvar a matriz (s/n)?\n";

    while(get!='n' || get != 's')
    {
        get = getch();
        if(get == 'n')
        {
            break;
        }
        if(get == 's')
        {
            if(SaveMatrix(&*fmatrix, matrixsize, matrixfile, result)==true)
                cout << "Matriz salva com sucesso!\n";
            else
                cout << "Nao foi possivel salvar a matriz.\n";
            break;
        }
    }


    delete [] fmatrix;
    fclose(pMatrix);
    return 0;
}
