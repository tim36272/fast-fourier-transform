/*
		Copyright note: Some portions of this software are derived from source code
		in the book "Numerical Recipes in C: The Art of Scientific Computing" and
		are not licensed for open source distribution, and have been redacted. To
		properly use this source code you must implement the single dimensional FFT
		as described in the stub function provided.
*/

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
 
#include <math.h>
#include "opencv2/opencv.hpp"
#include "fft.h"
#include "utility.h"
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

namespace original {
void fft(float data[], unsigned long nn, int isign)
{
	//if this is the forward transformation (isign==-1) shift the image
	if(isign==TRANSFORM_FORWARD) {
		for(int sample_index=1;sample_index<nn;sample_index++) {
			if((sample_index)%2==1)
				data[sample_index] *= -1.;
		}
		std::cout<<"Moved"<<std::endl;
	}


/* Implement the 1D FFT here. It must follow these design constraints:
----The first position in data, which is data[0], must be ignored
----The odd positions in data, starting with data[1] hold the real values
----The even positions in data, starting with data[2] hold the imaginary values
*/


	//if forward transform, scale the values
	if(isign==-1) {
		utility::scale_float_vector(data,nn*2,nn);
	}
//	utility::round_float_vector(data,nn*2);
}
#undef SWAP
}//namespace original

namespace fourier {
void fft2D(int rows,int cols, float** real_function,float** imaginary_function,int isign) {
	//if this is the forward transformation (isign==-1) shift the image
	//for each row

	if(isign==TRANSFORM_FORWARD) {
		for(int row_index=0;row_index<rows;row_index++) {
			//for each column
			for(int col_index=0;col_index<cols;col_index++) {
				real_function[row_index][col_index] = real_function[row_index][col_index]*pow(-1,(row_index+col_index)%2);
			}
		}
	}


	//compute the fourier transform of the rows
	//for each row
	for(int row_index=0;row_index<rows;row_index++) {
		//make an array to pass to the function fft
		//it starts at index 1 with the reals, 2 with imaginary, 3 reals, etc
		float this_row[cols*2+1];
		this_row[0]=0;
		for(int col_index=1;col_index<cols*2;col_index+=2) {
			//get real part
			//this depends on integer rounding
			float this_value = real_function[row_index][col_index/2];
			this_row[col_index] = this_value;
			//get imaginary part
			this_value = imaginary_function[row_index][col_index/2];
			this_row[col_index+1] = this_value;
		}
		//calculate the fast fourier transform of it
		original::fft(this_row,cols,isign);

		//extract the data back into the original matrix
		for(int col_index=1;col_index<cols*2;col_index+=2) {
			//get real part
			//this depends on integer rounding
			float this_value = this_row[col_index];
			real_function[row_index][col_index/2] = this_value;
			//get imaginary part
			this_value = this_row[col_index+1];
			imaginary_function[row_index][col_index/2] = this_value;
		}
	}

	//compute the fourier transform of the cols
	//for each col
	for(int col_index=0;col_index<cols;col_index++) {
		//make an array to pass to the function fft
		//it starts at index 1 with the reals, 2 with imaginary, 3 reals, etc
		float this_col[rows*2+1];
		this_col[0]=0;
		for(int row_index=1;row_index<rows*2;row_index+=2) {
			//get real part
			//this depends on integer rounding
			float this_value = real_function[row_index/2][col_index];
			this_col[row_index] = this_value;
			//get imaginary part
			this_value = imaginary_function[row_index/2][col_index];
			this_col[row_index+1] = this_value;
		}
		//calculate the fast fourier transform of it
		original::fft(this_col,rows,isign);

		//extract the data back into the original matrix
		for(int row_index=1;row_index<rows*2;row_index+=2) {
			//get real part
			//this depends on integer rounding
			float this_value = this_col[row_index];
			real_function[row_index/2][col_index] = this_value;
			//get imaginary part
			this_value = this_col[row_index+1];
			imaginary_function[row_index/2][col_index] = this_value;
		}
	}
	//done with 2dfft
}

} //namespace fft

