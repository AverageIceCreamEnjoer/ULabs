// ���������� ������������� �������� ����������� ������ shift � �������� scale 
// �������� ����� form �������� (������������ ��� ������������� � �������� ��������������)
#include <fstream>
#include <math.h>
#include <time.h>		
#define MAXDOUBLE 1e300 // MAXDOUBLE - ������� ������
using namespace std; 
const double pi=3.14159265358979;
// ������� ���������� ��������� ����������� ������������� � ����� �
double density(double x, double form=0, double scale=1, double shift=0)
{
	if(scale<=0)return MAXDOUBLE;
	return exp(-0.5*(x-shift)*(x-shift)/(scale*scale))/(sqrt(2.*pi)*scale);
}
// ������� ���������� ������������� ����������� �������������: 
// M - �����������, D - ���������, g1 - ����������� ����������, g2 - ����������� ��������
void moments(double &M, double &D, double &g1, double &g2, double form=0, double scale=1, double shift=0)
{
	M=shift;
	D=(scale<=0)?MAXDOUBLE:scale*scale;
	g1=0.;g2=3.;
}
// ������� ������������� ����������� �� ��������� (0,1) ��������� �������
double Rav(){
	double r; 
	do r=(double)rand()/RAND_MAX; while(r==0.||r==1.);
	return r;
}
// ������� ������������� ���������� ��������� ������� (������� �����-�������)
double randNum(double form=0, double scale=1, double shift=0)
{
	if(scale<=0)return MAXDOUBLE;
	return shift+scale*sqrt(-2*log(Rav()))*sin(2.*pi*Rav());
}
// ������ ������ ������� ����������� �������������
int main()
{
	const int n=100000;
	srand((unsigned)time(0));
	ofstream out("test.txt");
	double data[n];
	double form=0,scale=2,shift=1,M,D,G1,G2;
	// ���������� ������ - ��������� �������
	for(int i=0;i<n;i++)data[i]=randNum(form,scale,shift);
	// ��������� � ������������� ��������� � ������ �������
	for(int i=0;i<n;i++)out<<data[i]<<'\t'<<density(data[i],form,scale,shift)<<endl;
	// ��������� � ������������� �������� ��������������
	moments(M,D,G1,G2,form,scale,shift);
	out<<M<<'\t'<<D<<'\t'<<G1<<'\t'<<G2<<endl;
	// ��������� ������� ������������� - ��������� � ������������� ���������� ��������������
	double m=0,d=0,g1=0,g2=0;
	for(int i=0;i<n;i++)m+=data[i];
	m/=n;
	for(int i=0;i<n;i++)
	{
		double t=data[i]-m,t2=t*t;
		d+=t2;
		g1+=t2*t;
		g2+=t2*t2;
	}
	d/=n;
	g1/=n*pow(d,1.5);
	g2/=n*d*d;
	out<<m<<'\t'<<d<<'\t'<<g1<<'\t'<<g2<<endl;
	return 0;
}

