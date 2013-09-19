#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
class RedBlackTree;

class TreeNode;

TreeNode* insert(TreeNode*,int);

TreeNode* assigncolor(TreeNode*);

void rotateright(TreeNode*,TreeNode*);

void rotateleft(TreeNode*,TreeNode*);

int assignrank(TreeNode* node);

TreeNode* last;

void split(int no,int key,int no1,int no2);

void replacenode(TreeNode*,TreeNode*);


TreeNode* delete_case1(TreeNode *n,int no);

TreeNode* delete_case2(TreeNode *n,int no);

TreeNode* delete_case3(TreeNode *n,int no);

TreeNode* delete_case4(TreeNode *n,int no);

TreeNode* delete_case5(TreeNode *n,int no);

TreeNode* delete_case6(TreeNode *n,int no);

int leftsize(TreeNode*);

int kthsmallest(int,int);

RedBlackTree* r;

TreeNode* deletekey(int,int);

int is_leaf(TreeNode*);

int rep=0;//check for same node added

class TreeNode {
public:
friend class RedBlackTree;
int value;
TreeNode *left, *right, *parent;
int leftsize; // number of nodes in left subtree
int rank; // the number of black nodes on any path
char color;
TreeNode()
{
  rank=0;
}
};

class RedBlackTree {
public:
TreeNode *root;
RedBlackTree()
{
   root=NULL;
};
};
int leftsize(TreeNode *root)
{
    if(root==NULL)
    return 0;
    else
    {
       if(root->left==NULL && root->right==NULL)
       {
       root->leftsize=0;
       return 1;
       }
       else
       {
       root->leftsize=leftsize(root->left);
       return 1+root->leftsize+leftsize(root->right);
       }
    }
}
int kthsmallest(int k,int no)
    {
        TreeNode *node = r[no].root;
        
        int count = k;

        int sizeOfLeftSubtree = 0;

        while(node != NULL)
        {

            sizeOfLeftSubtree = node->leftsize;

            if (sizeOfLeftSubtree + 1 == count)
                return node->value;
            else if (sizeOfLeftSubtree < count)
            {
                node = node->right;
                count -= sizeOfLeftSubtree+1;
            }
            else
            {
                node = node->left;
            }
        }

        return -1;
    }
TreeNode* search(TreeNode *root,int val)
{
   if(root==NULL)
   {
   return NULL;
   }
   if(root->value==val)
   {
   return root;
   }
   else if(root->value>val)
   return search(root->left,val);
   else if(root->value<val)
   return search(root->right,val);
}
void giveblackht(TreeNode *root,int i)
{
   if(root==NULL)
   {
   return;
   }
   if(root->color=='b')
   giveblackht(root->left,i+1);
   else
   giveblackht(root->left,i);
   if(root->color=='b')
   giveblackht(root->right,i+1);
   else
   giveblackht(root->right,i);
}
void displayparents(TreeNode *root)
{
    if(root->left!=NULL)
    displayparents(root->left);
    if(root==NULL)
    {return ;}
    else
    {
     //printf("hello");
     if(root->parent!=NULL)
     {
      printf("\n value is %d ans parent is %d and color is %c rank is %d leftsize is %d",root->value,root->parent->value,root->color,root->rank,root->leftsize);
     }
     else
     {  
       //printf("bye");
      printf("\n value is %d ans parent is null and color is %c rank is %d leftsize is %d",root->value,root->color,root->rank,root->leftsize);
     }
    }
    if(root->right!=NULL)
    displayparents(root->right);
}

void transtreeinorder(TreeNode *root)
{
    if(root->left!=NULL)
    transtreeinorder(root->left);
    if(root==NULL)
    {return ;}
    else
    printf("\n %d ",root->value);
    if(root->right!=NULL)
    transtreeinorder(root->right);
}

