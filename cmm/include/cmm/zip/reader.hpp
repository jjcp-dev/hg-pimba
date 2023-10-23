#ifndef CMM_ZIP_READER_HPP_GWJQRKOU
#define CMM_ZIP_READER_HPP_GWJQRKOU

// #include <string_view>
#include <cstdint>


namespace cmm {
namespace detail {

struct End_of_central_directory {
    static auto signature() -> std::uint32_t
    {
        return 0x06054b50;
    }

    std::uint32_t id; /* signature() */
    std::uint16_t disk_number;
    std::uint16_t central_directory_start_disk;
    std::uint16_t records_count;
    std::uint16_t total_records_count;
    std::uint32_t central_directory_size;
    std::uint32_t central_directory_offset;
    std::uint16_t comment_length;
};

} /* detail */

struct Zip_file_info {
    std::string_view name;
};


template<typename IO>
class Zip_reader {
public:
    Zip_reader(IO& data_reader)
        : m_reader{data_reader}
    { }

private:
    IO m_reader;
};

} /* cmm */

#endif
