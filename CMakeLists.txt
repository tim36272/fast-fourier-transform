
#    Copyright (C) 2013  Timothy Sweet
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
cmake_minimum_required(VERSION 2.8)
project( valueFinder )

find_package( OpenCV REQUIRED )
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_library(utility utility.cpp)
target_link_libraries(utility ${catkin_LIBRARIES})
link_libraries(utility)

add_library(fft fft.cpp)
target_link_libraries(fft ${catkin_LIBRARIES})
link_libraries(fft)

add_executable( part_1 part_1.cpp )
target_link_libraries( part_1 ${OpenCV_LIBS} )
add_executable( part_2 part_2.cpp )
target_link_libraries( part_2 ${OpenCV_LIBS} )
add_executable( part_3 part_3.cpp )
target_link_libraries( part_3 ${OpenCV_LIBS} )
