
#ifndef BSDF_HPP
#define BSDF_HPP

#include"vec3.hpp"
#include"rng.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BRDFに関するクラス
namespace brdf {

//BRDF基底クラス
class brdf {
public:
    brdf() = default;

    brdf( const vec3 &wo, const vec3 &n ) : m_wo( wo ), m_n( n ), m_t( normalize(
            cross( n, ( std::abs( n.x ) < std::abs( n.y )) ? vec3( 0.0, n.z, -n.y ) : vec3( -n.z, 0.0, n.x )))),
                                            m_b( cross( m_t, m_n )), m_lwo( to_local( m_wo )) {}

    virtual ~brdf() = default;

    //BRDFに基づいて方向をサンプリング (pdf_wはサンプルされた方向の確率密度)
    virtual vec3 sample( random_number_generator &rng, double &pdf_w ) = 0;

    //方向wiの確率密度を返す
    virtual double pdf( const vec3 &wi ) = 0;

    //BRDFの値f(wi,wo)を返す
    virtual col3 f( const vec3 &wi ) = 0;

    //出射方向を返す(ワールド座標系)
    inline vec3 wo() const { return m_wo; }

    //ローカル座標系への変換
    inline vec3 to_local( const vec3 &w ) const { return vec3( dot( m_t, w ), dot( m_b, w ), dot( m_n, w )); }

    //ワールド座標系への変換
    inline vec3 to_world( const vec3 &w ) const { return w.x * m_t + w.y * m_b + w.z * m_n; }

protected:
    vec3 m_wo;  //出射方向
    vec3 m_n;   //法線(normal)
    vec3 m_t;   //接線(tangent)
    vec3 m_b;   //従法線(binormal)
    vec3 m_lwo; //outgoing direction in local coordinate system
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ランバートBRDF
class lambertian : public brdf {

public:

    //コンストラクタ wo:反射方向, n:法線, albedo:アルベド
    lambertian( const vec3 &wo, const vec3 &n, const col3 &albedo ) : brdf( wo, n ), m_albedo( albedo ) {}

    //方向をサンプリング
    vec3 sample( random_number_generator &rng, double &pdf_w ) override {
        //sample direction prop. to cosine
        const double costh = sqrt( 1.0 - rng.rand() );
        const double sinth = sqrt( std::max( 0.0, 1.0 - costh * costh ));
        const double ph = 2.0 * rng.rand() * M_PI;
        const double cosph = cos( ph );
        const double sinph = sin( ph );
        //pdf_w
        pdf_w = 1.0 / M_PI * costh;
        return to_world( vec3( sinth * cosph, sinth * sinph, costh ) );
    }

    //方向wiに対する確率密度を計算
    double pdf( const vec3 &wi ) override { return dot( wi, m_n ) / M_PI; }

    //方向wiに対するBRDFの値を計算
    col3 f( const vec3 &wi ) override { return m_albedo / M_PI; }

private:
    col3 m_albedo;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


#endif //BSDF_HPP
