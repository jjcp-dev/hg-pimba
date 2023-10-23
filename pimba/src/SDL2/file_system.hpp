#ifndef PIMBA_FILE_SYSTEM_HPP_F90ULMDB
#define PIMBA_FILE_SYSTEM_HPP_F90ULMDB

#include "pmb/fs/file_system.hpp"


namespace pimba {
namespace sdl {

class file_system : public pmb::file_system {
public:

   ~file_system() final;

    auto read(const char* path) const noexcept
        -> pmb::asset final;
};

} /* sdl */
} /* pimba */

#endif
