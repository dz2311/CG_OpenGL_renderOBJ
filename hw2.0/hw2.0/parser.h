#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <vector>
#include "amath.h"
//
// Basic parser for the scene files:
//
typedef amath::vec4  point4;

class Parser {
public:
    virtual void parse(
            const char *file,
            point4* vertices);
    
    
    void read_wavefront_file (
                                      const char *file,
                                      std::vector< int > &tris,
                              std::vector< float > &verts);

};

#endif