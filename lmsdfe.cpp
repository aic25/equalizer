#include<dos.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<rnd.h>
#include <complex>


#include "lmsdfe.h"




   main()
   {


   FILE *data;
   data=fopen("d:\\mad\\lmsdfe\\lmsdfe.wkr","w+");

  
 N=Lf+Lb+1;

  for(i=0;i<nmax;i++) mse[i]=0.0;
  
rnd(&seed);
seed=13;


	for(i=0;i<5;i++){amplit[i]=fmag[i]/8.0;}
	for(j=0;j<8;j++){teta[j]=j*2*pi/8;}
	


//GAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiN

//for(gain=5.1;gain> 0.01;gain=gain/sqrt(2.0)){

  gain=1.1; // 15 dB
//  gain=0.62; // 20 dB
//  gain=0.77; // 18 dB
//	gain=0.345; // 25 dB
//	gain=0.195; // 30 dB

	
   seed=-5;
   rnd(&seed);
   seed=13;


	ww=2*pi*fD*Ts;

//kanal    kanalkanal    kanalkanal    kanalkanal    kanal

  for(h=0;h<hmax;h++){  // kanal döngüsü

//   -------Rayleigh Channel Simulator_______________________
	for(i=0;i<5;i++){
	for(j=0;j<8;j++){alfa[i][j]=2*pi*rnd(&seed);}
	}
		for(i=0;i<5;i++){
	
		f[i]=0.0; fest[i]=0.0;
		
		for(j=0;j<8;j++){
			f[i]=f[i]+polar(amplit[i],alfa[i][j]+n*ww*cos(teta[j]));
		}
		}
//   -------Rayleigh Channel Simulator_______________________

//printf("\n%7.3f,%7.3f %7.3f,%7.3f %7.3f,%7.3f %7.3f,%7.3f %7.3f, %7.3f", f[0], f[1], f[2], f[3], f[4]); getch();

///////////////////////////////////////// Ana DÖNGÜ ///////////////////////////////////////////

for (j=0; j < N; j++){c[j].real(0.001);c[j].imag(0.001);}
//for (n=0;n<=40;n++){v[n].real(0.0); v[n].imag(0.0);x[n].real(0.0);x[n].imag(0.0);xu[n].real(0.0);xu[n].imag(0.0);}
for (n=0;n<=40;n++){v[n].real(0); v[n].imag(0);x[n].real(0);x[n].imag(0);xu[n]=0;}

//m=0;

for (n=0; n < nmax; n++){ // öðrenme döngüsü


	  k=n+40;
//	  if(n<90)
//	  if(n<nmax)
//	  {
//	   x[k].real(PN1[m]);x[k].imag(PN1[m]);m=m+1;
//	   if (m == 15) m=0;
//	  }
//	  if(n >=90) 
	  if(n < nmax){
	   x[k].real(((rand()%2)-0.5)*2);x[k].imag(((rand()%2)-0.5)*2);// random qpsk datalarý üretiliyor
	   }

	  v[k].real(0.0);v[k].imag(0.0);
	  for(j=0; j < 5; j++){ v[k]=v[k]+f[j]*x[k-j];} // 5 dallý kanaldan geçiriliyor

///// AWGN /////////////////////////
   a0=rnd(&seed);
   a1=rnd(&seed);
   R=sqrt(-2.0*pi*sigma*log(a0));
   U=2.*pi*a1;
   b0=R*cos(U);
   b1=R*sin(U);

   b.real(b0);
   b.imag(b1);
      
   nk=gain*b;

///// AWGN /////////////////////////

   svk=svk+norm(v[k]);
   snk=snk+norm(nk);

   v[k]=v[k]+nk;

   
   for (j=0;j <= Lf; j++) {y[j]=v[k-j];}       // fff
   for(j=1;j<=Lb;j++) {y[Lf+j]=x[k-Lf-j];}     // bilinen fbf
//   for(j=1;j<=Lb;j++) {y[Lf+j]=xm[k-j];}     // hard fbf
//     for(j=1;j<=Lb;j++) {y[Lf+j]=xu[k-j];}     // soft fbf

	xu[k].real(0.0);xu[k].imag(0.0);

	for (j=0;j<N;j++){xu[k]=xu[k]+y[j]*c[j];} // denkleþtiriliyor


if(real(xu[k]) > 0 && imag(xu[k]) > 0) {xm[k].real(1.0); xm[k].imag(1.0);}
if(real(xu[k]) > 0 && imag(xu[k]) < 0) {xm[k].real(1.0); xm[k].imag(-1.0);}
if(real(xu[k]) < 0 && imag(xu[k]) > 0) {xm[k].real(-1.0);xm[k].imag(1.0);}
if(real(xu[k]) < 0 && imag(xu[k]) < 0) {xm[k].real(-1.0);xm[k].imag(-1.0);}


      ee=x[k-Lf]-xu[k]; 
//	  ee=x[k-Lf]-xm[k];
  

	  mse[k]=mse[k]+norm(ee);

 for (j=0;j<N;j++) c[j]=c[j]+delta*conj(y[j])*ee; // lms algoritmasý


} // öðrenme döngüsü
	   
/////////////////////////////////Ana DÖNGÜ SONU///////////////////////////////////////


 //kanal    kanalkanal    kanalkanal    kanalkanal    kanal
   }  // kanal döngüsü

   SNR=10.0*log10(svk/snk);

   	for(n=48;n<nmax;n++)
	{
	fprintf(data,"%5d,%9.6f,%6.3f\n", n-48,(mse[n]/hmax),SNR);
	printf("%5d,%9.6f,%6.3f\n", n-48,(mse[n]/hmax),SNR);
//getch();
	}

svk=0.;
snk=0.;

	printf("\n KLMSDFE bitti\a\n");

//	getch();

    return 0;

   }


