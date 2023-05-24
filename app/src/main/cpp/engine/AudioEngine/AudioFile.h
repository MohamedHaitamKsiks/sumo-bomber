//
// Created by Homepunk on 15.01.2020.
//

#include <string>
#include <array>

class AudiFile {
public:
    AudiFile(std::string name/*, int bytesArr[]*/) {
        AudiFile::name = name;
//        AudiFile::bytes_arr = bytesArr;
    }

    ~AudiFile() {
//        delete bytes_arr;
    }

    void set_name(std::string name) {
        AudiFile::name = name;
    }

    std::string get_name() {
        return AudiFile::name;
    }
/*
    int* get_bytes_arr() {
        return AudiFile::bytes_arr;
    }*/

private:
    std::string name;
//    int bytes_arr[];
};
