#include "stdafx.h"
#include "runTestKey.h"
#include <fstream>
#include <list>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <ctime>

void runTestKey(std::string keys_path)
{
    std::ifstream infile(keys_path);

    std::string line;

    std::list<unsigned int>keys;
    while ( std::getline(infile, line) ) {
        unsigned int key = 0;

        try {
            key = boost::lexical_cast<unsigned int>( line );
        }
        catch ( boost::bad_lexical_cast& /*e*/ ) {
/*            std::cout << e.what() << std::end; */
        }
        if (key) keys.push_back(key);
    }

    keys.sort();

    char buf[20] = { 0 };
    for ( auto &key : keys ) {
        time_t t = (time_t)key;

        struct tm tt;
        localtime_s(&tt, &t);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tt);

        printf("%u %s ",key, buf);

        unsigned int r = key;
        for ( int i = 0; i < 16; i++ ) {
            r = r * 214013L + 2531011L;
            unsigned char k = ( r >> 16 ) & 0xff;
            printf("%.2x", k);
        }

        printf("\r\n");
    }
}