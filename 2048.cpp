#include <iostream>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

bool gameOver=false;
bool startGame=false;
const int ArrSize=4;
int x,y,score=0;
int Arr2048[ArrSize][ArrSize]={};

enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN}; //��������������� ��� eDirection
eDirection dir;									 // � ��� eDirection ��������� ����� dir


void randdigit2()    // ���������� � ���������� ���� ���� ����� 2
{
	for (int i=0;i<1;)		
	{
		x=rand()%ArrSize;
		y=rand()%ArrSize;
		if (Arr2048[y][x]==0)
		{
			int newDigit;
			newDigit=rand()%10;
			if (newDigit==4)
			{
				Arr2048[y][x]=4;
				i++;
			}				
			else
			{
				Arr2048[y][x]=2;
				i++;	
			}			
		}
	}
	bool game=false;
	for(int i=0;i<ArrSize;i++)   //�������� �� � �� ���� �������
		{
			for(int j=0;j<ArrSize;j++)
			{
				if (Arr2048[i][j]==0)
					game=true;
			}			
		}
	if (!game)   //���� ������ ������� ���� �� ����� ���
		gameOver = true;	
}

//*************************************************************

void colordigit(int Arr)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ����������
	switch(Arr)
	{		
		case 4: SetConsoleTextAttribute(hStdOut,2);break; //������ ���� ��� ������
		case 8: SetConsoleTextAttribute(hStdOut,3);break;
		case 16: SetConsoleTextAttribute(hStdOut,4);break;
		case 32: SetConsoleTextAttribute(hStdOut,5);break;
		case 64: SetConsoleTextAttribute(hStdOut,6);break;
		case 128: SetConsoleTextAttribute(hStdOut,9);break;
		case 256: SetConsoleTextAttribute(hStdOut,10);break;
		case 512: SetConsoleTextAttribute(hStdOut,11);break;
		case 1024: SetConsoleTextAttribute(hStdOut,12);break;
		case 2048: SetConsoleTextAttribute(hStdOut,13);break;
	}
}

//********************************************************

void draw()
{
system("cls");	
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ����������
SetConsoleTextAttribute(hStdOut,15);
	for(int i=0;i<ArrSize;i++)
	{
		for(int j=0;j<66;j++)
			{cout<<"|";}
		cout<<endl;	
		cout<<"|";		
		for(int j=0;j<ArrSize;j++)
			{cout<<"|\t"<<" "<<"\t|";}
		cout<<"|"<<endl;
		cout<<"|";
		for(int j=0;j<ArrSize;j++)
		{
			if (Arr2048[i][j]==0)
				{cout<<"|\t"<<" "<<"\t|";}
			else
			{
				cout<<"|\t";
				colordigit(Arr2048[i][j]);
				cout<<Arr2048[i][j];					
				SetConsoleTextAttribute(hStdOut,15);
				cout<<"\t|";
			}	
		}
		cout<<"|";							
		cout<<endl;
		cout<<"|";
		for(int j=0;j<ArrSize;j++)
			{cout<<"|\t"<<" "<<"\t|";}
		cout<<"|"<<endl;
	}
	for(int j=0;j<66;j++)
		{cout<<"|";}
	cout<<endl<<endl;
	for(int i=0;i<ArrSize;i++)
	{
		for(int j=0;j<ArrSize;j++)
		{
			if (score<Arr2048[i][j])
				{score=Arr2048[i][j];}
		}				
	}
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //������ ���� ��� ������
	cout<<"SCORE: "<<score<<endl;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY); //������ ���� ��� ������
	cout<<"Press SPACE - to EXIT"<<endl;
}

//********************************************************

void setup()
{
	srand(time(NULL));
	gameOver=false;
	dir=STOP;
	
	for(int i=0;i<ArrSize;i++)
		for(int j=0;j<ArrSize;j++)
			{Arr2048[i][j]=0;}	
	for (int i=0;i<2;)		
	{
		x=rand()%ArrSize;
		y=rand()%ArrSize;
		if (Arr2048[y][x]==0)
			{
				Arr2048[y][x]=2;
				i++;	
			}
	}	
	draw();
}

//********************************************************

void logic_lr()
{
	int y1,x1,z1;
	if(dir==LEFT)
	{x1=1; y1=0; z1=ArrSize-1;}
	if(dir==RIGHT)
	{x1=-1; y1=ArrSize-1; z1=0;}
		
	for(int i=0;i<ArrSize;i++)  //������ �� ����� ������/��������
	{
		if (Arr2048[i][0]!=0 && Arr2048[i][1]!=0 && Arr2048[i][2]!=0 && Arr2048[i][3]!=0)
			{continue;}
		if (Arr2048[i][0]==0 && Arr2048[i][1]==0 && Arr2048[i][2]==0 && Arr2048[i][3]==0)
			{continue;}
		else
		{						
			for(int j=y1;j!=z1;)
			{
				if (Arr2048[i][j]==0&&Arr2048[i][j+x1]==0)
					{j+=x1;continue;}
				if (Arr2048[i][j]!=0&&Arr2048[i][j+x1]!=0)
					{j+=x1;continue;}
				if (Arr2048[i][j]!=0&&Arr2048[i][j+x1]==0)
					{j+=x1;continue;}	
				if (Arr2048[i][j]==0&&Arr2048[i][j+x1]!=0)
				{
					Arr2048[i][j]=Arr2048[i][j+x1];
					Arr2048[i][j+x1]=0;	
					j=y1;															
				}							
			}				
		}
	}
	for(int i=0;i<ArrSize;i++)     //���������� �� ����� � ������� �����, ���� � �� ������ ��
	{
		for(int j=y1;j!=z1;)
		{						
			if(Arr2048[i][j]==Arr2048[i][j+x1])
			{
				Arr2048[i][j]=Arr2048[i][j]+Arr2048[i][j+x1];
				Arr2048[i][j+x1]=0;	
																				
				for(int h=y1;h!=z1;)
				{
					if (Arr2048[i][h]==0&&Arr2048[i][h+x1]==0)
						{h+=x1;continue;}
					if (Arr2048[i][h]!=0&&Arr2048[i][h+x1]!=0)
						{h+=x1;continue;}
					if (Arr2048[i][h]!=0&&Arr2048[i][h+x1]==0)
						{h+=x1;continue;}	
					if (Arr2048[i][h]==0&&Arr2048[i][h+x1]!=0)
					{
						Arr2048[i][h]=Arr2048[i][h+x1];
						Arr2048[i][h+x1]=0;
						h=y1;								
					}							
				}								
			}
			j+=x1;														
		}					
	}
	randdigit2();
	dir=STOP;
	draw();			
}

