//
// Created by root on 18-3-14.
//
#define CATCH_CONFIG_RUNNER
#include <rviz_visualise_tools/catch.hpp>
#include <rviz_visualise_tools/visual_tool.h>
TEST_CASE_METHOD(visual_tool,"test","[test]"){
    std::vector<unsigned char> vector_value = {0,203,203,236,236,0};
    while(true){
        publishOccupancyGrid(0.1,2,3,vector_value);
        sleep(2);
    }
}
TEST_CASE("test_case","[test_case]"){
    REQUIRE(1 == 1);
}
int main(int argc,char* argv[]){
    ros::init(argc,argv,"test_node");
    int result = Catch::Session().run(argc,argv);
    return result;
}

