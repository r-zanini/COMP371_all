//
// Created by Hrodrick on 2022-02-09.
//

#ifndef RAYTRACERV3_RAYTRACER_H
#define RAYTRACERV3_RAYTRACER_H

#include "json.hpp"

using nlohmann::json;

class RayTracer {
public:
    explicit RayTracer(json &j);

    ~RayTracer();

    void run();
};


#endif //RAYTRACERV3_RAYTRACER_H