//********************************************************

void logic_ud()
{
	int y1,x1,z1;
	if(dir==UP)
	{x1=1; y1=0; z1=ArrSize-1;}
	if(dir==DOWN)
	{x1=-1; y1=ArrSize-1; z1=0;}
	
	for(int i=0;i<ArrSize;i++)   //������ �� ����� �����/����
	{
		if (Arr2048[0][i]!=0 && Arr2048[1][i]!=0 && Arr2048[2][i]!=0 && Arr2048[3][i]!=0)
			{continue;}
		if (Arr2048[0][i]==0 && Arr2048[1][i]==0 && Arr2048[2][i]==0 && Arr2048[3][i]==0)
			{continue;}
		else
		{						
			for(int j=y1;j!=z1;)
			{
				if (Arr2048[j][i]==0&&Arr2048[j+x1][i]==0)
					{j+=x1;continue;}
				if (Arr2048[j][i]!=0&&Arr2048[j+x1][i]!=0)
					{j+=x1;continue;}
				if (Arr2048[j][i]!=0&&Arr2048[j+x1][i]==0)
					{j+=x1;continue;}	
				if (Arr2048[j][i]==0&&Arr2048[j+x1][i]!=0)
					{
						Arr2048[j][i]=Arr2048[j+x1][i];
						Arr2048[j+x1][i]=0;	
						j=y1;															
					}							
			}				
		}
	}				
	for(int i=0;i<ArrSize;i++)    //���������� �� ����� � ������� �����, ���� � �� ������ ��
	{
		for(int j=y1;j!=z1;)
		{
			if(Arr2048[j][i]==Arr2048[j+x1][i])
			{
				Arr2048[j][i]=Arr2048[j][i]+Arr2048[j+x1][i];
				Arr2048[j+x1][i]=0;					
							
				for(int h=y1;h!=z1;)
				{
					if (Arr2048[j][i]==0&&Arr2048[j+1][i]==0)
						{h+=x1;continue;}
					if (Arr2048[j][i]!=0&&Arr2048[j+1][i]!=0)
						{h+=x1;continue;}
					if (Arr2048[j][i]!=0&&Arr2048[j+1][i]==0)
						{h+=x1;continue;}	
					if (Arr2048[j][i]==0&&Arr2048[j+1][i]!=0)
					{
						Arr2048[j][i]=Arr2048[j+1][i];
						Arr2048[j+1][i]=0;
						h=y1;																		
					}			
			}
		}
		j+=x1;													
		}					
	}
	randdigit2();
	dir=STOP;
	draw();
}

//********************************************************

void input()
{	
	if (_kbhit()) //�������� �� ��������� ���� �� ��������
	{
		switch(_getch()) //�������� �� ���� ��������� �� ��������
		{
			case (char)75:
			{
				dir=LEFT;
				logic_lr();
				break;	
			}		
			case (char)77:
			{
				dir=RIGHT;
				logic_lr();
				break;
			}				
			case (char)72:
			{
				dir=UP;
				logic_ud();
				break;
			}				
			case (char)80:
			{
				dir=DOWN;
				logic_ud();
				break;
			}				
			case (char)32: //���� �����
			{
				gameOver = true;
				break;
			}
		}
	}		
}

//********************************************************

void rezult()
{
	system("cls");
	startGame=false;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ����������
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY); //������ ���� ��� ������
	cout<<"��� ���i�����"<<endl;
	cout<<"��� ���������: "<<score<<endl;
	cout<<"��������� ��. "<<endl;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	while(!startGame)
	{
		if (_kbhit()) //�������� �� ��������� ���� �� ��������
		{
			if (_getch()==(char)13)  //�������� �� ��������� ENTER �� ��������
				{startGame=true;}		
		}
	}
}

//********************************************************

int main()
{
	setlocale(0, ""); //�������� ���� � ������
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ����������
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //������ ���� ��� ������
	cout<<"GAME 2048  v 1.0"<<endl;
	cout<<"by Oleksii Melnyk"<<endl<<endl;	
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout<<"������i�� ENTER ��� ������� ��� / Press ENTER to start GAME 2048!!!"<<endl;
	
	while(!startGame)
	{
		if (_kbhit()) //�������� �� ��������� ���� �� ��������
		{
			if (_getch()==(char)13)  //�������� �� ��������� ENTER �� ��������
				{startGame=true;}		
		}
	}
	system("cls");
	system ("color 07"); // ������������ ���� ���� ��� ������
	setup(); // �������� ���
	while(!gameOver)
	{
		input();  // ����� �� ���� ������� � ���������
	}
	rezult();
	return 0;
}
