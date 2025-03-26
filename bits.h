#pragma once
#include <algorithm>
#include <cstdint>
#include <expected>
#include <string>
#include <format>



constexpr auto tohex(void* ptr, size_t size){
    std::string str{"0x"};
    for (size_t i = 0; i < size; i++){
        constexpr char e[] = "0123456789ABCDEF";
        str += std::format("{}{}", e[((uint8_t*)ptr)[i] >> 4], e[((uint8_t*)ptr)[i] & 0xF]);
    }
    return str;
}

template <typename T>
constexpr auto tohex(T struct_t){
    return tohex(&struct_t, sizeof(T));
}

constexpr uint64_t reverse(uint64_t value) {
    return ((value & 0x00000000000000FF) << 56) |
           ((value & 0x000000000000FF00) << 40) |
           ((value & 0x0000000000FF0000) << 24) |
           ((value & 0x00000000FF000000) << 8) |
           ((value & 0x000000FF00000000) >> 8) |
           ((value & 0x0000FF0000000000) >> 24) |
           ((value & 0x00FF000000000000) >> 40) |
           ((value & 0xFF00000000000000) >> 56);
}

constexpr uint32_t reverse(uint32_t value) {
    return ((value & 0x000000ff) << 24) |
           ((value & 0x0000ff00) << 8) |
           ((value & 0x00ff0000) >> 8) |
           ((value & 0xff000000) >> 24);
}

constexpr uint16_t reverse(uint16_t hostshort) {
    return (hostshort >> 8) | (hostshort << 8);
}

#if MY_BYTE_ORDER == MY_BIG_ENDIAN

constexpr uint64_t htobed(uint64_t hostlonglong) {
    return hostlonglong;
}


constexpr uint32_t htobed(uint32_t hostlong) {
    return hostlong;
}

constexpr uint16_t htobed(uint16_t hostshort) {
    return hostshort;
}

constexpr uint64_t htoled(uint64_t hostlonglong) {
    return reverse(hostlonglong);
}

constexpr uint32_t htoled(uint32_t hostlong) {
    return reverse(hostlong);
}

constexpr uint16_t htoled(uint16_t hostshort) {
    return reverse(hostshort);
}



constexpr uint64_t bedtoh(uint64_t blonglong) {
    return blonglong;
}

constexpr uint32_t bedtoh(uint32_t blong) {
    return blong;
}

constexpr uint16_t bedtoh(uint16_t bshort) {
    return bshort;
}

constexpr uint64_t ledtoh(uint64_t slonglong) {
    return reverse(slonglong);
}

constexpr uint32_t ledtoh(uint32_t slong) {
    return reverse(slong);
}

constexpr uint16_t ledtoh(uint16_t sshort) {
    return reverse(sshort);
}



#elif MY_BYTE_ORDER == MY_LITTLE_ENDIAN

constexpr uint64_t htobed(uint64_t hostlonglong) {
    return reverse(hostlonglong);
}

constexpr uint32_t htobed(uint32_t hostlong) {
    return reverse(hostlong);
}

constexpr uint16_t htobed(uint16_t hostshort) {
    return reverse(hostshort);
}

constexpr uint64_t htoled(uint64_t hostlonglong) {
    return hostlonglong;
}

constexpr uint32_t htoled(uint32_t hostlong) {
    return hostlong;
}

constexpr uint16_t htoled(uint16_t hostshort) {
    return hostshort;
}



constexpr uint64_t bedtoh(uint64_t blonglong) {
    return reverse(blonglong);
}

constexpr uint32_t bedtoh(uint32_t blong) {
    return reverse(blong);
}

constexpr uint16_t bedtoh(uint16_t bshort) {
    return reverse(bshort);
}

constexpr uint64_t ledtoh(uint64_t slonglong) {
    return slonglong;
}

constexpr uint32_t ledtoh(uint32_t slong) {
    return slong;
}

constexpr uint16_t ledtoh(uint16_t sshort) {
    return sshort;
}

#endif