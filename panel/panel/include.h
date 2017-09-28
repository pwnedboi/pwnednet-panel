//
//  include.h
//  panel
//
#pragma once

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stddef.h>
#include <cstdio>
#include <string>
#include <vector>
#include <array>

#include <sys/stat.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <sys/proc_info.h>
#include <libproc.h>

#include <curl/curl.h>
#include <curl//easy.h>

using namespace std;


void menu();
void printHeader();

// Input handling
void handleInput();

void hMining();
void hDdos();
void hUpdate();
void hStats();
void hKill();
