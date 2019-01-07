using namespace std;
typedef complex<double> cdouble;


double pi=4.*atan(1);

long int seed;

double PN[63]={1,1,1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,1,-1,1,
               -1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,1,1,-1,1,1,-1,-1,1,1,-1,1,-1,1,-1};

//double PN1[64]={0,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,0,0,0,0,0,
//			   0,0,0,0,0,0,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1};
int  PN1[15]={-1, 1, -1, 1, 1, -1, -1,  1, -1, -1, -1, 1, 1, 1, 1};

cdouble y[20],c[15],ee,b,eex,f[5],fest[5],nk;
cdouble x[5500],xe[550],v[5500],v2[550],xu[550],xm[5500];

int N,hmax=100,nmax=450,ndata=496;

int offset=0,i,j,k,m,n,h,t,Lf=8,Lb=4;

double a0,a1,b0,b1,U,R,sigma=0.001;

double delta=0.045, mse[550];

double svk=0.0, snk=0.0, SNR=0.0, BER=0.0,TBER=0.0, gain;

	double alfa[5][8],teta[8],amplit[5],fD=0.0,Ts=0.0000037,ww=0;
//	fD:Doppler frequency, Ts:Symbol Period
	double fmag[5]={0.227, 0.460, 0.688, 0.460, 0.227};  // proakis
//	double fmag[5]={0.9, 0.3, 0.1, 0.0, 0.0};            // gaus
//		double fmag[5]={1.0, 0.0, 0.0, 0.0, 0.0};  // proakis
