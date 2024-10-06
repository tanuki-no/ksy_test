#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <iomanip>


void usage(const char* name) {
    std::cerr << "Usage: " << name << " <input> <output>" << std::endl; 
}

uint8_t to_hex(const unsigned char c) {

    switch (c) {
        
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return (c - '0'); break;

        case 'a': case 'A': return 0xA; break;
        case 'b': case 'B': return 0xB; break;
        case 'c': case 'C': return 0xC; break;
        case 'd': case 'D': return 0xD; break;
        case 'e': case 'E': return 0xE; break;

        default:
            return 0xF;
    }
    return 0;
}

int main(
    const int argc,
    const char* argv[],
    const char* arge[]) {

    try {

        if (3 > argc) {
            usage(argv[0]);
            throw std::invalid_argument("Too few args");
        }

        std::ifstream   _ifs(argv[1]);
        std::ofstream   _ofs(argv[2], std::ofstream::binary);
        uint8_t         _b_out = 0;
        bool            _shift = true, _skip_line = false;
        unsigned int    _line_no = 0;

        for (std::string _line; std::getline(_ifs, _line); _line_no++) {

            std::cout << "Line " << _line_no << ": ";

            /* Ok. Look forward and skip not a dump starting with hex digit */
            for (std::string::size_type i = 0; i < _line.size(); ++i) {
                if (isspace(_line[i]) || isxdigit(_line[i])) {
                    continue;
                } else {
                    _skip_line = true;
                    break;
                }                
            }

            /* Do not process file*/
            if (_skip_line) {
                /* Not a hex encoded dump. Skip. */
                std::cout << "skipping ..." << std::endl;
                continue;
            }

            /* Ignore everything that is not hex encoded stuff */
            for (std::string::size_type i = 0; i < _line.size(); ++i) {

                // Skip spaces
                if (isspace(_line[i]))
                    continue;

                // Handle hex
                if (isxdigit(_line[i])) {
                    
                    if (_shift) {
                        _b_out = to_hex(_line[i]) << 4;    
                    } else {
                        _b_out |= to_hex(_line[i]);    
                    }

                    _shift = !_shift;
                    
                    if (_shift) {
                        _ofs.put(_b_out);
                        std::cout << '.';
                    }
                }
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& _e) {
        std::cerr << "Error: " << _e.what() << std::endl;
    } 
    
     return 0;
}