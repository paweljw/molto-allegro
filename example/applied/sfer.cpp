/*W¹tor £ukasz*/

#include<GL/glut.h>
#include<math.h>
#include <string.h>

void	dwie_proste(int zmien);
void	katy(int zmien);
void	plipr(int zmien);
void	ptrzy(int zmien);
void	trzy_plaszcz(int zmien);
void	pdwie(int zmien);
void	kwadrat(int zmien);

class punkt
{
 public:
 double x,y;
 punkt(){x=0;y=0;};
 punkt(double xx, double yy);
};
punkt::punkt(double xx, double yy)
{x=xx; y=yy;
}
class punkt3d
{
 public:
 double x,y,z;
 punkt3d(){x=0;y=0;z=0;};
 punkt3d(double xx,double yy,double zz);
};
punkt3d::punkt3d(double xx,double yy,double zz)
{x=xx;	y=yy;	z=zz;}
int  ktora=0;
const GLdouble left = - 10.0;
const GLdouble right = 10.0;
const GLdouble bottom = - 10.0;
const GLdouble top = 10.0;
const GLdouble near = 50.0;
const GLdouble far = -70.0;

// wspó³czynnik skalowania
GLfloat scale = 0.5;

// k¹ty obrotu
GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// przesuniêcie
GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

// wskaŸnik naciœniêcia lewego przycisku myszki
int button_state = GLUT_UP;

// po³o¿enie kursora myszki
int button_x, button_y;

//zmienne menu
int aktywne=1;
double dx=0,*dax=0,*day=0,*daz=0;
	 double *dbx=0,*dby=0,*dbz=0;
	 

#define PI 3.14159265
void SpecialKeys( int key, int x, int y )
{
    switch( key )
    {
        // kursor w lewo
    case GLUT_KEY_LEFT:
        rotatey -= 1;
        break;
        
        // kursor w górê
    case GLUT_KEY_UP:
        rotatex -= 1;
        break;
        
        // kursor w prawo
    case GLUT_KEY_RIGHT:
        rotatey += 1;
        break;
        
        // kursor w dó³
    case GLUT_KEY_DOWN:
        rotatex += 1;
        break;
    }

	switch(aktywne)
	{
	case 1:
		dwie_proste(ktora);
		break;
	case 2:
		katy(ktora);
		break;
	case 3:
		plipr(ktora);
		break;
	case 4:
		ptrzy(ktora);
		break;
	case 5:
		trzy_plaszcz(ktora);
		break;
	case 6:
		pdwie(ktora);
		break;
	case 7:
		kwadrat(ktora);
		break;
	}
    
    // odrysowanie okna
    glutPostRedisplay();
}
void MouseMotion( int x, int y )
{
    if( button_state == GLUT_DOWN )
    {
        translatex += 1.1 *( right - left ) / glutGet( GLUT_WINDOW_WIDTH ) *( x - button_x );
        button_x = x;
        translatey += 1.1 *( top - bottom ) / glutGet( GLUT_WINDOW_HEIGHT ) *( button_y - y );
        button_y = y;
        glutPostRedisplay();
    }
	switch(aktywne)
	{
	case 1:
		dwie_proste(ktora);
		break;
	case 2:
		katy(ktora);
		break;
	case 3:
		plipr(ktora);
		break;
	case 4:
		ptrzy(ktora);
		break;
	case 5:
		trzy_plaszcz(ktora);
		break;
	case 6:
		pdwie(ktora);
		break;
	case 7:
		kwadrat(ktora);
		break;
	}
}
void MouseButton( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON )
    {
        // zapamiêtanie stanu lewego przycisku myszki
        button_state = state;
        
        // zapamiêtanie po³o¿enia kursora myszki
        if( state == GLUT_DOWN )
        {
            button_x = x;
            button_y = y;
        }
    }
	switch(aktywne)
	{
	case 1:
		dwie_proste(ktora);
		break;
	case 2:
		katy(ktora);
		break;
	case 3:
		plipr(ktora);
		break;
	case 4:
		ptrzy(ktora);
		break;
	case 5:
		trzy_plaszcz(ktora);
		break;
	case 6:
		pdwie(ktora);
		break;
	case 7:
		kwadrat(ktora);
		break;
	}
}
void Keyboard( unsigned char key, int x, int y )
{
    // klawisz +
    if( key == '+' )
         scale += 0.05;
    else
    
    // klawisz -
    if( key == '-' && scale > 0.1 )
         scale -= 0.05;

	if(key == 'q')
		*dax-=dx;
	if(key == 'w')
		*dax+=dx;
	if(key == 'a')
		*day-=dx;
	if(key == 's')
		*day+=dx;
	if(key == 'z')
		*daz-=dx;
	if(key == 'x')
		*daz+=dx;

	if(key == 'e')
		*dbx-=dx;
	if(key == 'r')
		*dbx+=dx;
	if(key == 'd')
		*dby-=dx;
	if(key == 'f')
		*dby+=dx;
	if(key == 'c')
		*dbz-=dx;
	if(key == 'v')
		*dbz+=dx;

	
    switch(aktywne)
	{
	case 1:
		dwie_proste(ktora);
		break;
	case 2:
		katy(ktora);
		break;
	case 3:
		plipr(ktora);
		break;
	case 4:
		ptrzy(ktora);
		break;
	case 5:
		trzy_plaszcz(ktora);
		break;
	case 6:
		pdwie(ktora);
		break;
	case 7:
		kwadrat(ktora);
		break;
	}
    // odrysowanie okna
    glutPostRedisplay();
}

