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
class visual_tool {
public:
    visual_tool(const std::string& path_topic,const std::string& map_topic, ros::NodeHandle nh = ros::NodeHandle("~"));
    void publishPath(const std::vector<double>& x_vec,const std::vector<double>& y_vec);
    void publishPath(const std::vector<geometry_msgs::PoseStamped>& pose_stamped_vec);
    void publishPath(const std::vector<geometry_msgs::Pose>& pose_vec);
    void publishPath( nav_msgs::Path& path);
    void publishOccupancyGrid(const float& resolution,const unsigned int& width,const unsigned int& height,const std::vector<int>& cost_map_vec);
    void publishOccupancyGrid(const nav_msgs::OccupancyGrid& map);
    void publishPgm(const float& resolution,const unsigned int& width,const unsigned int& height,const std::vector<int>& cost_map_vec);
    ///value of costmap to value of occupancyGrid
    void initCostMapToOccTable();
    int8_t pgmToOccValue(int pgm_value);

    void getPathTopic(std::string& path_topic){
        path_topic = path_topic_name;
    }
    void getMapTopic(std::string& map_topic){
        map_topic = map_topic_name;
    }
private:
    ros::Publisher path_publisher;
    ros::Publisher map_publisher;
    const std::string path_topic_name,map_topic_name;
    ros::NodeHandle nh_;
    ///used for translating value of costMap to occupancyGrid
    char* costmap_to_occ_table = NULL;
};


#endif //RVIZ_VISUALIZE_TOOLS_VISUAL_PATH_TOOL_H
