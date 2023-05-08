#include "Tools.h"
#include "Compute.h"

namespace sablin{

bool IsInFov(const AABB &aabb, const Matrix4x4f &P,
        const Matrix4x4f &V, const Matrix4x4f &M,
        const float near_plane, const float far_plane){
    Matrix4x4f VM = V * M;

    Vector4f one = aabb.min_coord_;
    one = VM * one;
    float one_z = one.z_;

    Vector4f two = aabb.max_coord_;
    two = VM * two;
    float two_z = two.z_;

    one = P * one;
    one /= one.z_;
    if(one.x_ >= -1.0f && one.x_ <= 1.0f &&
            one.y_ >= -1.0f && one.y_ <= 1.0f &&
            one_z <= -near_plane && one_z >= -far_plane)
        return true;

    two = P * two;
    two /= two.z_;
    if(two.x_ >= -1.0f && two.x_ <= 1.0f &&
            two.y_ >= -1.0f && two.y_ <= 1.0f &&
            two_z <= -near_plane && two_z >= -far_plane)
        return true;
    return false;
}

void BoundingBoxScreen(const Primitive *primitive, Vector2i *min_coord_,
            Vector2i *max_coord_){
    for(int8_t i = 0;i != 3; ++i){
        if(std::floor(primitive->project_coord_[i].x_) < min_coord_->x_)
            min_coord_->x_ = std::floor(primitive->project_coord_[i].x_);
        if(std::floor(primitive->project_coord_[i].y_) < min_coord_->y_)
            min_coord_->y_ = std::floor(primitive->project_coord_[i].y_);

        if(std::ceil(primitive->project_coord_[i].x_) > max_coord_->x_)
            max_coord_->x_ = std::ceil(primitive->project_coord_[i].x_);
        if(std::ceil(primitive->project_coord_[i].y_) > max_coord_->y_)
            max_coord_->y_ = std::ceil(primitive->project_coord_[i].y_);
    }
}

Vector3f LUPSolve3f(const Matrix3x3f &L, const Matrix3x3f &U,
        const Vector3i &pi, const Vector3f &b){
    
    Vector3f x;
    float y[3]{};

    for(int8_t i = 0; i != 3; ++i){
        float second = 0.0f;
        for(int8_t j = 0; j != i; ++j)
            second += L.m_[i][j] * y[j];
        y[i] = b.s_[pi.s_[i]] - second;
    }

    for(int8_t i = 2; i != -1; --i){
        float second = 0.0f;
        for(int8_t j = i + 1; j != 3; ++j)
            second += U.m_[i][j] * x.s_[j];
        x.s_[i] = (y[i] - second) / U.m_[i][i];
    }
    return x;
}

Vector3i LUPDecomposition3x3f(Matrix3x3f &A){
    Vector3i pi{0, 1, 2};
    for(int8_t k = 0;k != 3; ++k){
        int8_t k_s = 0;
        float p = 0.0f;
        for(int8_t i = k; i != 3; ++i){
            if(Abs(A.m_[i][k]) > p){
                p = Abs(A.m_[i][k]);
                k_s = i;
            }
        }
        
#ifdef ASSERT
        assert(Abs(p) > FLOAT_ERROR);
#endif

        Swap(pi.s_[k], pi.s_[k_s]);
        for(int8_t i = 0; i != 3; ++i)
            Swap(A.m_[k][i], A.m_[k_s][i]);
        for(int8_t i = k + 1; i != 3; ++i){
            A.m_[i][k] /= A.m_[k][k];
            for(int8_t j = k + 1; j != 3; ++j)
                A.m_[i][j] -= A.m_[i][k] * A.m_[k][j];
        }
    }
    return pi;
}

Vector4f LUPSolve4f(const Matrix4x4f &L, const Matrix4x4f &U,
        const Vector4i &pi, const Vector4f &b){
    
    Vector4f x;
    float y[4]{};

    for(int8_t i = 0; i != 4; ++i){
        float second = 0.0f;
        for(int8_t j = 0; j != i; ++j)
            second += L.m_[i][j] * y[j];
        y[i] = b.s_[pi.s_[i]] - second;
    }

    for(int8_t i = 3; i != -1; --i){
        float second = 0.0f;
        for(int8_t j = i + 1; j != 4; ++j)
            second += U.m_[i][j] * x.s_[j];
        x.s_[i] = (y[i] - second) / U.m_[i][i];
    }
    return x;
}

Vector4i LUPDecomposition4x4f(Matrix4x4f &A){
    Vector4i pi{0, 1, 2, 3};
    for(int8_t k = 0;k != 4; ++k){
        int8_t k_s = 0;
        float p = 0.0f;
        for(int8_t i = k; i != 4; ++i){
            if(Abs(A.m_[i][k]) > p){
                p = Abs(A.m_[i][k]);
                k_s = i;
            }
        }
        
#ifdef ASSERT
        assert(Abs(p) > FLOAT_ERROR);
#endif

        Swap(pi.s_[k], pi.s_[k_s]);
        for(int8_t i = 0; i != 4; ++i)
            Swap(A.m_[k][i], A.m_[k_s][i]);
        for(int8_t i = k + 1; i != 4; ++i){
            A.m_[i][k] /= A.m_[k][k];
            for(int8_t j = k + 1; j != 4; ++j)
                A.m_[i][j] -= A.m_[i][k] * A.m_[k][j];
        }
    }
    return pi;
}

}