int submenu1,submenu2,submenu3,submenu4,submenu5,submenu6,submenu7;
char * doubletochar(double zmienna)
{
	int ujemna=0;
	if (zmienna<0){ujemna=1;zmienna*=(-1);}

	int i=0,j=0;
	long int calk=0;
	int ilec=0,iler=0;
	float reszta,sth;
	i=calk=zmienna;//static_cast<int>(zmienna);
	sth=reszta=zmienna-calk;//static_cast<double>(calk);
	
	while(calk>0)
	{
		ilec++;
		calk=calk/10;
	}
	while(reszta!=0)
	{
		reszta=reszta*10;
		iler++;
		calk=static_cast<int>(reszta);
		reszta-=calk;
	}
	char * str;
	str=new char[ilec+iler+3];
	for(int li=0;li<ilec+iler+3;li++)
			str[li]=NULL;
	j=0;
	calk=i;
	reszta=sth;
	if(ujemna){str[j]='-';j++;}
	int podziel=pow((double)10,(double)ilec-j-1);
	int temp;
	while(calk>0)
	{			
		temp=static_cast<int>(calk/podziel);
			str[j]=static_cast <char>(temp+48);
			calk -= temp*(podziel);
		
			podziel/=10;
			j++;
	}
	if(j<ilec||ilec==0)
		{str[j]='0'; j++;}
	if(j<ilec)
		{str[j]='0'; j++;}
	str[j]='.';
	j++;
	while(reszta!=0)
	{
		reszta*=10;
		
		calk=reszta;
		reszta-=calk;
		str[j]=static_cast <char>(calk+48);
		j++;
	}
	str[j]=NULL;


	return str;
}
double wyznacznik(double ** tab, double * wektor, int ktora)
{
	if (ktora)
	{
		for(int i=0;i<3;i++)
			tab[ktora-1][i]=wektor[i];
	}
	double det=0;

	det=tab[1][1]*tab[2][2]*tab[0][0] + tab[0][1]*tab[1][2]*tab[2][0] + tab[0][2]*tab[1][0]*tab[2][1]
		-tab[0][2]*tab[1][1]*tab[2][0] - tab[0][0]*tab[1][2]*tab[2][1] - tab[0][1]*tab[1][0]*tab[2][2];
	return det;
	
}
//////////////////////////////////////////////////////////////////////////
punkt a(0.5,1),b(-1,-1),a1(0.5,-1),b1(-1,1);	
void dwie_proste(int zmien)
{

	switch (zmien)
 {
  case 1:
  dax=&a.x;
  day=&a.y;
  dbx=&b.x;
  dby=&b.y;
   ktora=1;
   dx=0.05;
  break;
  case 2:
  dax=&a1.x;
  day=&a1.y;
  dbx=&b1.x;
  dby=&b1.y;
   ktora=2;
   dx=0.05;
  break;
 }

scale = 0.5;
rotatex = 0.0;
rotatey = 0.0;
translatex = 0.0;
translatey = 0.0;
button_state = GLUT_UP;
	aktywne=1;
	punkt przec;
	double mi=0,fi=0,dmi=0;
	double delta=0;
	delta=(b.x-a.x)*(a1.y-b1.y)-(a1.x-b1.x)*(b.y-a.y);
	if(delta!=0)
	{
		dmi=(a1.x-a.x)*(a1.y-b1.y)-(a1.x-b1.x)*(a1.y-a.y);
		mi=dmi/delta;
	}
	przec.x=(1-mi)*a.x+b.x*mi;
	przec.y=(1-mi)*a.y+b.y*mi;

    glColor3f( 0.0, 0.0, 0.0 );

	glBegin( GL_LINES );
		glVertex2f(a.x,a.y);
		glVertex2f(b.x,b.y);
	glEnd();

	glBegin( GL_LINES );
		glVertex2f(a1.x,a1.y);
		glVertex2f(b1.x,b1.y);
	glEnd();


	char * napis,* dnapis;

	int i=0;
	napis=doubletochar(przec.x);
	dnapis=doubletochar(przec.y);

	double x,y;
	x=0;//przec.x+0.1;
	y=0;//przec.y;
	i=0;
	int j=0;
	while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ',');
	 x+=0.03;
	while(j<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, dnapis[j]);
	 x+=0.03;
	 j++;
	}

	glutSwapBuffers();
}

