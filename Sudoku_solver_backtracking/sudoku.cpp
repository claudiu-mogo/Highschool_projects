#include <fstream>
using namespace std;
ifstream fin("sudoku.in");
ofstream fout("sudoku.out");
int mat[10][10],i,j,st[3][81],k=0,n,v[81];
float q;

void citire()
{
    for(i=1;i<=9;i++)
   {
       for(j=1;j<=9;j++)
        {
            fin>>mat[i][j];
            if(mat[i][j]==0)
            {
                st[1][++k]=i;
                st[2][k]=j;
            }
        }
   }
   n=k;
}

int Solutie(int k)
{
    if(k==n)
        return 1;
    else
        return 0;
}

int OK(int k)
{
    for(i=1;i<=9;i++)
    {
        if(mat[i][st[2][k]]==mat[st[1][k]][st[2][k]]&&(i!=st[1][k]))
            return 0;
    }
    for(j=1;j<=9;j++)
    {
        if(mat[st[1][k]][j]==mat[st[1][k]][st[2][k]]&&(j!=st[2][k]))
            return 0;
    }

    if(st[1][k]>=1&&st[1][k]<=3&&st[2][k]>=1&&st[2][k]<=3)
    {
        for(i=1;i<=3;i++)
            for(j=1;j<=3;j++)
                if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;
    }
    else
        if(st[1][k]>=1&&st[1][k]<=3&&st[2][k]>=4&&st[2][k]<=6)
        {for(i=1;i<=3;i++)
            for(j=4;j<=6;j++)
              if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                return 0;}
      else
        if(st[1][k]>=1&&st[1][k]<=3&&st[2][k]>=7&&st[2][k]<=9)
            {for(i=1;i<=3;i++)
                for(j=7;j<=9;j++)
                  if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;}
       else
         if(st[1][k]>=4&&st[1][k]<=6&&st[2][k]>=1&&st[2][k]<=3)
            {for(i=4;i<=6;i++)
                for(j=1;j<=3;j++)
                  if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;}
      else
        if(st[1][k]>=4&&st[1][k]<=6&&st[2][k]>=4&&st[2][k]<=6)
            {for(i=4;i<=6;i++)
                for(j=4;j<=6;j++)
                  if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;}
        else
          if(st[1][k]>=4&&st[1][k]<=6&&st[2][k]>=7&&st[2][k]<=9)
            {for(i=4;i<=6;i++)
                for(j=7;j<=9;j++)
                  if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;}
        else
         if(st[1][k]>=7&&st[1][k]<=9&&st[2][k]>=1&&st[2][k]<=3)
            {for(i=7;i<=9;i++)
                for(j=1;j<=3;j++)
                  if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;}
        else
         if(st[1][k]>=7&&st[1][k]<=9&&st[2][k]>=4&&st[2][k]<=6)
            {for(i=7;i<=9;i++)
                for(j=4;j<=6;j++)
                  if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;}
          else
           if(st[1][k]>=7&&st[1][k]<=9&&st[2][k]>=7&&st[2][k]<=9)
            {for(i=7;i<=9;i++)
                for(j=7;j<=9;j++)
                  if(mat[st[1][k]][st[2][k]]==mat[i][j]&&(i!=st[1][k]||j!=st[2][k]))
                    return 0;}
    return 1;
}

void Afisare()
{
    for(i=1;i<=9;i++)
    {
        for(j=1;j<=9;j++)
        {
            fout<<mat[i][j]<<" ";
        }
        fout<<'\n';
    }
}

void Back(int k)
{
    for(int i=1;i<=9;i++)
    {
        mat[st[1][k]][st[2][k]]=i;
        if(OK(k))
        {
            if(Solutie(k))
                Afisare();
            else
                Back(k+1);
        }
        mat[st[1][k]][st[2][k]]=0;
    }
}

int main()
{
    citire();
    Back(1);
    return 0;
}
