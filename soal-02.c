/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 5 - Recursion
*Percobaan        : -
*Hari dan Tanggal : Kamis, 24 Maret 2022
*Nama (NIM)       : -
*Asisten (NIM)    : -
*Nama File        : soal-02.c
*Deskripsi        : -
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_MAX 255

float hitung_polinom(float x, int degree, int* coef){
	float sum = 0;
	float temp = 0;
	for(int i = 0; i<=degree; i++){
		temp = 1;
		for(int j=0; j<i; j++){
			temp *= x;
		}
		sum += temp*coef[i];
	}
	return sum;
}

int turunan_polinom(int* degree, int curr_degree, int* coef, int* coef_new){
	coef_new[curr_degree-1] = (curr_degree)*coef[curr_degree];

	if(curr_degree > 1){
		turunan_polinom(degree,curr_degree-1,coef,coef_new);
	}
	else{ // Asumsikan derajat polinom terkecil adalah 1
		return *degree-1;
	}
}

void hitung_akar(float* x, int degree, int* coef, int* coef_dev){
	float hasil_polinom;
	float hasil_der;
	hasil_polinom = hitung_polinom(*x,degree,coef);
	if(hasil_polinom != 0){
		hasil_der = hitung_polinom(*x,degree-1,coef_dev);
		*x= *x - hasil_polinom/hasil_der;
		hitung_akar(x,degree,coef,coef_dev);
	}
	else{
		return;
	}
}


int main(){
	int degree;
	int *coef = (int*) malloc (sizeof(int));
		// Masukkan derajat polinom
	printf("Masukkan derajat polinom: ");
	scanf("%d",&degree);

	// Ubah ukuran array derajat polinom
	coef = realloc(coef,((degree)+1)*sizeof(int));

	// Input string koefisien polinom
	printf("Masukkan koefisien polinom: ");
	char coef_str[LEN_MAX];
	char* token;
	scanf("%s",coef_str);

	int i = degree;
	token = strtok(coef_str,",");
	while(token != NULL){
		coef[i] = atoi(token);
		i -= 1;
		token = strtok(NULL,",");
	}

	int coef_der[degree];
	int degree_der;
	degree_der = turunan_polinom(&degree, degree, coef,coef_der);

	float root=0;
	hitung_akar(&root,degree,coef,coef_der);
	printf("Akar polinom bersangkutan yang paling dekat dengan 0 adalah %.2f",root);
	free(coef);
}
