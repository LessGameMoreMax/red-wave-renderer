#ifndef PARALLELLIGHT_H
#define PARALLELLIGHT_H
#include "Light.h"
namespace sablin{
class ParallelLight : public Light{
private:
    Vector4f direction_;
public:
    ParallelLight(const Vector4f &direction,
            const Vector4f &color);
    ParallelLight(const ParallelLight&) = default;
    ParallelLight& operator=(const ParallelLight&) = default;
    ~ParallelLight() = default;

    Vector4f LightDirection(const Vector4f&) override;
    Vector4f LightColor(const Vector4f&) override;
};
}
#endif
