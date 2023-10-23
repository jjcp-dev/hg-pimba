#ifndef PMB_ENGINE_HPP_JFG7W2DK
#define PMB_ENGINE_HPP_JFG7W2DK

#include <chrono>

#include "lgf/shader.hpp"

#include "pmb/fs/file_system.hpp"

#include "./resource.hpp"
#include "./shader_store.hpp"


namespace pmb {

class engine {
public:

    pmb::file_system *file_system;
    pmb::resource     resource{file_system};
    pmb::shader_store shaders;

    engine(pmb::file_system* fs)
        : file_system{fs}
    { }

    void update(std::chrono::nanoseconds dt);

    void render();
};

} /* pmb */

#endif
