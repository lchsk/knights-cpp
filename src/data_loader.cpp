#include "data_loader.h"

namespace ks
{
    static const std::string DATA_DIR = "data/";
    static const std::string MAPS_DIR = "maps/";

    DataLoader::DataLoader()
    {
        load_jsons();
    }

    DataLoader::~DataLoader()
    {

    }

    void DataLoader::load_jsons()
    {
        std::vector<std::string> filenames = {
            "knights_archer.json"
        };

        for (const auto& filename : filenames) {
            std::string name = std::string(filename.begin(), filename.end() - 5);

            _jsons[name] = load_json(DATA_DIR + filename);
        }
    }

    const json& DataLoader::get_json(const std::string name)
    {
        return _jsons[name];
    }

    const json& DataLoader::load_map(const std::string filename)
    {
        _map = load_json(MAPS_DIR + filename);

        return _map;
    }

    json DataLoader::load_json(std::string path)
    {
        std::ifstream stream(path);

        if (stream.is_open()) {
            std::stringstream buffer;
            buffer << stream.rdbuf();

            return json::parse(buffer.str());
        }
    }
}
