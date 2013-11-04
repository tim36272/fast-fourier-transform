/*
    Copyright (C) 2013  Timothy Sweet

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <cmath>
#include <iostream>
#include <iomanip>
#include "fft.h"
#include "utility.cpp"
#define PART_1A
//#define PART_1B
//#define PART_1C
//#define PART_1D
//#define PART_1E

#define PI 3.1415892653


int main() {
#ifdef PART_1A
	unsigned long n_samples = 4;
	float data[] = {0,1,0,2,0,4,0,4,0};

#endif
#ifdef PART_1B
	unsigned long n_samples = 128;
	float data[n_samples*2+1];
	data[0]=0;
	for(int i=1;i<=n_samples*2;i++) {
		//divide i by 256 because it has to be divided by 2 as well
		if(i%2==1) data[i] = cos(2*PI*8*i/256.);
		else data[i] = 0;
	}
#endif
#ifdef PART_1C
	unsigned long n_samples = 128;
	float data[n_samples*2+1];
	data[0]=0;
	for(int i=1;i<=n_samples*2;i++) {
		//divide i by 256 because it has to be divided by 2 as well
		if(i%2==1) data[i] = sin(2*PI*8*i/256.);
		else data[i] = 0;
	}
#endif
#ifdef PART_1D
	unsigned long n_samples = 128;
	float data[n_samples*2+1];
	data[0]=0;
	for(int i=1;i<=n_samples*2;i++) {
		//divide i by 256 because it has to be divided by 2 as well
		if(i%2==1) data[i] = sin(2*PI*8*i/256.)+cos(2*PI*8*i/256.);
		else data[i] = 0;
	}
#endif
#ifdef PART_1E
	unsigned long n_samples = 128;
	float data[n_samples*2+1];
	data[0]=0;
	for(int i=1;i<=64;i++) {
		data[i] = 0;
	}
	for(int i=65;i<=192;i++) {
		if(i%2==1) data[i]=1;
		else data[i] = 0;
	}
	for(int i=193;i<=256;i++) {
		data[i] = 0;
	}
#endif


	int isign = TRANSFORM_FORWARD;
	std::cout<<"initial: ";
	utility::print_float_vector(data,n_samples*2);
	utility::write_float_vector(data,n_samples*2,"original.dat");

	//do fft
	original::fft(data,n_samples,isign);

	std::cout<<"FT: ";
	utility::print_float_vector(data,n_samples*2);
	utility::write_float_vector(data,n_samples*2,"transformed.dat");

	//do inverse fft
	isign = TRANSFORM_REVERSE;
	original::fft(data,n_samples,isign);
	//original::fft already scaled the values

	std::cout<<"Original: ";
	utility::print_float_vector(data,n_samples*2);
}
