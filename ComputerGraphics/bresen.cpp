#include <GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<stdio.h>
//struct definition for line and triangle
typedef struct line
{
    int x1,x2,y1,y2;
    float r1,g1,b1,a1,r2,g2,b2,a2;
}line;
typedef struct triangle
{
  int x1,x2,x3,y1,y2,y3;
  float r1,g1,b1,r2,g2,b2,r3,g3,b3,a1,a2,a3;
}triangle;

struct line* l;
struct triangle* tri;
int lines,triangles;
//swap two integers
void swap(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
//return maximum of two numbers
int max(int a,int b)
{
     return (a>b)?a:b;
}
//return minimum of two numbers
int min(int a,int b)
{
     return (a<b)?a:b;
}
//swap two floats
void swapf(float *x,float *y)
{
	float temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
//function for drawing a line
void Line(struct line* a)
{
	
	int x1=a->x1,x2=a->x2;
	int y1=a->y1,y2=a->y2;
	float r1=a->r1,r2=a->r2;
	float g1=a->g1,g2=a->g2;
	float b1=a->b1,b2=a->b2;
	float a1=a->a1,a2=a->a2;		
	int D,x,y;
	//plot starting point
	glColor4f (r1, g1, b1 , a1);		
	glVertex3f(x1,y1,0.0);

	//swap the points and their colors if x1>x2
	if((x2-x1)<0)
	  {
		swap(&x1,&x2);
		swap(&y1,&y2);
		swapf(&r1,&r2);	  
		swapf(&g1,&g2);	  
		swapf(&b1,&b2);	  
		swapf(&a1,&a2);	  	
	}	
	int dx=x2-x1;
	int dy=y2-y1;
	
	
	int sign=1;
	sign=dx*dy;//determines the sign of the slope
	if(dy<0 && sign==0)
	sign=-1;
			
	dx=abs(dx);
	dy=abs(dy);
	
	if(sign<0)
	{
		y2*=-1;
		y1*=-1;
	}		
		
	if(dy<dx)
	D=2*dy-dx;
	else if(dy>=dx)
	D=dy-2*dx;
	
	int incE=2*dy;
	int incNE=2*(dy-dx);
	int incN=-2*dx;
	
	//printf("plot %d %d\n",x1,y1);	
	if(dy<dx)	
	y=y1,x=x1+1;
	else if(dy>=dx)
	y=y1+1,x=x1;	
	
	
	float dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)); 
	float rs,gs,bs;
	float temp;

	//case for when slope lies between slope>1 or slope<-1
	if(dy>=dx)
      {
	//printf("N\n");
	while(y<=y2)
	{
		temp=sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
		rs=r1+(r2-r1)*(temp/dist);
		gs=g1+(g2-g1)*(temp/dist);
		bs=b1+(b2-b1)*(temp/dist);
		
		//choosing the color of the pixel by using parametric equation	
		glColor3f (rs,gs,bs);		
		//if sign is less than zero that is slope is less than zero
		//then the line is first reflected in the x-axis
		//and its points are calculated and then again reflected in the x-axis
		if(sign<0)
		glVertex3f(x,-1.0*y,0.0);
		else
		glVertex3f(x,y,0.0);		
		if(D>0)
			D+=incN;
		else
		   {
			D+=incNE;
			x++;
		   }
		y++;
	}
    }
	else if(dy<dx)
	{
	  			
	//case for when 0<slope<1 or -1<slope<0
	     
	while(x<=x2)
		{
		//choosing the color of the pixel by using parametric equation
		temp=sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
		rs=r1+(r2-r1)*(temp/dist);
		gs=g1+(g2-g1)*(temp/dist);
		bs=b1+(b2-b1)*(temp/dist);
		
		glColor3f (rs,gs,bs);		
		if(sign<0)
		glVertex3f(x,-1.0*y,0.0);
		else
		glVertex3f(x,y,0.0);		
		if(D<=0)
			D+=incE;
		else
		   {
			y++;
			D+=incNE;
		   }
		x++;
		}	
	}		
}
int area(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return (x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2));
}

