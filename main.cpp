#include <cstdlib>
#include <iostream>
#include "determinant.h"
#include "windows.h"
#include "string.h"
#include "conio.h"

using namespace std;

bool showCalc;

void cmatrix();
void configurations();
void lmatrix();
void showlist();
void delmatrix();
void lmatrixf();

int main()
{
    system("title Matrix");
    showCalc = false;
    char option;
    while(true)
    {
        system("cls");
        cout << "+---+---+---+---+---+---+---+---+---+---+---+---+---+\n";
        cout << "|           Calculadora de Determinantes            |\n";
        cout << "|                  Versao 2.0.2.0                   |\n";
        cout << "+/_\\_/_\\_/_\\_/_\\_/_\\_/_\\_/_\\_/_\\_/_\\_/_\\_/_\\_/_\\_/_\\+\n";
        cout << "|Escolha uma opcao:                                 |\n";
        cout << "|A)Calcular determinante                            +\n";
        cout << "|B)Carregar matriz                                  |\n";
        cout << "|C)Carregar matriz de grandes dimensoes             +\n";
        cout << "|D)Listar matrizes                                  |\n";
        cout << "|E)Deletar matriz                                   +\n";
        cout << "|F)Configuracoes                                    |\n";
        cout << "|G)Ajuda                                            +\n";
        cout << "|H)Sair                                             |\n";
        cout << "+---+---+---+---+---+---+---+---+---+---+---+---+---+\n\n";
        while(true)
        {
            option = getch();
            if(option=='a')
            {
                cout << "Calcular Determinante\n";
                cmatrix();
                break;
            }
            else if(option=='b')
            {
                lmatrix();
                break;
            }
            else if(option=='c')
            {
                lmatrixf();
                break;
            }
            else if(option=='d')
            {
                showlist();
                break;
            }
            else if(option=='e')
            {
                delmatrix();
                break;
            }
            else if(option=='f')
            {
                configurations();
                break;
            }
            else if(option=='g')
            {
                if(Help()==false)
                    cout << "Nao existem arquivos de ajuda.";
                cout << "\n\n...";
                getch();
                break;
            }
            else if(option=='h')
            {
                exit(0);
                return 0;
            }
        }
    }
    return 0;
}

void configurations()
{
    char get;
    while(true)
    {
        system("cls");
        cout << "Configuracoes\n\n";
        cout << "A)Mostrar calculos: ";
        if(showCalc == true)
        {
            cout << "Sim";
        }
        else
        {
            cout << "Nao";
        }
        cout << "\nb)Sair";
        get = getch();
        if(get == 'b')
        {
            break;
        }
        if(get == 'a')
        {
            if(showCalc==true)
            {
                showCalc=false;
            }
            else
            {
                showCalc=true;
            }
        }
    }
}

void cmatrix()
{
    char get;
    short int tmq; //Tamanho da matriz quadrada
    char mn[10]; //Nome da matriz
    cout << "Digite o tamanho da matriz quadrada: ";
    cin >> tmq;

    while(tmq<1)
    {
        cout << "Este tamanho nao e valido.\n";
        cout << "Digite outro tamanho maior que 0: ";
        cin >> tmq;
    }

    double **matrix = new double*[tmq];

        for(int counter=0; counter<tmq; counter++) //Cria a matriz com alocação dinâmica.
            matrix[counter] = new double[tmq];

    cout << "Agora digite a matriz, linha por linha:\n";

    int c1 = 0, c2 = 0;
    while(c1<tmq)
    {
           c2=0;
           while(c2<tmq)
           {
                 if(c2==0)
                 cout << "linha " << c1+1 << "| ";

                 cin >> matrix[c1][c2];
                 c2++;
           }
           c1++;
    }

    double result;

    result = LaPlace(&*matrix, tmq, true, showCalc);

    cout << "/---------------------------------------------------\\\n";
    cout << "A determinante da matriz " << tmq << "x" << tmq << " de " << sizeof(double)*tmq*tmq << " bytes e " << result << ".\n";
    cout << "\\---------------------------------------------------/\n";
    cout << "Deseja salvar a matriz (s/n)?\n";

    while(get!='n' || get != 's')
    {
         get = getch(); //Inapropriado
         if(get == 'n')
         {
                break;
         }
         if(get == 's')
         {
                cout << "Digite o nome da matriz (apenas como referencia)\n";
                cout << "(Maximo de 10 caracteres): ";
                cin.getline(mn, 10); //Algum tipo de bug no C++, faz com que cin.getline pule para o break antes do usuário digitar os dados.
                cin.getline(mn, 10); //A solução que encontrei foi 2 cin.getline seguidos. OBS: O mesmo acontece com fgets.
                while(strcmp(mn, "") == 0)
                {
                    cout << "Voce deve digitar um nome: ";
                    cin.getline(mn, 10);
                }
                break;
         }
    }

    if(SaveMatrix(&*matrix, tmq, mn, result)==true && get == 's')
        cout << "Matriz salva com sucesso!\n";
    else if(get == 's')
        cout << "Nao foi possivel salvar a matriz.\n";

    delete[]matrix; //Deleta a matriz.

    cout << "\n...";

    getch();
}

