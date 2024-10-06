/*!
 *	\file		main.cpp
 *	\brief		Gather everything together
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		05.10.2024
 *	\version	1.0
 */

#include "version.hpp"
#include <iostream>
#include <fstream>
#include "teltonica_proto.h"


/* Usage */
void usage(void) {
    std::cerr
        << std::endl
        << "Kaitai struct Teltonica protocol test. Version " << mts::test::version::full << std::endl
        << "-----------------------------------------------" << std::endl
        << "Usage: " << mts::test::name() << "[options] <filename>" << std::endl << std::endl
        << "-d|--direction (bin|json)" << std::endl
        << "-v|--version" << std::endl
        << "-h|--help" << std::endl
        << std::endl;    
}

/* Main */
int main(int argc, char* argv[], char* env[]) {

    // Process arguments
    std::string _direction("json");
    std::ifstream src;
    try {
        if (2 > argc) {
            throw std::invalid_argument("Too few arguments");
        }

        for (int i = 1; argc > i; ++i) {

            std::string arg(argv[i]);

            if ("-h" == arg || "--help" == arg) {
                throw std::invalid_argument("Too few arguments");
            } else if ("-v" == arg || "--version" == arg) {
                std::cerr << mts::test::version::full << std::endl;
                return 1;
            } else if ("-d" == arg || "--destination" == arg) {
                if (argc > i + 1) {
                    arg.assign(argv[i + 1]);
                    if ("bin" == arg) {
                        ++i;
                        _direction.assign("bin");
                    } else if ("json" == arg) {
                        ++i;
                    } else {
                        throw std::invalid_argument("Invalid argument");
                    }
                }
            } else {
                if (0 == _direction.compare("bin")) {
                    src.open(arg, std::fstream::binary);

                    kaitai::kstream ks(&src);
                    mts::test::teltonica_proto_t* tp = new mts::test::teltonica_proto_t(&ks);

                    delete tp;

                } else {
                    src.open(arg, std::fstream::in);
                }
                if (src.fail()) {
                    std::string e = "File \"" + arg + "\" not found or not accessiable";
                    throw std::runtime_error(e);
                }
            }
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        usage();
        return 2;
    } catch (const std::exception& e) {
        std::cerr << e.what() << ". Exiting ..." << std::endl;
        return 3;
    }

    return 0;
}


/* End of file */