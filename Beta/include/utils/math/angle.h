#pragma once
#include <ostream>
#include <stdint.h>
#include <cmath> //trigonometry
#include <algorithm> //clamp
#include <variant> //Angle class

#include "../cout_utilities.h"
#include "constants.h"

namespace utils::angle
	{
	using constants::PIf;
	using constants::PId;
	using constants::PI;

	inline float deg_to_rad(float d) noexcept { return d * (PIf / 180); }
	inline float rad_to_deg(float r) noexcept { return r * (180 / PIf); }

	class deg;
	class rad;

	namespace literals//@section MISSING DEFINITIONS
		{
		inline deg operator""_deg(long double value)        noexcept;
		inline deg operator""_deg(unsigned long long value) noexcept;
		inline rad operator""_rad(long double value)        noexcept;
		inline rad operator""_rad(unsigned long long value) noexcept;
		inline rad operator""_radpi(long double value)        noexcept;
		inline rad operator""_radpi(unsigned long long value) noexcept;
		}

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== =====                 DEG                 ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	class deg
		{
		friend class rad;
		friend deg literals::operator""_deg(long double value) noexcept;
		friend deg literals::operator""_deg(unsigned long long value) noexcept;
		private:

		public:
			deg() noexcept = default;
			deg(float value) noexcept : value(value) {}
			float value{0.f};

			deg(const rad r) noexcept;//@section MISSING DEFINITIONS : value(rad_to_deg(r.value)) {}
			deg& operator=(const rad r) noexcept;//@section MISSING DEFINITIONS { value = rad_to_deg(r.value); return *this; };
			rad to_rad() const noexcept;//@section MISSING DEFINITIONS { return rad{*this}; }

			deg clamped() const noexcept 
				{
				float v = value;
				while (v < 0) { v += 360; }
				while (v >= 360) { v -= 360; }
				return deg{v};
				}
			void clamp() noexcept { *this = this->clamped(); }

			deg  operator+ (const deg oth) const noexcept { return deg{value + oth.value}; }
			deg  operator- (const deg oth) const noexcept { return deg{value - oth.value}; }
			deg& operator+=(const deg oth)       noexcept { return *this = *this + oth; }
			deg& operator-=(const deg oth)       noexcept { return *this = *this - oth; }
			deg  operator+ (const rad oth) const noexcept;//@section MISSING DEFINITIONS
			deg  operator- (const rad oth) const noexcept;//@section MISSING DEFINITIONS
			deg& operator+=(const rad oth)       noexcept;//@section MISSING DEFINITIONS
			deg& operator-=(const rad oth)       noexcept;//@section MISSING DEFINITIONS

			deg  operator* (float oth) const noexcept { return deg{value * oth}; }
			deg  operator/ (float oth) const noexcept { return deg{value / oth}; }
			deg& operator*=(float oth)       noexcept { return *this = *this * oth; }
			deg& operator/=(float oth)       noexcept { return *this = *this / oth; }

			deg  operator- () const noexcept { return {-value}; };

			bool operator==(const deg oth) const noexcept { return clamped().value == oth.clamped().value; }
			bool operator!=(const deg oth) const noexcept { return !(*this == oth); }
			bool operator==(const rad oth) const noexcept;//@section MISSING DEFINITIONS
			bool operator!=(const rad oth) const noexcept;//@section MISSING DEFINITIONS

			       float sin()      const noexcept { return std::sin(deg_to_rad(value)); }
			       float cos()      const noexcept { return std::cos(deg_to_rad(value)); }
			       float tan()      const noexcept { return std::tan(deg_to_rad(value)); }
			static float sin(const deg a) noexcept { return a.sin(); }
			static float cos(const deg a) noexcept { return a.cos(); }
			static float tan(const deg a) noexcept { return a.tan(); }
		};


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== =====                 RAD                 ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	class rad
		{
		friend class deg;
		friend rad literals::operator""_rad(long double value) noexcept;
		friend rad literals::operator""_rad(unsigned long long value) noexcept;
		private:

		public:
			rad() noexcept = default;
			rad(float value) noexcept : value(value) {}
			float value{0.f};

			rad(const deg d) noexcept : value(deg_to_rad(d.value)) {}
			rad& operator=(const deg& d) noexcept { value = deg_to_rad(d.value); return *this; };
			deg to_deg() const noexcept { return deg{*this}; }

			deg clamped() const noexcept
				{
				float v = value;
				while (v < 0) { v += 2 * PIf; }
				while (v >= 2*PIf) { v -= 2 * PIf; }
				return deg{v};
				}
			void clamp() noexcept { *this = this->clamped(); }

			rad  operator+ (const rad oth) const noexcept { return {value + oth.value}; }
			rad  operator- (const rad oth) const noexcept { return {value - oth.value}; }
			rad& operator+=(const rad oth)       noexcept { return *this = *this + oth; }
			rad& operator-=(const rad oth)       noexcept { return *this = *this - oth; }
			rad  operator+ (const deg oth) const noexcept { return {value + deg_to_rad(oth.value)}; }
			rad  operator- (const deg oth) const noexcept { return {value - deg_to_rad(oth.value)}; }
			rad& operator+=(const deg oth)       noexcept { return *this = *this + oth; }
			rad& operator-=(const deg oth)       noexcept { return *this = *this - oth; }

			rad  operator* (float oth) const noexcept { return rad{value * oth}; }
			rad  operator/ (float oth) const noexcept { return rad{value / oth}; }
			rad& operator*=(float oth)       noexcept { return *this = *this * oth; }
			rad& operator/=(float oth)       noexcept { return *this = *this / oth; }

			rad  operator- ()          const noexcept { return {value - PI}; };

			bool operator==(const rad oth) const noexcept { return clamped().value == oth.clamped().value; }
			bool operator!=(const rad oth) const noexcept { return !(*this == oth); } 
			bool operator==(const deg oth) const noexcept { return *this == oth.to_rad(); }
			bool operator!=(const deg oth) const noexcept { return !(*this == oth); }

			       float sin()      const noexcept { return std::sin(value); }
			       float cos()      const noexcept { return std::cos(value); }
			       float tan()      const noexcept { return std::tan(value); }
			static float sin(const rad a) noexcept { return a.sin(); }
			static float cos(const rad a) noexcept { return a.cos(); }
			static float tan(const rad a) noexcept { return a.tan(); }
			static rad asin(float n)      noexcept { return {std::asin(n)}; }
			static rad acos(float n)      noexcept { return {std::acos(n)}; }
			static rad atan(float n)      noexcept { return {std::atan(n)}; }
			static rad atan2(float a, float b) noexcept { return{std::atan2(a, b)}; }
		};


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== =====                ANGLE                ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	//Not sure if good idea or not. Bigger overhead, way more intuitive.
	class Angle
		{
		private:
			std::variant<deg, rad> value;
			void make_rad() noexcept { if (std::holds_alternative<deg>(value)) { value = rad{std::get<deg>(value)}; } }
			void make_deg() noexcept { if (std::holds_alternative<rad>(value)) { value = deg{std::get<rad>(value)}; } }

		public:
			Angle() noexcept = default;
			Angle(const deg d) noexcept : value(d) {}
			Angle(const rad r) noexcept : value(r) {}
			rad get_rad() noexcept { make_rad(); return std::get<rad>(value); }
			deg get_deg() noexcept { make_deg(); return std::get<deg>(value); }

			Angle  operator+ (const Angle& oth) const noexcept
				{
				if (std::holds_alternative<deg>(value))
					{
					if (std::holds_alternative<deg>(oth.value)) { return {std::get<deg>(value) + std::get<deg>(oth.value)}; }
					else { return {std::get<deg>(value) + std::get<rad>(oth.value)}; }
					}
				else
					{
					if (std::holds_alternative<deg>(oth.value)) { return {std::get<rad>(value) + std::get<deg>(oth.value)}; }
					else { return {std::get<rad>(value) + std::get<rad>(oth.value)}; }
					}
				}
			Angle  operator- (const Angle& oth) const noexcept
				{
				if (std::holds_alternative<deg>(value))
					{
					if (std::holds_alternative<deg>(oth.value)) { return {std::get<deg>(value) - std::get<deg>(oth.value)}; }
					else { return {std::get<deg>(value) - std::get<rad>(oth.value)}; }
					}
				else
					{
					if (std::holds_alternative<deg>(oth.value)) { return {std::get<rad>(value) - std::get<deg>(oth.value)}; }
					else { return {std::get<rad>(value) - std::get<rad>(oth.value)}; }
					}
				}
			Angle& operator+=(const Angle& oth)       noexcept { return *this = *this + oth; }
			Angle& operator-=(const Angle& oth)       noexcept { return *this = *this - oth; }
			Angle  operator+ (const rad oth)    const noexcept
				{
				if (std::holds_alternative<deg>(value)) { return {std::get<deg>(value) + oth}; }
				else { return{std::get<rad>(value) + oth}; }
				}
			Angle  operator- (const rad oth)    const noexcept
				{
				if (std::holds_alternative<deg>(value)) { return {std::get<deg>(value) - oth}; }
				else { return{std::get<rad>(value) - oth}; }
				}
			Angle& operator+=(const rad oth)          noexcept { return *this = *this + oth; }
			Angle& operator-=(const rad oth)          noexcept { return *this = *this - oth; }
			Angle  operator+ (const deg oth)    const noexcept
				{
				if (std::holds_alternative<deg>(value)) { return {std::get<deg>(value) + oth}; }
				else { return{std::get<rad>(value) + oth}; }
				}
			Angle  operator- (const deg oth)    const noexcept
				{
				if (std::holds_alternative<deg>(value)) { return {std::get<deg>(value) - oth}; }
				else { return{std::get<rad>(value) - oth}; }
				}
			Angle& operator+=(const deg oth)          noexcept { return *this = *this + oth; }
			Angle& operator-=(const deg oth)          noexcept { return *this = *this - oth; }

			Angle  operator* (float oth) const noexcept
				{
				if (std::holds_alternative<deg>(value)) { return {std::get<deg>(value) * oth}; }
				else { return {std::get<rad>(value) * oth}; }
				}
			Angle  operator/ (float oth) const noexcept
				{
				if (std::holds_alternative<deg>(value)) { return {std::get<deg>(value) / oth}; }
				else { return {std::get<rad>(value) / oth}; }
				}
			Angle& operator*=(float oth) noexcept { return *this = *this * oth; }
			Angle& operator/=(float oth) noexcept { return *this = *this / oth; }

			Angle  operator- () const noexcept
				{
				if (std::holds_alternative<deg>(value)) { return {-std::get<deg>(value)}; }
				else { return {-std::get<rad>(value)}; }
				}

			       float sin()         noexcept { return get_rad().sin(); }
			       float cos()         noexcept { return get_rad().cos(); }
			       float tan()         noexcept { return get_rad().tan(); }
			static float sin(Angle& a) noexcept { return a.sin(); }
			static float cos(Angle& a) noexcept { return a.cos(); }
			static float tan(Angle& a) noexcept { return a.tan(); }
			static Angle asin(float n) noexcept { return {rad::asin(n)}; }
			static Angle acos(float n) noexcept { return {rad::acos(n)}; }
			static Angle atan(float n) noexcept { return {rad::atan(n)}; }
			static Angle atan2(float a, float b) noexcept { return{rad::atan2(a, b)}; }
		};

	namespace trigonometry
		{
		inline float sin(const rad a) noexcept { return a.sin(); }
		inline float cos(const rad a) noexcept { return a.cos(); }
		inline float tan(const rad a) noexcept { return a.tan(); }
		inline float sin(const deg a) noexcept { return rad{a}.sin(); }
		inline float cos(const deg a) noexcept { return rad{a}.cos(); }
		inline float tan(const deg a) noexcept { return rad{a}.tan(); }
		inline rad asin(float n) noexcept { return rad::asin(n); }
		inline rad acos(float n) noexcept { return rad::acos(n); }
		inline rad atan(float n) noexcept { return rad::atan(n); }
		inline rad atan2(float a, float b) noexcept { return rad::atan2(a, b); }
		}

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== =====         MISSING DEFINITIONS         ===== ===== ===== ===== ===== ===== =====
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	inline deg::deg(const rad r) noexcept : value(rad_to_deg(r.value)) {}
	deg& deg::operator=(const rad r) noexcept { value = rad_to_deg(r.value); return *this; };
	inline rad deg::to_rad() const noexcept { return rad{*this}; }

	inline deg  deg::operator+ (const rad oth) const noexcept { return deg{value + rad_to_deg(oth.value)}; }
	inline deg  deg::operator- (const rad oth) const noexcept { return deg{value - rad_to_deg(oth.value)}; }
	inline deg& deg::operator+=(const rad oth)       noexcept { return *this = *this + oth; }
	inline deg& deg::operator-=(const rad oth)       noexcept { return *this = *this - oth; }
	inline bool deg::operator==(const rad oth) const noexcept { return *this == oth.to_deg(); }
	inline bool deg::operator!=(const rad oth) const noexcept { return !(*this == oth); }
	
	namespace literals
		{
		inline deg operator""_deg(long double        value) noexcept { return deg{float(value)}; }
		inline deg operator""_deg(unsigned long long value) noexcept { return deg{float(value)}; }
		inline rad operator""_rad(long double        value) noexcept { return rad{float(value)}; }
		inline rad operator""_rad(unsigned long long value) noexcept { return rad{float(value)}; }
		inline rad operator""_radpi(long double        value) noexcept { return rad{float(value) * PIf}; }
		inline rad operator""_radpi(unsigned long long value) noexcept { return rad{float(value) * PIf}; }
		}

	}

namespace utils::cout
	{
	inline std::ostream& operator<<(std::ostream& os, const angle::deg& d)   noexcept { namespace ccu = utils::cout::support; return os << ccu::value << d.value << ccu::type << "d"; }
	inline std::ostream& operator<<(std::ostream& os, const angle::rad& r)   noexcept { namespace ccu = utils::cout::support; return os << ccu::value << r.value << ccu::type << "r"; }
	inline std::ostream& operator<<(std::ostream& os, const angle::Angle& a) noexcept { namespace ccu = utils::cout::support; return os << angle::Angle{a}.get_deg(); }
	}