void lmatrix()
{
    char matrixname[10];
    bool result;
    cout << "Digite o nome da matriz a ser carregada: ";
    cin.getline(matrixname, 10);
    result = LoadMatrix(matrixname);
    if(result == false)
        cout << "Essa matriz nao existe.\n";
    cout << "\n...";

    getch();
}

void showlist()
{
    bool value;
    value = ListMatrix();
    if(value==false)
        cout << "Nao ha nenhuma matriz salva no momento.\n";
    cout << "\n...";

    getch();
}

void delmatrix()
{
    bool result;
    char matrix[10];
    cout << "Digite o nome da matriz a ser deletada: ";
    cin.getline(matrix, 10);
    result = DeleteMatrix(matrix);
    if(result==true)
        cout << "A matriz foi deletada com sucesso !\n";
    else
        cout << "Essa matriz nao existe.\n";
    cout << "\n...";

    getch();
}

void lmatrixf()
{
    char get;
    char name[15];
    cout << "Para carregar uma matriz de dimensoes maiores,\n";
    cout << "e necessario que voce configure um arquivo.txt\n";
    cout << "corretamente. Se necessario, o programa criara\n";
    cout << "o arquivo pre-configurado.\n\n";
    cout << "Deseja que o programa crie o arquivo pre-configurado (s/n)?\n\n";
    while(get!='n' || get != 's')
    {
        get = getch();
        if(get == 'n')
        {
            break;
        }
        if(get == 's')
        {
            FILE *pFile;
            cout << "Digite o nome da matriz sem sua extensao (.txt)\n";
            cout << "Max 10 digitos: ";
            cin.getline(name, 10);
            while(strcmp(name, "") == 0)
            {
                cout << "Voce deve digitar um nome: ";
                cin.getline(name, 10);
            }

            strcat(name, ".txt");

            while(CheckExistence(name)==true)
            {
                cout << "Um arquivo com esse nome ja existe salvo, deseja sobrescreve-lo?\n[S]im [N]ao [C]ancelar\n";
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
                        cin.getline(name, 10);
                        strcat(name, ".txt");
                        break;
                    }
                    if(get == 'c')
                    {
                        cout << "\n...";
                        getch();
                        return;
                    }
                }
                if(get == 's')
                {
                    break;
                }
            }
            pFile = fopen(name, "wt");
            fputs("size = Tamanho da matriz\nmatrix{\nDigite aqui a matriz, linha por linha\n}", pFile);
            fclose(pFile);
            cout << "O arquivo foi criado com sucesso!\n";
            cout << "\n...";
            getch();
            return;
        }
    }

    double check;
    cout << "Digite o nome da matriz a ser carregada\n";
    cout << "Max 10 digitos: ";
    cin.getline(name, 10);
    check = LoadFrom(name);

    if(check==FILE_FALSE)
    {
        cout << "O arquivo nao existe !\n";
        cout << "Nao foi possivel carregar a matriz.\n";
    }
    else if(check==WRONG_SIZE)
    {
        cout << "O tamanho da matriz e invalido.\n";
        cout << "Consulte o manual de instrucoes para saber mais.\n";
    }
    cout << "\n...";
    getch();
}
