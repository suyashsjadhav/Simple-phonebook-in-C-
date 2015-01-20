
#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>
#include<graphics.h>
#include<dos.h>
 union REGS in,out;

	 int callmouse()
	  {
		 in.x.ax=1;
		 int86(51,&in,&out);
		 return 1;
	  }
	void mouseposi(int &xpos,int &ypos,int &click)
       {
	      in.x.ax=3;
	      int86(51,&in,&out);
	      click=out.x.bx;
	      xpos=out.x.cx;
	      ypos=out.x.dx;
	}

	 void restrictmouseptr(int x1,int y1,int x2,int y2)
	  {
		 in.x.ax=7;
		 in.x.cx=x1;
		 in.x.dx=x2;
		 int86(51,&in,&out);
		 in.x.ax=8;
		 in.x.cx=y1;
		 in.x.dx=y2;
		 int86(51,&in,&out);
	  }

int max=101;
int cntr=0;
 struct s1
 {
	int total,records;
 };
 struct s2
 {
	char key_name[20];
	double address;
 };
 struct s3
 {
	char key_name[20];
	char phn_no[20];

 };

 class stud
 {
	s1 a;
	s2 b;
	s3 c;
	public:
		stud()
		{
			a.total=max;
			a.records=0;
			strcpy(b.key_name,"DEFAULT");
			b.address=-1;
			strcpy(c.phn_no,"0000000000");
			strcpy(c.key_name,"DEFAULT");
		}

		void insert();
		void display();
		void search();
		void edit();
		void sort();
 };
 void stud::edit()
 {

	fstream f;
	f.open("phnbook.dat",ios::in|ios::out|ios::binary);
	if(!f)
	{
	cout<<"\nFile creation error in Edit!!";
	getch();
	}
	f.seekg(0,ios::beg);
	f.read((char *)&a,sizeof(a));
	cntr=a.records;
	cout<<"\nEnter the name to Edit ::";
	char nm[20];
	cin>>nm;
	for(int j=0;j<cntr;j++)
	{
		f.seekg(sizeof(a)+sizeof(b)*j,ios::beg);
		f.read((char *)&b,sizeof(b));
		if(strcmp(nm,b.key_name)==0)
		break;
	}
	if(j==cntr)
	cout<<"\nContact don't Exist!!!";
	else
	{
	 cout<<"\nEditing contact with name :: "<<b.key_name;
	 cout<<"\nEnter name::";
	 cin>>c.key_name;
	 strcpy(b.key_name,c.key_name);
	 cout<<"\nEnter Phone no.::";
	 cin>>c.phn_no;
	 f.seekp(sizeof(a)+sizeof(b)*j,ios::beg);
	 f.write((char *)&b,sizeof(b));
	 f.seekp(b.address,ios::beg);
	 f.write((char *)&c,sizeof(c));

	}
      f.close();


 }
 void stud::insert()
 {
	fstream f;
	f.open("phnbook.dat",ios::out|ios::in|ios::binary);
	if(!f)
	cout<<"\nFile creation error in Insert!!!";

	f.seekg(0,ios::beg);
	f.read((char *)&a,sizeof(a));

	a.records++;
	cntr=a.records-1;
	f.seekp(0,ios::beg);
	f.write((char *)&a,sizeof(a));
	cout<<"\nEnter the Name ::";
	cin>>c.key_name;
	strcpy(b.key_name,c.key_name);
	b.address=(sizeof(a)+(max*sizeof(b))+((cntr)*sizeof(c)));
	cout<<"\nEnter the Phone no ::";
	cin>>c.phn_no;
	f.seekp(sizeof(a)+((cntr)*sizeof(b)),ios::beg);
	f.write((char *)&b,sizeof(b));
	f.seekp(sizeof(a)+sizeof(b)*max+sizeof(c)*cntr,ios::beg);
	f.write((char *)&c,sizeof(c));
       f.close();
 }
 void stud::display()
 {
	fstream f;
	f.open("phnbook.dat",ios::in|ios::binary);
	if(!f)
	{
	cout<<"\nFile creation error in Dispaly!!!";
	getch();
	}
	f.seekg(0,ios::beg);
	f.read((char *)&a,sizeof(a));
	cout<<"\nMax Contacts:: "<<a.total-1;
	cout<<"\tContaats present:: "<<a.records<<"\t\n\n";
	cout<<"\nContacts Present::\n";
	cntr=a.records;
	for(int j=cntr-1;j>=0;j--)
	{
		f.seekg(sizeof(a)+sizeof(b)*j,ios::beg);
		f.read((char *)&b,sizeof(b));
		f.seekg(b.address,ios::beg);
		f.read((char *)&c,sizeof(c));
		cout<<"\nName::"<<c.key_name;
		cout<<"\tPhone No::"<<c.phn_no;
	}

      f.close();
 }
