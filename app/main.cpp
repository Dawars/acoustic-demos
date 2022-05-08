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
#include "polyscope/volume_mesh.h"

#include <igl/readOBJ.h>
#include <igl/barycenter.h>
#include <igl/copyleft/tetgen/tetrahedralize.h>

#include "imgui.h"

#include "acoustics/eigen_frequency.h"


using namespace geometrycentral;
using namespace geometrycentral::surface;

// == Geometry-central data
std::unique_ptr<ManifoldSurfaceMesh> mesh;
std::unique_ptr<VertexPositionGeometry> geometry;

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
    obj.test();

    std::string inputFilename = "./data/bridge.obj";

    // Initialize polyscope
    polyscope::init();

    // Set the callback function
    polyscope::state::userCallback = myCallback;

    // Input polygon
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::MatrixXd B;

    // Tetrahedralized interior
    Eigen::MatrixXd TV;
    Eigen::MatrixXi TT;
    Eigen::MatrixXi TF;
    // Load a surface mesh
    igl::readOBJ(inputFilename, V, F);

    // Tetrahedralize the interior
    igl::copyleft::tetgen::tetrahedralize(V, F, "pq1.414", TV, TT, TF);

    // Compute barycenters
    igl::barycenter(TV, TT, B);

    // Register the volume mesh with Polyscope
    polyscope::registerTetMesh("bridge_volume", TV, TT);

    // Add a scalar quantity
    size_t nVerts = TV.rows();
    std::vector<double> scalarV(nVerts);
    for (size_t i = 0; i < nVerts; i++) {
        // use the x-coordinate of vertex position as a test function
        scalarV[i] = TV(i, 0);
    }
    polyscope::getVolumeMesh("bridge_volume")->addVertexScalarQuantity("scalar Q", scalarV);

    // Give control to the polyscope gui
    polyscope::show();

    return EXIT_SUCCESS;
}