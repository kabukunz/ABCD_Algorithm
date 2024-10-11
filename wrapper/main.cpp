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

    // ABCD_PN_demo.m

    // %% 
    // in_mesh     = './data/D1_00478_bff.obj';    % V,F,TC,FTC
    // target_mesh = 'uv';             %initialized by texture UV coordinates
    // options.free_bnd       = 1;     %boundary is free except the anchors
    // options.fixed_vertices = [];    %unconstrained
    // options.is_uv_mesh     = 1;     %surface mesh
    // run ABCD_MexWrapperScript.m


    // 
    // do st
    // 

    return EXIT_SUCCESS;
}