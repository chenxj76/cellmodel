// HHmodel.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>


FILE *ap;
double v,v0;
double t, dt,tau;

double ki();
double nai();
double leaki();
double ion();


int _tmain(int argc, _TCHAR* argv[])
{ 
	ap = fopen("ap", "w");
	double cm = 1.0;//膜电容，单位uF cm^-2.
	v0 = 0.0;
	dt = 0.01;
	t = 0.0;
	for (int i = 0; i < 100; i++)
	{
	
 	v = v +(int)ion * dt;
	t = t + dt;
	fprintf(ap, "d%d%\n", t, v);

	}

	fclose(ap);
	return 0;
}

double ki()
{
	double an, an0, bn0, bn;
	double kn,kn0,knn;
	double taun;
	double dndt;
	double iki;//单位uA。
	double gk0=36.0;//单位m mho cm^-2.
	double vk=-12.0;//单位mv。

	an0 = 0.01*(v0 + 10) / (exp(v0 / 10 + 1) - 1);
	bn0 = 0.125*exp(v0 / 80);
	an = 0.01*(v + 10) / (exp(v / 10 + 1) - 1);
	bn = 0.125*exp(v / 80);
	taun = 1 / (an + bn);
	knn = an / (an + bn);
	kn0 = an0 / (an0 + bn0);
	//kn = knn - (knn - kn0)*exp(-t / taun);
	dndt = an*(1 - kn) - bn*kn;
	kn = kn + dndt*dt;
	iki = (kn*kn*kn*kn)*gk0*(v - vk);
	return iki;
}

double nai(){
	double am, am0, bm0, bm,ah,ah0,bh,bh0;
	double nam, nam0, namm;
	double nah, nah0, nahh;
	double taum, tauh;
	double dmdt,dhdt;
	double inai;//单位uA。
	double gna0 = 120.0;//单位m mho cm^-2.
	double vna = -115.0;//单位mv。

	am0 = 0.1*(v0 + 25) / (exp(v0 / 10 + 2.5) - 1);
	bm0 = 4 * exp(v0 / 18);
	ah0 = 0.07*exp(v0 / 20);
	bh0 = 1 / (exp(v0 / 10 + 3) + 1);
	am = 0.1*(v + 25) / (exp(v / 10 + 2.5) - 1);
	bm = 4*exp(v / 18);
	ah = 0.07*exp(v / 20);
	bh = 1 / (exp(v / 10 + 3) + 1);
	taum = 1 / (am + bm);
	tauh = 1 / (ah + bh);
	namm = am / (am + bm);
	nahh = ah / (ah + bh);
	nam0 = am0 / (am0 + bm0);
	nah0 = ah0 / (ah0 + bh0);

	//nam = namm - (namm - nam0)*exp(-t / tau);
	//nah = nahh - (nahh - nah0)*exp(-t / tau);
	
	dmdt = am*(1 - nam) - bm*nam;
	nam = nam + dmdt*dt;
	dhdt = ah*(1 - nah) - bh*nah;
	nah = nah+ dhdt*dt;
	inai = nam*nam*nam*nah*gna0*(v - vna);
	return inai;
}

double leaki()
{
	double gl0 = 0.3;//单位m mho cm^-2.
	double vl = -10;//单位mv,取值范围在-10~613
	
	return gl0*(v - vl);
}

double ion()
{
	double it;
	it=ki + nai + leaki;
	return it;
}