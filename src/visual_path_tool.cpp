//
// Created by root on 18-1-29.
//

#include "rviz_visualise_tools/visual_path_tool.h"
visual_path_tool::visual_path_tool(std::string path_topic, std::string map_topic, ros::NodeHandle nh) : path_topic_name(path_topic),map_topic_name(map_topic),nh_(nh){
    path_publisher = nh_.advertise<nav_msgs::Path>(path_topic,1,true);
    map_publisher = nh_.advertise<nav_msgs::OccupancyGrid>(map_topic,10, true);
    ROS_INFO("initial publisher with topic = %s\n",path_topic.c_str());
}
void visual_path_tool::publishPath(std::vector<double>& x_vec, std::vector<double>& y_vec) {
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
void visual_path_tool::publishPath(std::vector<geometry_msgs::PoseStamped>& pose_stamped_vec) {
    nav_msgs::Path path;
    path.header.stamp = pose_stamped_vec[0].header.stamp;
    path.poses.assign(pose_stamped_vec.begin(),pose_stamped_vec.end());
    publishPath(path);
}
void visual_path_tool::publishPath(std::vector<geometry_msgs::Pose>& pose_vec){
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
void visual_path_tool::publishPath(nav_msgs::Path& path) {
    path.header.frame_id = "world";
    path_publisher.publish(path);
}

void visual_path_tool::publishOccupancyGrid(){
    nav_msgs::OccupancyGrid map;
    map.info.resolution = 1;
    map.info.width = 480;
    map.info.height = 480;
    int8_t a[4] = {100,100,50,0};
    std::vector<int8_t > map_vec;
    for (int i = 0; i < 480*480; ++i) {
        map_vec.push_back(a[i%4]);
    }
    map.data = map_vec;
    map_publisher.publish(map);
}