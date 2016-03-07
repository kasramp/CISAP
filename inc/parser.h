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

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Parser {
public:
    void parse(int argc, char** argv);
    vector<string> construct_vector_from_argv(int argc, char** argv);
    int get_loop();
    void set_loop(int loop);
    bool get_is_help();
    void set_is_help(bool is_help);
    vector<string> get_songs();
    void set_songs(vector<string>& songs);
    
private:
    int loop;
    bool is_help;
    vector<string> songs;
    vector<string> argv_vector;
    static const string LOOP;
    static const string PLAY_LIST;
    static const string STREAM;
    static const string HELP;
};
#endif /* PARSER_H */

