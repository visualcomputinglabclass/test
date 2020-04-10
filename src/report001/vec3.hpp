
#ifndef VEC3_HPP
#define VEC3_HPP

#include<cmath>
#include<cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ベクトルクラス
class vec3 {
public:
    //コンストラクタ
    vec3() : x( 0.0 ), y( 0.0 ), z( 0.0 ) {}
    vec3( const double _x, const double _y, const double _z ) : x( _x ), y( _y ), z( _z ) {}
    explicit vec3( const double s ) : x( s ), y( s ), z( s ) {}

    //2項演算子
    inline vec3 operator+( const vec3 &rhs ) const { return vec3( x + rhs.x, y + rhs.y, z + rhs.z ); }
    inline vec3 operator-( const vec3 &rhs ) const { return vec3( x - rhs.x, y - rhs.y, z - rhs.z ); }
    inline vec3 operator*( const vec3 &rhs ) const { return vec3( x * rhs.x, y * rhs.y, z * rhs.z ); }
    inline vec3 operator/( const vec3 &rhs ) const { return vec3( x / rhs.x, y / rhs.y, z / rhs.z ); }
    inline vec3 operator*( const double scale ) const { return vec3( scale * x, scale * y, scale * z ); }
    inline vec3 operator/( const double scale ) const { return vec3( x / scale, y / scale, z / scale ); }

    inline double operator[]( const int dim ) const { return assert( 0 <= dim && dim < 3 ), ( dim == 0 ) ? x : ( dim == 1 ) ? y : z; }

    inline vec3& operator+=( const vec3 &rhs ) { return x += rhs.x, y += rhs.y, z += rhs.z, *this; }
    inline vec3& operator-=( const vec3 &rhs ) { return x -= rhs.x, y -= rhs.y, z -= rhs.z, *this; }
    inline vec3& operator*=( const vec3 &rhs ) { return x *= rhs.x, y *= rhs.y, z *= rhs.z, *this; }
    inline vec3& operator*=( const double scale ) { return x *= scale, y *= scale, z *= scale, *this; }
    inline vec3& operator/=( const vec3 &rhs ) { return x /= rhs.x, y /= rhs.y, z /= rhs.z, *this; }
    inline vec3& operator/=( const double scale ) { return x /= scale, y /= scale, z /= scale, *this; }
    inline vec3 operator-() const { return vec3( - x, - y, - z ); }
    inline friend vec3 operator*( const double scale, const vec3 &v ) { return vec3( scale * v.x, scale * v.y, scale * v.z ); }

    //内積など
    inline friend double dot( const vec3 &lhs, const vec3 &rhs ) { return ( lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z ); }
    inline friend double norm( const vec3 &v ) { return sqrt( v.x * v.x + v.y * v.y + v.z * v.z ); }
    inline friend vec3 normalize( const vec3 &v ) { const double l = norm( v ); assert( std::abs( l ) > 1e-10 ); return vec3( v.x / l, v.y / l, v.z / l ); }
    inline friend vec3 cross( const vec3 &lhs, const vec3 &rhs ) { return vec3( lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x ); }
    inline friend bool isfinite( const vec3 &v ) { return std::isfinite( v.x ) && std::isfinite( v.y ) && std::isfinite( v.z ); }
    inline friend vec3 min( const vec3 &lhs, const vec3 &rhs ){ return vec3( std::min( lhs.x, rhs.x ), std::min( lhs.y, rhs.y ), std::min( lhs.z, rhs.z ) ); }
    inline friend vec3 max( const vec3 &lhs, const vec3 &rhs ){ return vec3( std::max( lhs.x, rhs.x ), std::max( lhs.y, rhs.y ), std::max( lhs.z, rhs.z ) ); }

    double x, y, z;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//色も3次元ベクトルとして扱う
typedef vec3 col3;

#endif //VEC3_HPP
