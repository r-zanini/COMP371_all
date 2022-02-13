//
// Created by Roderick on 2022-02-13.
//

#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include "Tools.h"

//Forward declarations
class Ray;

class Hittable : public Printable {
protected:
    Color ka_, kd_, ks_;
    float pc_;

public:
    Hittable(Color ka, Color kd, Color ks, float pc) : ka_(ka), kd_(kd), ks_(ks), pc_(pc) {};

    ~Hittable() override = default;

    virtual bool hit(Ray &ray) const = 0;

    ostream &toStream(ostream &os) const override {
        os << "ka: {" << ka_ << "}, kd: {" << kd_ << "}, ks: {" << ks_ << "}, pc: " << pc_;
        return os;
    }

    const V3f &ka() const { return ka_; }

    const V3f &kd() const { return kd_; }

    const V3f &ks() const { return ks_; }

    float pc() const { return pc_; }
};

class Hit : public Printable {
private:
    float t_;
    V3f p;
    V3f n;
    Hittable *h;
public:
    Hit() : t_(-1), p(), n(), h(nullptr) {};

    explicit Hit(float t) : t_(t), p(), n(), h(nullptr) {};

    Hit(float t, const V3f &point, const V3f &normal, Hittable *hittable)
            : t_(t), p(point), n(normal), h(hittable) {}

    ~Hit() override = default;

    ostream &toStream(ostream &os) const override {
        if (h == nullptr) os << "No hit registered";
        else os << "t: " << t_ << ", point: {" << p << "}, normal: {" << n << "}, hittable: {" << h << '}';
        return os;
    }

    float t() const { return t_; }

    const V3f &point() const { return p; }

    const V3f &normal() const { return n; }

    Hittable *hittable() const { return h; }
};

class Ray : public Printable {
private:
    V3f o, d, i;
    Hit h;
public:
    Ray() : o(), d(), h(), i(INF) {}

    Ray(const V3f &origin, const V3f &direction) : o(origin), d(direction), h(), i(1 / d) {}

    bool hit(const Hit &n) {
        if (n.t() < 0) return false;
        bool hitObject = (n.hittable() != nullptr);
        if (h.t() < 0) {
            if (hitObject) h = n;
            return true;
        }
        if (h.hittable() == nullptr) {
            h = n;
            return true;
        }
        if (n.t() < h.t()) {
            if (hitObject) h = n;
            return true;
        }
        return false;
    }

    ostream &toStream(ostream &os) const override {
        os << "origin: {" << o << "}, direction: {" << d << "}, inverse: {" << i << "}, hit: {" << h << '}';
        return os;
    }

    V3f at(float t) const { return o + t * d; }

    const V3f &origin() const { return o; }

    const V3f &direction() const { return d; }

    const V3f &inverse() const { return i; }

    const Hit &hit() const { return h; }
};

#endif //RAYTRACER_RAY_HPP
