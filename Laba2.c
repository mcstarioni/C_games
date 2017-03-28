//-std=c99
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <math.h>

void getSize(int *N,int *M);
int **Field_Initialize(int N,int M);
int **getField(int N,int M);
int **getUserField(int N,int M);
int **getStandardField(int N,int M);
void Field_Output(int **a,int N,int M);
int **Life(int **a,int N, int M);
int Life_Count(int **a,int N, int M,int x,int y);
void **Random(int **a,int N,int M);
void **Glider(int **a,int N,int M);
void **Moat(int **a,int N,int M);
void **Star(int **a,int N,int M);
void **Spaceship(int **a,int N,int M);
void Free(int **a,int N);



int main()
{
    system("color 4F");
    int M,N;
    int Answer;
    do
    {
        system("cls");
        printf("Press : 'Enter' to set your own field\n"
               "        'Space' to choose one of standard variants\n"
               "        'Escape' to exit\n");
        Answer = getch();
        int **Field;
        switch(Answer)
        {
        case(13):
            {
                system("cls");
                getSize(&N,&M);
                Field = getUserField(N,M);
                break;
            }
        case(32):
            {
                system("cls");
                N = 20;
                M = 40;
                Field = getStandardField(N,M);
                Answer = 32;
                break;
            }
        default:
            {
            }
        }
        if(Answer == 27)
        {
            break;
        }
        do
        {
            switch(Answer)
            {
            case(13):
                {
                    system("cls");
                    Field_Output(Field,N,M);
                    Field = Life(Field,N,M);
                    Field_Output(Field,N,M);
                    printf("Press : 'Enter' to see the next move\n"
                           "        'Space' to start/stop automatic mode\n"
                           "        'Backspace' for new field\n"
                           "        'Escape' to exit" );
                    break;
                }
            case(32):
                {
                    while(1)
                    {
                        system("cls");
                        printf("Press 'Space' to start/stop\n");
                        Field = Life(Field,N,M);
                        Field_Output(Field,N,M);
                        usleep(40000);
                        if((kbhit() == 1)&&(getch() == 32))
                        {
                            printf("Press : 'Enter' to see the next move\n"
                                   "        'Space' to start/stop automatic mode\n"
                                   "        'Backspace' for new field\n"
                                   "        'Escape' to exit" );
                            break;
                        }
                    }
                }
                default:
                {
                }
            }
            Answer = getch();
        }while((Answer != 27)&&(Answer != 8));
        Free(Field,N);
    }while(Answer == 8);

    return 0;
}
int Life_Count(int **a,int N, int M,int x,int y)
{
    int Count = 0;
    int i_temp = 0;
    int j_temp = 0;
    for(int i = -1; i < 2; i++)
    {
        i_temp = (x+i < 0)?(N-1):((x+i > N-1)?0:(x+i));
        for(int j = -1; j < 2; j++)
        {
            j_temp = (y+j < 0)?(M-1):((y+j > M-1)?0:(y+j));
            if(*(*(a + i_temp)+ j_temp) == 1)
            {
                Count++;
            }
        }
    }
    if(*(*(a+x)+y) == 1)
    {
        return (Count - 1);
    }else
    {
        return Count;
    }
}
int **Life(int **a, int N, int M)
{
    int **b = Field_Initialize(N,M);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            int count = Life_Count(a,N,M,i,j);
            if(*(*(a+i)+j) == 0)
            {
                if(count == 3)
                {
                    *(*(b+i)+j) = 1;
                }else
                {
                    *(*(b+i)+j) = 0;
                }
            }else
            {
                if((count < 2)||(count > 3))
                {
                    *(*(b+i)+j) = 0;
                }else
                {
                    *(*(b+i)+j) = 1;
                }
            }
        }
    }
    return b;
}
void Field_Output(int **a,int N,int M)
{
    for(int i = 0; i < M+2; i++)
    {
        printf("_");
    }
    printf("\n");
    for(int i = 0; i < N; i++)
    {
        printf("|");
        for(int j = 0; j < M; j++)
        {
            if(*(*(a+i)+j) == 0)
            {
                printf(" ");
            }else
            {
                if(a[i][j] == 3)
                {
                    printf("X");
                }else
                {
                    printf("#");
                }
            }
        }
        printf("|\n");
    }
    for(int i = 0; i < M+2; i++)
    {
        printf("_");
    }
    printf("\n");
}
int **getField(int N,int M)
{
    int  **a = Field_Initialize(N,M);
    int Temp = 0;
    printf("Enter your field: \n"
           " - Anykey for 'Life'\n"
           " - Space for 'no Life'\n");
    for(int i = 0; i < N; i++)
    {
        if(i < 9)
        {
            printf(" %d. |",i+1);
        }else
        {
            printf(" %d.|",i+1);
        }
        for(int j = 0; j < M; j++)
        {
            Temp = getch();
            if(Temp == 32)
            {
                *(*(a+i)+j) = 0;
                printf("_");
            }else
            {
                *(*(a+i)+j) = 1;
                printf("#");
            }

        }
        printf("|\n");
    }
    return a;
}
int **getUserField(int N,int M)
{
    int  **a = Field_Initialize(N,M);
    int Temp = 0;
    int Answer;
    printf("Enter your field: \n"
           " - Any key for 'Life'\n"
           " - Space for 'no Life'\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j] = 0;
        }
    }
    int i = N/2;
    int j = M/2;
    a[i][j] = 3;
    do
    {
        Field_Output(a,N,M);
        Answer = getch();
        switch(Answer)
        {
        case(119):
            {
                a[i][j] = Temp;
                i = ((i--)>0)?(i--):N-1;
                Temp = a[i][j];
                a[i][j] = 3;
                break;

            }
        case(115):
            {
                a[i][j] = Temp;
                i = ((++i)<N)?(i++):0;
                Temp = a[i][j];
                a[i][j] = 3;
                break;
            }
        case(97):
            {
                a[i][j] = Temp;
                j = ((j--)>0)?(j--):M-1;
                Temp = a[i][j];
                a[i][j] = 3;
                break;
            }
        case(100):
            {
                a[i][j] = Temp;
                j = ((++j)< M)?(j++):0;
                Temp = a[i][j];
                a[i][j] = 3;
                break;
            }
        case(13):
            {
                break;
            }
        case(32):
            {
                a[i][j] = 0;
                j = ((++j)< M)?(j++):0;
                Temp = a[i][j];
                a[i][j] = 3;
                break;

            }
        default:
            {
                a[i][j] = 1;
                j = ((++j)< M)?(j++):0;
                Temp = a[i][j];
                a[i][j] = 3;
                break;
            }
        }
        system("cls");
    }while(Answer != 13);
    return a;
}

