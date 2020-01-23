//
// Created by vtta 🍉 on 2020/1/17.
//

#ifndef DSA_COMMON_HPP
#define DSA_COMMON_HPP

#include <cstdint>

namespace dsa {

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using isize = std::intptr_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using usize = std::uintptr_t;

// // trim from start (in place)
// static inline auto ltrim(std::string &s) {
//     s.erase(s.begin(), std::find_if(s.begin(), s.end(),
//                                     [](int ch) { return !std::isspace(ch);
//                                     }));
//     return s;
// }
//
// // trim from end (in place)
// static inline auto rtrim(std::string &s) {
//     s.erase(std::find_if(s.rbegin(), s.rend(),
//                          [](int ch) { return !std::isspace(ch); })
//                 .base(),
//             s.end());
//     return s;
// }
//
// // trim from both ends (in place)
// static inline auto trim(std::string &s) {
//     ltrim(s);
//     rtrim(s);
//     return s;
// }

}  // namespace dsa

#endif  // DSA_COMMON_HPP
