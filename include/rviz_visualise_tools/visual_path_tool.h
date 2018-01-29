//
// Created by root on 18-1-29.
//

#ifndef RVIZ_VISUALIZE_TOOLS_VISUAL_PATH_TOOL_H
#define RVIZ_VISUALIZE_TOOLS_VISUAL_PATH_TOOL_H

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/OccupancyGrid.h>
#include <ros/console.h>
#include <geometry_msgs/PoseStamped.h>
class visual_path_tool {
public:
    visual_path_tool(std::string path_topic,std::string map_topic, ros::NodeHandle nh = ros::NodeHandle("~"));
    void publishPath(std::vector<double>& x_vec,std::vector<double>& y_vec);
    void publishPath(std::vector<geometry_msgs::PoseStamped>& pose_stamped_vec);
    void publishPath(std::vector<geometry_msgs::Pose>& pose_vec);
    void publishPath(nav_msgs::Path& path);
    void publishOccupancyGrid();
private:
    ros::Publisher path_publisher;
    ros::Publisher map_publisher;
    const std::string path_topic_name,map_topic_name;
    ros::NodeHandle nh_;
};


#endif //RVIZ_VISUALIZE_TOOLS_VISUAL_PATH_TOOL_H
