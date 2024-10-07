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
#include "teltonica_extended.h"


/* Usage */
void usage(void) {
    std::cerr
        << std::endl
        << "Kaitai struct Teltonica Extended protocol (codec 0x8E) test. Version " << mts::test::version::full << std::endl
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
                    _ifs.open(arg);
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
            mts::test::teltonica_extended_t _tp(&_ks);

            // Check codec ID
            if (mts::test::teltonica_extended_t::codec_type_t::CODEC_TYPE_CODEC8_EXTENDED != _tp.data()->codec_id()) {
                throw std::invalid_argument("The codec is not Teltonica Extended (0x8E)!");
            }
            // if (_tp.data()->number_of_data_1() != _tp.data()->number_of_data_2()) {
            //     throw std::invalid_argument("Number of records does not match!");
            // }

            // JSONize the result
            Json::StyledWriter  _writer;
            Json::Value         _v;
            Json::Value         _io_data;

            // Fill JSON
            _v["packet"]["preambule"]   = _tp.preamble();
            _v["packet"]["data_len"]    = _tp.len_data();
            _v["packet"]["codec_id"]    = _tp.data()->codec_id();
            _v["packet"]["records_num"] = _tp.data()->number_of_data_1();

            _v["packet"]["avl_data"]["timestamp"] = _tp.data()->avl_data()->timestamp();
            _v["packet"]["avl_data"]["priority"]  = _tp.data()->avl_data()->priority();

            /* GPS */
            {
                Json::Value _tmp;

                _tmp["longitude"]   = _tp.data()->avl_data()->gps()->longitude() * 0.0000001;
                _tmp["latitude"]    = _tp.data()->avl_data()->gps()->latitude() * 0.0000001;
                _tmp["altitude"]    = _tp.data()->avl_data()->gps()->altitude();
                _tmp["angle"]       = _tp.data()->avl_data()->gps()->angle();
                _tmp["satellites"]  = _tp.data()->avl_data()->gps()->satellites();
                _tmp["speed"]       = _tp.data()->avl_data()->gps()->speed();

                _v["packet"]["avl_data"]["gps_data"] = _tmp;
            }

            /* AVL Data */
            _v["packet"]["avl_data"]["io_data"]["event_id"]     = _tp.data()->avl_data()->io_element()->event_id();
            _v["packet"]["avl_data"]["io_data"]["total_ios"]    = _tp.data()->avl_data()->io_element()->total_io();


            // std::cout
            //     << "N1 = " << _tp.data()->avl_data()->io_element()->num_n1_data()
            //     << ", N2 = " << _tp.data()->avl_data()->io_element()->num_n2_data()
            //     << ", N4 = " << _tp.data()->avl_data()->io_element()->num_n4_data()
            //     << ", N8 = " << _tp.data()->avl_data()->io_element()->num_n8_data()
            //     << ", NX = " << _tp.data()->avl_data()->io_element()->num_nx_data()
            //     << std::endl;

            /* N1 */
            if (0 < _tp.data()->avl_data()->io_element()->num_n1_data()) {

                Json::Value _tmp;

                auto _n1 = _tp.data()->avl_data()->io_element()->n1_data();
                for (auto i = _n1->begin(); i != _n1->end(); ++i) {
                    _tmp["io_id"] = (*i).get()->key();
                    _tmp["value"] = (*i).get()->value();
                    _io_data.append(_tmp);
                }
            }

            /* N2 */
            if (0 < _tp.data()->avl_data()->io_element()->num_n2_data()) {

                Json::Value _tmp;

                auto _n2 = _tp.data()->avl_data()->io_element()->n2_data();
                for (auto i = _n2->begin(); i != _n2->end(); ++i) {
                    _tmp["io_id"] = (*i).get()->key();
                    _tmp["value"] = (*i).get()->value();
                    _io_data.append(_tmp);
                }
            }

            /* N4 */
            if (0 < _tp.data()->avl_data()->io_element()->num_n4_data()) {

                Json::Value _tmp;

                auto _n4 = _tp.data()->avl_data()->io_element()->n4_data();
                for (auto i = _n4->begin(); i != _n4->end(); ++i) {
                    _tmp["io_id"] = (*i).get()->key();
                    _tmp["value"] = (*i).get()->value();
                    _io_data.append(_tmp);
                }
            }

            /* N8 */
            if (0 < _tp.data()->avl_data()->io_element()->num_n8_data()) {

                Json::Value _tmp;

                auto _n8 = _tp.data()->avl_data()->io_element()->n8_data();
                for (auto i = _n8->begin(); i != _n8->end(); ++i) {
                    _tmp["io_id"] = (*i).get()->key();
                    _tmp["value"] = (*i).get()->value();
                    _io_data.append(_tmp);
                }
            }

            /* NX */
            if (0 < _tp.data()->avl_data()->io_element()->num_nx_data()) {

                Json::Value _tmp;

                // auto _nx = _tp.data()->avl_data()->io_element()->nx_data();
                // for (auto i = _nx->begin(); i != _nx->end(); ++i) {
                //     _tmp["io_id"] = (*i).get()->key();
                //     _tmp["value"] = (*i).get()->value();
                //      _io_data.append(_tmp);
                // }
            }

             _v["packet"]["avl_data"]["io_data"]["io_data"] = _io_data;

            // Dump the result
            std::string _output = _writer.write(_v);
            std::cout
                << "------------------------------------------------------------------" << std::endl
                << _output
                << "------------------------------------------------------------------" << std::endl
                << std::endl;

        } else {

        }
    } catch (const std::exception& _e) {
        std::cerr << "Parsing error: " << _e.what() << std::endl;
    }

    return 0;
}


/* End of file */