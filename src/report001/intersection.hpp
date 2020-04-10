
#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP


#include"material.hpp"

//前方宣言
namespace material {
    class material;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 交点情報
class intersection
{
public:

    intersection() : m_p(), m_n(), m_wo(), m_material( nullptr ) {}
    intersection( const vec3 &p, const vec3 &n, const vec3 &wo, const std::shared_ptr< material::material >& mat ) : m_p( p ), m_n( n ), m_wo( wo ), m_material( mat ) {}

    vec3 p() const { return m_p; } //交点の位置を返す
    vec3 n() const { return m_n; } //交点の法線を返す
    vec3 wo() const { return m_wo; } //交点計算時のレイの方向

    //交点が光源上の場合，光源の放射輝度を返す
    col3 Le() const { return assert( is_light() ), m_material->Le(); }

    //シーン中の球と交差していたらtrue, そうでなければfalseを返す
    bool is_valid() const { return m_material != nullptr; }

    //交点が光源上かどうかを判定，光源上ならtrue, そうでなければfalseを返す
    bool is_light() const { return assert( is_valid() ), ( m_material->type() == material::LIGHT ); }

    //交点のBRDFを返す
    std::unique_ptr< brdf::brdf > brdf() const { return m_material->brdf( m_wo, m_n ); }

    //交点の材質型を返す
    material::type  type() const { return m_material->type(); }

private:
    vec3 m_p;   //交点の位置
    vec3 m_n;   //交点の法線
    vec3 m_wo;  //反射方向
    std::shared_ptr< material::material > m_material;   //交点の材質
};

#endif //INTERSECTION_HPP
