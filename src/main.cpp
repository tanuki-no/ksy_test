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
#include <json/json.h>
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
int main(
    const int argc,
    const char* argv[],
    const char* env[]) {

    // Process arguments
    std::string _direction("json");
    std::ifstream _ifs;
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
                if ("bin" == _direction) {
                    _ifs.open(arg, std::fstream::binary);
                } else {
                    _ifs.open(arg, std::fstream::in);
                }
                if (_ifs.fail()) {
                    std::string e = "File \"" + arg + "\" not found or not accessiable";
                    throw std::runtime_error(e);
                }
            }
        }
    } catch (const std::invalid_argument& _e) {
        std::cerr << _e.what() << std::endl;
        usage();
        return 2;
    } catch (const std::exception& _e) {
        std::cerr << _e.what() << ". Exiting ..." << std::endl;
        return 3;
    }

    /* Do parsing here to make it more clear to understand */
    try {
        if ("bin" == _direction) {

            // Create Kaitai stream
            kaitai::kstream _ks(&_ifs);

            // Construct object from stream
            mts::test::teltonica_proto_t* _tp = new mts::test::teltonica_proto_t(&_ks);

            // JSONize the result
            Json::StyledWriter  _jsw;
            Json::Value         _v;
            
            // Dump the result
            std::cout << _jsw.write(_v);

            // Wash dirty laundry
            delete _tp;

        } else {

        }
    } catch (const std::exception& _e) {
        std::cerr << "Parsing error: " << _e.what() << std::endl;
    }

    return 0;
}


/* End of file */