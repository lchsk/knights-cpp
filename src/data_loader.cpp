#include "data_loader.h"

namespace ks
{
    static const std::string DATA_DIR = "data/";

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
            std::ifstream stream(DATA_DIR + filename);

            if (stream.is_open()) {
                std::cout << filename << " " << "open" << std::endl;

                std::stringstream buffer;
                buffer << stream.rdbuf();

                _jsons[std::string(filename.begin(), filename.end() - 5)] = json::parse(buffer.str());

                std::cout << _jsons[filename] << std::endl;
            } else {
                std::cout
                    << filename
                    << " "
                    << "not found in "
                    << DATA_DIR
                    << std::endl;
            }
        }
    }

    const json& DataLoader::get_json(const std::string name)
    {
        return _jsons[name];
    }
}
