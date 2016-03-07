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

#ifndef READM3U_H
#define READM3U_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
using namespace std;

class Readm3u {
public:
    int read_m3u_file(string str_path, vector<string>& songs);
};
#endif /* READM3U_H */

