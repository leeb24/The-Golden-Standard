#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include "Model.h"


void do_move_command(Model*,int,int,int);

void do_work_command(Model*,int,int,int);

void do_stop_command(Model*,int);

void do_go_command(Model*);

void do_run_command(Model*);

void do_quit_command(Model*);

void do_attack_command(Model*,int,int);

void do_make_command(Model*, char , int, int, int);

#endif
