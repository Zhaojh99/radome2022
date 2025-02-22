#include "correlation_coefficient.h"

void Correlation_Coefficient_Omega(double frequency0, double ds, int M0, int N0,
	const vector <vector <complex<double>>> &EX,
	const vector <vector <complex<double>>> &EY,
	int &index, int &MaxE_i, int &MaxE_j, double &W0)
{
	double MaxEX = 0;//��ʼ��
	double MaxEY = 0;
	double MaxE = 0;
	int MaxEX_i = 0;//maxposition_EX
	int MaxEX_j = 0;
	int MaxEY_i = 0;//maxposition_EY
	int MaxEY_j = 0;

	//�����ҵ���ǿ���ֵ,Ȼ���ҵ���ǿ���ֵ���ڵ�ii,jj
	for (int i = 0; i < M0; i++)
		for (int j = 0; j < N0; j++)
		{
			{
				
				if (abs(EX[i][j]) > MaxEX)
				{
					MaxEX = abs(EX[i][j]);
					MaxEX_i = i;
					MaxEX_j = j;
				}

				if (abs(EY[i][j]) > MaxEY)
				{
					MaxEY = abs(EY[i][j]);
					MaxEY_i = i;
					MaxEY_j = j;
				}
			}
		}

	MaxE_i = MaxEX_i;
	MaxE_j = MaxEX_j;
	MaxE = MaxEX;
	index = 0;

	if (MaxEY > MaxEX)
	{
		MaxE_i = MaxEY_i;
		MaxE_j = MaxEY_j;
		MaxE = MaxEY;
		index = 1;
	}

	vector <vector <double>> AbsE(M0, vector<double>(N0, 0));//�������糡����ֵ
	if (MaxEX > MaxEY)
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					AbsE[i][j] = abs(EX[i][j]);
				}
			}
	}
	if (MaxEY > MaxEX)
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					AbsE[i][j] = abs(EY[i][j]);
				}
			}
	}

//���濪ʼƥ�����������С
		int ii0 = 0;
		for (int k = 0; k < MaxE_i; k++)
		{
			ii0 = k;
			if ((AbsE[MaxE_i - k - 1][MaxE_j] <= (1.0 / Universal_Constant_e*MaxE))
				& (AbsE[MaxE_i - k][MaxE_j]>(1.0 / Universal_Constant_e*MaxE)))
				break;//һ�ҵ�������ѭ��
		}

		int ii1 = MaxE_i;
		for (int k = MaxE_i; k < M0 - 1; k++)
		{
			ii1 = k;
			if ((AbsE[k + 1][MaxE_j] <= (1.0 / Universal_Constant_e*MaxE))
				& (AbsE[k][MaxE_j]>(1.0 / Universal_Constant_e*MaxE)))
				break;
		}

		int jj0 = 0;
		for (int k = 0; k < MaxE_j; k++)
		{
			jj0 = k;
			if ((AbsE[MaxE_i][MaxE_j - k - 1] <= (1.0 / Universal_Constant_e*MaxE))
				& (AbsE[MaxE_i][MaxE_j - k]>(1.0 / Universal_Constant_e*MaxE)))
				break;//һ�ҵ�������ѭ��
		}

		int jj1 = MaxE_j;
		for (int k = MaxE_j; k < N0 - 1; k++)
		{
			jj1 = k;
			if ((AbsE[MaxE_i][k + 1] <= (1.0 / Universal_Constant_e*MaxE))
				& (AbsE[MaxE_i][k]>(1.0 / Universal_Constant_e*MaxE)))
				break;
		}

//���ƥ������ֵ
//20181118�޸�,���ýϴ������ֵ
		double W0_x=0, W0_y=0;
		W0_x = ds * ii0;
		if((ii1 - MaxE_i)>ii0) W0_x = ds * (ii1 - MaxE_i);

		W0_y = ds * jj0;
		if ((jj1 - MaxE_j)>jj0) W0_y = ds * (jj1 - MaxE_j);

		W0 = W0_x * 1.1;
		if (W0_y>W0_x) W0 = W0_y * 1.1;
}


double Scalar_Correlation_Coefficient(double frequency0, double ds, int M0, int N0,
	const vector <vector <complex<double>>> &EX,
	const vector <vector <complex<double>>> &EY)
{
	int index0 = 0; int MaxE_i0 = 0; int MaxE_j0 = 0; double w0 = 0;
	Correlation_Coefficient_Omega(frequency0, ds, M0, N0, EX, EY,
		index0, MaxE_i0, MaxE_j0, w0);//�ȴ���һ��

//��˹�������������ĵ糡����ֵ
	vector <vector <complex<double>>> Gauss_E(M0, vector<complex<double>>(N0, 0));
	for (int i = 0; i < M0; i++)
		for (int j = 0; j < N0; j++)
		{ 
			{
				Gauss_E[i][j] = Gauss_E_Circular(frequency0, w0,
					Vector3(ds*(i - MaxE_i0), ds*(j - MaxE_j0), 0));
			}
		}

//�����˹����ϵ��
	double sum1 = 0; double sum2 = 0; double sum3 = 0;
	double scalar_coefficient = 0;
	if (index0 == 0)//������ΪEX	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + abs(EX[i][j])*abs(Gauss_E[i][j]);
					sum2 = sum2 + abs(EX[i][j])*abs(EX[i][j]);
					sum3 = sum3 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	if (index0 == 1)//������ΪEY	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + abs(EY[i][j])*abs(Gauss_E[i][j]);
					sum2 = sum2 + abs(EY[i][j])*abs(EY[i][j]);
					sum3 = sum3 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	scalar_coefficient = sum1 / pow(sum2*sum3, 0.5);
	return scalar_coefficient;
}

