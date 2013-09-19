#include<stdio.h>
#include<iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 2147483647
using namespace std;
int n;
int *array;
class node
{
public:
int y;
int wt;
node* next;
};
class graph
{
public:
int obs;
node* head;
int p;
int d;
int v;
};
graph* ghead;
class heap
{
public:
int n;
graph *ar;
graph* s;
void insert(int n);
void swap(int ptr,int par);
void deleteh();
void heapify(int num);
};

void heap :: swap(int ptr,int par)
{
graph temp;

temp.obs=ar[ptr].obs;
ar[ptr].obs=ar[par].obs;
ar[par].obs=temp.obs;

temp.head=ar[ptr].head;
ar[ptr].head=ar[par].head;
ar[par].head=temp.head;

temp.d=ar[ptr].d;
ar[ptr].d=ar[par].d;
ar[par].d=temp.d;

temp.v=ar[ptr].v;
ar[ptr].v=ar[par].v;
ar[par].v=temp.v;

temp.p=ar[ptr].p;
ar[ptr].p=ar[par].p;
ar[par].p=temp.p;

}


void heap :: insert(int n)
{    
     int flag=0;
     int par=(n-1)/2;
     int ptr=n;
     while(ar[ptr].d<=ar[par].d)
     {
        if(par==0)
        flag=1;
        swap(ptr,par);
        //temp=ar[ptr];
        //ar[ptr]=ar[par];
        //ar[par]=temp;
        ptr=par;
        par=(ptr-1)/2;
        if(flag==1)
        break;
     }
}

void heap :: deleteh()
{
int last=n-1;
n--;
if(last==0)
return;
swap(0,last);
heapify(n-1);
}

void heap :: heapify(int num)
{
//cout<<"hello";
if(num==0)
return;
int par=(num-1)/2;
if(ar[par].d>ar[num].d)
swap(par,num);
if(num%2==0)
{
if(ar[par].d>ar[num-1].d)
swap(par,num-1);
}
if(num%2==0)
return heapify(num-2);
else
return heapify(num-1);
}

int shortestpath(int start,int goal)
{
 if(ghead[start].head==NULL)
 {
 cout<<"No path to goal exists\n";
 return 0;
 }
 int i;
 int v;
 node *curr;
 int length=0;
 heap h;
 graph *ar;
 int vert;
 int shortest;
 int tempvert;
 ar=(graph*)malloc(n*sizeof(graph)); 
 h.s=(graph*)malloc(n*sizeof(graph)); 
 h.ar=ar;
 h.n=n;
 for(i=0;i<n;i++)
     {
       h.ar[i]=ghead[i];
       if(i==start)
       h.ar[i].d=0;
       else
       h.ar[i].d=MAX;
       h.ar[i].p=-1;
       if(i!=0)
       h.insert(i);       
     }
  while(h.n!=0)
  {
  vert=h.ar[0].v;
  if(h.ar[0].d==MAX)
  {
  cout<<"No path to goal exists\n";
    return 0;
  }
  curr=ghead[vert].head;
  if(vert==goal)
  {
  shortest=h.ar[0].d;
  //cout<<"yo goal in heap shortest"<<goal<<shortest;
  }
  while(curr!=NULL)
  {
      v=curr->y;
      i=0;
      while(h.ar[i].v!=v)
      {i++;}
      if(h.ar[i].d>curr->wt + h.ar[0].d)
      {
       h.ar[i].p=h.ar[0].v;
       h.ar[i].d=curr->wt + h.ar[0].d;
      } 
      curr=curr->next; 
   }
   h.s[vert]=h.ar[0];
   h.deleteh();
   //printf("hello\n");
 /*for(i=0;i<n;i++)
     {
       cout<<h.ar[i].v;
       printf(" ");
       cout<<h.ar[i].d;
       printf("\n");       
     }
     */
  }
  //printf("shortest %d ",shortest);
  array=(int*)malloc((shortest+2)*sizeof(int));
  vert=goal;
  i=shortest;
  while(vert!=-1)
  {
    vert=h.s[vert].p;
    length++;
  }
  i=length-1;
  vert=goal;
  while(vert!=-1)
  {
    array[i]=vert;
    vert=h.s[vert].p;
    i--;
  }
  /*for(i=0;i<length;i++)
  {
    cout<<array[i]<<" ";
  }*/
  return length;
 //cout<<"length "<<length;
}
int main()
{  
 int y,wt;
 int i,j,k;
 int b;
 int start;
 int goal;
 int block;
 int v;
 int weight;
 node *curr;
 node *temp;
 cin>>n;
 cin>>start;
 cin>>goal;
 ghead=(graph*)malloc(n*sizeof(graph));
 for(i=0;i<n;i++)
 {
   ghead[i].head=NULL;
   ghead[i].obs=0;
   ghead[i].v=i;
   cin>>k;
   for(j=0;j<k;j++)
   {
     curr=(node*)malloc(sizeof(node));
     if(j==0)
     {
       ghead[i].head=curr;
     } 
     else
     {
      temp->next=curr;
     }
       cin>>curr->y;
       cin>>curr->wt;
       temp=curr;
       if(j==(k-1))
       curr->next=NULL; 
   }
 }
 cin>>b;
 for(i=0;i<b;i++)
 {
  cin>>block;
  ghead[block].obs=1;
 }
 int flag=0;
 int flag2=0;
 int yeah=0;
 while(1)
 {
 //o++;
 //cout<<"start and goal"<<start<<goal<<endl;
 flag=0;
 flag2=0;
 int length=shortestpath(start,goal);
 if(length==0)
 break;
 weight=0;
 for(i=0;i<length-1;i++)
  {
    curr=ghead[array[i]].head;
    while(curr->y!=array[i+1])
    {curr=curr->next;}
    weight+=curr->wt;
  }
 cout<<"Found new path from "<<start<<" of length "<<weight << " : " <<endl;
  for(i=0;i<length;i++)
  {
    cout<<array[i]<<" ";
  }
  for(i=0;i<length;i++)
  {
    if(ghead[array[i]].obs==1)
    {
    flag=1;
    cout<<"\nFound blocked vertex at "<<array[i]<<endl;
    ghead[array[i]].head=NULL;
    if(i==0)
    {
    cout<<"No path to goal exists\n";
    break;
    }
    start=array[i-1]; 
    //cout<<"predecessor"<<start;
    flag2=1;
    break;
    }
    if(i==(length-1))
    yeah=1;
  }
  if(flag==0)
  break;
  if(flag2==1)
  continue; 
 }
 if(yeah==1)
 cout<<"\nReached goal\n";
 return 0;
 //getch();
}