punkt s(0.5,1),d(-1,-1),f(0.5,-1),g(-1,1);	
void  katy(int zmien)
{
	switch (zmien)
 {
  case 1:
  dax=&s.x;
  day=&s.y;
  dbx=&d.x;
  dby=&d.y;
   ktora=1;
   dx=0.05;
  break;
  case 2:
  dax=&f.x;
  day=&f.y;
  dbx=&g.x;
  dby=&g.y;
   ktora=2;
   dx=0.05;
  break;
 }

	scale = 0.5;
rotatex = 0.0;
rotatey = 0.0;
translatex = 0.0;
translatey = 0.0;
button_state = GLUT_UP;
	aktywne=2;
	punkt przec;
	double mi=0,fi=0,dmi=0;
	double delta=0;
	delta=(d.x-s.x)*(f.y-g.y)-(f.x-g.x)*(d.y-s.y);
	if(delta!=0)
	{
		dmi=(f.x-s.x)*(f.y-g.y)-(f.x-g.x)*(f.y-s.y);
		mi=dmi/delta;
	}
	przec.x=(1-mi)*s.x+d.x*mi;
	przec.y=(1-mi)*s.y+d.y*mi;

	punkt aa,bb;
	aa.x=s.x-przec.x;
	aa.y=s.y-przec.y;
	bb.x=f.x-przec.x;
	bb.y=f.y-przec.y;

	 glColor3f( 0.0, 0.0, 0.0 );
	glBegin( GL_LINES );
		glVertex2f(s.x,s.y);
		glVertex2f(d.x,d.y);
	glEnd();

	glBegin( GL_LINES );
		glVertex2f(f.x,f.y);
		glVertex2f(g.x,g.y);
	glEnd();

	double q,w,e;
	q=sqrt(aa.x*aa.x+aa.y*aa.y);
	w=sqrt(bb.x*bb.x+bb.y*bb.y);
	e=sqrt((aa.x-bb.x)*(aa.x-bb.x)+(aa.y-bb.y)*(aa.y-bb.y));
	double kat;
	kat=((-pow(e,2))+pow(q,2)+pow(w,2))/(2*q*w);
	kat=acos(kat)* 180.0 / PI;
	char * napis;

	int i=0;
	napis=doubletochar(kat);
	double x,y;
	x=0;//przec.x+0.1;
	y=0;//przec.y;
	i=0;
	while(i<6)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 //x+=glutBitmapWidth(GLUT_BITMAP_9_BY_15,napis[i+1]);
	 i++;
	}
	glutSwapBuffers();
}

