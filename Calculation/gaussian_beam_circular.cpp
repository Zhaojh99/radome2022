#include "gaussian_beam_circular.h"

//���ش���z���Ⱥ�ĸ�˹����Wֵ
double Gauss_Omega_Circular(double frequency0, double w0, double z0)
{
	double lamda = C_Speed / frequency0;
	double w = w0*pow(1.0 + pow((lamda*z0 / Pi / w0 / w0), 2), 0.5);

	return w;
}

//����Բ��˹������P��x,y,z���ĸ���������ֵ
complex<double> Gauss_E_Circular(double frequency0, double w0, Vector3 P)
{
	double x0 = P.x;
	double y0 = P.y;
	double z0 = P.z;
	double lamda = C_Speed / frequency0;
	double k = 2 * Pi / lamda;

	//���ڹ�ʽ�е�R�������ʰ뾶��ʽ�д���zΪ��ĸ�����,Ϊ�˱��������Ϊ����R1=1/R
	double R1 = z0 / (z0*z0 + pow(Pi*w0*w0 / lamda, 2));

	double phi0 = atan(lamda*z0 / Pi / w0 / w0);

	complex <double> j(0, 1);//����������λj

	complex<double> E = pow(2.0 / Pi / pow(Gauss_Omega_Circular(frequency0, w0, z0), 2), 0.5)
		*exp(-(x0*x0 + y0*y0) / pow(Gauss_Omega_Circular(frequency0, w0, z0), 2))
		*exp(-j*k*z0)
		*exp(-j*k*(x0*x0 + y0*y0) / 2.0 *R1)
		*exp(j*phi0);
	//��ʽ��Դ����Gaussian Beam Quasi-optical Propagation and Applications��P25
	return E;
}

//����Բ��˹������P��x,y,z���Ļ�����ʽ��δ�۵���λֵ
double Gauss_Phase_Circular(double frequency0, double w0, Vector3 P)
{
	double x0 = P.x;
	double y0 = P.y;
	double z0 = P.z;
	double lamda = C_Speed / frequency0;
	double k = 2 * Pi / lamda;

	//���ڹ�ʽ�е�R�������ʰ뾶��ʽ�д���zΪ��ĸ�����,Ϊ�˱��������Ϊ����R1=1/R
	double R1 = z0 / (z0*z0 + pow(Pi*w0*w0 / lamda, 2));

	double phi0 = atan(lamda*z0 / Pi / w0 / w0);

	double Phase = -k*z0 - k*(x0*x0 + y0*y0) / 2.0 *R1 + phi0;
	//��ʽ��Դ����Gaussian Beam Quasi-optical Propagation and Applications��P25
	return Phase;
}