//
// Created by dawars on 2022. 04. 22..
//

#pragma once

#define TETLIBRARY
#include "tetgen.h"
#include "Eigen/Core"
namespace acoustics {

    class eigen_frequency {
    public:
        void test(tetgenio mesh);
        static tetgenio getTetgenMesh(Eigen::MatrixXd V, Eigen::MatrixXi F);

    };

}