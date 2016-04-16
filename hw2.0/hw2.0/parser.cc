
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "parser.h"


using namespace std;
// In this code, you can see how Sphere and Camera are set up - you
// will need to do similar for the other classes.
//
// You will also need to keep track of the last material defined, so
// that you can connect it to any surfaces that are subsequently defined.
//
void Parser::parse(
    const char *file,
    point4* vertices)
{
    std::vector<int> tri_ids;
    std::vector<float> tri_verts;
    read_wavefront_file(file, tri_ids, tri_verts);
    vertices = new point4[(int)tri_ids.size()];
    // build all the surfaces:
    for (int k = 0; k < (int)tri_ids.size() / 3; ++k) {
        point4 pa(tri_verts[3*tri_ids[3*k]],
                   tri_verts[3*tri_ids[3*k]+1],
                   tri_verts[3*tri_ids[3*k]+2],
                  1.0);
        
        point4 pb(tri_verts[3*tri_ids[3*k+1]],
                   tri_verts[3*tri_ids[3*k+1]+1],
                   tri_verts[3*tri_ids[3*k+1]+2],
                  1.0);
        
        point4 pc(tri_verts[3*tri_ids[3*k+2]],
                   tri_verts[3*tri_ids[3*k+2]+1],
                   tri_verts[3*tri_ids[3*k+2]+2],
                  1.0);
        vertices[3*k] = pa;
        vertices[1+3*k] = pb;
        vertices[2+3*k] = pc;
    }
    
}
void Parser::read_wavefront_file (
                                  const char *file,
                                  std::vector< int > &tris,
                                  std::vector< float > &verts)
{
    
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
            
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
        }
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
    }
    
    in.close();
    
    std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  "
    << verts.size () / 3.0 << std::endl;
}

