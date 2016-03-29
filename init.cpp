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

#include "init.h"
//const string Init::URL = "http://api.chartlyrics.com/apiv1.asmx/SearchLyricDirect?artist=";
const string Init::URL = "http://lyricextractor.herokuapp.com/getSimpleLyric?artist=";
const string Init::ARTIST = "ARTIST";
const string Init::TITLE = "TITLE";
const string Init::BR_TAG = "<br>";

void Init::print_help() {
    cout << "Usage:\tcisap [options] [url|path/]filename" << endl;
    cout << endl;
    cout << "Basic options:" << endl;
    cout << " --playlist <.m3u>\tplaying from list" << endl;
    cout << " --stream <url>\t\tplaying from stream" << endl;
    cout << " --loop <number>\tloop playback <number> times.  -1 means forever" << endl;
    cout << " --loop\t\t\trandomly play songs [New]" << endl;
    cout << " --help\t\t\tshow help page" << endl;
    cout << endl;
    cout << "Basic keys:" << endl;
    cout << " < or >\t\t\tstep backward/forward in playlist" << endl;
    cout << " + or -\t\t\tincrease or decrease PCM volume" << endl;
    cout << " m \t\t\tmute or unmute" << endl;
    cout << " [ or ]\t\t\tleft/right speaker adjustment" << endl;
    cout << " p\t\t\tbalance speaker channel" << endl;
    cout << " { or }\t\t\tincrease/decrease audio delay" << endl;
    cout << " f\t\t\treset audio delay" << endl;
    cout << " w\t\t\tdisplay/hide lyric [New]" << endl;
    cout << " <- or ->\t\tseek backward/forward 10 seconds" << endl;
    cout << " down or up\t\tseek backward/forward 1 minute" << endl;
    cout << " pgdown or pgup\t\tseek backward/forward 10 minutes" << endl;
    cout << " SPACE\t\t\tpause song" << endl;
    cout << " q\t\t\tstop playing and quit program" << endl;
    cout << " 1\t\t\tactivate/diactivate 'Lowpass' sound effect" << endl;
    cout << " 2\t\t\tactivate/diactivate 'Highpass' sound effect" << endl;
    cout << " 3\t\t\tactivate/diactivate 'Echo' sound effect" << endl;
    cout << " 4\t\t\tactivate/diactivate 'Flange' sound effect" << endl;
    cout << " 5\t\t\tactivate/diactivate 'Dist' sound effect [Deprecated]" << endl;
    cout << " 6\t\t\tactivate/diactivate 'Chorous' sound effect [Deprecated]" << endl;
    cout << " 7\t\t\tactivate/diactivate 'Parameq' sound effect [Deprecated]" << endl;
    cout << endl;
    cout << "Cisap v0.2 2012-2016 Kasra Madadipouya" << endl;
    exit(0);
}

void Init::intro_print() {
    int y, x, xx, yy;
    getmaxyx(stdscr, y, x);
    move(y / 2 - 3, 0);
    for (int i = 1; i <= x; i++) {
        printw("=");
    }
    getyx(stdscr, yy, xx);
    move(yy, ((x - 57) / 2));
    printw("Cisap © Copyright Written By Kasra Madadipouya v0.2 2012-2016.\n");
    getyx(stdscr, yy, xx);
    move(yy, ((x - 42) / 2));
    printw("The program uses FMOD API version %08x\n", (FMOD_VERSION));
    for (int i = 1; i <= x; i++) {
        printw("=");
    }
    printw("Loading...");
    refresh();
    sleep(1);
    clear();
    refresh();
}

void Init::start() {
    initscr();
    halfdelay(1);
    keypad(stdscr, TRUE);
    noecho();
}

void Init::shut_down() {
    clear();
    endwin();
}

void Init::re_fresh() {
    printw("Buffering...");
    refresh();
}

void Init::print_track_info(string path, FMOD::Sound *sound) {
    printw(" (99%%)\n\n");
    string file_name = Init::get_file_name(path);
    Init::track_separator();
    printw("FILE NAME = %s\n", file_name.c_str());
    Init::get_tag(sound);
    track_separator();
    printw("\n");
    refresh();
}

string Init::get_lyric(string path, FMOD::Sound* sound) {
    try {
        string lyric;
        string artist = Init::get_custom_tag(sound, Init::ARTIST);
        string song_name = Init::get_custom_tag(sound, Init::TITLE);
        if (artist.length() > 1 && song_name.length() > 1) {
            lyric = Init::call_lyric_service(artist, song_name);
            if (lyric.length() > 1) {
                return lyric;
            }
        }
        return "Lyric not found";
    } catch (...) {
    }
}

