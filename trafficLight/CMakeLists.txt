add_executable(trafficLight trafficLight.cpp main.cpp)
target_link_libraries(trafficLight ${MP2_LIBRARY})
target_include_directories(trafficLight PRIVATE ${MP2_INCLUDE})