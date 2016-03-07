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

#ifndef INIT_H
#define INIT_H

#include "fmod.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;
class Init 
{
public:
    void print_help();
    void start();
    void intro_print();
    void shut_down();
    void re_fresh();
    void print_track_info(string path, FMOD::Sound *sound);
    void save_position();
    void restore_position();
    void print_exit_message();
private:
    int tag_exist;
    int x;
    int y;
    string get_file_name(string path);
    void track_separator();
    void get_tag(FMOD::Sound *sound);
    void check_tag(FMOD_TAG tag);
    void print_tag(char *name,char *data,int datalen);
    
};

#endif /* INIT_H */

