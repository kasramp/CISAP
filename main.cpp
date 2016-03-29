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

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "inc/init.h"
#include "inc/parser.h"
#include "inc/fmod.hpp"
#include "inc/common.h"
using namespace std;

/*
 *
 */
template <typename T>
void _destruct(T arg);
void lyric_display(string file_name, Init *init, string song, FMOD::Sound *sound);

int main(int argc, char** argv) {
    static const char KEY_RIGHT_BRACKET = ']';
    static const char KEY_LEFT_BRACKET = '[';
    static const char KEY_RIGHT_BRACE = '}';
    static const char KEY_LEFT_BRACE = '{';
    static const char KEY_GREATER = '>';
    static const char KEY_LESS = '<';
    static const char KEY_PLUS = '+';
    static const char KEY_MINUS = '-';
    static const char KEY_ONE = '1';
    static const char KEY_TWO = '2';
    static const char KEY_THREE = '3';
    static const char KEY_FOUR = '4';
    static const char KEY_L = 'l';
    static const char KEY_H = 'h';
    static const char KEY_P = 'p';
    static const char KEY_F = 'f';
    static const char KEY_Q = 'q';
    static const char KEY_M = 'm';
    static const char KEY_W = 'w';
    static const char KEY_SPACE = ' ';
    static const unsigned int TEN_SECOND = 10000;
    static const unsigned int ONE_MINUTE = 60000;
    static const unsigned int TEN_MINUTE = ONE_MINUTE * 10;
    static const unsigned int BUFFER_SIZE = 64 * 2048;
    static const float DEFAULT_VOLUME = 1.0f;
    static const float DEFAULT_PAN = 0.0f;
    static float DEFAULT_FREQUENCY = 44100.00000003f;
    string lyric;
    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::Channel *channel = 0;
    FMOD::ChannelGroup *mastergroup = 0;
    FMOD::DSP *dsp_low_pass = 0;
    FMOD::DSP *dsp_high_pass = 0;
    FMOD::DSP *dsp_echo = 0;
    FMOD::DSP *dsp_flange = 0;
    FMOD_OPENSTATE open_state;
    FMOD_RESULT result;
    void *extra_driver_data = 0;
    bool mute = FALSE, paused = FALSE, starving = FALSE;
    unsigned int version, ms, lenms = 0, percent = 0;
    int loop, lp = 0, empt_buf = 0;
    float volume = DEFAULT_VOLUME, pan = DEFAULT_PAN, frequency = DEFAULT_FREQUENCY;
    vector<string> songs;
    Init* init = new Init();
    Parser* parser = new Parser();
    srand(time(NULL));
    try {
        //Common_Init(&extradriverdata);
        result = FMOD::System_Create(&system);
        //ERRCHECK(result);
        result = system->getVersion(&version);
        //ERRCHECK(result);
        if (version < FMOD_VERSION) {
            cout << "FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION;
        }
        result = system->init(32, FMOD_INIT_NORMAL, extra_driver_data);
        //ERRCHECK(result);
        parser->parse(argc, argv);
        loop = parser->get_loop();
        songs = parser->get_songs();
        if (parser->get_is_help()) {
            init->print_help();
        }
        _destruct(parser);
        init->start();
        init->intro_print();
        while (loop != lp++) {
            for (int i = 0; i < songs.size(); i++) {
                lyric = "";
                init->re_fresh();
                system->setStreamBufferSize(BUFFER_SIZE, FMOD_TIMEUNIT_RAWBYTES);
                result = system->getMasterChannelGroup(&mastergroup);
                result = system->createSound(songs[i].c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);
                result = system->playSound(sound, 0, true, &channel);
                channel->setLoopCount(0);
                //ERRCHECK(result);
                init->print_track_info(songs[i], sound);
                channel->setVolume(volume);
                channel->setPaused(paused);
                channel->setMute(mute);
                channel->setPan(DEFAULT_PAN);
                channel->getFrequency(&frequency);
                DEFAULT_FREQUENCY = frequency;
                result = system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsp_low_pass);
                result = system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &dsp_high_pass);
                result = system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp_echo);
                result = system->createDSPByType(FMOD_DSP_TYPE_FLANGE, &dsp_flange);
                result = mastergroup->addDSP(0, dsp_low_pass);
                result = mastergroup->addDSP(0, dsp_high_pass);
                result = mastergroup->addDSP(0, dsp_echo);
                result = mastergroup->addDSP(0, dsp_flange);
                result = dsp_low_pass->setBypass(true);
                result = dsp_high_pass->setBypass(true);
                result = dsp_echo->setBypass(true);
                result = dsp_flange->setBypass(true);
                system->update();
                sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                //ERRCHECK(result);
                do {
                    int ch = getch();
                    if (ch == KEY_Q) {
                        init->print_exit_message();
                        result = sound->release();
                        //ERRCHECK(result);
                        result = system->close();
                        //ERRCHECK(result);
                        result = system->release();
                        //ERRCHECK(result);
                        init->shut_down();
                        _destruct(init);
                        return 0;
                    } else if (ch == KEY_W) {
                        clear();
                        refresh();
                        printw("Please wait, retrieving lyric...");
                        refresh();
                        if (!lyric.length() > 0) {
                            lyric = init->get_lyric(songs[i], sound);
                        }
                        lyric_display(lyric, init, songs[i], sound);
                    } else if (ch == KEY_GREATER || ch == KEY_L) {
                        channel->stop();
                        result = sound->release();
                        //ERRCHECK(result);
                        break;
                    } else if (ch == KEY_LESS || ch == KEY_H) {
                        if ((i - 1) >= 0) {
                            i -= 2;
                            result = sound->release();
                            //ERRCHECK(result);
                            break;
                        }
                    } else if (ch == KEY_SPACE && !starving) {
                        result = channel->getPaused(&paused);
                        //ERRCHECK(result);
                        result = channel->setPaused(!paused);
                        //ERRCHECK(result);
                    } else if (ch == KEY_PLUS) {
                        channel->getVolume(&volume);
                        if ((volume += 0.1f) > 1) {
                            volume = 1.0;
                        }
                        channel->setVolume(volume);
                    } else if (ch == KEY_MINUS) {
                        channel->getVolume(&volume);
                        if ((volume -= 0.1f) < 0) {
                            volume = 0.0;
                        }
                        channel->setVolume(volume);
                    } else if (ch == KEY_M) {
                        channel->getMute(&mute);
                        channel->setMute(!mute);
                    } else if (ch == KEY_RIGHT_BRACKET) {
                        if ((pan += 0.1f) > 1) {
                            pan = 1.0;
                        }
                        channel->setPan(pan);
                    } else if (ch == KEY_LEFT_BRACKET) {
                        if ((pan -= 0.1f) < -1) {
                            pan = -1.0;
                        }
                        channel->setPan(pan);
                    } else if (ch == KEY_P) {
                        pan = DEFAULT_PAN;
                        channel->setPan(pan);
                    } else if (ch == KEY_RIGHT_BRACE) {
                        //channel->getFrequency(&frequency);
                        channel->setFrequency((frequency += 500.0f));
                    } else if (ch == KEY_LEFT_BRACE) {
                        //channel->getFrequency(&frequency);
                        channel->setFrequency((frequency -= 500.0f));
                    } else if (ch == KEY_F) {
                        //channel->getFrequency(&frequency);
                        frequency = DEFAULT_FREQUENCY;
                        channel->setFrequency(DEFAULT_FREQUENCY);
                    } else if (ch == KEY_ONE) {
                        bool bypass;
                        result = dsp_low_pass->getBypass(&bypass);
                        ERRCHECK(result);
                        bypass = !bypass;
                        result = dsp_low_pass->setBypass(bypass);
                        ERRCHECK(result);
                    } else if (ch == KEY_TWO) {
                        bool bypass;
                        result = dsp_high_pass->getBypass(&bypass);
                        ERRCHECK(result);
                        bypass = !bypass;
                        result = dsp_high_pass->setBypass(bypass);
                        ERRCHECK(result);
                    } else if (ch == KEY_THREE) {
                        bool bypass;
                        result = dsp_echo->getBypass(&bypass);
                        ERRCHECK(result);
                        bypass = !bypass;
                        result = dsp_echo->setBypass(bypass);
                        ERRCHECK(result);
                    } else if (ch == KEY_FOUR) {
                        bool bypass;
                        result = dsp_flange->getBypass(&bypass);
                        ERRCHECK(result);
                        bypass = !bypass;
                        result = dsp_flange->setBypass(bypass);
                        ERRCHECK(result);
                    } else if (ch == KEY_RIGHT) {
                        channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                        ms += TEN_SECOND;
                        if (ms > lenms) {
                            result = sound->release();
                            break;
                        }
                        channel->setPosition(ms, FMOD_TIMEUNIT_MS);
                    } else if (ch == KEY_LEFT) {
                        channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                        if (ms < TEN_SECOND) {
                            ms = 0;
                        } else {
                            ms -= TEN_SECOND;
                        }
                        channel->setPosition(ms, FMOD_TIMEUNIT_MS);
                    } else if (ch == KEY_UP) {
                        channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                        ms += ONE_MINUTE;
                        if (ms > lenms) {
                            result = sound->release();
                            break;
                        }
                        channel->setPosition(ms, FMOD_TIMEUNIT_MS);
                    } else if (ch == KEY_DOWN) {
                        channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                        if (ms < ONE_MINUTE) {
                            ms = 0;
                        } else {
                            ms -= ONE_MINUTE;
                        }
                        channel->setPosition(ms, FMOD_TIMEUNIT_MS);
                    } else if (ch == KEY_PPAGE) {
                        channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                        ms += TEN_MINUTE;
                        if (ms > lenms) {
                            result = sound->release();
                            break;
                        }
                        channel->setPosition(ms, FMOD_TIMEUNIT_MS);
                    } else if (ch == KEY_NPAGE) {
                        channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                        if (ms < TEN_MINUTE) {
                            ms = 0;
                        } else {
                            ms -= TEN_MINUTE;
                        }
                        channel->setPosition(ms, FMOD_TIMEUNIT_MS);
                    }
                    channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                    channel->getPaused(&paused);
                    sound->getOpenState(&open_state, &percent, &starving, 0);
                    channel->getMute(&mute);
                    //ERRCHECK(result);
                    {
                        bool playing = 0;
                        bool paused = 0;
                        int channels_playing = 0;
                        bool dsp_low_pass_bypass;
                        bool dsp_high_pass_bypass;
                        bool dsp_echo_bypass;
                        bool dsp_flange_bypass;
                        dsp_low_pass->getBypass(&dsp_low_pass_bypass);
                        dsp_high_pass->getBypass(&dsp_high_pass_bypass);
                        dsp_echo->getBypass(&dsp_echo_bypass);
                        dsp_flange->getBypass(&dsp_flange_bypass);
                        if (channel) {
                            FMOD::Sound *current_sound = 0;
                            result = channel->isPlaying(&playing);
                            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                                //ERRCHECK(result);
                            }
                            result = channel->getPaused(&paused);
                            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                                //ERRCHECK(result);
                            }
                            result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                                //ERRCHECK(result);
                            }
                            channel->getCurrentSound(&current_sound);
                            if (current_sound) {
                                result = current_sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                                    //ERRCHECK(result);
                                }
                            }
                        }
                        system->getChannelsPlaying(&channels_playing);
                        init->save_position();
                        string str_loop = to_string(loop == 1 ? 0 : loop);
                        string str_remaining = to_string(loop - lp);
                        char str_volume[10];
                        sprintf(str_volume, "%.1f", volume);
                        printw("Effects : Lowpass[%c] Highpass[%c] Echo[%c] Flange[%c]\n\n",
                                dsp_low_pass_bypass ? ' ' : 'x',
                                dsp_high_pass_bypass ? ' ' : 'x',
                                dsp_echo_bypass ? ' ' : 'x',
                                dsp_flange_bypass ? ' ' : 'x');
                        printw("Track number(s) %d : Current Track %d : Loop time(s) %s : Remain loop(s) %s\n\n", songs.size(), i + 1, loop > 0 ? str_loop.c_str() : "INF", loop > 0 ? str_remaining.c_str() : "INF");
                        printw("Time %02d:%02d:%02d/%02d:%02d:%02d : -%02d:%02d:%02d/%02d:%02d:%02d : %s : (%%%d) %s\n\n", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, (lenms - ms) / 1000 / 60, (lenms - ms) / 1000 % 60, (lenms - ms) / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, starving ? "Buffering..." : paused ? "Paused      " : (!playing) ? "Stop        " : "Playing     ", percent, starving ? "STARVING" : "         ");
                        printw("Volume %s : Balance %.1f %s : Frequency %.1f(Hz)%s\n\n", mute == FALSE ? str_volume : "Mute", pan, ((unsigned) (pan * 1000000) == 0) ? "Center" : ((pan * 1000000) <= 0) ? "Left" : "Right", frequency, frequency == DEFAULT_FREQUENCY ? "Normal play" : frequency < DEFAULT_FREQUENCY ? "Slow play" : "Fast play");
                        init->restore_position();
                        if ((!empt_buf)&&(playing)&&(starving)) {
                            empt_buf = 1;
                            channel->setPaused(!paused);
                        } else if ((empt_buf)&&(!starving)) {
                            empt_buf = 0;
                            channel->setPaused(!paused);
                        }
                        if (!playing) {
                            break;
                        }
                    }
                } while (TRUE);
                result = system->update();
                clear();
            }
        }
    } catch (...) {
    }
    try {
        if (songs.size() > 0) {
            sound->release();
        }
        result = system->close();
        //ERRCHECK(result);
        result = system->release();
        //ERRCHECK(result);
        init->shut_down();
        _destruct(init);
    } catch (...) {
    }
    return 0;
}

