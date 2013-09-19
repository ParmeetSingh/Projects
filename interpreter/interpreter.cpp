                                                                                                                                                                                                                                  #include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
int pos;
char str[100];
int count=0;
struct genlistnode
{
       int flag;
       char atom[30];
       struct genlistnode *next;
       struct genlistnode *down;
};
struct value
{
       int flag;
       float v;
       genlistnode *p;
};
struct env
{
       value* a[26];
       env* parent;
       env()
       {
           int i;
           for(i=0;i<26;i++)
           a[i]=NULL;
       }
};

value evalnode(genlistnode*,env*);
value evallist(genlistnode*,env*);
value* findinenv(char,env*);
value evalfunc(genlistnode*,value,env*);
void addtoenv(char,value,env*);
int isalphabet(char x[30])
{
    if(x[0]-'a'>=0 && x[0]-'z'<=0 && x[1]=='\0')
    return 1;
    else
    return 0;
}

///forming an integer number
float isnum(char* st)
{
      int sum=0;
      int i=0;
      int flag=0;
      int flag1=0;
      float form=1.0;
      while(st[i]!='\0')
      {
        
         if((st[i]>='0' && st[i]<='9')|| st[i]=='.')
         {
            if(flag1==1)
            form*=10;
            if(st[i]>='0' && st[i]<='9')
            {
                          sum*=10;
                          sum+=st[i]-'0';
            }
            if(st[i]=='.')
            flag1=1;
         }
         else
         {
             flag=1;break;
         }
         i++;
      }
      return sum/form;
}
int iskeyword(char st[30])
{
    if(strcmp(st,"define")==0 || strcmp(st,"begin")==0 || strcmp(st,"if")==0 || strcmp(st,"set")==0 || strcmp(st,"lambda")==0 || strcmp(st,"while")==0)
    {printf("its is a keyword");
    return 1;}
    else if(strcmp(st,"+")==0 || strcmp(st,"-")==0 || strcmp(st,"*")==0 || strcmp(st,"/")==0 || strcmp(st,"%")==0 || strcmp(st,"==")==0 || strcmp(st,"<")==0 || strcmp(st,">")==0 || strcmp(st,"<=")==0)
    return 1;
    else
    printf("not a keyword");
    return 0;
}
int iscorrect(char ch)
{
switch(ch)
{
  case ' ':
  case '(':
  case ')':
  return 0;
  break;
  default:
  return 1;
}

return 1;
}
value evalfunc(genlistnode* p,value v,env *e)
{     int flag=0;
      env e1;
      e1.parent=e;
      genlistnode *arglist,*body;
      genlistnode *temp;
      temp=v.p;
      arglist=temp->next->down;
      body=temp->next->next;
      while(1)
      {  
         if(arglist->next==NULL && p->next->next==NULL)
         flag=1;
         addtoenv(arglist->atom[0],evalnode(p->next,e),&e1);
         if(flag==1)
         break;
         arglist=arglist->next;
         p=p->next;
      }
      value v3= evalnode(body,&e1);
      return v3;
}
void addtoenv(char x,value val,env *e)
{
  value* v1;
  v1=(value*)malloc(sizeof(value));
  v1->v=val.v;
  v1->p=val.p;
  v1->flag=val.flag;
  e->a[x-'a']=v1;
       
}
genlistnode* makelist()
{
  genlistnode *head;
  head=NULL;
  genlistnode *curr,*curr1,*test;
  curr=NULL;
  curr1=NULL;
  char form[30];
  int i=0;
  char m;
  while(pos<strlen(str))
  {  m=str[pos];
     if(m=='(')
     {
       curr1=(genlistnode*)malloc(sizeof(genlistnode));
       curr1->flag=1;
       pos++;
       curr1->down=makelist();
       test=curr1->down;
       if(head==NULL)
       {head=curr1;curr=curr1;}
       else
       {
           curr->next=curr1;
           curr=curr1;
       }
     }
     else if(iscorrect(str[pos])==1)
     { i=0;
       while(str[pos]!=' ')
       {
          form[i++]=str[pos++];
       }
       form[i]='\0';
       curr1=(genlistnode*)malloc(sizeof(genlistnode));
       strcpy(curr1->atom,form);
       curr1->flag=0;
       curr1->down=NULL;
       if(head==NULL)
       {
       head=curr1;curr=curr1;
       }
       else
       {
           curr->next=curr1;
           curr=curr1;
       }
     }
     else if(str[pos]==')')
     {
          pos++;
          curr->next=NULL;
          return head;
     }
     else{
          pos++;}
         }
     return head;
}
int displaylist(genlistnode *head,int i)
{
  int flag=0;
  genlistnode *curr=head;
  while(1)
  {
   if(curr->next==NULL)
   flag=1;
   if(curr->flag==1)
   displaylist(curr->down,i+1);
   else
   {
       printf("\nlevel %d",i);
       puts(curr->atom);
   }    
   if(flag==1)
   return 0;
   curr=curr->next;   
  }
}
value evalnode(genlistnode *p,env *e)
{     float f;
      value val;
      value *v1;
      char x=p->atom[0];
      if(p->flag==1)
      {return evallist(p->down,e);}
      if(p->atom[0]>='0' && p->atom[0]<='9')
      {
        f=isnum(p->atom);
        val.flag=0;
        val.v=f;
        val.p=NULL;
        return val;
      }
     if(strlen(p->atom)==1 && isalphabet(p->atom)==1)
    { 
       v1=findinenv(p->atom[0],e);
       return *v1;
       }
       if(iskeyword(p->atom)==1)
     { return evallist(p,e);}
      
}
value* findinenv(char x,env *e)
{
      value* p1;
      if(e->a[x-'a']!=NULL)
      {
      p1=e->a[x-'a'];
      return (e->a[x-'a']);}
      else
      {
       if(e->parent==NULL)
       printf("error:value not found");
       else
       return findinenv(x,e->parent);
      }
}
value evallist(genlistnode *p,env *e)
{     int flag;
      genlistnode *p1,*p2;
      char st[30];
      value val,val1,val2;
      value *val3;
      strcpy(st,p->atom);
      if(strlen(p->atom)==1 && isalphabet(p->atom)==1)
      { 
       val3=findinenv(p->atom[0],e);
       if(val3->flag==1)
       { 
       return evalfunc(p,*val3,e);
       }
       return *val3;
       }
       
      if(strcmp(st,"<")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        if(val1.v<val2.v)
        val.v=1;
        else
        val.v=0;
        val.p=NULL;
        return val;
      }
      if(strcmp(st,">")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        if(val1.v>val2.v)
        val.v=1;
        else
        val.v=0;
        val.p=NULL;
        return val;
      }
      if(strcmp(st,"<=")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        if(val1.v<=val2.v)
        val.v=1;
        else
        val.v=0;
        val.p=NULL;
        return val;
      }
      
      if(strcmp(st,"begin")==0)
      {
        p=p->next;
        while(p->next != NULL)
        {
        evalnode(p,e);
        p = p->next;
        }
        return evalnode(p, e);
      }
      if(p->flag==1)
      {
      if(strcmp(p->down->atom,"lambda")==0)
      {
      int flag=0;
      env e1;
      e1.parent=e;
      genlistnode *arglist,*body;
      genlistnode *temp;
      temp=p->down;
      arglist=temp->next->down;
      body=temp->next->next;
      while(1)
      {  
         if(arglist->next==NULL && p->next->next==NULL)
         flag=1;
         addtoenv(arglist->atom[0],evalnode(p->next,e),&e1);
         if(flag==1)
         break;
         arglist=arglist->next;
         p=p->next;
      }
      return evalnode(body,&e1);
      }
      }
      if(strcmp(st,"set")==0)
      {
        p=p->next;
        val3=findinenv(p->atom[0],e);
        val=evalnode(p->next,e);
        val3->v=val.v;
        return val;
      }
      
      if(strcmp(st,"if")==0)
      {
        val=evalnode(p->next,e);
        if(val.v==1)
        {
        return evalnode(p->next->next,e);
        }
        else
        {
        return evalnode(p->next->next->next,e);
        }
      }
      if(strcmp(st,"while")==0)
      {
        val=evalnode(p->next,e);
        while(val.v==1)
        {
          evalnode(p->next->next,e);
          val=evalnode(p->next,e);
        }
        return val;
      }
       if(strcmp(st,"define")==0)
      {
        p1=p->next;
        if(isalphabet(p1->atom)==0)
        {
           printf("error");
        }
        if(p1->next->flag==1)
        {
          if(strcmp(p1->next->down->atom,"lambda")==0)
        {
         val.flag=1;
         val.p=p1->next->down;
         addtoenv(p1->atom[0],val,e);
         return val;
        }
        
        }
        val=evalnode(p1->next,e);
        addtoenv(p1->atom[0],val,e);
        return val;
      }
      if(strcmp(st,"+")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        val.v=val1.v + val2.v;
        val.p=NULL;
        return val;
      }
      if(strcmp(st,"-")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        val.v=val1.v-val2.v;
        val.p=NULL;
        return val;
      }
      if(strcmp(st,"*")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        val.v=val1.v*val2.v;
        val.p=NULL;
        return val;
      }
      if(strcmp(st,"/")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        val.v=val1.v/val2.v;
        val.p=NULL;
        return val;
      }
     if(strcmp(st,"%")==0)
      {
        val1=evalnode(p->next,e);
        p1=p->next;     
        val2=evalnode(p1->next,e);
        val.flag=0;
        int a=val1.v;
        int b=val2.v;
        val.v=a%b;
        val.p=NULL;
        return val;
      }
      if(strcmp(st,"==")==0)
      {
        val1=evalnode(p->next,e);
        val2=evalnode(p->next->next,e);
        val.flag=0;
        if(val1.v==val2.v)
        val.v=1;
        else
        val.v=0;
        val.p=NULL;
        return val;
      }
      return evalnode(p,e);      
}
int main()
{   int j;
     gets(str);
     
     genlistnode *head=NULL;
     genlistnode *curr=NULL;
     if(str[0]!='(')
     printf("please make first place as (");
     pos=0;
     int i=0;
     head=makelist();
     curr=head;
     //displaylist(head,1);
     value v1;
    env e;
     v1=evallist(head,&e);
    
     printf("%f\n",v1.v);
     return 0;
}
