
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include"vec3.hpp"
#include"ray.hpp"

//(ピンホール)カメラクラス
class camera {
public:

    //コンストラクタ eye:視点, ref:注視点, width,height:スクリーンの横・縦の画素数, tanfovy: tan(¥theta_{fovy}/2), ¥theta_{fovy}は視野角
    camera( const vec3 &eye, const vec3 &ref, const int width, const int height, const double tanfovy = tan( 45.0 / 360 * M_PI ) ) : m_eye( eye ), m_ref( ref ), m_width( width ), m_height( height ), m_tanfovy( tanfovy ), m_p( 2 * m_tanfovy / m_height ) {}

    vec3 eye() const { return m_eye; }  //視点を返す
    vec3 ref() const { return m_ref; }  //注視点を返す
    int width() const { return m_width; }   //スクリーンの横の画素数を返す
    int height() const { return m_height; } //スクリーンの縦の画素数を返す

    //スクリーン座標(x,y)を通るレイを生成
    inline ray generate_ray( const double x, const double y ) const
    {
        const auto dx = m_p * ( x - m_width / 2.0 );
        const auto dy = m_p * ( m_height / 2.0 - y );
        return ray( m_eye, normalize( vec3( dx, dy, 1.0 ) ) );
    }

private:
    vec3    m_eye; //視点
    vec3    m_ref; //注視点
    int     m_width;    //スクリーンの横の画素数
    int     m_height;   //スクリーンの縦の画素数
    double  m_tanfovy;  //tan(¥theta_{fovy}/2) スクリーンの縦の1/2の長さ
    double  m_p;        //1ピクセルの大きさ
};



#endif //CAMERA_HPP
