#include "file_handler.h"
#include <fstream>
#include <iostream>
// struct Placement {
    // x: int,
    // y: int,
    // height: int,
    // width int,
// }



Game_map File_handler::load_map(std::string file_name) { 
    Game_map map {0,0};
    std::fstream file;
    file.open(file_name);

    file >> map.width >> map.height;
    std::cout << map.height << std::endl;
    std::cout << map.width << std::endl;
    return map;
}