template <typename T>
void _destruct(T arg) {
    delete arg;
}

void lyric_display(string lyric, Init *init, string song, FMOD::Sound *sound) {
    WINDOW *p;
    int y, x, i = 0, n = 0, flag = 1, flag1 = 0, ch;
    string line;
    istringstream f(lyric);
    initscr();
    clear();
    refresh();
    getmaxyx(stdscr, y, x);
    while (std::getline(f, line)) {
        if (line.length() > x) {
            i += 2;
        } else {
            ++i;
        }
    }
    i = i + (y - (i % y));
    p = newpad(i, x);
    curs_set(0);
    waddstr(p, lyric.c_str());
    prefresh(p, 0, 0, 0, 0, y - 1, x);
    while (1) {
        ch = getch();
        if (ch == 'q' || ch == 'w') {
            erase();
            endwin();
            refresh();
            init->re_fresh();
            init->print_track_info(song, sound);
            refresh();
            return;
        } else if (ch == 'n' || ch == '>' || ch == KEY_DOWN) {
            if (flag) {
                n++;
                if ((y * n) >= i) {
                    flag = 0;
                    n--;
                }
                prefresh(p, y*n, 0, 0, 0, y - 1, x);
                flag1 = 1;
            }
        } else if (ch == 'p' || ch == '<' || ch == KEY_UP) {
            if (flag1) {
                n--;
                if ((y * n) == 0) {
                    flag1 = 0;
                }
                flag = 1;
                prefresh(p, y*n, 0, 0, 0, y - 1, x);
            }
        }
    }
}