int **getStandardField(int N,int M)
{
    int **a = Field_Initialize(N,M);
    int Answer;
    printf("Press : '1' - random field\n"
           "        '2' - Glider \n"
           "        '3' - Moat\n"
           "        '4' - Star\n"
           "        '5' - Spaceship");
    do
    {
        Answer = getch();
    }while((Answer > 53)||(Answer < 49));
    switch(Answer)
    {
    case(49):
        {
            Random(a,N,M);
            break;
        }
    case(50):
        {
            Glider(a,N,M);
            break;
        }
    case(51):
        {
            Moat(a,N,M);
            break;
        }
    case(52):
        {
            Star(a,N,M);
            break;
        }
    case(53):
        {
            Spaceship(a,N,M);
            break;
        }
    default:
        {
        }
    }
    return a;
}
int **Field_Initialize(int N,int M)
{
    int **a = (int **)malloc(N*sizeof(int *));
    if (a == NULL)
    {
        printf("Error\n");
        free(a);
        return NULL;
    }
    for(int i = 0; i < N; i++)
    {
        *(a+i) = (int *)malloc(M*sizeof(int));
        if (*(a+i) == NULL)
        {
            printf("Error\n");
            for(int k = 0; k <= i; k++)
            {
                free(*(a+k));
            }
            free(a);
            break;
        }
    }
    return a;
}
void getSize(int *N,int *M)
{
    printf("Enter the size of the field: \nHeigth: ");
    scanf("%d",N);
    printf("Length: ");
    scanf("%d",M);
}
void **Random(int **a,int N,int M)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j] = rand()%2;
        }
    }
}
void **Glider(int **a,int N,int M)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j] = 0;
        }
    }
    a[0][1] = 1;
    a[1][2] = 1;
    a[2][0] = 1;
    a[2][1] = 1;
    a[2][2] = 1;
}
void **Moat(int **a,int N,int M)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j] = 0;
        }
    }
    for(int i = 6; i < 15; i++)
    {
        a[i][20] = 1;
    }
    for(int j = 15; j < 26; j++)
    {
        a[10][j] = 1;
    }
    a[10][20] = 0;
    a[8][16] = 1;
    a[8][17] = 1;
    a[8][18] = 1;
    a[7][18] = 1;
    a[8][22] = 1;
    a[7][22] = 1;
    a[8][23] = 1;
    a[8][24] = 1;
    a[12][16] = 1;
    a[12][17] = 1;
    a[12][18] = 1;
    a[13][18] = 1;
    a[12][22] = 1;
    a[13][22] = 1;
    a[12][23] = 1;
    a[12][24] = 1;
    a[5][19] = 1;
    a[5][21] = 1;
    a[6][17] = 1;
    a[6][23] = 1;
    a[15][19] = 1;
    a[15][21] = 1;
    a[14][17] = 1;
    a[14][23] = 1;

}
void **Star(int **a,int N,int M)
{
     for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j] = 0;
        }
    }
    for(int i = 7; i < 14; i++)
    {
        a[i][17] = 1;
    }
    for(int i = 7; i < 14; i++)
    {
        a[i][23] = 1;
    }
    for(int j = 18; j < 23; j++)
    {
        a[7][j] = 1;
    }
    for(int j = 18; j < 23; j++)
    {
        a[13][j] = 1;
    }
    a[7][20] = 0;
    a[10][17] = 0;
    a[13][20] = 0;
    a[10][23] = 0;
    a[9][16] = 1;
    a[10][16] = 1;      a[10][15] = 1;
    a[11][16] = 1;
    a[9][24] = 1;
    a[10][24] = 1;      a[10][25] = 1;
    a[11][24] = 1;
    a[6][19] = 1;
    a[6][20] = 1;       a[5][20] = 1;
    a[6][21] = 1;
    a[14][19] = 1;
    a[14][20] = 1;      a[15][20] = 1;
    a[14][21] = 1;



}
void **Spaceship(int **a,int N,int M)
{
     for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j] = 0;
        }
    }
     for(int i = 5; i < 8; i++)
    {
        for(int j = 20; j < 26; j++)
        {
            a[i][j] = 1;
        }
    }
    a[7][20] = 0;
    a[7][25] = 0;
    a[5][24] = 0;
    a[5][26] = 1;
    a[4][24] = 1;
    a[4][25] = 1;

}
void Free(int **a,int N)
{
    for(int i = 0; i < N; i++)
    {
        free(a[i]);
    }
    free(a);
}

