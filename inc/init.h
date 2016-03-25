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
#include <curl/curl.h>
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>



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
    string get_lyric(string path, FMOD::Sound *sound);
private:
    int tag_exist;
    int x;
    int y;
    //string service_result;
    string get_file_name(string path);
    void track_separator();
    void get_tag(FMOD::Sound *sound);
    void check_tag(FMOD_TAG tag);
    void print_tag(char *name,char *data,int datalen);
    string get_custom_tag(FMOD::Sound *sound, string tag_name);
    string call_lyric_service(string artist, string song_name);
    string trim_lyric(string lyric);
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static const string URL;
    static const string BR_TAG;
    static const string ARTIST;
    static const string TITLE;  
};

#endif /* INIT_H */

