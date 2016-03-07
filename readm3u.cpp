/* 
 * This file is part of CISAP.
 * CISAP is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * CISAP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.  <http://www.gnu.org/licenses/>
 *
 * Author(s):
 * © 2016 Kasra Madadipouya <kasra@madadipouya.com>
 */
#include "inc/readm3u.h"

/* This function add songs to songs vector and
 * returns number of added elements to the vector
*/
int Readm3u::read_m3u_file(string str_path, vector<string>& songs) {
    int i=0;
    try {
        ifstream input_file(str_path);
        for (string one_line; getline(input_file, one_line);) {
            songs.push_back(one_line);
            i++;
        }
    } catch (...) {
    }
    return i;
}
