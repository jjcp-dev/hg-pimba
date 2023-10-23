#ifndef PMB_FS_FILE_SYSTEM_HPP_NQSREWDB
#define PMB_FS_FILE_SYSTEM_HPP_NQSREWDB

#include "./asset.hpp"


namespace pmb {

class file_system {
public:
    virtual ~file_system() { };

    virtual auto read(const char* path) const noexcept
        -> pmb::asset =0;
};

} /* pmb */

#endif
