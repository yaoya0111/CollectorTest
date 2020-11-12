//
// Created by z on 2020/11/12.
//

#ifndef COLLECTORTTEST_COLLECTOR_H
#define COLLECTORTTEST_COLLECTOR_H

#include "csapp.h"
#include <string>
#include <sys/time.h>
#include <ctime>
#include <sys/epoll.h>
#include <fstream>
#include <functional>

class Collector {
    FILE* logfp;
    int listenPreparefd;
    int listenCommitfd;
public:
    Collector();
    int openPreparePort();
    int openCommitPort();
    bool collect4prepare();
    bool collect4commit();
    ~Collector();
};

void start();

#endif //COLLECTORTTEST_COLLECTOR_H
