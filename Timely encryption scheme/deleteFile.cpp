#include "AES.h"

void deleteFile(string Filename) {
    if (std::remove(Filename.c_str()) == 0) {
        std::cout << "File deleted successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to delete the file." << std::endl;
    }
};