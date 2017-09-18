// rulueri.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <math.h>

#define PI 3.14159265358

double *matrix (double (*A1), double (*A2))
{
	double (*b), c[3][3];
	int i,j;
	for(i=0;i<=2;i++)
	{
		for(j=0;j<=2;j++)
		{
			c[i][j] = (*(A1 + 3 * i + 0)) * (*(A2 + 3 * 0 +j)) + (*(A1 + 3 * i + 1)) * (*(A2 + 3 * 1 +j)) +  (*(A1 + 3 * i + 2)) * (*(A2 + 3 * 2 +j));
		}
	}
	b = * c;
	return *c;
}



int main ()
{

	int i,j;

	double t;
	t = int(365.25 * 2016) + int(30.6001 * (10 + 1)) + 1 + 1720981.5;
	double T;
	T = t / 36525;     //儒略世纪数

	printf ("T = %f \n",T);

	double zeta, theta, eta, zeta1, theta1, eta1, x, y, z, X1, Y1, Z1;
	x = y = z = 1000000;
	double cz, sz, ct, st, ce, se;

	zeta = 0.6406161 * T + 0.0000839 * T * T + 0.0000050 * T * T * T;
	theta = 0.6406161 * T - 0.0001185 * T * T - 0.0000116 * T * T * T;
	eta = 0.6406161 * T + 0.0003041 * T * T + 0.0000051 * T * T * T;

	printf("zeta = %f\n theta = %f\n eta = %f\n",zeta, theta, eta);

	zeta1 = zeta * PI / 180;
	theta1 = theta * PI / 180;
	eta1 = eta * PI / 180;

	cz=cos(zeta1);
	sz=sin(zeta1);
	ct=cos(theta1);
	st=sin(theta1);
	ce=cos(eta1);
	se=sin(eta1);

	//计算矩阵中的各项的值
	/*
	double z_eta[3][3] = {{ce, -se, 0}, {se, ce, 0}, {0, 0, 1}};
	double y_theta[3][3] = {{ct, 0, -st}, {0, 1, 0}, {st, 0, ct}};
	double z_zeta[3][3] = {{cz, -sz, 0}, {sz, cz, 0}, {0, 0, 1}};
	double xyz[3][3] = {{1000000, 0, 0}, {1000000, 0, 0}, {1000000, 0, 0}};
	double xyz_1[3][3], xyz_2[3][3], xyz_3[3][3];
	double a[3][3];

	;
	
	for (i=0;i<=2;i++)
	{
		for (j=0;j<=2;j++)
		{
			xyz_1[i][j] = *(matrix(z_eta[0], y_theta[0]) + 3 * i + j);
			printf("%lf..\n",xyz_3[i][j]);
		}		
	}

	for (i=0;i<=2;i++)
	{
		for (j=0;j<=2;j++)
		{
			xyz_2[i][j] = *(matrix(xyz_1[0], z_zeta[0]) + 3 * i + j);
			printf("%lf.\n",xyz_3[i][j]);
		}		
	}

	for (i=0;i<=2;i++)
	{
		for (j=0;j<=2;j++)
		{
			xyz_3[i][j] = *(matrix(xyz_2[0], xyz[0]) + 3 * i + j);
		}		
		printf("%lf \n",xyz_3[i][j]);
	}
	*/

	X1 = (ce * ct * cz - se * sz) * x + (- ce * ct * sz - se * cz) * y + (- st * ce ) * z;
	Y1 = (se * ct * cz + ce * sz) * x + (- se * ct * sz + ce * cz) * y + (- st * se ) * z;
	Z1 = (st * cz ) * x + (- st * sz) * y + ct * z;
	printf("X1=%f \nY1=%f \nZ1=%f \n",X1, Y1, Z1);


	double epsilon, psi, delta_epsilon, omega, D, F, o1, d1, f1, sep, cep, sd, cd, sp,cp;
	double e1, e2, e3, e4, p1, p2, p3, de1, de2, de3;

	e1 = 23 + 26 / 60 + 21.448 / 3600;
	e2 = -46.815 / 3600;
	e3 = -0.00059 / 3600;
	e4 = 0.001813 / 3600;

	de1 = 9.2025 / 3600;
	de2 = 0.5736 / 3600;
	de3 = 0.0927 / 3600;

	p1 = -17.1996 / 3600;
	p2 = -1.3187 / 3600;
	p3 = -0.2274 / 3600;

	omega = 125.0445550 - 1934.1361849 * T + 0.0020762 * T * T + T * T * T / 467410 - T * T * T *T / 60616000;
	D = 297.8502042 + 445267.1115168 * T - 0.0016399 * T * T + T * T * T / 545868 - T * T * T * T / 113065000;
	F = 93.2720993 + 483202.0175273 * T - 0.0034029 * T * T - T * T * T / 3526000 + T * T * T * T / 863310000;

	printf("omega = %f \n D = %f \n F = %f\n", omega, D, F);

	o1 = omega * PI / 180;
	d1 = D * PI / 180;
	f1 = F * PI /180;

	epsilon = e1 + e2 * T + e3 * T * T + e4 * T * T * T;
	delta_epsilon = de1 * cos (o1) + de2 * cos(2 * f1 - 2 * d1 + 2 * o1) + de3 * cos(2 * f1 - 2 * o1);
	psi = p1 * sin(o1) + p2 * sin(2 * f1 - 2 * d1 + 2 * o1) + p3 * cos(2 * f1 - 2 * o1);

	double ep, dep, ps, X, Y, Z;

	ep = epsilon * PI / 180;
	dep = delta_epsilon * PI / 180;
	ps = psi * PI / 180;

	sep = sin(ep);
	cep = cos(ep);
	sd = sin(dep + ep);
	cd = cos(dep + ep);
	sp = sin(ps);
	cp = cos(ps);

	X = cp * X1 + (- sp * cep ) * Y1 + (- sp * sep) * Z1;
	Y = cd * sp * X1 + (cd * cp * cep + sd * sep) * Y1 + (cd * cp * sep - sd * cep) * Z1;
	Z = sd * sp * X1 + (sd * cp * cep - cd * sep) * Y1 + (sd * cp * sep + cd * cep) * Z1;

	printf("epsilon = %f \n delta_epsilon = %f \n psi = %f \nX = %f \nY = %f \nZ = %f \n", epsilon, delta_epsilon, psi, X, Y, Z);
	return 0;
}
