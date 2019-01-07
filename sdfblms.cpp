#include<dos.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<rnd.h>
#include <complex>


#include "sdfblms.h"




   main()
   {


   FILE *data;
   data=fopen("d:\\aopwpc\\sdfblms\\sdfblms.wkr","w+");

  
 N=Lf+Lb+1;

  for(i=0;i<nmax;i++) mse[i]=0.0;
  
rnd(&seed);
seed=13;


	for(i=0;i<5;i++){amplit[i]=fmag[i]/8.0;}
	for(j=0;j<8;j++){teta[j]=j*2*pi/8;}
	


//GAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiN

	for(gain=6.5;gain> 0.05;gain=gain/sqrt(2.0)){  //  gain (SNR) döngüsü

//  gain=1.1; // 15 dB
//  gain=0.62; // 20 dB
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
			f[i]=f[i]+polar(amplit[i],alfa[i][j]+nnn*ww*cos(teta[j]));
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
	  if(n < nmax){
	   x[k].real(((rand()%2)-0.5)*2);x[k].imag(((rand()%2)-0.5)*2);
	   }

	  v[k].real(0.0);v[k].imag(0.0);
	  for(j=0; j < 5; j++){ v[k]=v[k]+f[j]*x[k-j];}

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

//////////////// denkleþtirici /////////////////////////////////////////////////////////////

   for (j=0;j <= Lf; j++) {y[j]=v[k-j];}       // fff
   for(j=1;j<=Lb;j++) {y[Lf+j]=x[k-Lf-j];}     // bilinen fbf
//   for(j=1;j<=Lb;j++) {y[Lf+j]=xm[k-j];}     // hard fbf
//     for(j=1;j<=Lb;j++) {y[Lf+j]=xu[k-j];}     // soft fbf

	xu[k].real(0.0);xu[k].imag(0.0);

      for (j=0;j<N;j++){xu[k]=xu[k]+y[j]*c[j];}

//////////////// denkleþtirici /////////////////////////////////////////////////////////////

if(real(xu[k]) > 0 && imag(xu[k]) > 0) {xm[k].real(1.0); xm[k].imag(1.0);}
if(real(xu[k]) > 0 && imag(xu[k]) < 0) {xm[k].real(1.0); xm[k].imag(-1.0);}
if(real(xu[k]) < 0 && imag(xu[k]) > 0) {xm[k].real(-1.0);xm[k].imag(1.0);}
if(real(xu[k]) < 0 && imag(xu[k]) < 0) {xm[k].real(-1.0);xm[k].imag(-1.0);}


      ee=x[k-Lf]-xu[k]; 
//	  ee=x[k-Lf]-xm[k];
  

//	  mse[k]=mse[k]+norm(ee);

 for (j=0;j<N;j++) c[j]=c[j]+delta*conj(y[j])*ee; // lms algoritmasý


}  // öðrenme döngüsü
	   
/////////////////////////////////Ana DÖNGÜ SONU///////////////////////////////////////

////////BER BER BER BER BER BER BER BER BER BER BER BER BER BER BER///////////////

   for (n=0;n<=40;n++){xu[n]=0.0; xm[n]=0.0; v[n]=0.0; x[n]=0.0;}

   for (n=0; n < ndata; n++){ // BER döngüsü
	  k=n+40;
	  x[k].real(((rand()%2)-0.5)*2);x[k].imag(((rand()%2)-0.5)*2);

	  v[k].real(0);v[k].imag(0);
	  for(j=0; j < 5; j++){ v[k]=v[k]+(f[j])*x[k-j]; }

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

   for (j=0;j <= Lf; j++) {y[j]=v[k-j];}   // fff
   for(j=1;j<= Lb; j++) {y[Lf+j]=xm[k-j];} // fbf
//   for(j=1;j<= Lb; j++) {y[Lf+j]=xu[k-j];} // fbf

      xu[k].real(0);xu[k].imag(0);
      for (j=0;j<N;j++){xu[k]=xu[k]+(y[j])*c[j];}

	if(real(xu[k]) > 0 && imag(xu[k]) > 0) {xm[k].real(1.0);xm[k].imag(1.0);}
	if(real(xu[k]) > 0 && imag(xu[k]) < 0) {xm[k].real(1.0);xm[k].imag(-1.0);}
	if(real(xu[k]) < 0 && imag(xu[k]) > 0) {xm[k].real(-1.0);xm[k].imag(1.0);}
	if(real(xu[k]) < 0 && imag(xu[k]) < 0) {xm[k].real(-1.0);xm[k].imag(-1.0);}

   
	if(n > 40) { TBER=TBER+(norm(x[k-Lf]-xm[k]))/4.0;}
//    		printf("TBER=%7.3f\n",TBER);
//	getch();

   }   // BER döngüsü ndata

//kanal    kanalkanal    kanalkanal    kanalkanal    kanal

   } // kanal döngüsü

	SNR=10.0*log10(svk/snk);
	BER=TBER/(2.*ndata*hmax);

	printf("<< sdfblms >> SNR=%6.3f, BER=%8.5f, delta=%8.5f\n", SNR,BER,delta);
	fprintf(data,"%6.3f %8.5f %8.5f %8.5f   \n", SNR,BER,delta);

//getch();

svk=0.;
snk=0.;
TBER=0.;

	}  // gain (SNR) döngüsü

	printf("\n sdfblms bitti\a\n");

//	getch();

    return 0;

   }