punkt3d wpr(1,1,0),pr(0,0,0),wpl(1,0,0),pl(1,0,0);
void plipr(int zmien)
{

	switch (zmien)
 {
  case 1:
   dax=&wpl.x;
  day=&wpl.y;
  daz=&wpl.z;
  dbz=&pl.z;
  dbx=&pl.x;
  dby=&pl.y;
   ktora=1;
   dx=0.05;
  break;
  case 2:
  dax=&wpr.x;
  day=&wpr.y;
  daz=&wpr.z;
  dbz=&pr.z;
  dbx=&pr.x;
  dby=&pr.y;
   ktora=2;
   dx=0.05;
  break;
 }

	scale = 0.5;
rotatex = 0.0;
rotatey = 0.0;
translatex = 0.0;
translatey = 0.0;
button_state = GLUT_UP;
	aktywne=3;
    	punkt3d przec;
   
    glColor3f( 0.0, 0.0, 0.0 );

				//rysujemy prost¹
	glBegin(GL_LINES);
		glVertex3f(pr.x+2*wpr.x , pr.y+2*wpr.y , pr.z+2*wpr.z);
		glVertex3f(pr.x-2*wpr.x , pr.y-2*wpr.y , pr.z-2*wpr.z);
	glEnd();
				//rysujemy plaszczyznê

	double prostopadle;
	prostopadle=wpl.x*wpr.x + wpl.y*wpr.y + wpl.z*wpr.z; //jezeli prostopadle to rowne 0 i mie ma punktów wspolnych
	double D=0,t=0,temp=0;

	if(prostopadle)
	{
		D=-wpl.x*pl.x -wpl.y*pl.y -wpl.z*pl.z;
		t+=wpl.x*wpr.x;
		temp+=wpl.y*pr.y;
			t+=wpl.y*wpr.y;
			temp+=wpl.y*pr.y;
		t+=wpl.z*wpr.z;
		temp+=wpl.z*pr.z;
		
		temp+=D;
		temp*=(-1);
		t=t/temp;
		przec.x=pr.x+t*wpr.x;
		przec.y=pr.y+t*wpr.y;
		przec.z=pr.z+t*wpr.z;
	

	char* napis;
	int i=0;
	napis=doubletochar(przec.x);

	double x,y;
	x=0;//przec.x+0.1;
	y=0;//przec.y;
	i=0;
	while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
			 glRasterPos2f(x,y);
			 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ',');
			 x+=0.03;
	 i=0;
	 napis=doubletochar(przec.y);
	 while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
			 glRasterPos2f(x,y);
			 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ',');
			 x+=0.03;
	  i=0;
	 napis=doubletochar(przec.z);
	 while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
	}
	glutSwapBuffers();
	
}

punkt3d j(1,0,0),k(0,1,0),l(0,0,1);
void ptrzy (int zmien)
{
switch (zmien)
 {
  case 1:
  dax=&j.x;
  day=&j.y;
  daz=&j.z;
   ktora=1;
   dx=0.05;
  break;

  case 2:
  dax=&k.x;
  day=&k.y;
  daz=&k.z;
   ktora=2;
   dx=0.05;
  break;

  case 3:
  dax=&l.x;
  day=&l.y;
  daz=&l.z;
   ktora=3;
   dx=0.05;
  break;
}

	scale = 0.5;
rotatex = 0.0;
rotatey = 0.0;
translatex = 0.0;
translatey = 0.0;
button_state = GLUT_UP;
	aktywne=4;
	glColor3f( 0.0, 0.0, 0.0 );
	glBegin(GL_LINE_LOOP);
		glVertex3f(j.x,j.y,j.z);
		glVertex3f(k.x,k.y,k.z);
		glVertex3f(l.x,l.y,l.z);
	glEnd();
	punkt3d b_a(k.x-j.x,k.y-j.y,k.z-j.z);
	punkt3d c_a(l.x-j.x,l.y-j.y,l.z-j.z);

	punkt3d bxc(b_a.y*c_a.z - c_a.y*b_a.z,
				  b_a.z*c_a.x - b_a.x*c_a.z,
				  b_a.x*c_a.y - b_a.y*c_a.x);
	double * tab;
	tab=new double [4];
	tab[0]=bxc.x;
	tab[1]=bxc.y;
	tab[2]=bxc.z;
	tab[3]=bxc.x*j.x + bxc.y*j.y + bxc.z*j.z;

	char* napis;
	int i=0;
	napis=doubletochar(tab[0]);

	double x,y;
	x=0;//przec.x+0.1;
	y=0;//przec.y;
	i=0;
	while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
				 glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'x');
				 x+=0.03;
				  glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '+');
				 x+=0.03;
	i=0;
	napis=doubletochar(tab[1]);
	while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
				 glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'y');
				 x+=0.03;
				  glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '+');
				 x+=0.03;
  i=0;
	napis=doubletochar(tab[2]);
	while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
				 glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'z');
				 x+=0.03;
				  glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '+');
				 x+=0.03;
	i=0;
	napis=doubletochar(tab[3]);
	while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
				 glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
				 x+=0.03;
				  glRasterPos2f(x,y);
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
				 x+=0.03;
				

	glutSwapBuffers();
}

