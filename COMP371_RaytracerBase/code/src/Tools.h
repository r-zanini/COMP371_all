//
// Created by Roderick on 2022-02-12.
//

#ifndef RAYTRACER_TOOLS_H
#define RAYTRACER_TOOLS_H

#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <future>
#include <unordered_map>

using std::cout;
using std::endl;
using std::ostream;
using std::move;
using std::vector;
using std::string;
using std::unique_ptr;
using std::future;
using std::unordered_map;
using std::ofstream;

const float EPSILON = 1e-8f;
const float INF = std::numeric_limits<float>::max();
const float PI = 3.14159265358979323846264338327950288419716939937510f;

template<typename T>
class V3 {
public:
    T x, y, z;

    V3() : x(0), y(0), z(0) {}

    explicit V3(T x) : x(x), y(x), z(x) {}

    V3(T x, T y, T z) : x(x), y(y), z(z) {}

    V3 operator*(const V3 &v) const { return V3(x * v.x, y * v.y, z * v.z); }

    V3 operator*(const T &r) const { return V3(x * r, y * r, z * r); }

    friend V3 operator*(const T &r, const V3 &v) { return V3(v.x * r, v.y * r, v.z * r); }

    V3 operator/(const V3 &v) const { return V3(x / v.x, y / v.y, z / v.z); }

    V3 operator/(const T &r) const { return V3(x / r, y / r, z / r); }

    friend V3 operator/(const T r, const V3 &v) { return V3(r / v.x, r / v.y, r / v.z); }

    V3 operator+(const V3 &v) const { return V3(x + v.x, y + v.y, z + v.z); }

    V3 operator+(const T r) { return V3(x + r, y + r, z + r); }

    V3 operator-(const V3 &v) const { return V3(x - v.x, y - v.y, z - v.z); }

    V3 operator-(const T r) { return V3(x - r, y - r, z - r); }

    const T &operator[](size_t i) const { return (&x)[i]; }

    T &operator[](size_t i) { return (&x)[i]; }

    friend ostream &operator<<(ostream &os, const V3<T> &v) {
        os << v.x << ", " << v.y << ", " << v.z;
        return os;
    }

    void normalize() {
        T d = x * x + y * y + z * z;
        if (d == 0 || d == 1) return;
        d = 1 / sqrt(d);
        x *= d;
        y *= d;
        z *= d;
    }

    V3 normalized() {
        T d = x * x + y * y + z * z;
        if (d == 0 || d == 1) return *this;
        d = 1 / sqrt(d);
        return {x * d, y * d, z * d};
    }

    V3 cross(V3 v) const { return V3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

    T dot(V3 v) const { return x * v.x + y * v.y + z * v.z; }

    T dot() const { return x * x + y * y + z * z; };

    T norm() const { return sqrt(dot()); }
};

template<typename T>
class M4 {
public:
    T m[4][4] = {{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};

    M4() = default;;

    M4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33) {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
    }

    T (&operator[](size_t row))[4] { return m[row]; }
};

class Printable {
public:
    Printable() = default;

    virtual ~Printable() = default;

    friend ostream &operator<<(ostream &os, const Printable &p) { return p.toStream(os); }

    virtual ostream &toStream(ostream &os) const = 0;
};

using V3f = V3<float>;
using Color = V3<float>;
using M4f = M4<float>;

inline float clamp(const float &v, const float &min, const float &max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

inline float rnd() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator((size_t) std::chrono::high_resolution_clock::now().time_since_epoch().count());
    return distribution(generator);
}

inline float rnd(float min, float max) {
    static std::uniform_real_distribution<float> distribution(min, max);
    static std::mt19937 generator((size_t) std::chrono::high_resolution_clock::now().time_since_epoch().count());
    return distribution(generator);
}

#endif //RAYTRACER_TOOLS_H

