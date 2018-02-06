#include <iostream>
#include <fstream>
#include <sstream>
#include <rviz_visualise_tools/visual_tool.h>
#include <rviz_visualise_tools/general_tool.h>
void readCostMapFromFile(std::vector<int>& value_vec);
int main(int argc,char** argv) {
    std::cout << "Hello, World!" << std::endl;
    std::string node_name = "visualise_tools";
    ros::init(argc,argv,node_name);
    visual_tool tool("path","map");

    std::vector<double> x_vec,y_vec;
    double index = 0.0;
    ros::Duration d(5);
    ros::Rate r(d);
    for (int i = 0; i < 480; ++i) {
        x_vec.push_back(index);
        y_vec.push_back(index);
        index += 1.0;
    }
    std::vector<int> value_vec;
    unsigned int width,height;//willow-full.pgm,tb_condo_2.pgm
    readPgm("/home/pengjiawei/willow-full.pgm",width,height,value_vec);
//    readCostMapFromFile(value_vec);
//    tool.publishOccupancyGrid(1,480,480,value_vec);
    printf("value_vec size = %d\n",value_vec.size());
    printf("width = %d, height =%d\n",width,height);
//    tool.publishPgm(0.05,2,2,value_vec);
    while(ros::ok()){
        tool.publishPath(x_vec,y_vec);
//        tool.publishOccupancyGrid(1,480,480,value_vec);
        tool.publishPgm(0.01,height,width,value_vec);
        ros::spinOnce();
        ROS_INFO("publish");
        r.sleep();
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

