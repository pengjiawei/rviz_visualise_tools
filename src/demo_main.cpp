#include <iostream>
#include <fstream>
#include <sstream>
#include <rviz_visualise_tools/visual_tool.h>
#include <rviz_visualise_tools/general_tool.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

void readCostMapFromFile(std::vector<int>& value_vec);
int main(int argc,char** argv) {
    std::cout << "Hello, World!" << std::endl;
    std::string node_name = "visualise_tools";
    ros::init(argc,argv,node_name);
    visual_tool tool("path","map");

    std::vector<double> x_vec,y_vec;
    ros::Duration d(5);
    ros::Rate r(d);
    std::vector<int> value_vec;
    unsigned int width,height;//willow-full.pgm,tb_condo_2.pgm
//    readPgm("/home/pengjiawei/map.pgm",width,height,value_vec);
    work_done = false;
    char* recvData;
    recvData = new char[BUFF_SIZE];
    boost::thread recvThread(SocketReceive,recvData,12345,"/tmp/recvFile.txt");

//    tool.publishPgm(0.05,2,2,value_vec);
    while(ros::ok() && !work_done){
        boost::mutex::scoped_lock lock(mutex);
        cv.wait(mutex);
        lock.unlock();

        std::ifstream file("/tmp/recvFile.txt",ifstream::out);
//        boost::archive::text_iarchive ia(file);
        boost::archive::binary_iarchive ia(file);
        int width,height;
        double resolution;
        int i;
        ia >> width >> height >> resolution;
        ROS_INFO("width = %d,height =%d, resolution = %4f",width,height,resolution);
        for(int32 y = 0 ; y < 480 ; ++y){
            for(int32 x = 0; x< 480 ; ++x){
                ia >> i;
                value_vec.push_back(i);
            }
        }
        tool.publishOccupancyGrid(0.01,480,480,value_vec);
//        tool.publishPgm(0.01,height,width,value_vec);
        ros::spinOnce();

        ROS_INFO("publish");
//        r.sleep();
    }


    return 0;
}
///line of file is like this eg: x y value
void readCostMapFromFile(std::vector<int>& value_vec){
    std::ifstream fin("/home/pengjiawei/costmap.log");
    std::string s;
    int x,y,value ;

    while(!fin.eof()){
        getline(fin,s);
        std::stringstream stringin(s);
        stringin >> x;
        stringin >> y;
        stringin >> value;
//        x_vec.push_back(x);
//        y_vec.push_back(y);
        value_vec.push_back(value);
    }
    fin.close();
    printf("size = %d\n",value_vec.size());
}

