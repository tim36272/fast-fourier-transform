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
 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "utility.h"

namespace utility {

static const int kPrintWidth = 12;

void print_float_vector(float data[],unsigned long length) {

	for(unsigned long i=0;i<=length;i++) {
		if(i%12==0)std::cout<<std::endl;
		if(data[i] < 0.00001 && data[i] > -0.00001) std::cout<<std::setw(kPrintWidth)<<0<<" ";
		else std::cout<<std::setw(kPrintWidth)<<data[i]<<" ";
	}
	std::cout<<std::endl;
}

void write_float_vector(float data[],unsigned long length,const std::string& name) {
	std::ofstream fout;
	fout.open(name.c_str());
	for(unsigned long i=1;i<=length;i++) {
		if(i%2==1)fout<<std::endl;
		if(data[i] < 0.00001 && data[i] > -0.00001) fout<<std::setw(kPrintWidth)<<0<<" ";
		else fout<<std::setw(kPrintWidth)<<data[i]<<" ";
	}
	fout.close();
}

void scale_float_vector(float data[],unsigned long length, int factor) {
	for(unsigned long i=0;i<=length;i++) {
		data[i] = data[i]/factor;
	}
}

void round_float_vector(float data[],unsigned long length) {
	for(unsigned long i=0;i<=length;i++) {
		if(data[i] < 0.00001 && data[i] > -0.00001) data[i] = 0;
	}
}

void float_image_to_mat(int rows, int cols, float** image, cv::Mat* image_mat) {
	image_mat->create(rows,cols,CV_32FC1);
	for(int row_index=0;row_index<rows;row_index++) {
		for(int col_index=0;col_index<cols;col_index++) {
			image_mat->at<float>(row_index,col_index) = image[row_index][col_index];
			if(image_mat->at<float>(row_index,col_index) < 0) {
				image_mat->at<float>(row_index,col_index) = -1*image_mat->at<float>(row_index,col_index);
			}
		}
	}
}

void mat_to_float_image(int rows, int cols, float** image, cv::Mat* image_mat) {
	for(int row_index=0;row_index<rows;row_index++) {
		for(int col_index=0;col_index<cols;col_index++) {
			image[row_index][col_index] = image_mat->at<float>(row_index,col_index);
		}
	}
}

void move_to_log_scale(cv::Mat* image) {
	for(int row_index=0;row_index<image->rows;row_index++) {
		for(int col_index=0;col_index<image->cols;col_index++) {
//			std::cout<<"to log: "<<image->at<float>(row_index,col_index)<<std::endl;
			image->at<float>(row_index,col_index) = log(image->at<float>(row_index,col_index)+1);
		}
	}
}

void stretch(cv::Mat* image) {
	//scale image
	double dummy_d,max;
	cv::Point dummy;
	cv::minMaxLoc(*image,&dummy_d,&max,&dummy,&dummy);
	std::cout<<"Max: "<<max<<std::endl;
	*image = *image / max;
}

void write(const std::string& name,const cv::Mat& image) {
	cv::Mat output;
	image.convertTo(output,CV_8U,255);
	cv::imwrite(name,output);
}
}