void insertintree(int no,int n,int* ar)
{
    int i;
    TreeNode *node;
     for(i=0;i<n;i++)
     {
        r[no].root=insert(r[no].root,ar[i]);
        r[no].root->parent=NULL;
        if(rep==0)
        {
         r[no].root=assigncolor(r[no].root);
        }
        rep=0; 
     }
     int y=assignrank(r[no].root);
     r[no].root->leftsize=leftsize(r[no].root->left);
     int x=leftsize(r[no].root->right);
}
TreeNode* assigncolor(TreeNode *root)
{
   TreeNode *gp=NULL;
   TreeNode *uncle=NULL;
   TreeNode *child=last;
   TreeNode *temp;
   char colortemp;
   last->color='r';//added should be red
   if(root==last)
   {
   root->color='b';
   return root;
   }
   TreeNode *p=last->parent;
   gp=last->parent->parent;
   if(gp==NULL || p->color=='b')
   {
   last->color='r';
   return root;
   }
   if(p==gp->left)
   uncle=gp->right;
   if(p==gp->right)
   uncle=gp->left;
   if(p->color=='r')
   {
      if(uncle==NULL || uncle->color=='b')
      {
          if(gp->left==p && p->left==child)
          {
             rotateright(p,gp);
             colortemp=p->color;
             p->color=gp->color;
             gp->color=colortemp;
             if(gp==root)
             return p;
             else
             return root;
          }
          //case RRb
          else if(gp->right==p && p->right==child)
          {
             rotateleft(p,gp);
             colortemp=p->color;
             p->color=gp->color;
             gp->color=colortemp;
             if(gp==root)
             return p;
             else
             return root;
          }
          //case LRb
          else if(gp->left==p && p->right==child)
          {
             rotateleft(child,p);
             rotateright(child,gp);
             colortemp=child->color;
             child->color=gp->color;
             gp->color=colortemp;
             if(root==gp)
             {
              return child;
             }
             else
             return root;
          }
          //case RLb
          else if(gp->right==p && p->left==child)
          {
             rotateright(child,p);
             rotateleft(child,gp);
             colortemp=child->color;
             child->color=gp->color;
             gp->color=colortemp;
             if(root==gp)
             return child;
             else
             return root;
          }
      }
      else
      {
          //case LLr //case LRr
          if(gp->left==p)
          {
             p->color='b';
             uncle->color='b';
             gp->color='r';
             if(gp==root)
             gp->color='b';
             else
             if(gp->parent->color=='r')
             {
                last=gp;
                root=assigncolor(root);
             }
             return root;
          }
          //case RLr,RRr
          else if(gp->right==p)
          {
             p->color='b';
             uncle->color='b';
             gp->color='r';
             if(gp==root)
             gp->color='b';
             else
             if(gp->parent->color=='r')
             {
                last=gp;
                root=assigncolor(root);
             }
             return root;
          }
          
      }
    }
}
void rotateright(TreeNode *p,TreeNode *gp)
{
             TreeNode* temp;
             temp=p->right;
             p->right=gp;
             gp->left=temp;
             p->parent=gp->parent;
             if(temp!=NULL)
             temp->parent=gp;
             if(gp->parent!=NULL)
             {
                if(gp==gp->parent->left)
                gp->parent->left=p;
                if(gp==gp->parent->right)
                gp->parent->right=p;
             }
             gp->parent=p;
             
}
void  rotateleft(TreeNode *p,TreeNode *gp)
{
             TreeNode* temp;
             temp=p->left;
             p->left=gp;
             gp->right=temp;
             p->parent=gp->parent;
             if(temp!=NULL)
             temp->parent=gp;
             if(gp->parent!=NULL)
             {
                if(gp==gp->parent->left)
                gp->parent->left=p;
                if(gp==gp->parent->right)
                gp->parent->right=p;
             }
             gp->parent=p;
}

