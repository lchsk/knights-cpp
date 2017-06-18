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
        // List of json files to load
        // <path, identifier>
        std::vector<std::pair<std::string, std::string> > jsons = {
            {"assets/images/tiles.png.json", "tiles"}
        };

        for (const auto& j : jsons) {
            load_json(j.first, j.second);
        }
    }

    const json& DataLoader::get_json(const std::string& name)
    {
        if (_jsons.find(name) == _jsons.end())
            throw std::runtime_error(name + " not found");

        return _jsons[name];
    }

    void DataLoader::load_map(const std::string& filename)
    {
        load_json(MAPS_DIR + filename, filename);
    }

    void DataLoader::load_json(const std::string& path,
                               const std::string& identifier)
    {
        if (_jsons.find(identifier) != _jsons.end())
            throw std::runtime_error(identifier + " already exists");

        std::ifstream stream(path);

        if (stream.is_open()) {
            std::stringstream buffer;
            buffer << stream.rdbuf();

            _jsons[identifier] = json::parse(buffer.str());
        } else {
            throw std::runtime_error(path + " was not found");
        }
    }
}