punkt3d n1(1,1,1),pu1(1,0,0),n2(1,-1,1),pu2(1,0,0),n3(-1,1,1),pu3(1,0,0);
void trzy_plaszcz(int zmien)
{ 
	
switch (zmien)
 {
  case 1:
  dax=&n1.x;
  day=&n1.y;
  daz=&n1.z;
  dbz=&pu1.z;
  dbx=&pu1.x;
  dby=&pu1.y;
   ktora=1;
   dx=0.05;
  break;
  case 2:
  dax=&n2.x;
  day=&n2.y;
  daz=&n2.z;
  dbz=&pu2.z;
  dbx=&pu2.x;
  dby=&pu2.y;
   ktora=2;
   dx=0.05;
  break;
  case 3:
  dax=&n3.x;
  day=&n3.y;
  daz=&n3.z;
  dbz=&pu3.z;
  dbx=&pu3.x;
  dby=&pu3.y;
   ktora=3;
   dx=0.05;
  break;
 }

	scale = 0.5;
rotatex = 0.0;
rotatey = 0.0;
translatex = 0.0;
translatey = 0.0;
button_state = GLUT_UP;
	aktywne=5;
	double ** tab;
	tab=new double*[3];
	for (int i=0;i<3;i++)
		tab[i]=new double[3];//[n]X[m] n-wiersz m-kolumna
	tab[0][0]=n1.x;
		tab[0][1]=n1.y;
			tab[0][2]=n1.z;
	tab[1][0]=n2.x;
		tab[1][1]=n2.y;
			tab[1][2]=n2.z;
	tab[2][0]=n3.x;
		tab[2][1]=n3.y;
			tab[2][2]=n3.z;
	double * wektor;
	wektor = new double[3];
	wektor[0]=n1.x*pu1.x + n1.y*pu1.y + n1.z*pu1.z;
	wektor[1]=n2.x*pu2.x + n2.y*pu2.y + n2.z*pu2.z;
	wektor[2]=n3.x*pu3.x + n3.y*pu3.y + n3.z*pu3.z;
	punkt3d pkt;
	double W=0,Wx=0,Wy=0,Wz=0;
	W=wyznacznik(tab,wektor,0);
	if(W)
	{
		Wx=wyznacznik(tab,wektor,1);
		Wy=wyznacznik(tab,wektor,2);
		Wz=wyznacznik(tab,wektor,3);
		pkt.x=Wx/W;
		pkt.y=Wy/W;
		pkt.z=Wz/W;
	}

 glColor3f( 0.0, 0.0, 0.0 );
	char* napis;
	int i=0;
	napis=doubletochar(pkt.x);

	double x,y;
	x=0;//przec.x+0.1;
	y=0;//przec.y;
	i=0;
	while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
			 glRasterPos2f(x,y);
			 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ',');
			 x+=0.03;
	 i=0;
	 napis=doubletochar(pkt.y);
	 while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}
			 glRasterPos2f(x,y);
			 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ',');
			 x+=0.03;
	  i=0;
	 napis=doubletochar(pkt.z);
	 while(i<5)
	{
	 glRasterPos2f(x,y);
	 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, napis[i]);
	 x+=0.03;
	 i++;
	}

	 glutSwapBuffers();
}