TreeNode* insert(TreeNode *node,int val)
{
   if(node==NULL)
   {
   node=(TreeNode*)malloc(sizeof(TreeNode));
   node->left=NULL;
   node->right=NULL;
   node->value=val;
   last=node;//last change will be the one to be rotated
   }     
   else
   if(node->value>val)
   {
   if(node->left==NULL)
   {
   node->left=insert(node->left,val);
   node->left->parent=node;
   }
   else
   insert(node->left,val);
   }
   else
   if(node->value<val)
   {
   if(node->right==NULL)
   {
   node->right=insert(node->right,val);
   node->right->parent=node;
   }
   else
   insert(node->right,val);
   }
   else
   if(node->value==val)
   {
   printf("element already present");
   rep=1;//for repition
   }
   return node;
}
int assignrank(TreeNode* node)
{
   if(node==NULL)
   return 0;
   if(node->right!=NULL)
   assignrank(node->right);
   if(node->color=='b')
   {
      node->rank=1+assignrank(node->left);
      return node->rank;
   }
   else{
      node->rank=assignrank(node->left);
      return node->rank;
   }
}
void jointree(int no1,int key,int no2,int no3)
{
   TreeNode *temp;
   TreeNode *curr1=r[no1].root;
   TreeNode *curr2=r[no2].root;
   TreeNode *tem=new TreeNode;
   int *ar=&key;
   if(no1!=no3 && no2!=no3)
   r[no3].root=new TreeNode;
   TreeNode *z=new TreeNode;
   if(curr1==NULL)
   {
   r[no1].root=new TreeNode;
   }
   if(curr2==NULL)
   {
   r[no2].root=new TreeNode;
   }
   int rank1=r[no1].root->rank;
   int rank2=r[no2].root->rank;
   if(rank1==rank2)
   {
     if(rank1==0)
     {
       r[no3].root->value=key;
       r[no3].root->rank=1;
       r[no3].root->color='b';
       r[no3].root->parent=NULL;
       r[no3].root->left=NULL;
       r[no3].root->right=NULL;
     }
     else
     {    
     tem->value=key;
     tem->rank=rank1+1;
     tem->left=r[no1].root;
     tem->right=r[no2].root;
     r[no1].root->parent=tem;
     r[no2].root->parent=tem;
     tem->left->color='b';
     tem->right->color='b';
     tem->color='b';
     tem->parent=NULL;
     r[no3].root=tem;
     if(no1!=no3)
     r[no1].root=NULL;
     if(no2!=no3)
     r[no2].root=NULL;
     }
   }
   else if(rank1>rank2)
   {
         if(rank2==0)
         {
         insertintree(no1,1,ar);
         r[no3].root=r[no1].root;
         if(no3!=no1)
         r[no1].root=NULL;
        }
   else
   {
         while(curr1->rank>curr2->rank)
         {
            curr1=curr1->right;
         }
        z->color='r';
        z->left=curr1;
        z->rank=curr2->rank;
        temp=curr1->parent;
        curr1->parent=z;
        z->value=key;
        z->right=curr2;
        curr2->parent=z;
        z->left->color='b';
        z->right->color='b';
        temp->right=z;
        z->parent=temp;
        r[no3].root=r[no1].root;
        if(no1!=no3)
        r[no1].root=NULL;
        if(no2!=no3)
        r[no2].root=NULL;
        temp=z;
        while(temp!=r[no3].root)
        {
           if(temp->color=='r' && temp->parent->color=='r')
           {
              last=temp;
              r[no3].root=assigncolor(r[no3].root);
           }
           temp=temp->parent;
        }
     }
   }
   else if(rank1<rank2)
   {
          if(rank1==0)
         {
         insertintree(no2,1,ar);
         r[no3].root=r[no2].root;
         if(no3!=no2)
         r[no2].root=NULL;
         }
         else
         {     
         while(curr1->rank<curr2->rank)
         {
            curr2=curr2->left;
         }
        z->color='r';
        z->right=curr2;
        z->rank=curr1->rank;
        temp=curr2->parent;
        curr2->parent=z;
        z->value=key;
        z->left=curr1;
        curr1->parent=z;
        z->right->color='b';
        z->left->color='b';
        temp->left=z;
        z->parent=temp;
        r[no3].root=r[no2].root;
        if(no3!=no1)
        r[no1].root=NULL;
        if(no2!=no1)
        r[no2].root=NULL;
        while(temp!=r[no3].root)
        {
           if(temp->color=='r' && temp->parent->color=='r')
           {
              last=temp;
              r[no3].root=assigncolor(r[no3].root);
           }
            temp=temp->parent;
        }
   }
  }   
     r[no3].root->leftsize=leftsize(r[no3].root->left);
     leftsize(r[no3].root->right);
   
}
TreeNode* findinorderleaf(TreeNode* node)
{
   TreeNode* curr=node;
   curr=curr->left;
   while(curr->right!=NULL)
   {
      curr=curr->right;
   }
   return curr;
}
TreeNode* deletekey(int no,int key)
{
   TreeNode* child;
   TreeNode *root=r[no].root;
   TreeNode *temp;
   TreeNode* n=search(root,key);//search the key first
   if(n==NULL)//if key not present
   {
      printf("\nKey not present");
      return root;
   }
   //the node to be deleted after this has at most one null node
  if(n->left!=NULL && n->right!=NULL)
   {
        temp=findinorderleaf(n);
        n->value=temp->value;
        n=temp;
   }
   last=n;
   //assume at most one non-leaf node
   if(n->color=='r')
   {
     replacenode(n,NULL); 
     return r[no].root;  
   }
   if(n->left==NULL && n->right==NULL)
   {
       if(n==r[no].root)
       {
       //printf("The tree is empty");
       free(n);
       return NULL;
       }
       else
       {
          r[no].root=delete_case1(n,no);
          if(n==n->parent->left)
          {
          n->parent->left=NULL;
          free(n);
          }
          else
          {
          n->parent->right=NULL;
          free(n);
          }
          
          return r[no].root;
       }
   }
   if(n->left!=NULL)
   child=n->left;
   else
   child=n->right;
   if(n->color=='b' && child->color=='r')
   {    
        replacenode(n,child);
        child->color='b';
        if(child->parent==NULL)
        return child;
   }
   return r[no].root;
}
TreeNode* sibling(TreeNode *n)
{
        if (n == n->parent->left)
                return n->parent->right;
        else
                return n->parent->left;
}
TreeNode* delete_case1(TreeNode *n,int no)
{
        if (n->parent != NULL)
             return delete_case2(n,no);
        else
        {
        return r[no].root;
        }
}

