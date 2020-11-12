//
// Created by z on 2020/11/12.
//

#include "Collector.h"

const int PreparePort = 10002;
const int CommitPort = 10003;
const char* logFileName = "./logger.txt";

#define LOG(...) {                                          \
    std::time_t t = std::time(NULL);                        \
    std::string logTime = std::asctime(std::localtime(&t)); \
    logTime.pop_back();                                     \
    pid_t tmppid = getpid();                                   \
    timeval tv{};                                             \
    gettimeofday(&tv, nullptr);                             \
    int ft = tv.tv_usec / 10;                        \
    fprintf(logfp, "pid:[%d]\t%s, ms:%d\t%s\n", tmppid, logTime.c_str(), ft, __VA_ARGS__);\
}

Collector::Collector() {
    logfp = Fopen(logFileName, "w");
    listenPreparefd = 0;
    listenCommitfd = 0;
}

bool Collector::collect4prepare() {
    LOG(__func__);
    Collector::openPreparePort();

}

bool Collector::collect4commit() {
    LOG(__func__);
    Collector::openCommitPort();
}

int Collector::openPreparePort() {
    LOG(__func__);
    // epoll
    listenPreparefd = Open_listenfd(PreparePort);
    sockaddr_in serverAddr{};
    socklen_t serverAddrLen = sizeof(serverAddr);
    int connfd = Accept(listenPreparefd, (sockaddr*) &serverAddr, &serverAddrLen);
    rio_t rio{};
    char buf[MAXBUF];
    char retBuf[] = "get";
    Rio_readinitb(&rio, connfd);
    size_t n;
    // write to testFile test message
    while ((n = Rio_readlineb(&rio, buf, MAXLINE) != 0)) {
        Rio_writen(1, buf, strlen(buf));
        Rio_writen(connfd, retBuf, strlen(retBuf));
    }
    close(connfd);
    return 0;
}

int Collector::openCommitPort() {
    LOG(__func__);
    listenCommitfd = Open_listenfd(CommitPort);
    sockaddr_in serverAddr{};
    socklen_t serverAddrLen = sizeof(serverAddr);
    int connfd = Accept(listenCommitfd, (sockaddr*) &serverAddr, &serverAddrLen);
    rio_t rio{};
    char buf[MAXBUF];
    Rio_readinitb(&rio, connfd);
    size_t n;
    // write to testFile test message
    while ((n = Rio_readlineb(&rio, buf, MAXLINE) != 0)) {
        Rio_writen(1, buf, strlen(buf));
    }
    close(connfd);
}

Collector::~Collector() {
    close(listenPreparefd);
    close(listenCommitfd);
    Fclose(logfp);
}

void start() {
    Collector c;
    c.collect4prepare();
    c.openPreparePort();
}
