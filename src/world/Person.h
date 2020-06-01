//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_PERSON_H
#define SOCIETY_PERSON_H

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "collision/Rectangle.h"


class Person {
public:
    typedef std::shared_ptr<Person> Ptr;

    const std::string &getName() const;

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

private:
    class BodyPart {
    public:
        typedef std::shared_ptr<BodyPart> Ptr;

        enum ShapeClass {
            SPHERE,
            CYLINDER,
            BOX,
            OVAL
        };

        glm::vec3 orientation;
        glm::vec3 dimensions;
        glm::vec3 infinitesimalDims;
        std::vector<glm::vec3> surfacePoints;
        Ptr parent;
        std::vector<Ptr> children;
        ShapeClass shape;

        void generateSurfacePoints();
    };

    std::string name;
    glm::vec3 position;
    BodyPart::Ptr head;
};


#endif //SOCIETY_PERSON_H