void Triangle(struct triangle *tri)
{
    line* ll=malloc(3*sizeof(line));
    ll[0].x1=tri->x1,ll[0].y1=tri->y1,ll[0].x2=tri->x2,ll[0].y2=tri->y2;
  ll[0].r1=tri->r1,ll[0].r2=tri->r2,ll[0].g1=tri->g1,ll[0].g2=tri->g2,ll[0].b1=tri->b1,ll[0].b2=tri->b2;ll[0].a1=tri->a1,ll[0].a2=tri->a2;    
    ll[1].x1=tri->x2,ll[1].y1=tri->y2,ll[1].x2=tri->x3,ll[1].y2=tri->y3;    
    ll[1].r1=tri->r1,ll[1].r2=tri->r2,ll[1].g1=tri->g1,ll[1].g2=tri->g2,ll[1].b1=tri->b1,ll[1].b2=tri->b2;ll[1].a1=tri->a1,ll[1].a2=tri->a2;    
  
    ll[2].x1=tri->x1,ll[2].y1=tri->y1,ll[2].x2=tri->x3,ll[2].y2=tri->y3;
  ll[2].r1=tri->r1,ll[2].r2=tri->r2,ll[2].g1=tri->g1,ll[2].g2=tri->g2,ll[2].b1=tri->b1,ll[2].b2=tri->b2;ll[2].a1=tri->a1,ll[2].a2=tri->a2;    
    int x1=tri->x1,x2=tri->x2,x3=tri->x3,y1=tri->y1,y2=tri->y2,y3=tri->y3;
 	//the outlines for the triangle were drawn
    Line(&ll[0]);    
    Line(&ll[1]);	
    Line(&ll[2]);
    int minx=min(min(x1,x2),x3);
    int maxx=max(max(x1,x2),x3);
    
    int miny=min(min(y1,y2),y3);
    int maxy=max(max(y1,y2),y3);
    
    int i,j; 
    int total=abs(area(x1,y1,x2,y2,x3,y3));   
	float rs,bs,gs,as;    
	int a1,a2,a3;
   //a scan was done for the rectangle enclosing the triangle
	//and the points which lie inside were colored
    //to check whether a given point is interior to the triangle
   // we check the sum of areas of triangles fromes by the point and 
	//other two vertices equals the area of the triangle		 
	for(i=minx;i<=maxx;i++)
	{
	    for(j=miny;j<=maxy;j++)
		{
		   a1=abs(area(i,j,x2,y2,x3,y3));
		   a2=abs(area(i,j,x1,y1,x3,y3));
		   a3=abs(area(i,j,x1,y1,x2,y2));
		   if((a1+a2+a3)==total)
			{
			   rs=((tri->r1)*a1 + (tri->r2)*a2 + (tri->r3)*a3)/total;
			   gs=((tri->g1)*a1 + (tri->g2)*a2 + (tri->g3)*a3)/total;
			   bs=((tri->b1)*a1 + (tri->b2)*a2 + (tri->b3)*a3)/total;
				
				glColor4f (rs, gs, bs , as);		
								
				glVertex3f(i,j,0.0);
			}		     
		}
	}
}	
void displayfunc(void)
{
	/*  select clearing (background) color       */

	glClearColor (1.0, 1.0, 1.0, 1.0);

    /*  clear all pixels  */
        glClear (GL_COLOR_BUFFER_BIT);

	glPointSize(1.0f);
	glBegin(GL_POINTS); //starts drawing of points
	int i;	
	//loop for drawing of lines
	for(i=0;i<lines;i++)	
	Line(&l[i]);
	
	//loop for drawing of triangles
	for(i=0;i<triangles;i++)	
	Triangle(&tri[i]);
	
			
	glEnd();//end drawing of points

    
/*  don't wait!  
 *  start processing buffered OpenGL routines 
 */
    glFlush ();
}

void init (void) 
{
    
/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, 1.0f, -1.0f);
}

/* 
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv) 
{
    FILE* f1=fopen(argv[1],"r");
    if(!f1)
    printf("file not opened\n");
    int i;	
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 600); 
    glutInitWindowPosition (200, 150);
    glutCreateWindow ("2011CS1026");
    init ();
	//printf("enter lines\n");
	fscanf(f1,"%d",&lines);	
	l=(line*)malloc(lines*sizeof(line));	
	for(i=0;i<lines;i++)
	{
	   fscanf(f1,"%d",&l[i].x1);
	   fscanf(f1,"%d",&l[i].y1);
	   fscanf(f1,"%f",&l[i].r1);
	   fscanf(f1,"%f",&l[i].g1);
	   fscanf(f1,"%f",&l[i].b1);
	   fscanf(f1,"%f",&l[i].a1);
		
	   fscanf(f1,"%d",&l[i].x2);
	   fscanf(f1,"%d",&l[i].y2);
	   fscanf(f1,"%f",&l[i].r2);
	   fscanf(f1,"%f",&l[i].g2);
	   fscanf(f1,"%f",&l[i].b2);
	   fscanf(f1,"%f",&l[i].a2);
	}
	fscanf(f1,"%d",&triangles);	
	tri=(triangle*)malloc(triangles*sizeof(triangle));	
	for(i=0;i<triangles;i++)
	{
	   fscanf(f1,"%d",&tri[i].x1);
	   fscanf(f1,"%d",&tri[i].y1);
	   fscanf(f1,"%f",&tri[i].r1);
	   fscanf(f1,"%f",&tri[i].g1);
	   fscanf(f1,"%f",&tri[i].b1);
	   fscanf(f1,"%f",&tri[i].a1);
		
	   fscanf(f1,"%d",&tri[i].x2);
	   fscanf(f1,"%d",&tri[i].y2);
	   fscanf(f1,"%f",&tri[i].r2);
	   fscanf(f1,"%f",&tri[i].g2);
	   fscanf(f1,"%f",&tri[i].b2);
	   fscanf(f1,"%f",&tri[i].a2);

	   fscanf(f1,"%d",&tri[i].x3);
	   fscanf(f1,"%d",&tri[i].y3);
	   fscanf(f1,"%f",&tri[i].r3);
	   fscanf(f1,"%f",&tri[i].g3);
	   fscanf(f1,"%f",&tri[i].b3);
	   fscanf(f1,"%f",&tri[i].a3);	
	}
	fclose(f1);	
    glutDisplayFunc(displayfunc);   
    glutMainLoop();
    
    return 0;   /* ISO C requires main to return int. */
}