punkt3d nn1(1,1,1),pp1(1,0,0),nn2(1,-1,1),pp2(0,0,1);
void pdwie(int zmien)
{
	switch (zmien)
 {
  case 1:
  dax=&nn1.x;
  day=&nn1.y;
  daz=&nn1.z;
  dbz=&pp1.z;
  dbx=&pp1.x;
  dby=&pp1.y;
   ktora=1;
   dx=0.05;
  break;
  case 2:
  dax=&nn2.x;
  day=&nn2.y;
  daz=&nn2.z;
  dbz=&pp2.z;
  dbx=&pp2.x;
  dby=&pp2.y;
   ktora=2;
   dx=0.05;
   break;
	}

	scale = 0.5;
rotatex = 0.0;
rotatey = 0.0;
translatex = 0.0;
translatey = 0.0;
button_state = GLUT_UP;
	aktywne=6;
	double ** tab;
	tab=new double*[3];
	for (int i=0;i<3;i++)
		tab[i]=new double[3];//[n]X[m] n-wiersz m-kolumna
	tab[0][0]=nn1.x;
		tab[0][1]=nn1.y;
			tab[0][2]=nn1.z;
	tab[1][0]=nn2.x;
		tab[1][1]=nn2.y;
			tab[1][2]=nn2.z;
	tab[2][0]=nn1.y*nn2.z - nn1.z*nn2.y;
		tab[2][1]=nn1.z*nn2.x - nn1.x*nn2.z;
			tab[2][2]=nn1.x*nn2.y - nn1.y*nn2.x;

			double * wektor;
	wektor = new double[3];
	wektor[0]=nn1.x*pp1.x + nn1.y*pp1.y + nn1.z*pp1.z;
	wektor[1]=nn2.x*pp2.x + nn2.y*pp2.y + nn2.z*pp2.z;
	wektor[2]=0;

	punkt3d bxc(nn1.y*nn2.z - nn2.y*nn1.z,
				  nn1.z*nn2.x - nn1.x*nn2.z,
				  nn1.x*nn2.y - nn1.y*nn2.x); //iloczyn wektorowy

	punkt3d *pkt;
	pkt=new punkt3d[2];
	pkt[0]=bxc;
	double W=0,Wx=0,Wy=0,Wz=0;
	W=wyznacznik(tab,wektor,0);
	if(W)
	{
		Wx=wyznacznik(tab,wektor,1);
		Wy=wyznacznik(tab,wektor,2);
		Wz=wyznacznik(tab,wektor,3);
		pkt[1].x=Wx/W;
		pkt[1].y=Wy/W;
		pkt[1].z=Wz/W;
	}
	
}

void kwadrat(int zmien)
{
	aktywne=7;
	 // kolor t³a - zawartoœæ bufora koloru
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    
    // czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );
    
    // wybór macierzy modelowania
    glMatrixMode( GL_MODELVIEW );
    
    // macierz modelowania = macierz jednostkowa
    glLoadIdentity();
    
    // przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
   // glTranslatef( 0, 0, -( near + far ) / 2 );
    
    // przesuniêcie obiektu - ruch myszk¹
    glTranslatef( translatex, translatey, 0.0 );
    
    // skalowanie obiektu - klawisze "+" i "-"
    glScalef( scale, scale, scale );
    
    // obroty obiektu - klawisze kursora
   glRotatef( rotatex, 1.0, 0, 0 );
    glRotatef( rotatey, 0, 1.0, 0 );


	glBegin(GL_LINE_LOOP);               // rysujemy szeœcian

     
	  // œciana F - z do³u
      glColor3f(  1.0f, 1.0f, 0.5f);
      glVertex3f(-1.0f,-1.0f, 1.0f);
      glVertex3f( 1.0f,-1.0f, 1.0f);
      glVertex3f( 1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);	
	 glEnd();   
	 	glBegin(GL_LINE_LOOP); 
      // œciana B - z prawej
      glColor3f(  0.5f, 0.0f, 1.0f);
      glVertex3f( 1.0f, 1.0f, 1.0f);
      glVertex3f( 1.0f, 1.0f,-1.0f);
      glVertex3f( 1.0f,-1.0f,-1.0f);
      glVertex3f( 1.0f,-1.0f, 1.0f);
 glEnd(); 
 	glBegin(GL_LINE_LOOP); 
      // œciana C - z ty³u
      glColor3f(  0.5f, 0.5f, 1.0f);
      glVertex3f( 1.0f, 1.0f,-1.0f);
      glVertex3f(-1.0f, 1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f( 1.0f,-1.0f,-1.0f);
 glEnd(); 
 	glBegin(GL_LINE_LOOP); 
      // œciana D - z lewej
      glColor3f(  0.0f, 1.0f, 0.5f);
      glVertex3f(-1.0f, 1.0f, 1.0f);
      glVertex3f(-1.0f, 1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);
 glEnd(); 
 	glBegin(GL_LINE_LOOP); 
      // œciana E - z góry
      glColor3f(  1.0f, 0.5f, 0.5f);
      glVertex3f(-1.0f, 1.0f,-1.0f);
      glVertex3f( 1.0f, 1.0f,-1.0f);
      glVertex3f( 1.0f, 1.0f, 1.0f);
      glVertex3f(-1.0f, 1.0f, 1.0f);

  glEnd();    
  	glBegin(GL_LINE_LOOP); 
	   // œciana A - z przodu
      glColor3f(  0.0f, 0.5f, 0.0f);
      glVertex3f(-1.0f, 1.0f, 1.0f);
      glVertex3f( 1.0f, 1.0f, 1.0f);
      glVertex3f( 1.0f,-1.0f, 1.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);

    glEnd(); 
	glFlush();
	glutSwapBuffers();
}

///////////////////////////////////////////

void czekaj(int val)
{glutPostRedisplay();}


void rysuj ()
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );
	//przec=dwie_proste(p1,p2,p3,p4);

	//kat=katy(p1,p2,p3,p4);
	//punkt3d wpr(1,1,0),pr(0,0,0),wpl(1,0,0),pl(1,0,0),pip;
	//pip=plipr(wpl,pl,wpr,pr);
	
	//rownanie=ptrzy(a,b,c);

	//trzy = trzy_plaszcz(n1,pu1,n2,pu2,n3,pu3);
	
	//dwie=pdwie(n1,pu1,n2,pu2);

	//kwadrat(1);

	glutTimerFunc(100,czekaj,0);
	glFlush();
}

