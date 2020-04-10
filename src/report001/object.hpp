
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include"vec3.hpp"
#include"ray.hpp"
#include"material.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//シーンを構成する物体を定義する

//物体の基底クラス
class object
{
public:
    object() = default;
    virtual ~object() = default;
    virtual double intersect( const ray &r ) const = 0;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//球クラス
class sphere : public object
{
public:
    //コンストラクタ
    sphere( const double r, const vec3 &center, const material::type &type, const std::vector< double > &param ) : m_center( center ), m_radius( r ), m_area( 4.0 * M_PI * m_radius * m_radius )
    {
        switch( type ) {
            case material::DIFFUSE:
                assert( param.size() >= 3 );
                m_material = std::make_shared< material::diffuse >( param );
                break;
            case material::GLOSSY:
            case material::SPECULAR:
            case material::LIGHT:
            case material::NONE:
                break;
        }
    }

    //交差判定　交差した場合レイの始点からの距離を返す　交差しない場合0を返す
    double intersect( const ray& r ) const {
        vec3 p = m_center - r.o();
        const double b = dot( p, r.d() );
        const double det = b * b - dot( p, p ) + m_radius * m_radius;
        if( det >= 0.0 ) {
            const double sqrt_det = sqrt( det );
            const double t1 = b - sqrt_det;
            const double t2 = b + sqrt_det;
            if( t1 > eps ) {
                return t1;
            } else if( t2 > eps ) {
                return t2;
            }
        }
        return 0.0;
    }

    vec3        center() const { return m_center; }
    double      radius() const { return m_radius; }
    double      area() const { return m_area; }
    std::shared_ptr< material::material > material() const { return m_material; }

private:
    vec3                                    m_center;
    double                                  m_radius;
    double                                  m_area;
    std::shared_ptr< material::material >   m_material;

    static constexpr double eps = 1e-6;
};



#endif //OBJECT_HPP
