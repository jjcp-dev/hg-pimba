#ifndef CMM_ZIP_HEADERS_HPP_KFYV1EVH
#define CMM_ZIP_HEADERS_HPP_KFYV1EVH

#include <cstdint>


namespace cmm {
namespace zip {

struct Local_file_header {
    std::uint32_t header_signature;  // MUST BE 0x04034b50
    std::uint16_t minimum_version_required;
    std::uint16_t general_purpose_flag;
    std::uint16_t compression_method;
    std::uint16_t last_mod_time;
    std::uint16_t last_mod_date;
    std::uint32_t crc32;
    std::uint32_t compressed_size;
    std::uint32_t uncompressed_size;
    std::uint16_t file_name_length;
    std::uint16_t extra_field_length;
};


struct Data_descriptor {  // Without signature
    std::uint32_t crc32;
    std::uint32_t compressed_size;
    std::uint32_t uncompressed_size;
};


struct Central_directory_header {
    std::uint32_t header_signature;  // MUST BE 0x02014b50
    std::uint16_t creator_version;
    std::uint16_t extractor_version;
    std::uint16_t flags;
    std::uint16_t compression_method;
    std::uint16_t last_mod_time;
    std::uint16_t last_mod_date;
    std::uint32_t crc32;
    std::uint32_t compressed_size;
    std::uint32_t uncompressed_size;
    std::uint16_t file_name_length;
    std::uint16_t extra_field_length;
    std::uint16_t file_comment_length;
    std::uint16_t segment_file_number;
    std::uint16_t internal_file_attributes;
    std::uint32_t external_file_attributes;
    std::uint32_t local_header_offset;
};


struct End_of_central_directory {
    std::uint32_t header_signature;  // MUST BE 0x06054b50
    std::uint16_t disk_no;
    std::uint16_t disk;
    std::uint16_t records;
    std::uint16_t total;
    std::uint32_t size;
    std::uint32_t offset;
    std::uint16_t comment_length;
};

} /* zip */
} /* cmm */

#endif