string Init::get_file_name(string path) {
    int pos = path.rfind("/");
    if (pos == -1) {
        return path;
    }
    return path.substr(pos + 1, path.length() - 1);
}

void Init::track_separator() {
    int y, x;
    getmaxyx(stdscr, y, x);
    for (int i = 1; i <= x; i++) {
        printw("#");
    }
}

void Init::get_tag(FMOD::Sound *sound) {
    FMOD_TAG tag;
    Init::tag_exist = 1;
    if (sound->getTag(0, -1, &tag) != FMOD_OK) {
        printw("TITLE = Unknown (? bytes)\n");
        printw("ARTIST = Unknown (? bytes)\n");
        printw("ALBUM = Unknown (? bytes)\n");
        printw("YEAR = Unknown (? bytes)\n");
        printw("COMMENT = Unknown (? bytes)\n");
        printw("GENERE = Unknown (? bytes)\n");
        refresh();
        Init::tag_exist = 0;
    }

    check_tag(tag);
    sound->getTag("ARTIST", 0, &tag);
    check_tag(tag);
    sound->getTag(0, 2, &tag);
    check_tag(tag);
    sound->getTag(0, 3, &tag);
    check_tag(tag);
    sound->getTag(0, 4, &tag);
    check_tag(tag);
    sound->getTag(0, 6, &tag);
    check_tag(tag);
}

void Init::check_tag(FMOD_TAG tag) {
    if (Init::tag_exist) {
        if (tag.datatype == FMOD_TAGDATATYPE_STRING) {
            Init::print_tag(tag.name, (char*) tag.data, tag.datalen);
        } else {
            printw("%s = Unknown (%d bytes)\n", tag.name, tag.datalen);
            refresh();
        }
    }
}

void Init::print_tag(char *name, char *data, int datalen) {
    printw("%s = %s (%d bytes)\n", name, data, datalen);
    refresh();
}

void Init::save_position() {
    getyx(stdscr, Init::y, Init::x);
}

void Init::restore_position() {
    move(y, x);
    refresh();
}

void Init::print_exit_message() {
    printw("\nExiting... (Quit)\n");
    refresh();
}

string Init::get_custom_tag(FMOD::Sound* sound, string tag_name) {
    try {
        string tag_result;
        FMOD_TAG tag;
        Init::tag_exist = 1;
        transform(tag_name.begin(), tag_name.end(), tag_name.begin(), ::toupper);
        if (sound->getTag(tag_name.c_str(), 0, &tag) == FMOD_OK) {
            if (Init::tag_exist) {
                if (tag.datatype == FMOD_TAGDATATYPE_STRING) {
                    //sound->getTag("TITLE", 0, &tag);
                    tag_result = ((char*) tag.data);
                }
            }
        }
        return tag_result;
    } catch (...) {
    }
}

string Init::call_lyric_service(string artist, string song_name) {
    try {
        CURL* curl;
        string lyric;
        string service_result;
        artist.erase(std::remove(artist.begin(), artist.end(), ' '), artist.end());
        song_name.erase(std::remove(song_name.begin(), song_name.end(), ' '), song_name.end());
        //artist.erase(remove_if(artist.begin(), artist.end(), isspace), artist.end());
        //song_name.erase(remove_if(song_name.begin(), song_name.end(), isspace), song_name.end());
        //replace(artist.begin(), artist.end(), ' ', ''); // replace all 'space' to '%'
        //replace(song_name.begin(), song_name.end(), ' ', ''); // replace all 'space' to '%'
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        string end_url = Init::URL + artist + "&song=" + song_name;
        curl_easy_setopt(curl, CURLOPT_URL, end_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Init::writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &service_result);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        if (service_result.length() > 0) {
            lyric = Init::trim_lyric(service_result);
        } else {
            lyric = "Lyric not found";
        }
        return lyric;
    } catch (...) {
    }
}

string Init::trim_lyric(string lyric) {
    size_t pos;
    while ((pos = lyric.find(BR_TAG)) != std::string::npos) {
        lyric.replace(pos, std::string(BR_TAG).length(), "");
    }
    return lyric;
}

size_t Init::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*) contents, size * nmemb);
    return size * nmemb;
}
