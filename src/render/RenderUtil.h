//
// Created by Philip on 3/1/2020.
//

#ifndef HIVEMIND_RENDERUTIL_H
#define HIVEMIND_RENDERUTIL_H

#include <memory>
#include <string>

#include "Mesh.h"


class RenderUtil {
public:
    static void renderMesh(const std::weak_ptr<Mesh> &mesh);

    static char *readShader(const std::string &path);

};


#endif //HIVEMIND_RENDERUTIL_H
