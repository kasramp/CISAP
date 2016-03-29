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
#include "inc/parser.h"
#include "inc/readm3u.h"
const string Parser::LOOP = "--loop";
const string Parser::PLAY_LIST = "--playlist";
const string Parser::STREAM = "--stream";
const string Parser::HELP = "--help";
const string Parser::SHUFFLE = "--shuffle";

void Parser::parse(int argc, char** argv) {
    argv_vector = Parser::construct_vector_from_argv(argc, argv);
    for (int i = 0; i < argv_vector.size(); i++) {
        if (!argv_vector[i].compare(LOOP)) {
            int loop;
            try {
                loop = stoi(argv_vector[++i]);
            } catch (std::invalid_argument e) {
                exit(-1);
                //return -1;
            }
            // set loop
            if (loop == 0) {
                loop = 1;
            }
            Parser::loop = loop;
            continue;
        } else if (!argv_vector[i].compare(PLAY_LIST)) {
            string file_path = argv_vector[++i];
            Readm3u* readm3u = new Readm3u();
            readm3u->read_m3u_file(file_path, songs);
            delete readm3u;
            continue;
        } else if (!argv_vector[i].compare(STREAM)) {
            songs.push_back(argv_vector[++i]);
            continue;
        } else if (!argv_vector[i].compare(HELP)) {
            is_help = true;
            break;
        } else if(!argv_vector[i].compare(SHUFFLE)) {
			is_shuffle = true;
        } else {
            songs.push_back(argv_vector[i]);
        }
    }
    shuffle(is_shuffle);
}

vector<string> Parser::construct_vector_from_argv(int argc, char** argv) {
    vector<string> argv_vector;
    try {
        if (argc > 0) {
            for (int i = 1; i < argc; i++) {
                argv_vector.push_back(argv[i]);
            }
        }
    } catch (...) {
    }
    return argv_vector;
}

void Parser::shuffle(bool is_shuffle) {
	if(is_shuffle) {
		std::random_shuffle(Parser::songs.begin(), Parser::songs.end());
	}
}

int Parser::get_loop() {
    if(Parser::loop == 0) {
        Parser::loop = 1;
    }
    return Parser::loop;
}

void Parser::set_loop(int loop) {
    Parser::loop = loop;
}

bool Parser::get_is_help() {
    return Parser::is_help;
}

void Parser::set_is_help(bool is_help) {
    Parser::is_help = is_help;
}

vector<string> Parser::get_songs() {
    return Parser::songs;
}

void Parser::set_songs(vector<string>& songs) {
    Parser::songs = songs;
}
