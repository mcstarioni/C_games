#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
/*
TODO:
1. Initialize DONE
2. Output
3. Selection
4. Opening
5. Reaction
*/
struct Cell
{
    int isCursor;
    int isOpened;
    int isMine;
    int isFlag;
    int minesAround;
};
int mines = 0;
int minesLeft = 0;
//0. set Main
//1. Initialize
void getSize(int *N,int *M);
struct Cell** initializeField(int N,int M);
int minesCount(struct Cell** a,int N,int M,int x, int y);
//2. Output
void printField(struct Cell **a,int N,int M);
//3. Selection
int chooseCell(struct Cell **a,int N,int M);
int openCell(struct Cell** a, int N, int M, int x, int y);
void Free(struct Cell **a,int N);

int main()
{
    system("color 4F");
    int M,N;
    int Answer;
    do
    {
        mines = 0;
        minesLeft = 0;
        system("cls");
        printf("Press : 'Enter' to set your own size\n"
               "        'Space' to choose standard field\n"
               "        'Escape' to exit\n");
        Answer = getch();
        struct Cell **field;
        switch(Answer)
        {
        case(13):
            {
                system("cls");
                getSize(&N,&M);
                break;
            }
        case(32):
            {
                system("cls");
                N = 20;
                M = 40;
                Answer = 32;
                break;
            }
        case(27):
            {
                return 0;
            }
        }
        field = initializeField(N,M);
        while(1)
        {
            if(chooseCell(field,N,M) == -1)
            {
                printf("You have lost.\n");
                break;
            }
            else{
                printf("You have won!!!\n");
                break;
            }
        }
        printf("Do you want to start a new game?\n"
                       "Press 'Enter'  to continue\n"
                       "Press 'Escape' to exit\n");
        Free(field,N);
        Answer = getch();
    }while(Answer != 27);
    return 0;
}
void printField(struct Cell **a,int N,int M)
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

            char cell = (a[i][j].isCursor == 1)?'X':((a[i][j].isFlag == 1)?'F':
                ((a[i][j].isOpened == 0)?'#':
                    ((a[i][j].minesAround == 0)?' ':
                        (a[i][j].minesAround+48))));
            printf("%c",cell);
        }
        printf("|\n");
    }
    for(int i = 0; i < M+2; i++)
    {
        printf("_");
    }
    printf("\nMines left: %d.  Mines total: %d\n",minesLeft,mines);
    printf("Move with - W S A D\n"
           "Open with - ENTER\n"
           "Flag with - F\n");
}
int chooseCell(struct Cell **a,int N,int M)
{
    int Answer;
    int i = N/2;
    int j = M/2;
    a[i][j].isCursor = 1;
    do
    {
        printField(a,N,M);
        Answer = getch();
        switch(Answer)
        {
        case(119):
            {
                a[i][j].isCursor = 0;
                i = ((i--)>0)?(i--):N-1;
                a[i][j].isCursor = 1;
                break;

            }
        case(115):
            {
                a[i][j].isCursor = 0;
                i = ((++i)<N)?(i++):0;
                a[i][j].isCursor = 1;
                break;
            }
        case(97):
            {
                a[i][j].isCursor = 0;
                j = ((j--)>0)?(j--):M-1;
                a[i][j].isCursor = 1;
                break;
            }
        case(100):
            {
                a[i][j].isCursor = 0;
                j = ((++j)< M)?(j++):0;
                a[i][j].isCursor = 1;
                break;
            }
        case(102):
            {
                if(a[i][j].isFlag == 1)
                {
                    a[i][j].isFlag = 0;
                    if(a[i][j].isMine == 1)
                        minesLeft++;
                }else
                {
                    a[i][j].isFlag = 1;
                    if(a[i][j].isMine == 1)
                        minesLeft--;
                }
                if(minesLeft == 0)
                {
                    return 0;
                }
                break;
            }
        case(27):
            {
                break;
            }
        case(13):
            {
                if(a[i][j].isOpened == 0)
                {
                    if(openCell(a,N,M,i,j) == -1)
                    {
                        return -1;
                    }
                }
            }
        default:
            {
                break;
            }
        }
        system("cls");
    }while(Answer != 27);
    return -1;
}
void getSize(int *N,int *M)
{
    printf("Enter the size of the field: \nHeigth: ");
    scanf("%d",N);
    printf("Length: ");
    scanf("%d",M);
}
int openCell(struct Cell** a, int N, int M, int x, int y)
{
    if(a[x][y].isMine == 1)
    {
        return -1;
    }else
    {
        a[x][y].isOpened = 1;
        if(a[x][y].minesAround == 0)
        {
            int i_temp = 0;
            int j_temp = 0;
            for(int i = -1; i < 2; i++)
            {
                if((x+i < 0)||(x+i > N-1))
                {
                    continue;
                }
                i_temp = x+i;
                for(int j = -1; j < 2; j++)
                {
                    if((y+j < 0)||(y+j > M-1))
                    {
                        continue;
                    }
                    j_temp = y+j;
                    if(a[i_temp][j_temp].isOpened == 0)
                    {
                        openCell(a,N,M,i_temp,j_temp);
                    }
                }
            }
        }
    }
    return 0;
}
void Free(struct Cell **a,int N)
{
    for(int i = 0; i < N; i++)
    {
        free(a[i]);
    }
    free(a);
}
struct Cell **initializeField(int N,int M)
{
    struct Cell **a = (struct Cell **)malloc(N*sizeof(struct Cell *));
    if (a == NULL)
    {
        printf("Error\n");
        free(a);
        return NULL;
    }
    for(int i = 0; i < N; i++)
    {
        *(a+i) = (struct Cell *)malloc(M*sizeof(struct Cell));
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
    srand(time(NULL));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            struct Cell *cell = &a[i][j];
            cell->isCursor = 0;
            cell->isOpened = 0;
            cell->isFlag = 0;
            cell->minesAround = 0;
            cell->isMine = 0;
            if(rand()%9 == 0)
            {
                cell->isMine = 1;
                mines++;
            }
        }
    }
    minesLeft = mines;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j].minesAround = minesCount(a,N,M,i,j);
        }
    }
    return a;
}
int minesCount(struct Cell **a,int N, int M,int x,int y)
{
    int Count = 0;
    int i_temp = 0;
    int j_temp = 0;
    for(int i = -1; i < 2; i++)
    {
        if((x+i < 0)||(x+i > N-1))
        {
            continue;
        }
        i_temp = x+i;
        for(int j = -1; j < 2; j++)
        {
            if((y+j < 0)||(y+j > M-1))
            {
                continue;
            }
            j_temp = y+j;
            if(a[i_temp][j_temp].isMine == 1)
            {
                Count++;
            }
        }
    }
    if(a[x][y].isMine == 1)
    {
        return (Count - 1);
    }else
    {
        return Count;
    }
}
