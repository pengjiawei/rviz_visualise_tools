#include <iostream>
#include <rviz_visualise_tools/visual_path_tool.h>
int main(int argc,char** argv) {
    std::cout << "Hello, World!" << std::endl;
    std::string node_name = "visualise_tools";
    ros::init(argc,argv,node_name);
    ROS_DEBUG("initial ros\n");
    visual_path_tool tool("path","map");
    std::vector<double> x_vec,y_vec;
    double index = 0.0;
    ros::Rate r(10);
    for (int i = 0; i < 10; ++i) {

        x_vec.push_back(index);
        y_vec.push_back(index);
        index += 1.0;
    }
    while(ros::ok()){
        tool.publishPath(x_vec,y_vec);
        tool.publishOccupancyGrid();
        ros::spinOnce();
        printf("publish\n");
        r.sleep();
    }

//        ros::spin();

    return 0;
}
