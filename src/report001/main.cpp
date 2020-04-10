#define _USE_MATH_DEFINES
#include<cmath>
#include<iostream>
#include<cassert>
#include<random>
#include<limits>
#include<algorithm>
#include<chrono>
#include<memory>
#include<array>

#include"vec3.hpp"
#include"ray.hpp"
#include"scene.hpp"
#include"camera.hpp"

#include"renderer/renderer.hpp"
#include"renderer/simple.hpp"

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"../image/stb_image_write.h"

const size_t image_width    = 512;
const size_t image_height   = 512;
const double fov            = 40.0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void save_png( const size_t width, const size_t height, const std::vector< float >& pixel, const std::string& filename )
{
    std::vector< unsigned char > pixels( 3 * width * height );
    std::transform( pixel.begin(), pixel.end(), pixels.begin(), []( const float x ){ return static_cast< unsigned char >( std::clamp( 255 * powf( x, 1.f / 2.2f ), 0.f, 255.f ) ); } );
    stbi_write_png( filename.c_str(), int( width ), int( height ), 3, pixels.data(), 0 );
}

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

/*
int main( int argc, char ** argv )
{
    std::vector< sphere > spheres = { sphere( 1e5, vec3( 0.0, - 1e5 - 1.0, 0 ), material::DIFFUSE, { 0.8, 0.8, 0.8 } ), //床
                                      sphere( 1e5, vec3(  1e5 + 5, 0.0, 0 ), material::DIFFUSE, { 0.8, 0.2, 0.1 } ),    //右
                                      sphere( 1e5, vec3( -1e5 - 5, 0.0, 0 ), material::DIFFUSE, { 0.1, 0.2, 0.8 } ),    //左
                                      sphere( 1e5, vec3( 0.0, 0.0, 1e5 + 15 ), material::DIFFUSE, { 0.8, 0.8, 0.8 } ),  //上
                                      sphere( 1e5, vec3( 0.0, 1e5 + 8, 0 ), material::DIFFUSE, { 0.8, 0.8, 0.8 } ),     //奥
//                                      sphere( 1.0, vec3( -2.0, 0.1, 10.0 ), material::GLOSSY, { 0.1, 1.0, 1.0, 1.0 } ),                                   //球
//                                      sphere( 0.5, vec3( 0.0, 7.0, 10.0 ), material::LIGHT, { 30.0, 30.0, 30.0 } ),                                      //光源
    };
    const vec3 eye = { 0.0, 3.0, - 5.0 };
    const vec3 ref;
    const scene scn( std::move( spheres ) );
    const camera cmr( eye, ref, image_width, image_height, tan( fov / 2 * M_PI / 180.0 ) );


    const simple::renderer render;
    const auto pixel = render.render( scn, cmr );

    save_png( image_width, image_height, pixel, "image.png" );

}
*/