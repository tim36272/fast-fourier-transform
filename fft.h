/*
 * fft.h
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

#ifndef FFT_H_
#define FFT_H_

#include <math.h>
#include "opencv2/opencv.hpp"

#define TRANSFORM_FORWARD -1
#define TRANSFORM_REVERSE 1


namespace original {
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
void fft(float data[], unsigned long nn, int isign);
#undef SWAP
}//namespace original

namespace fourier {

inline void swap(float* lhs, float* rhs);
void fft(float data[], unsigned long n_samples, int i_sign);
void fft2D(int rows,int cols, float** real_function,float** imaginary_function,int isign);

} //namespace fft

#endif /* FFT_H_ */
