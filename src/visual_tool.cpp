//
// Created by root on 18-1-29.
//

#include "rviz_visualise_tools/visual_tool.h"
visual_tool::visual_tool(const std::string& path_topic, const std::string& map_topic, ros::NodeHandle nh) : path_topic_name(path_topic),map_topic_name(map_topic),nh_(nh){
    path_publisher = nh_.advertise<nav_msgs::Path>(path_topic,1);
    map_publisher = nh_.advertise<nav_msgs::OccupancyGrid>(map_topic,1);
    ROS_INFO("initial publisher with topic = %s\n",path_topic.c_str());
}
void visual_tool::publishPath(const std::vector<double>& x_vec,const std::vector<double>& y_vec) {
    if(x_vec.size() != y_vec.size()){
        ROS_ERROR("size of x and y is not compatible");
    }
    nav_msgs::Path path;
    for (int i = 0; i < x_vec.size(); ++i) {
        geometry_msgs::PoseStamped poseStamped;
        poseStamped.pose.position.x = x_vec[i];
        poseStamped.pose.position.y = y_vec[i];
        path.poses.push_back(poseStamped);
    }
    publishPath(path);
}
void visual_tool::publishPath(const std::vector<geometry_msgs::PoseStamped>& pose_stamped_vec) {
    nav_msgs::Path path;
    path.header.stamp = pose_stamped_vec[0].header.stamp;
    path.poses.assign(pose_stamped_vec.begin(),pose_stamped_vec.end());
    publishPath(path);
}
void visual_tool::publishPath(const std::vector<geometry_msgs::Pose>& pose_vec){
    nav_msgs::Path path;
    path.header.stamp = ros::Time::now();
//    path.header.frame_id
    for (int i = 0; i < pose_vec.size(); ++i) {
        geometry_msgs::PoseStamped poseStamped;
        poseStamped.pose = pose_vec[i];
        poseStamped.header.stamp = ros::Time::now();
        path.poses.push_back(poseStamped);
    }
    publishPath(path);
}
void visual_tool::publishPath( nav_msgs::Path& path) {
    path.header.frame_id = "world";
    path_publisher.publish(path);
}

void visual_tool::publishOccupancyGrid(const float& resolution,const unsigned int& width,const unsigned int& height,const std::vector<int>& cost_map_vec){
    if(costmap_to_occ_table == NULL){
        initCostMapToOccTable();
    }
    nav_msgs::OccupancyGrid map;
    map.info.resolution = resolution;
    map.info.width = width;
    map.info.height = height;
    std::vector<int8_t > map_vec;
    int index = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            index = j + i * height;
            map_vec.push_back(costmap_to_occ_table[cost_map_vec[index]]);
        }
    }
    map.data = map_vec;
    publishOccupancyGrid(map);
}
void visual_tool::publishPgm(const float &resolution,const unsigned int &width,const unsigned int &height,
                             const std::vector<int> &grey_vec) {
    nav_msgs::OccupancyGrid map;
    map.header.stamp = ros::Time::now();
    map.info.resolution = resolution;
    map.info.width = width;
    map.info.height = height;
    std::vector<int8_t > map_vec;
    int index = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            index = j + i * height;
            map_vec.push_back(pgmToOccValue(grey_vec[index]));
        }
    }
    map.data = map_vec;
    publishOccupancyGrid(map);
}
void visual_tool::publishOccupancyGrid(const nav_msgs::OccupancyGrid &map) {
    map_publisher.publish(map);
}
void visual_tool::initCostMapToOccTable() {
    costmap_to_occ_table = new char[256];
    costmap_to_occ_table[0] = 0;
    costmap_to_occ_table[253] = 99;
    costmap_to_occ_table[254] = 100;
    costmap_to_occ_table[255] = -1;
    for(int i = 1; i < 253; i++)
    {
        costmap_to_occ_table[i] = char(1 + (97 * (i - 1)) / 251);
    }
}
int8_t visual_tool::pgmToOccValue(int pgm_value) {
    int8_t value = 0;
    if(pgm_value == 255){
        value = 0;
    }else if(pgm_value == 205){
        value = -1;
    }else if(pgm_value == 0){
        value = 100;
    }
    return value;
}