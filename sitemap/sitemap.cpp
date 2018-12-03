// sitemap.cpp : Defines the entry point for the application.
//

#include <filesystem>
#include "json.hpp"
#include "sitemap.h"

namespace fs = std::filesystem;

using namespace std;
using namespace sitemap;

int main(int argc, char** argv)
{
    if (argc > 1) {
        std::cout << "Usage: " << argv[0] << " [folder]" << std::endl;
        return 1;
    }

    for (auto& p : fs::directory_iterator("")) {
        std::cout << p << std::endl;
    }

    Sitemap sitemap("http://vincela.com/");
    sitemap.addUrl({ "index.html" });
    sitemap.addUrl({ "blog/index.html" });

    std::cout << (string)sitemap << std::endl;

	return 0;
}
