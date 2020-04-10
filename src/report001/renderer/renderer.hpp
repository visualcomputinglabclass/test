
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include"../scene.hpp"
#include"../camera.hpp"
#include"../vec3.hpp"

//レンダラー(画像生成)の基底クラス
class renderer {
public:
    virtual ~renderer() = default;
    virtual std::vector< float > render( const class scene &scene, const class camera &camera ) const = 0;
};


#endif //RENDERER_HPP