void stud::search()
{
  fstream f;

  f.open("phnbook.dat",ios::in|ios::binary);
  if(!f)
  {
	cout<<"\nError in file creation in search!!!" ;
	return;
  }

int i=0,flag;
  while(1)
  {


  char chr,ch[20];
  flag=0;

  chr=getch();
  clrscr();
  cout<<"\nEnter the Name ::";
  ch[i]=chr;
  cout<<ch;

  if(chr==13)
  return;
  for(int j=0;j<cntr;j++)
  {
   f.seekg(sizeof(a)+sizeof(b)*j,ios::beg);
   f.read((char *)&b,sizeof(b));
   if(b.key_name[i]==chr)
   {
   f.seekg(b.address,ios::beg);
   f.read((char *)&c,sizeof(c));
   cout<<"\nName::"<<c.key_name;
   cout<<"\tPhone no.::"<<c.phn_no;
   flag=1;
   }
  }
  if(flag==0)
  {
   clrscr();
   cout<<"\nRecord with this Contact Name do not exist!!!!";
   getch();
   return;
  }
  i++;

  }

}
void stud::sort()
{
   fstream f;
   f.open("phnbook.dat",ios::in|ios::out|ios::binary);
   f.seekg(0,ios::beg);
   f.read((char *)&a,sizeof(a));
   cntr=a.records;
   s2 s;
   for(int i=0;i<cntr;i++)
  {
  for(int j=0;j<cntr-i;j++)
   {
    f.seekg(sizeof(a)+sizeof(b)*j,ios::beg);
    f.read((char *)&b,sizeof(b));
    f.seekg(sizeof(a)+sizeof(b)*(j+1),ios::beg);
    f.read((char *)&s,sizeof(b));
    if(strcmp(s.key_name,b.key_name)>0)
    {
      f.seekp(sizeof(a)+sizeof(b)*(j+1),ios::beg);
      f.write((char *)&b,sizeof(b));
      f.seekp(sizeof(a)+sizeof(b)*j,ios::beg);
      f.write((char *)&s,sizeof(b));


    }
   }
  }
 f.close();
}

 void main()
 {
	stud s;

	clrscr();

    while(1)
    {
	s.sort();
	clrscr();
	int i;
	int x,y,cl=0;
	int g=DETECT,m;
	initgraph(&g,&m," ");
	cout<<"\n\n\n\n";
	s.display();
		 while(cl!=1)
		 {
		 rectangle(10,10,110,50);
		 rectangle(100,10,210,50);
		 rectangle(200,10,310,50);
		 rectangle(300,10,410,50);
		 rectangle(400,10,510,50);
		 gotoxy(5,3);
		 cout<<"Insert";
		 gotoxy(17,3);
		 cout<<"Display";
		 gotoxy(30,3);
		 cout<<"Search";
		 gotoxy(42,3);
		 cout<<"Edit";
		 gotoxy(55,3);
		 cout<<"Exit";
		 mouseposi(x,y,cl);
		 callmouse();
		 restrictmouseptr(10,10,510,50);
		 }

		 closegraph();
	if(x<100&&cl==1)
	i=1;
	else
	if(x<200&&cl==1)
	i=2;
	else
	if(x<300&&cl==1)
	i=3;
	else
	if(x<400&&cl==1)
	i=4;
	else
	i=5;
	switch(i)
	{
		case 1:
			if(cntr==max-1)
			{
				cout<<"\nPhone Book Full!!!!\nPress any key_name!!";
				getch();
				break;
			 }

			s.insert();
			break;
		 case 2:
			s.display();
			getch();
			break;
		 case 3:
			cout<<"\nEnter the name::";
			s.search();
			 break;

		 case 4:
			s.edit() ;
			break;
		 case 5:
			exit(0);
	}

    }
 }