double Scalar_Correlation_Coefficient(double frequency0, double ds, int M0, int N0,
	const vector <vector <complex<double>>> &EX,
	const vector <vector <complex<double>>> &EY,double& _waistradiu)	//Mark20201025
{
	int index0 = 0; int MaxE_i0 = 0; int MaxE_j0 = 0; double w0 = 0;
	Correlation_Coefficient_Omega(frequency0, ds, M0, N0, EX, EY,
		index0, MaxE_i0, MaxE_j0, w0);//�ȴ���һ��
	 _waistradiu = w0;
									  //��˹�������������ĵ糡����ֵ
	vector <vector <complex<double>>> Gauss_E(M0, vector<complex<double>>(N0, 0));
	for (int i = 0; i < M0; i++)
		for (int j = 0; j < N0; j++)
		{
			{
				Gauss_E[i][j] = Gauss_E_Circular(frequency0, w0,
					Vector3(ds*(i - MaxE_i0), ds*(j - MaxE_j0), 0));
			}
		}

	//�����˹����ϵ��
	double sum1 = 0; double sum2 = 0; double sum3 = 0;
	double scalar_coefficient = 0;
	if (index0 == 0)//������ΪEX	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + abs(EX[i][j])*abs(Gauss_E[i][j]);
					sum2 = sum2 + abs(EX[i][j])*abs(EX[i][j]);
					sum3 = sum3 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	if (index0 == 1)//������ΪEY	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + abs(EY[i][j])*abs(Gauss_E[i][j]);
					sum2 = sum2 + abs(EY[i][j])*abs(EY[i][j]);
					sum3 = sum3 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	scalar_coefficient = sum1 / pow(sum2*sum3, 0.5);
	return scalar_coefficient;
}

double Vector_Correlation_Coefficient(double frequency0, double ds, int M0, int N0,
	const vector <vector <complex<double>>> &EX,
	const vector <vector <complex<double>>> &EY, double& _waistradius) {
	int index0 = 0; int MaxE_i0 = 0; int MaxE_j0 = 0; double w0 = 0;
	Correlation_Coefficient_Omega(frequency0, ds, M0, N0, EX, EY,
		index0, MaxE_i0, MaxE_j0, w0);//�ȴ���һ��
	_waistradius = w0;

									  //��˹�������������ĵ糡����ֵ
	vector <vector <complex<double>>> Gauss_E(N0, vector<complex<double>>(N0, 0));
	for (int i = 0; i < M0; i++)
		for (int j = 0; j < N0; j++)
		{
			{
				Gauss_E[i][j] = Gauss_E_Circular(frequency0, w0,
					Vector3(ds*(i - MaxE_i0), ds*(j - MaxE_j0), 0));
			}
		}

	//�����˹ʸ��ϵ��
	complex<double> sum1 = 0; complex<double> sum2 = 0;
	double sum3 = 0; double sum4 = 0;
	double vector_coefficient = 0;
	if (index0 == 0)//������ΪEX	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + EX[i][j] * Gauss_E[i][j];
					sum2 = sum2 + conj(EX[i][j]) * Gauss_E[i][j];
					sum3 = sum3 + abs(EX[i][j])*abs(EX[i][j]);
					sum4 = sum4 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	if (index0 == 1)//������ΪEY	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + EY[i][j] * Gauss_E[i][j];
					sum2 = sum2 + conj(EY[i][j]) * Gauss_E[i][j];
					sum3 = sum3 + abs(EY[i][j])*abs(EY[i][j]);
					sum4 = sum4 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	vector_coefficient = abs(sum1 * sum2 / sum3 / sum4);//��ʵ������ľ���ʵ��
	return vector_coefficient;
}