TreeNode* delete_case2(TreeNode *n,int no)
{
        TreeNode *s = sibling(n);
        if (s->color == 'r') {
                n->parent->color = 'r';
                s->color = 'b';
                if(n->parent==r[no].root)
                r[no].root=s;
                if (n==n->parent->left)
                        rotateleft(s,n->parent);
                else
                        rotateright(s,n->parent);
        }
        return delete_case3(n,no);
}

TreeNode* delete_case3(TreeNode *n,int no)
{
        TreeNode *s = sibling(n);
 
        if ((n->parent->color == 'b') &&
            (s->color == 'b') &&
            (s->left==NULL || s->left->color ==  'b') 
            && (s->right==NULL || s->right->color == 'b')) {
                s->color = 'r';
                return delete_case1(n->parent,no);
        } else
                return delete_case4(n,no);
}

TreeNode* delete_case4(TreeNode *n,int no)
{
        TreeNode *s = sibling(n);
        if ((n->parent->color == 'r') &&
            (s->color ==  'b') &&
            (s->left==NULL || s->left->color ==  'b') &&
            (s->right==NULL || s->right->color ==  'b')) {
                s->color = 'r';
                n->parent->color =  'b';
        } else
                r[no].root=delete_case5(n,no);
        return r[no].root;       
}

TreeNode* delete_case5(TreeNode *n,int no)
{
        TreeNode *s = sibling(n);
 
        if  (s->color ==  'b') { 
                if ((n == n->parent->left) &&
                    (s->right==NULL || s->right->color ==  'b') &&
                    (s->left->color == 'r')) { 
                        s->color = 'r';
                        s->left->color =  'b';
                        rotateright(s->left,s);
                        if(s==r[no].root)
                        r[no].root=s->left;
                } else if ((n == n->parent->right) &&
                           (s->left==NULL || s->left->color ==  'b') &&
                           (s->right->color == 'r')) {
                        s->color = 'r';
                        s->right->color =  'b';
                        rotateleft(s->right,s);
                        if(s==r[no].root)
                        r[no].root=s->right;
                }
        }
        return delete_case6(n,no);
}

