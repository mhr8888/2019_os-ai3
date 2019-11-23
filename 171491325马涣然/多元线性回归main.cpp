#include <iostream>
#include<fstream>
#include<cmath>
const int sample = 28;//������ fish����Ϊ44 house_price����Ϊ28
const int feature = 13;//����ֵ�� fish����Ϊ4 house_price����Ϊ13
const int scaling = 10;//�������Ŵ�С fish����Ϊ100 house_price����Ϊ10
double a =0.001;//ѧϰ�� fish����Ϊ0.0002 house_price����Ϊ0.001
#define path "D:\house_price.txt"
using namespace std;
int main()
{
	double x[sample][feature] = { 0 };
	
	ifstream infile;
	infile.open(path);
	int i, j;
	if (!infile)
	{
		cout << "cannot open file" << endl;
		return -1;
	}
	for ( i = 0; i < sample ; i++)
	{
		for ( j = 0; j < feature; j++)
		{
			infile >> x[i][j];
			if (j == feature-1)
				x[i][j] = x[i][j] /scaling;
			if (j == 0)
				x[i][j] = 1;
			cout << x[i][j] << " ";
		}
		cout << endl;
	}
	infile.close();
	double J=0;//���ۺ���
	double Y[sample] = { 0 };//Ԥ�⺯��
	double temp[feature - 1] = { 0 }, t = 1, p[feature] = { 1 };//�û�����
	double w[feature-1] = {0};//ϵ������
	double hype;//��ֵ֤
	double A=0;//��ֵ֤����ʵֵ��ƽ������
	int cnt = 0;//��������
	double sum = 0, s[feature - 1] = { 0 };//��ͱ���
	cout << endl;
	cout <<"�����֤�����"<< endl;
	for (int  m = 0; m < sample; m++)
	{
		for (int n = 0; n < feature; n++)
		{
			p[n] = x[m][n]; 
			x[m][n] = 0;
			//��ȡһ��Ϊ���Լ�
	
			while (fabs(J - t) > 0.001)//�����ۺ����仯��Сʱ�˳�ѭ��
			{
				t = J;//������һ�����ۺ�����ֵ
				J = 0;//���ۺ�������
				for (i = 0; i < sample; i++)//��ÿ��������Ԥ�⺯��
				{
					sum = 0;
					for (j = 1; j < feature - 1; j++)//��ȥ��ֵ
					{
						sum += w[j] * x[i][j];
					}
					Y[i] = sum;
				}
				for (j = 0; j < feature - 1; j++)//�ݶ��½���
				{
					sum = 0;
					for (i = 0; i < sample; i++)
					{
						sum += (1.0 / (sample))*(Y[i] - x[i][feature - 1])*x[i][j];
						cnt++;
					}
					temp[j] = w[j] - a * sum;
 
				}
				for (int i = 0; i < feature; i++)
				{
					w[i] = temp[i];
	
				}
				for (i = 0; i < sample; i++)//����ۺ���
				{
					for (j = 1; j < feature - 1; j++)
					{
						J += (1.0 / 2.0 / (double)(sample))*pow((Y[i] - x[i][feature - 1]),2);
					}
				}	
			}
 
		}	
			sum = 0;
			for (i = 0; i < feature-1; i++)//��ʼʹ����һ�����в���
			{
				x[m][i] = p[i];
				sum += w[i] * x[m][i];
			}
			hype = sum;
			cout << "��" << m+1<<"�����Խ����" << endl;
 
			cout << "��ֵ֤Ϊ" << hype << endl;
			
			cout << "��ʵֵΪ" << p[3] << endl;
			cout << "��ֵ֤����ʵֵ�Ĳ�Ϊ" << fabs(p[3]-hype) << endl<<endl;
			A += fabs(p[3] - hype);
			//��ϵ����ֵ
			for (i = 0; i < feature - 1; i++)//��ƽ��ϵ��ֵ
			s[i]+= w[i];			
	}
	cout << endl;
 
	cout << "���Իع�ϵ��ֵ��" << endl;
	
	
			
	for (i = 0; i < feature - 1; i++)
	{
		w[i]  =s[i] / sample;
		cout << "��" << i + 1 << "��ϵ��Ϊ" << w[i] << endl;
	}
	cout <<endl<< "���ۺ�����ֵΪ"<< J << endl;
	cout <<endl<<"�ݶ��½���һ��������"<< cnt<<"��"<<endl << endl;
 
	cout << "��ֵ֤����ʵֵ��ƽ����Ϊ" << A/(sample)<< endl<<endl;
	cout << "���������ݼ�ѧϰ��Ϊ" << a  << endl;
	cout << "���������ݼ�������Ϊ" << sample << endl;
	cout << "���������ݼ�������Ϊ" << feature << endl;
	cout<< "�������ݼ���ǵõ������������Լ����ϲ���!" << endl;
	cout << endl;
	system("pause");
	return 0;
}