double Vector_Correlation_Coefficient(double frequency0, double ds, int M0, int N0,
	const vector <vector <complex<double>>> &EX,
	const vector <vector <complex<double>>> &EY)
{
	int index0 = 0; int MaxE_i0 = 0; int MaxE_j0 = 0; double w0 = 0;
	Correlation_Coefficient_Omega(frequency0, ds, M0, N0, EX, EY,
		index0, MaxE_i0, MaxE_j0, w0);//�ȴ���һ��

//��˹�������������ĵ糡����ֵ
	vector <vector <complex<double>>> Gauss_E(N0, vector<complex<double>>(N0, 0));
	for (int i = 0; i < M0; i++)
		for (int j = 0; j < N0; j++)
		{
			{
				Gauss_E[i][j] = Gauss_E_Circular(frequency0, w0,
					Vector3(ds*(i - MaxE_i0), ds*(j - MaxE_j0), 0));
			}
		}

	//�����˹ʸ��ϵ��
	complex<double> sum1 = 0;complex<double> sum2 = 0;
	double sum3 = 0; double sum4 = 0;
	double vector_coefficient = 0;
	if (index0 == 0)//������ΪEX	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + EX[i][j] * Gauss_E[i][j];
					sum2 = sum2 + conj(EX[i][j]) * Gauss_E[i][j];
					sum3 = sum3 + abs(EX[i][j])*abs(EX[i][j]);
					sum4 = sum4 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	if (index0 == 1)//������ΪEY	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + EY[i][j] * Gauss_E[i][j];
					sum2 = sum2 + conj(EY[i][j]) * Gauss_E[i][j];
					sum3 = sum3 + abs(EY[i][j])*abs(EY[i][j]);
					sum4 = sum4 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	vector_coefficient = abs(sum1 * sum2 / sum3 / sum4);//��ʵ������ľ���ʵ��
	return vector_coefficient;
}


double Scalar_Correlation_Coefficient_TargetW0(double frequency0, double ds, int M0, int N0,
	const vector <vector <complex<double>>> &EX,
	const vector <vector <complex<double>>> &EY,
	double Target_W0)
{
	int index0 = 0; int MaxE_i0 = 0; int MaxE_j0 = 0; double w0 = 0;
	Correlation_Coefficient_Omega(frequency0, ds, M0, N0, EX, EY,
		index0, MaxE_i0, MaxE_j0, w0);//�ȴ���һ��,w0����

//��˹�������������ĵ糡����ֵ
	vector <vector <complex<double>>> Gauss_E(N0, vector<complex<double>>(N0, 0));
	for (int i = 0; i < M0; i++)
		for (int j = 0; j < N0; j++)
		{
			{
				Gauss_E[i][j] = Gauss_E_Circular(frequency0, Target_W0,
					Vector3(ds*(i - MaxE_i0), ds*(j - MaxE_j0), 0));
			}
		}

	//�����˹����ϵ��
	double sum1 = 0; double sum2 = 0; double sum3 = 0;
	double scalar_coefficient = 0;
	if (index0 == 0)//������ΪEX	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + abs(EX[i][j])*abs(Gauss_E[i][j]);
					sum2 = sum2 + abs(EX[i][j])*abs(EX[i][j]);
					sum3 = sum3 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	if (index0 == 1)//������ΪEY	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + abs(EY[i][j])*abs(Gauss_E[i][j]);
					sum2 = sum2 + abs(EY[i][j])*abs(EY[i][j]);
					sum3 = sum3 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	scalar_coefficient = sum1 / pow(sum2*sum3, 0.5);
	return scalar_coefficient;
}


double Vector_Correlation_Coefficient_TargetW0(double frequency0, double ds, int M0, int N0,
	const vector <vector <complex<double>>> &EX,
	const vector <vector <complex<double>>> &EY,
	double Target_W0)
{
	int index0 = 0; int MaxE_i0 = 0; int MaxE_j0 = 0; double w0 = 0;
	Correlation_Coefficient_Omega(frequency0, ds, M0, N0, EX, EY,
		index0, MaxE_i0, MaxE_j0, w0);//�ȴ���һ��

//��˹�������������ĵ糡����ֵ
	vector <vector <complex<double>>> Gauss_E(N0, vector<complex<double>>(N0, 0));
	for (int i = 0; i < M0; i++)
		for (int j = 0; j < N0; j++)
		{
			{
				Gauss_E[i][j] = Gauss_E_Circular(frequency0, Target_W0,
					Vector3(ds*(i - MaxE_i0), ds*(j - MaxE_j0), 0));
			}
		}

	//�����˹ʸ��ϵ��
	complex<double> sum1 = 0; complex<double> sum2 = 0;
	double sum3 = 0; double sum4 = 0;
	double vector_coefficient = 0;
	if (index0 == 0)//������ΪEX	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + EX[i][j] * Gauss_E[i][j];
					sum2 = sum2 + conj(EX[i][j]) * Gauss_E[i][j];
					sum3 = sum3 + abs(EX[i][j])*abs(EX[i][j]);
					sum4 = sum4 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	if (index0 == 1)//������ΪEY	
	{
		for (int i = 0; i < M0; i++)
			for (int j = 0; j < N0; j++)
			{
				{
					sum1 = sum1 + EY[i][j] * Gauss_E[i][j];
					sum2 = sum2 + conj(EY[i][j]) * Gauss_E[i][j];
					sum3 = sum3 + abs(EY[i][j])*abs(EY[i][j]);
					sum4 = sum4 + abs(Gauss_E[i][j])*abs(Gauss_E[i][j]);
				}
			}
	}

	vector_coefficient = abs(sum1 * sum2 / sum3 / sum4);//��ʵ������ľ���ʵ��
	return vector_coefficient;
}
