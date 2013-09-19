#include<stdio.h>
#include<math.h>
int n;
int sudoku(int ar[][n*n],int row,int col)
{   int x,a[n*n],i,check1;
    for(i=0;i<n*n;i++)
    {a[i]=i+1;}
    if(ar[row][col]!=0)
    {                //  printf("next fill before %d %d,,,%d\n",row,col,x);
                       x=next(ar,row,col);
                       //printf("next fill after %d %d,,%d\n",row,col,x);
                       return x;}
    else
    {  int flag=0;
        check1=check(ar,a,row,col);
        if(check1!=0)
        {
          for(i=0;i<n*n;i++)
          { 
            if(a[i]==0)
            continue;
            ar[row][col]=a[i];
         //   printf("next before case %d %d %d\n",row,col,a[i]);
            x=next(ar,row,col);
         //   printf("next after x and case %d %d,,%d,,%d\n",row,col,x,a[i]);
            if(x==1)
            {flag=1;return 1;}
          } 
        }
        if(flag==0)
        {ar[row][col]=0;
        return 0;}   
    }
}
int next(int ar[][n*n],int row,int col)
{   int x;
    if(col<=(n*n-2))
    {x=sudoku(ar,row,col+1);return x;}
    else if(row<=(n*n-2))
    {x=sudoku(ar,row+1,0);return x;}
    else 
    return 1;
    }
int check(int ar[][n*n],int *a[n*n],int row,int col)
{  int i,num,j,flag,count;
    for(i=0;i<n*n;i++)
    {
      if(ar[i][col]!=0)
      {
       num=ar[i][col];
       a[num-1]=0;
      }
     }
     for(i=0;i<n*n;i++)
    {
      if(ar[row][i]!=0)
      {
       num=ar[row][i];
       a[num-1]=0;
      }
    }
     
     int c=col+1,r=row+1;
     while(c%n!=0)
     {c++;
     }
     while(r%n!=0)
     {r++;
     }
     for(i=(r-n);i<r;i++)
     {
                       for(j=(c-n);j<c;j++)
                       {   
                           if(ar[i][j]!=0)
                           {
                               num=ar[i][j];
                               a[num-1]=0;             
                            }
                       }
                                         
     }
     
     flag=0,count=0;
     for(i=0;i<n*n;i++)
     {
     if(a[i]!=0)
     count++;
     }
     if(count==0)
     flag=0;
     else 
     flag=1;
     return flag;
     
    }    
int main()
{  int i,j;
    printf("Enter the order of the puzzle\n");
     scanf("%d",&n);
     int length=n*n;
     int ar[length][length],a[length];
     printf("Enter the puzzle\n");
     for(i=0;i<n*n;i++)
     {
                       for(j=0;j<n*n;j++)
                       {
                                         scanf("%d",&ar[i][j]);
                                         }
     }
     for(i=0;i<n*n;i++)
     {a[i]=i+1;}
      int  c=sudoku(ar,0,0);
        if(c==0)
          printf("\nThe sudoku is not solvable");
    for(i=0;i<n*n;i++)
     {
                       for(j=0;j<n*n;j++)
                       {
                                         printf(" %d ",ar[i][j]);
                                         }
                                         printf("\n");
     }

                                         
}
     
             
