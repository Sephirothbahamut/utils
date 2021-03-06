#pragma once
#include <ostream>
#include <cmath>
#include <numbers>

#include "math.h"

#ifndef UTILS_NOANGLE
#include "angle.h"
#endif
#ifdef COUT_CONTAINERS
#include "../cout_utilities.h"
#endif

namespace utils::math
	{
	template <typename T> class vec2;
	}

#ifdef COUT_CONTAINERS
namespace utils::cout
	{
	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const utils::math::vec2<T>& vec) noexcept
		{
		namespace ccu = cout::support;
		return os << ccu::type << "vec2" << ccu::brace << "(" << ccu::value << vec.x << ccu::separ << ", " << ccu::value << vec.y << ccu::brace << ")";
		}
	}
#endif

namespace utils::math
	{
	//fast typenames
	using vec2i   = vec2<int>;
	using vec2i8  = vec2<int8_t>;
	using vec2i16 = vec2<int16_t>;
	using vec2i32 = vec2<int32_t>;
	using vec2i64 = vec2<int64_t>;
	
	using vec2u   = vec2<unsigned>;
	using vec2u8  = vec2<uint8_t>;
	using vec2u16 = vec2<uint16_t>;
	using vec2u32 = vec2<uint32_t>;
	using vec2u46 = vec2<uint64_t>;
	
	using vec2s = vec2<size_t>;
	using vec2f = vec2<float>;
	using vec2d = vec2<double>;

	template <typename T>
	class vec2
		{
		public:
			vec2<T>()         noexcept = default;
			vec2<T>(T x, T y) noexcept : x(x), y(y) {};
			vec2<T>(T xy)     noexcept : x(xy), y(xy) {}
			static vec2<T> rr()    noexcept { return {T{ 1}, T{ 0}}; }
			static vec2<T> ll()    noexcept { return {T{-1}, T{ 0}}; }
			static vec2<T> up()    noexcept { return {T{ 0}, T{-1}}; }
			static vec2<T> dw()    noexcept { return {T{ 0}, T{ 1}}; }
			static vec2<T> right() noexcept { return rr(); }
			static vec2<T> left()  noexcept { return ll(); }
			static vec2<T> down()  noexcept { return dw(); }
			static vec2<T> zero()  noexcept { return {}; }

			T x = 0, y = 0;

			T magnitude2()    const noexcept { return x * x + y * y; }
			T magnitude()     const noexcept { return std::sqrt(magnitude2()); }
			vec2<T>  normal() const noexcept { return magnitude() ? *this / magnitude() : *this; }
			vec2<T>& normalize()    noexcept { return *this = normal(); }

			float to_angle() const noexcept 
				{
				return (std::atan2f(x, y) * 180.f / static_cast<float>(std::acos(-1)/*numbers::pi*/)) + 180.f; 
				}

			// OPERATORS
			vec2<T>  operator-() const noexcept { return {-x, -y}; }

			// VEC & SCALAR OPERATORS
			vec2<T>  operator++() noexcept { return *this += T(1); }
			vec2<T>  operator--() noexcept { return *this -= T(1); }

			vec2<T>  operator+ (const T n) const noexcept { return {normal() * (magnitude() + n)}; }
			vec2<T>  operator- (const T n) const noexcept { return {normal() * (magnitude() - n)}; }
			vec2<T>  operator* (const T n) const noexcept { return {x * n, y * n}; }
			vec2<T>  operator/ (const T n) const noexcept { return {x / n, y / n}; }

			vec2<T>& operator+=(const T n)       noexcept { return *this = *this + n; }
			vec2<T>& operator-=(const T n)       noexcept { return *this = *this - n; }
			vec2<T>& operator*=(const T n)       noexcept { return *this = *this * n; }
			vec2<T>& operator/=(const T n)       noexcept { return *this = *this / n; }
			vec2<T>& operator= (const T n)       noexcept { return normalize() *= n; }

			// VEC & ANGLE OPERATIONS
#ifndef UTILS_NOANGLE
			vec2<T>  operator+ (const utils::angle::deg angle) const noexcept { utils::angle::rad rngle{angle}; return {x * rngle.cos() - y * rngle.sin(), x * rngle.sin() + y * rngle.cos()}; }
			vec2<T>  operator+ (const utils::angle::rad angle) const noexcept { return {x * angle.cos() - y * angle.sin(), x * angle.sin() + y * angle.cos()}; }
			vec2<T>  operator- (const utils::angle::deg angle) const noexcept { utils::angle::rad rngle{angle}; return {x * rngle.cos() - y * rngle.sin(), x * rngle.sin() + y * rngle.cos()}; }
			vec2<T>  operator- (const utils::angle::rad angle) const noexcept { return {x * angle.cos() - y * angle.sin(), x * angle.sin() + y * angle.cos()}; }
			vec2<T>& operator+=(const utils::angle::deg angle)       noexcept { return *this = *this + angle; }
			vec2<T>& operator+=(const utils::angle::rad angle)       noexcept { return *this = *this + angle; }
			vec2<T>& operator-=(const utils::angle::deg angle)       noexcept { return *this = *this - angle; }
			vec2<T>& operator-=(const utils::angle::rad angle)       noexcept { return *this = *this - angle; }
			vec2<T>& operator= (const utils::angle::deg angle)       noexcept { return *this = angle.to_rad(); }
			vec2<T>& operator= (const utils::angle::rad angle)       noexcept { return *this = {angle.cos() * magnitude(), angle.sin() * magnitude()}; }
#endif
			// VEC & VEC OPERATORS
			vec2<T>  operator+ (const vec2<T>& oth) const noexcept { return {x + oth.x, y + oth.y}; }
			vec2<T>  operator- (const vec2<T>& oth) const noexcept { return {x - oth.x, y - oth.y}; }
			vec2<T>  operator* (const vec2<T>& oth) const noexcept { return {x * oth.x, y * oth.y}; }
			vec2<T>  operator/ (const vec2<T>& oth) const noexcept { return {x / oth.x, y / oth.y}; }

			vec2<T>& operator+=(const vec2<T>& oth)       noexcept { return *this = *this + oth; }
			vec2<T>& operator-=(const vec2<T>& oth)       noexcept { return *this = *this - oth; }
			vec2<T>& operator*=(const vec2<T>& oth)       noexcept { return *this = *this * oth; }
			vec2<T>& operator/=(const vec2<T>& oth)       noexcept { return *this = *this / oth; }

			bool     operator==(const vec2<T>& oth) const noexcept { return x == oth.x && y == oth.y; }
			bool     operator!=(const vec2<T>& oth) const noexcept { return !(*this == oth); }

			static T dot(const vec2<T>& a, const vec2<T>& b) noexcept { return a.x * b.x + a.y * b.y; }
			static T distance(const vec2<T>& a, const vec2<T>& b) noexcept
				{
				T dx = a.x - b.x;
				T dy = a.y - b.y;
				return std::sqrt(dx * dx + dy * dy);
				}

			// OTHER
			static vec2<T> lerp(const vec2<T>& a, const vec2<T>& b, T t) noexcept
				{
				return {utils::lerp(a.x, b.x, t), utils::lerp(a.y, b.y, t)};
				}
			static vec2<T> slerp_fast(const vec2<T>& a, const vec2<T>& b, T t) noexcept
				{
				return vec2{utils::lerp(a.x, b.x, t), utils::lerp(a.y, b.y, t)}.normalize()
					* (utils::lerp(a.magnitude(), b.magnitude(), t));
				}
			static vec2<T> tlerp_fast(const vec2<T>& a, const vec2<T>& b, T t) noexcept
				{
				return vec2{utils::lerp(a.x, b.x, t), utils::lerp(a.y, b.y, t)}.normalize()
					* std::sqrt(utils::lerp(a.magnitude2(), b.magnitude2(), t));
				}
			static vec2<T> slerp(const vec2<T>& a, const vec2<T>& b, T t) noexcept
				{
				T dot = std::clamp(vec2::dot(a, b), -1.0f, 1.0f);
				T theta = std::acos(dot) * t;
				vec2<T> relative_vec = (b - a * dot).normal();
				return ((a * std::cos(theta)) + (relative_vec * std::sin(theta)));
				}
		};
	}
