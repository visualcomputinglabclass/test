
#ifndef SCENE_HPP
#define SCENE_HPP

#include<vector>
#include"object.hpp"
#include"intersection.hpp"
#include"ray.hpp"
#include"material.hpp"


//シーン情報を格納したクラス
class scene {
public:

    //コンストラクタ
    explicit scene( std::vector< sphere > &&obj ) : m_object( std::move( obj ) )
    {

    }

    //レイと物体(球)との交点計算
    intersection intersect( const ray &r ) const
    {
        double mint = std::numeric_limits< double >::max();
        bool hit = false;
        size_t id = 0;
        for( size_t i = 0, n = m_object.size(); i < n; ++i ) {
            double t = m_object[ i ].intersect( r );
            if( t < mint && t > 0.0 ) {
                mint = t;
                hit = true;
                id = i;
            }
        }

        if( hit ) {
            const auto p = r.o() + mint * r.d();
            const auto n = normalize( p - m_object[ id ].center() );
            return intersection( p, n, - r.d(), m_object[ id ].material() );
        }
        return intersection();
    }

    // ray rが距離d以内で物体と交差するかどうかを判定　(交点は求めない, shadow ray用)
    bool intersect( const ray &r, const double d ) const
    {
        constexpr double eps = 1e-10;
        for( const auto& s : m_object ) {
            double t = s.intersect( r );
            if( 0.0 < t && t < d - eps ) return true;
        }
        return false;
    }

    //シーン中の光源をサンプリング， pdf_aはサンプリング確率(area measure)
    intersection sample_light( random_number_generator &rng, double &pdf_a ) const
    {
        //光源を一つサンプリング(現状一様サンプリング，光束に比例させたほうがいい)
        const sphere& light = m_light[ rng.rand( 0, m_light.size() ) ];
        //光源の選択確率
        const double pdf_l = 1.0 / m_light.size();

        //uniform sampling of sphere
        const double costh = 1.0 - 2.0 * rng.rand();
        const double sinth = sqrt( std::max( 0.0, 1.0 - costh * costh ) );
        const double ph = 2.0 * M_PI * rng.rand();
        const double cosph = cos( ph );
        const double sinph = sin( ph );
        const vec3 p = vec3( sinth * cosph, sinth * sinph, costh );

        //pdf = 1 / A (A : 面積) * pdf_l (光源の選択確率)
        pdf_a = 1.0 / light.area() * pdf_l;
        return intersection( light.center() + light.radius() * p, p, vec3(), light.material() );
    }


private:

    std::vector< sphere >   m_object;
    std::vector< sphere >   m_light;
    double                  m_flux;

};




#endif //SCENE_HPP
