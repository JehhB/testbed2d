#include "testbed2d/util.h"

void Mesh::loadFromObjString(const std::string &obj) {
    vertices.clear();
    triangles.clear();

    const char* cursor = obj.c_str();
    while (*cursor != '\0') {
        if (cursor[0] == 'v' && cursor[1] == ' ') {
            float x, y, z;
            if (sscanf(cursor, "v %f %f %f", &x, &y, &z) == 3) {
                vertices.push_back({ x, y, z });
            }
        } else if (cursor[0] == 'f' && cursor[1] == ' ') {
            int v1, v2, v3;
            if (sscanf(cursor, "f %d %d %d", &v1, &v2, &v3) == 3) {
                triangles.push_back({ v1 - 1, v2 - 1, v3 - 1 });
            }
        }
        while (*cursor != '\n' && *cursor != '\0') cursor++;
        if (*cursor == '\n') cursor++;
    }
}
