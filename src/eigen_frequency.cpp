//
// Created by dawars on 2022. 04. 22..
//

#include "acoustics/eigen_frequency.h"

#include <Eigen/Core>
#include "fmt/core.h"

namespace acoustics {


void eigen_frequency::test(tetgenio in) {
    tetgenio out;

    tetrahedralize((char*)"", &in, &out);

}

tetgenio eigen_frequency::getTetgenMesh(Eigen::MatrixXd V, Eigen::MatrixXi F) {

    tetgenio in;
    tetgenio::facet *f;
    tetgenio::polygon *p;

    in.firstnumber = 1;

    in.numberofpoints = V.rows();
    fmt::print("V: {} {}\n", V.rows(), V.cols());
    in.pointlist = new REAL[in.numberofpoints * 3];
    for (int i = 0; i < in.numberofpoints; ++i) {
        in.pointlist[i * 3 + 0] = V(i, 0);
        in.pointlist[i * 3 + 0] = V(i, 1);
        in.pointlist[i * 3 + 0] = V(i, 2);
    }

    in.numberoffacets = F.rows();
    fmt::print("F: {} {}\n", F.rows(), F.cols());
    in.facetlist = new tetgenio::facet[in.numberoffacets];
    in.facetmarkerlist = new int[in.numberoffacets];

    for (int i = 0; i < in.numberoffacets; ++i) {
        f = &in.facetlist[i];
        f->numberofpolygons = 1;
        f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
        f->numberofholes = 0;
        f->holelist = NULL;
        p = &f->polygonlist[0];
        p->numberofvertices = 3; // assume triangulated mesh
        p->vertexlist = new int[p->numberofvertices];
        p->vertexlist[0] = F(i,0);
        p->vertexlist[1] = F(i,1);
        p->vertexlist[2] = F(i,2);
    }
    return in;
}


}