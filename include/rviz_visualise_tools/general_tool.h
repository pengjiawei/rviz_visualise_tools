//
// Created by root on 18-1-30.
//

#ifndef RVIZ_VISUALISE_TOOLS_GENERAL_TOOL_H
#define RVIZ_VISUALISE_TOOLS_GENERAL_TOOL_H

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
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
