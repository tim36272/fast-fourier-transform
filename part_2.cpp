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
 

#include "fft.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "utility.h"
#define PART_2A
//#define PART_2B
//#define PART_2C

#define PI 3.1415892653

int main() {
	//generate an image
	int rows=512,cols=512;
#ifdef PART_2A
	int box_size = 32;
#endif
#ifdef PART_2B
	int box_size = 64;
#endif
#ifdef PART_2C
	int box_size = 128;
#endif

	int box_start = rows/2-box_size/2;
	int box_end = box_start+box_size;
	float** real_image;
	float** imaginary_image;

	real_image = new float*[rows];
	imaginary_image = new float*[rows];
	//generate the image
	for(int row_index=0;row_index<rows;row_index++) {
		//allocate space for the row
		real_image[row_index] = new float[cols];
		imaginary_image[row_index] = new float[cols];
		//determine if the pixel will be black or undetermined
		//this gets multiplied by the col value and forces the white box
		//to be drawn
		int multiplier = (row_index < box_start || row_index > box_end) ? 0 : 1;
		//assign each pixel
		for(int col_index=0;col_index<cols;col_index++) {
			real_image[row_index][col_index] = (col_index < box_start || col_index > box_end) ? 0 : 1*multiplier;
			imaginary_image[row_index][col_index] = 0;
		}
	}

	//create cv::Mat to show the data
	cv::Mat real_mat,imaginary_mat;


	utility::float_image_to_mat(rows,cols,real_image,&real_mat);
	utility::float_image_to_mat(rows,cols,imaginary_image,&imaginary_mat);


	imshow("Real",real_mat);
	imshow("Imaginary",imaginary_mat);
	utility::write("real_original.png",real_mat);
	utility::write("imaginary_original.png",imaginary_mat);

	cv::waitKey(0);

	int isign = TRANSFORM_FORWARD;

//	std::cout<<"Transforming forward, this is original: "<<std::endl<<real_mat<<std::endl;
	//calculate the fft of the image
	fourier::fft2D(rows,cols,real_image,imaginary_image,isign);
	//and display it
	utility::float_image_to_mat(rows,cols,real_image,&real_mat);
	utility::float_image_to_mat(rows,cols,imaginary_image,&imaginary_mat);
	utility::move_to_log_scale(&real_mat);
	utility::stretch(&real_mat);
	imshow("Real",real_mat);
	imshow("Imaginary",imaginary_mat);
	utility::write("real_transformed.png",real_mat);
	utility::write("imaginary_transformed.png",imaginary_mat);

//	std::cout<<"Transforming backward, this is the real FT: "<<std::endl<<real_mat<<std::endl;
//	std::cout<<"Transforming backward, this is the imaginary FT: "<<std::endl<<imaginary_mat<<std::endl;
	cv::waitKey(0);

	//Calculate the inverse fft of the image
	isign = TRANSFORM_REVERSE;
	fourier::fft2D(rows,cols,real_image,imaginary_image,isign);

	//and display it
	utility::float_image_to_mat(rows,cols,real_image,&real_mat);
	utility::float_image_to_mat(rows,cols,imaginary_image,&imaginary_mat);
	imshow("Real",real_mat);
	imshow("Imaginary",imaginary_mat);
	cv::waitKey(0);

//		std::cout<<"Transformed backward, this is original: "<<std::endl<<real_mat<<std::endl;


}
