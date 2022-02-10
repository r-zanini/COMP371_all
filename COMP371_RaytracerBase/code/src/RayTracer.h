//
// Created by Hrodrick on 2022-02-09.
//

#ifndef RAYTRACERV3_RAYTRACER_H
#define RAYTRACERV3_RAYTRACER_H

#include "ThreadPool.h"

#include "json.hpp"

using nlohmann::json;

class RayTracer {
private:
    ThreadPool threadPool;
public:
    explicit RayTracer(json &j);

    ~RayTracer();

    void run();
};


#endif //RAYTRACERV3_RAYTRACER_H
