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

#ifndef UTILITY_H_
#define UTILITY_H_

namespace utility {

void print_float_vector(float data[],unsigned long length);

void write_float_vector(float data[],unsigned long length,const std::string& name);

void scale_float_vector(float data[],unsigned long length, int factor);

void round_float_vector(float data[],unsigned long length);

void float_image_to_mat(int rows, int cols, float** image, cv::Mat* image_mat);

void mat_to_float_image(int rows, int cols, float** image, cv::Mat* image_mat);

void move_to_log_scale(cv::Mat* image);

void stretch(cv::Mat* image);

void zoom(int width,cv::Mat* image);

void write(const std::string& name, const cv::Mat& image);

} //namespace utility

#endif /* UTILITY_H_ */
