
#ifndef RAY_HPP
#define RAY_HPP

#include"vec3.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//　光線(レイ)クラス
class ray
{
public:
    //コンストラクタ
    ray( const vec3 &_o, const vec3 &_d ) : m_o( _o ), m_d( _d ) {}

    vec3 o() const { return m_o; } //レイの始点を返す
    vec3 d() const { return m_d; } //レイの単位方向ベクトルを返す

private:
    vec3 m_o;   //レイの始点
    vec3 m_d;   //レイの単位方向ベクトル
};



#endif //RAY_HPP
