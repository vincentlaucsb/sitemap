// sitemap.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string_view>
#include <sstream>
#include <vector>
#include <unordered_map>

namespace sitemap {
    namespace xml {
        class Element;

        using List = std::vector<Element>;
        using Value = std::string;

        class Element {
        public:
            Element(
                std::string_view _tag,
                const std::string& _value="") : 
                tag(_tag), child_value(_value) {};

            void operator<<(std::string_view value) {
                this->child_value = value;
            }

            void operator<<(const Element& elem) {
                this->children.push_back(elem);
            }

            operator std::string() {
                return str();
            }

        private:
            std::string tag;
            List children = {};
            Value child_value;

            std::string str(const size_t indent_level = 0) {
                // Create a string representation of the XML Element
                std::stringstream temp;
                std::string indent(indent_level, '\t');
                std::string tag_end = "</" + this->tag + ">";
                temp << indent << "<" << this->tag << ">";

                if (!child_value.empty()) {
                    temp << child_value;
                    temp << tag_end;
                }
                else {
                    for (auto child : children) {
                        temp << std::endl << (std::string)child.str(indent_level + 1) << std::endl;
                    }

                    temp << indent << tag_end;
                }
                
                return temp.str();
            }
        };
    }

    struct UrlInfo {
        UrlInfo(std::string_view url) : loc(url) {};
        std::string loc;
        std::string lastmod = "";
        std::string changefreq = "";
        double priority = -1;
    };

    class Sitemap {
    public:
        Sitemap(std::string_view _root = "") : root(_root) {

        }

        void addUrl(const UrlInfo& info) {
            auto temp = xml::Element("url");

            // Concatenate root to URL
            temp << xml::Element("loc", this->root + info.loc);

            urlset << temp;
        }

        operator std::string() {
            std::stringstream temp;
            temp << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
            temp << (std::string)urlset;
            return temp.str();
        }

    private:
        std::string root;
        xml::Element urlset = xml::Element("urlset");
    };
}