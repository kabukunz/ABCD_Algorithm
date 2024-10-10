#include <iostream>

// #include <igl/read_triangle_mesh.h>

// Eigen::MatrixXd V;
// Eigen::MatrixXi F;

int main(int argc, char *argv[])
{
    // check args
    if (argc < 2)
    {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <objfile>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFile = argv[1];

    // if (!read_triangle_mesh(inputFile, V, F))
    //     cout << "failed to load mesh" << endl;

    // 
    // do st
    // 

    return EXIT_SUCCESS;
}