int main(int argc, char* argv[])
{
	 glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600,600);
    glutCreateWindow ("graf");

	// do³¹czenie funkcji obs³ugi klawiatury
    glutKeyboardFunc( Keyboard );

	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
    glutSpecialFunc( SpecialKeys );
    
    // obs³uga przycisków myszki
    glutMouseFunc( MouseButton );
    
    // obs³uga ruchu kursora myszki
    glutMotionFunc( MouseMotion );
	glutDisplayFunc(rysuj);


	submenu1 = glutCreateMenu(dwie_proste);
 glutAddMenuEntry("Zmien pierwsza prosta", 1);
 glutAddMenuEntry("Zmien druga prosta", 2);

 submenu2 = glutCreateMenu(katy);
 glutAddMenuEntry("Zmien pierwsza prosta", 1);
 glutAddMenuEntry("Zmien druga prosta", 2);
  
 submenu3 = glutCreateMenu(plipr);
 glutAddMenuEntry("Zmien plaszczyzne", 1);
 glutAddMenuEntry("Zmien prosta", 2);

 submenu4 = glutCreateMenu(ptrzy);
 glutAddMenuEntry("Zmien pierwszy punkt", 1);
 glutAddMenuEntry("Zmien drugi punkt", 2);
 glutAddMenuEntry("Zmien trzeci punkt", 3);

 submenu5 = glutCreateMenu(trzy_plaszcz);
 glutAddMenuEntry("Zmien pierwsza plaszczyzne", 1);
 glutAddMenuEntry("Zmien druga plaszczyzne", 2);
 glutAddMenuEntry("Zmien trzeci¹ plaszczyzne", 3);

 submenu6 = glutCreateMenu(pdwie);
 glutAddMenuEntry("Zmien pierwsza plaszczyzne", 1);
 glutAddMenuEntry("Zmien druga plaszczyzne", 2);

 submenu7 = glutCreateMenu(kwadrat);
 glutAddMenuEntry("Zmien kwadrat", 1);


	glutCreateMenu(czekaj);
  glutAddSubMenu("Punkt przeciêcia prostych", submenu1);
   glutAddSubMenu("K¹t miêdzy prostymi", submenu2);
    glutAddSubMenu("Punkt przeciêcia prostej i p³aszczyzny", submenu3);
	 glutAddSubMenu("P³aszczyzna za trzech punktach", submenu4);
	  glutAddSubMenu("Punkt przeciêcia trzech p³aszczyzn", submenu5);
	   glutAddSubMenu("Prosta wspólna dla dwóch plaszczyzn", submenu6);
	    glutAddSubMenu("Kwadrat", submenu7);


	glutAttachMenu( GLUT_RIGHT_BUTTON );
	
	glutMainLoop();
	return 0;
}




