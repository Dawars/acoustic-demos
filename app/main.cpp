//
// Created by dawars on 2022. 04. 22..
//
#include "fmt/core.h"
#include "geometrycentral/surface/manifold_surface_mesh.h"
#include "geometrycentral/surface/meshio.h"
#include "geometrycentral/surface/vertex_position_geometry.h"

#include "geometrycentral/surface/direction_fields.h"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include "igl/readOBJ.h"

#include "imgui.h"

#include "acoustics/eigen_frequency.h"


using namespace geometrycentral;
using namespace geometrycentral::surface;

// Polyscope visualization handle, to quickly add data to the surface
polyscope::SurfaceMesh *psMesh;

// Some algorithm parameters
float param1 = 42.0;

// Example computation function -- this one computes and registers a scalar
// quantity
void doWork() {
    polyscope::warning("Computing Gaussian curvature.\nalso, parameter value = " +
                       std::to_string(param1));

//    geometry->requireVertexGaussianCurvatures();
//    psMesh->addVertexScalarQuantity("curvature",
//                                    geometry->vertexGaussianCurvatures,
//                                    polyscope::DataType::SYMMETRIC);
}

// A user-defined callback, for creating control panels (etc)
// Use ImGUI commands to build whatever you want here, see
// https://github.com/ocornut/imgui/blob/master/imgui.h
void myCallback() {

    if (ImGui::Button("do work")) {
        doWork();
    }

    ImGui::SliderFloat("param", &param1, 0., 100.);
}

int main(int argc, char **argv) {

    acoustics::eigen_frequency obj;

    std::string inputFilename = "./data/bridge.obj";

    // Initialize polyscope
    polyscope::init();

    // Set the callback function
    polyscope::state::userCallback = myCallback;

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    igl::readOBJ(inputFilename, V,  F);

    tetgenio tet_input = acoustics::eigen_frequency::getTetgenMesh(V, F);

    tet_input.save_nodes("input");
    tet_input.save_poly("input");

//    obj.test(tet_input);

    // Register the mesh with polyscope
    psMesh = polyscope::registerSurfaceMesh(
            polyscope::guessNiceNameFromPath(inputFilename),
            V, F);


//    psMesh->setVertexTangentBasisX(vBasisX);

//    auto vField =
//            geometrycentral::surface::computeSmoothestVertexDirectionField(*geometry);
//    psMesh->addVertexIntrinsicVectorQuantity("VF", vField);

    // Give control to the polyscope gui
    polyscope::show();

    return EXIT_SUCCESS;
}