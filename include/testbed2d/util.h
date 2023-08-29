#ifndef TESTBED2D_UTIL_H
#define TESTBED2D_UTIL_H

#include <vector>
#include <array>
#include <string>

struct Mesh {
    std::vector<std::array<float,3>> vertices;
    std::vector<std::array<int, 3>> triangles;

    void loadFromObjString(const std::string &obj);
};

#endif
