#pragma once

// base_gmath module inclusion with printing
// print code for <format>, variadic template functions cannot be exported from modules

//#include <iostream>
#include <format>

import base_def;
import base_gmath;


#if 1
template <>
struct std::formatter<gm::vec2> : std::formatter<std::string> {
  auto format(gm::vec2 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}", a[0], a[1]), ctx);
  }
};

template <>
struct std::formatter<gm::vec3> : std::formatter<std::string> {
  auto format(gm::vec3 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2]), ctx);
  }
};

template <>
struct std::formatter<gm::vec4> : std::formatter<std::string> {
  auto format(gm::vec4 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};


template <>
struct std::formatter<gm::quat> : std::formatter<std::string> {
  auto format(gm::quat a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};

template <>
struct std::formatter<gm::plane> : std::formatter<std::string> {
  auto format(gm::plane a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};

template <>
struct std::formatter<gm::colorf> : std::formatter<std::string> {
  auto format(gm::colorf a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};


template <>
struct std::formatter<gm::mat2> : std::formatter<std::string> {
  auto format(gm::mat2 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};

template <>
struct std::formatter<gm::mat3> : std::formatter<std::string> {
  auto format(gm::mat3 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f},\n"
		  , a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]), ctx);
  }
};

template <>
struct std::formatter<gm::mat4> : std::formatter<std::string> {
  auto format(gm::mat4 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f}, {:.6f},\n"
		  , a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]), ctx);
  }
};
#endif