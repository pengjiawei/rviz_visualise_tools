//
// Created by root on 18-1-30.
//

#ifndef RVIZ_VISUALISE_TOOLS_GENERAL_TOOL_H
#define RVIZ_VISUALISE_TOOLS_GENERAL_TOOL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <tiff.h>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
using namespace std;
const int BUFF_SIZE = 1024;
bool work_done;
boost::mutex mutex;

boost::condition cv;
void SocketReceive(char* recvData,int port,std::string recvFileName) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bzero(&(server_addr.sin_zero), 8);

    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_fd == -1) {
        printf("Create goal socket failure!");
    }
    //绑定socket
    int bind_result = bind(server_sock_fd, (struct sockaddr *) &server_addr,
                           sizeof(server_addr));
    if (bind_result == -1) {
        printf("Set goal port failure!");
    }
    //listen
    printf("i am listening!!!!!!!!!!\n");
    if (listen(server_sock_fd, 3) == -1) {
        printf("Listen goal port error!");
    }

    fd_set server_fd_set;
    int max_fd = -1;
//    struct timeval tv;
//    int times = 0;
//    tv.tv_sec = 5;
//    tv.tv_usec = 0;


    while (true) {


        FD_ZERO(&server_fd_set);
        FD_SET(server_sock_fd, &server_fd_set);

        int ret = select(server_sock_fd + 1, &server_fd_set, NULL, NULL, NULL);
        printf("select return = %d\n", ret);
        if (ret > 0) {
            int client_sock_fd = 0;
            bool flag = FD_ISSET(server_sock_fd, &server_fd_set);
            printf("is in the set? = %d\n", flag);
            if (flag) {
                struct sockaddr_in client_address;
                memset(&client_address, 0, sizeof(client_address));

                socklen_t address_len = sizeof(client_address);
                printf("i am accept!!!!!!!!!!\n");
                client_sock_fd = accept(server_sock_fd,
                                        (struct sockaddr *) &client_address, &address_len);

                printf("client_sock_fd = %d\n", client_sock_fd);
                if (client_sock_fd <= 0) {
                    printf("client_sock_tf_in_controller < 0");
                }
            }

            if (client_sock_fd != 0) {


                memset(recvData, 0, BUFF_SIZE);

                printf("sizeof recv Data = %d\n",sizeof(recvData));
                size_t byte_num = 0;
                size_t all = 0;
                int offset = 0;

                FILE* file = fopen(recvFileName.c_str(),"w+");
                while(byte_num = recv(client_sock_fd, recvData, BUFF_SIZE,
                                      0)){
                    printf("recv_return = %d\n", byte_num);
                    all += byte_num;

                    int write_length = fwrite(recvData, sizeof(char),byte_num,file);
                    printf("write_length = %d\n",write_length);
                    bzero(recvData,BUFF_SIZE);
                }
                printf("all recv size = %d\n",all);
                fclose(file);
                boost::mutex::scoped_lock lock(mutex);
                cv.notify_one();
                lock.unlock();
                if (byte_num > 0) {
                } else if (byte_num < 0) {
                    close(client_sock_fd);
                    client_sock_fd = 0;
                } else {
                    FD_CLR(client_sock_fd, &server_fd_set);
                    client_sock_fd = 0;
                }
            }
        } else if (ret == 0) {
            FD_ZERO(&server_fd_set);
            FD_SET(server_sock_fd, &server_fd_set);
        }
    }
}
void readPgm(std::string pgm_file_path,unsigned int& width ,unsigned int& height,std::vector<int>& value_vec){
    int row = 0, col = 0;
    ifstream infile(pgm_file_path);
    stringstream ss;
    string inputLine = "";

    // First line : version
    getline(infile,inputLine);
    if(inputLine.compare("P5") != 0) cerr << "Version error" << endl;
    else cout << "Version : " << inputLine << endl;

    // Second line : comment
    getline(infile,inputLine);

    while(inputLine.find("#") != string::npos){
        cout << "Comment : " << inputLine << endl;
        getline(infile,inputLine);
    }
    // Continue with a stringstream
    ss << infile.rdbuf();
    // Third line : size
    stringstream wwhhss(inputLine);
    wwhhss >> width >> height;
    cout << width << " columns and " << height << " rows" << endl;

    int array[height][width];

    int max_value;
    ss >> max_value;
    cout <<"max value = "<<max_value<<endl;
    unsigned char pixel;
    // Following lines : data
    for(row = 0; row < height; ++row){
        for (col = 0; col < width; ++col){
            ss >> pixel;
            array[row][col] = pixel;
            value_vec.push_back(pixel);
        }
    }
    // Now print the array to see the result
    FILE* file = fopen("/home/pengjiawei/pixels.log","a");
    for(row = 0; row < height; ++row) {
        for(col = 0; col < width; ++col) {
            fprintf(file,"%d\n",array[row][col]);
        }
    }

    fclose(file);
    infile.close();
}


#endif //RVIZ_VISUALISE_TOOLS_GENERAL_TOOL_H
