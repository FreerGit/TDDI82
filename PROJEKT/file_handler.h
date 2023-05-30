#include <string>

struct Game_map {
    unsigned int height;
    unsigned int width;
    // platforms: vector<Placement>;
};


class File_handler {
public:
    File_handler() = default;
    ~File_handler() = default;
    // SFML::image load_sprite(std::string file_name);
    Game_map load_map(std::string);
};