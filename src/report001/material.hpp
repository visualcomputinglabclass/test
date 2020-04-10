
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include"brdf.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//材質クラス
namespace material {

    enum type {
        DIFFUSE,
        GLOSSY,
        SPECULAR,
        LIGHT,
        NONE
    };

//材質の基底クラス
class material {
public:
    //コンストラクタ
    material() : m_type( NONE ) {};

    explicit material( const type &t ) : m_type( t ) {};

    virtual ~material() = default;

    //BRDFを返す wo, nはワールド座標系での出謝方向
    virtual std::unique_ptr< brdf::brdf > brdf( const vec3 &wo, const vec3 &n ) const = 0;

    //光源の放射輝度を返す
    virtual col3 Le() const = 0;

    enum type type() const { return m_type; }

protected:
    enum type m_type;
};


//拡散反射材質
class diffuse : public material {
public:

    explicit diffuse( const std::vector<double> &param ) : material( DIFFUSE ), m_kd( param[ 0 ], param[ 1 ], param[ 2 ] ) {}

    std::unique_ptr< brdf::brdf > brdf( const vec3 &wo, const vec3 &n ) const override {
        return std::make_unique< brdf::lambertian >( wo, n, m_kd );
    }

    //発光成分は(0,0,0)を返す
    col3 Le() const override { return col3(); }

private:
    col3 m_kd;
};



}
#endif //MATERIAL_HPP
