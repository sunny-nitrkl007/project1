#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    //char filename[] = "10129_ÿÿÿÿÿÿÿÿ1190304181742_DQ1.VP3";
    char filename[] = "10129_        1190304181742_DQ1.VP3";

    // Replace with bad characters
    unsigned char badchar = 0xFF;
    filename[6] = static_cast<char>(badchar);
    filename[7] = static_cast<char>(badchar);
    filename[8] = static_cast<char>(badchar);
    filename[9] = static_cast<char>(badchar);
    filename[10] = static_cast<char>(badchar);
    filename[11] = static_cast<char>(badchar);
    filename[12] = static_cast<char>(badchar);
    filename[13] = static_cast<char>(badchar);

    std::string filepath = "./";
    filepath += std::string(filename, sizeof(filename)/sizeof(filename[0]));

    std::ofstream ofs;
    ofs.open(filepath);
    if (ofs) {
        ofs << "garbage" << std::endl;
        ofs.close();
        std::cout << "Wrote file: " << filepath << std::endl;
        return 0;
    }

    std::cerr << "Could not open file: " << filepath << std::endl;
    return 1;
}
