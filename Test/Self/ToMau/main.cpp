#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>

#define maxdinh 20
#define INPUT "chopcut.txt"
#define MTK "chopcutmtk.txt"

int D[maxdinh][maxdinh];
int X[maxdinh];
int Y[maxdinh];
int Z[maxdinh];
int sodinh, sochieu;
float hsg[maxdinh];

FILE *fp;
void nhaptoado() {
	int i;
	fp = fopen(INPUT,"r");
	if(fp == NULL) {
		printf("Khong tim thay file INPUT!");
		exit(1);
	} else {
		fscanf(fp,"%d",&sochieu);
		fscanf(fp,"%d\n",&sodinh);
		printf("So chieu: %d \nSo dinh: %d\n", sochieu,sodinh);
		
		for(i=0; i<sodinh; i++) {
			fscanf(fp,"%d",&X[i]);
			printf("%d ",X[i]);
		}
		printf("\n");
		
		for(i=0; i<sodinh; i++) {
			fscanf(fp,"%d",&Y[i]);
			printf("%d ",Y[i]);
		}
		printf("\n");
		
		for(i=0; i<sodinh; i++) {
			fscanf(fp,"%d",&Z[i]);
			printf("%d ",Z[i]);
		}
		printf("\n");
		
		fclose(fp);
	}
}

void matranke() {
	int i,j;
	fp = fopen(MTK,"r");
	if(fp == NULL) {
		printf("Khong tim thay file MTK!");
		exit(1);
	} else {
		for(i=0; i<sodinh; i++) {
			for(j=0; j<sodinh; j++) {
				fscanf(fp,"%d",&D[i][j]);
			}
		}
		printf("\n In ma tran ke: \n");
		for(i=0; i<sodinh; i++) {
			for(j=0; j<sodinh; j++) {
				printf("%d ", D[i][j]);
			}
			printf("\n");
		}
	}
}

void Oxy()
{
	for(int i=0;i<sodinh-1;i++){
		for(int j=i+1;j<sodinh;j++){
			if(D[i][j]==1){
				line(X[i],Y[i],X[j],Y[j]);
			}
		}
	}				
}

void Oxz()
{
	for(int i=0;i<sodinh-1;i++){
		for(int j=i+1;j<sodinh;j++){
			if(D[i][j]==1){
				line(X[i],Z[i],X[j],Z[j]);
			}
		}
	}				
}

void Oyz()
{

	for(int i=0;i<sodinh-1;i++){
		for(int j=i+1;j<sodinh;j++){
			if(D[i][j]==1){
				line(Y[i],Z[i],Y[j],Z[j]);
			}
		}
	}				
}

void hesogoc(int A[maxdinh], int B[maxdinh])
{
	for(int i=0;i<sodinh;i++) {
			printf("%5d",A[i]);
	}
	A[sodinh]=A[0]; // Xmoi=Xdau
	B[sodinh]=B[0]; // ymoi=ydau
	sodinh++;
	// tim he so goc
	for(int i=0;i<sodinh-1;i++) {
		if (A[i+1]==A[i]){//dx=0;
			hsg[i]=99999;
		}
		else {
			if (B[i+1]==B[i]){
				hsg[i]=1;
				
			}
			else{
			hsg[i]=(float)(B[i+1]-B[i])/(A[i+1]-A[i]);		
			}
		}
	}
	// in ra he so goc
	printf("\nhe so goc cac canh cua da giac: \n");
	for(int i=0;i<sodinh-1;i++){
		printf("%.2f\t",hsg[i]);
	}
}

void scanline(int A[maxdinh], int B[maxdinh], int color){
	hesogoc(A,B);
	// tim ymin, ymax
	int ymin=B[0];// Y0
	int ymax=B[0];// Y0
	int i;
	
	for(i=0;i<sodinh-1;i++){
		if (ymin > B[i+1]){
			ymin = B[i+1];
			}
		}
	for(i=0;i<sodinh-1;i++){
		if (ymax < B[i+1]){
			ymax = B[i+1];
			}
		}
	// tim hoanh do giao diem tu ymin den ymax
	int y;
	int xgd[sodinh];
	for(y=ymin; y<=ymax;y++){
		int dem=0; // reset so luong gdiem
		for(int i=0;i<sodinh-1;i++){
		if ((y<B[i] && y<B[i+1])||(y>B[i] && y>B[i+1])){
			//printf("\nVoi y= %d, khong co giao diem\n",z);
		}
		else{
			// xac dinh giao diem cho tung canh
				xgd[dem]=round(A[i]+(y-B[i])/hsg[i]);
				dem++;
			}
		}	
		// ve cac doan thang noi cac hoanh do gdiem
		setcolor(color);	
		for(int i=0;i<dem-1;i=i+2){
			line(xgd[i],y,xgd[i+1],y);
		}
	}
	
}
int main()
{
	initwindow(800,600);
	nhaptoado();
	matranke();	
	
	scanline(X,Z,10);	
	setcolor(5);
	Oxy();
	getch();
	return 0;
	
}
