#include<dos.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<rnd.h>
#include <complex>


#include "qpskawgn.h"




   main()
   {


   FILE *data;
   data=fopen("f:\\qpskawgn\\qpskawgn.wkr","w+");

  
rnd(&seed);
seed=13;



//GAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiNGAiN

//	for(gain=6.5;gain> 0.05;gain=gain/sqrt(2.0)){  //  gain (SNR) döngüsü
	for(gain=20.0424;gain>2.5;gain=gain/sqrt(1.412537545)){/////////////SNR DÖNGÜSÜ//////////////


	
   seed=-5;
   rnd(&seed);
   seed=13;



//kanal    kanalkanal    kanalkanal    kanalkanal    kanal

  for(h=0;h<hmax;h++){  // kanal döngüsü


///////////////////////////////////////// Ana DÖNGÜ ///////////////////////////////////////////

for (j=0; j < N; j++){c[j].real(0.001);c[j].imag(0.001);}
//for (n=0;n<=40;n++){v[n].real(0.0); v[n].imag(0.0);x[n].real(0.0);x[n].imag(0.0);xu[n].real(0.0);xu[n].imag(0.0);}
for (n=0;n<=40;n++){v[n].real(0); v[n].imag(0);x[n].real(0);x[n].imag(0);xu[n]=0;}

//m=0;

for (n=0; n < nmax; n++){ // öðrenme döngüsü

	  k=n+40;
	  if(n < nmax){
	   x[k].real(((rand()%2)-0.5)*2);x[k].imag(((rand()%2)-0.5)*2);//printf("%7.3f, %7.3f\n",x[k]);getch();
	   }

//	  v[k].real(0.0);v[k].imag(0.0);
//	  for(j=0; j < 5; j++){ v[k]=v[k]+f[j]*x[k-j];}
	  v[k]=x[k];

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

   v[k]=v[k]+nk;//printf("%7.3f, %7.3f\n",v[k]);getch();


	if(real(v[k]) > 0 && imag(v[k]) > 0) {xm[k].real(1.0);xm[k].imag(1.0);}
	if(real(v[k]) > 0 && imag(v[k]) < 0) {xm[k].real(1.0);xm[k].imag(-1.0);}
	if(real(v[k]) < 0 && imag(v[k]) > 0) {xm[k].real(-1.0);xm[k].imag(1.0);}
	if(real(v[k]) < 0 && imag(v[k]) < 0) {xm[k].real(-1.0);xm[k].imag(-1.0);}

//TBER=TBER+(norm(x[k]-xm[k]))/4.0;   
	if(n > 40) { TBER=TBER+(norm(x[k]-xm[k]))/4.0;}
	//if(n > 40) { TBER=TBER+(norm(x[k]-v[k]))/4.0;}
//    		printf("TBER=%7.3f\n",TBER);
//	getch();

   }   // BER döngüsü ndata

//kanal    kanalkanal    kanalkanal    kanalkanal    kanal

   } // kanal döngüsü

	SNR=10.0*log10(svk/snk);
	BER=TBER/(2.*ndata*hmax);

	printf("<< qpskawgn >> SNR=%6.3f, BER=%8.5f, delta=%8.5f\n", SNR,BER,delta);
	fprintf(data,"%6.3f %8.5f %8.5f %8.5f   \n", SNR,BER,delta);

//getch();

svk=0.;
snk=0.;
TBER=0.;

	}  // gain (SNR) döngüsü

	printf("\n qpskawgn bitti\a\n");

//	getch();

    return 0;

   }