TreeNode* delete_case6(TreeNode *n,int no)
{
        TreeNode *s = sibling(n);
 
        s->color = n->parent->color;
        n->parent->color =  'b';
 
        if (n == n->parent->left) {
                s->right->color =  'b';
                rotateleft(s,n->parent);
                if(n->parent==r[no].root)
                r[no].root=s;
        } else {
                s->left->color =  'b';
                rotateright(s,n->parent);
                if(n->parent==r[no].root)
                r[no].root=s;
             }
             return r[no].root;
}

void replacenode(TreeNode* n,TreeNode* child)
{
   if(child==NULL)
   {
      if(n->parent!=NULL)
      {
         if(n==n->parent->right)
         n->parent->right=NULL;
         else if(n==n->parent->left)
         n->parent->left=NULL;
      }
      free(n);
      return;
   }
   else
   {
       
       if(n->parent!=NULL)
      {
         if(n==n->parent->right)
         n->parent->right=child;
         else if(n==n->parent->left)
         n->parent->left=child;
         child->parent=n->parent;
      }
      else if(n->parent==NULL)
      {
         child->parent=NULL;
      }
      free(n);
      return;
   }
}    
void split(int no,int key,int no1,int no2)
{
  int *ar=&key;
   TreeNode* curr;
   r[no1].root=new TreeNode;
   r[no2].root=new TreeNode;
   TreeNode* p=search(r[no].root,key);
   if(p==NULL)
   insertintree(no,1,ar);
   p=search(r[no].root,key);
   TreeNode *head=r[no].root;
     r[no1].root=p->left;
     if(p->left!=NULL)
     {
       p->left->color='b';
       r[no1].root->parent=NULL;
     }  
     r[no2].root=p->right;
     if(p->right!=NULL)
     {
     p->right->color='b';
     r[no2].root->parent=NULL;
     }
     p->left=NULL;
     p->right=NULL;
     assignrank(p->left);
     assignrank(p->right);
     curr=p->parent;
     while(curr!=NULL)
     {
       if(curr->left==p)
       {
       r[no].root=curr->right;
       if(r[no].root!=NULL)
       {
       r[no].root->color='b';
       r[no].root->parent=NULL;
       }
       assignrank(r[no].root);
       jointree(no2,curr->value,no,no2);
       }
       else
       if(curr->right==p)
       {
       r[no].root=curr->left;
       if(r[no].root!=NULL)
       {
       r[no].root->color='b';
       r[no].root->parent=NULL;
       }
       assignrank(r[no].root);
       jointree(no,curr->value,no1,no1);
       }
       curr=curr->parent;
       p=p->parent;
     }
  
}    

int main()
{
    int i,no,n;
    int no1,no2,no3;//for joining of trees
    int key;
    int *ar;
    TreeNode *node;//recieve from search
    r=(RedBlackTree*)malloc(10000*sizeof(RedBlackTree));
    for(i=0;i<10000;i++)
    {
       r[i].root=NULL;
    }
    int ins;
    int flag=0;
    cin>>ins;
    string s;
    int j=0;
    for(j=0;j<ins;j++)
    {
              cin>>s;
              if(s=="insert")
              {
                   cin>>no;
                   cin>>n;
                   ar=(int*)malloc(n*sizeof(int));
                   for(i=0;i<n;i++)
                   {
                   cin>>ar[i];
                   }
                   insertintree(no,n,ar);
                      
               }
              else if(s=="select")
              {
                   cin>>no;
                   cin>>key;
                   cout<<kthsmallest(key,no);
                   cout<<endl;
               }
               else if(s=="join")
              {
                   cin>>no1;
                   cin>>key;
                   cin>>no2;
                   cin>>no3;
                   jointree(no1,key,no2,no3);
               }
               if(s=="delete")
              {
                   cin>>no;
                   cin>>n;
                   for(i=0;i<n;i++)
                   {
                   cin>>key;
                   r[no].root=deletekey(no,key);
                     assignrank(r[no].root);
                     r[no].root->leftsize=leftsize(r[no].root->left);
                     leftsize(r[no].root->right);
                   }   
               }
               else if(s=="split")
              {
                   cin>>no1;
                   cin>>key;
                   cin>>no2;
                   cin>>no3;
                   split(no1,key,no2,no3);
               }
    }
    return 0;
}
