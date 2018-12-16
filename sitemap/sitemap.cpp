// sitemap.cpp : Defines the entry point for the application.
//

#include <filesystem>
#include <algorithm>
#include "json.hpp"
#include "sitemap.h"

namespace fs = std::filesystem;

using namespace std;
using namespace sitemap;

bool is_html_file(std::string_view filename) {
    if (filename.length() > 5) {
        if ((filename.substr(filename.size() - 4) == ".htm") ||
            (filename.substr(filename.size() - 5) == ".html"))
            return true;
    }

    return false;
}

int main(int argc, char** argv)
{
    if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " [folder]" << std::endl;
        return 1;
    }

    std::string folder = argv[1];
    Sitemap sitemap("http://vincela.com/");

    for (auto& p : fs::recursive_directory_iterator(folder)) {
        // Get path and strip name of current folder
        std::string path = fs::path(p).relative_path().string();
        path = path.substr(folder.length() + 1); // +1 is to handle trailing slash

#ifdef _MSC_VER
        std::replace(path.begin(), path.end(), '\\', '/');
#endif

        if (is_html_file(path)) {
            UrlInfo url(path);
            sitemap.addUrl({ path });
        }
    }

    std::cout << (string)sitemap << std::endl;

	return 0;
}
