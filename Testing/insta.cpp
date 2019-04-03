#include <iostream>
#include <experimental/filesystem>
#include "CImg.h"
#include <variant>

namespace fs = std::experimental::filesystem::v1;
namespace c = cimg_library;

std::string path_downloaded = "";
std::string path_resized = "";

void print(auto data){
    std::cout<<data<<std::endl;
}

void resize(std::vector<std::string> files){
    c::CImg<unsigned char> image;
    c::CImg<unsigned char> image_grey;
    unsigned char black[] = {0,0,0};
    unsigned char white[] = {255,255,255};
    std::string new_path;
    std::string checked_path;
    for(std::string s : files){
        print(s);
        if(s.find("checked") != std::string::npos){
            print("[]Already checked!");
            continue;
        }
        image.load(s.c_str());
        //checked_path = s + ".checked";
        std::rename(s.c_str(),(s+".checked").c_str());
        //image.save(checked_path.c_str());
        image.resize(1080,1080);
        image_grey = image;
        image.draw_text(0,0,"@yourname",black,0,1,23);
        new_path = path_resized + "/resized_" + s.substr(s.find_last_of("/")+1,s.length());
        image.save(new_path.c_str());
        //greyscale
        image_grey.channel(0);
        image_grey.draw_text(0,0,"@yourname",white,0,1,23);
        image_grey.save((new_path + ".grey").c_str());


    }
}

int main()
{
    //INIT
    std::vector<std::string> files;
    print("[]InstaResizer! 0.1");



    for (auto & p : fs::directory_iterator(path_downloaded)){
        files.push_back(p.path().string());
        //print(p);
    }
    print("[]Paths added!");
    resize(files);


    return 0;
}
