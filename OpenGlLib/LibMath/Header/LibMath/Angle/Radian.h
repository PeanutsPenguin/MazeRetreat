#ifndef __LIBMATH__ANGLE__RADIAN_H__
#define __LIBMATH__ANGLE__RADIAN_H__

namespace LibMath
{
	class Degree;

	class Radian
	{
	public:
		Radian(void) : Radian(0.f) {}
		explicit Radian(float raw) : m_value(raw) {}						// explicit so no ambiguous / implicit conversion from float to angle can happen
		Radian(Radian const&) = default;
		~Radian(void) = default;

		operator Degree(void) const;					// Degree angle = Radian{0.5};		// implicit conversion from Radian to Degree

		Radian& operator=(Radian const&) = default;
		Radian& operator+=(Radian);					// Radian angle += Radian{0.5};
		Radian& operator-=(Radian);					// Radian angle -= Radian{0.5};
		Radian& operator*=(float);					// Radian angle *= 3;
		Radian& operator/=(float);					// Radian angle /= 3;

		void	wrap(bool = false);					// true -> limite m_value to range [-pi, pi[	// false -> limite m_value to range [0, 2 pi[

		float	radian(bool = true) const;			// return angle in radian	// true -> limite value to range [-pi, pi[		// false -> limite value to range [0, 2 pi[
		float	degree(bool = false) const;			// return angle in degree	// true -> limite value to range [-180, 180[	// false -> limite value to range [0, 360[
		float	raw(void) const;						// return m_angle

	private:
		float m_value{ 0 };
	};

	bool	operator>(Radian, Radian);
	bool	operator<(Radian, Radian);

	bool	operator==(Radian, Radian);				// bool isEqual = Radian{0.5} == Radian{0.5};	// true
	bool	operator==(Radian, Degree const&);		// bool isEqual = Radian{0.5} == Degree{60};	// false

	Radian	operator-(Radian);						// Degree angle = - Radian{0.5};				// Radian{-0.5}

	Radian	operator+(Radian, Radian);				// Radian angle = Radian{0.5} + Radian{0.5};	// Radian{1}
	Radian	operator-(Radian, Radian);				// Radian angle = Radian{0.5} - Radian{0.5};	// Radian{0}
	Radian	operator*(Radian, float);				// Radian angle = Radian{0.5} * 3;				// Radian{1.5}
	Radian	operator/(Radian, float);				// Radian angle = Radian{0.5} / 3;				// Radian{0.166...}

	inline namespace Literal
	{
		LibMath::Radian operator""_rad(long double);			// Radian angle = 0.5_rad;
		LibMath::Radian operator""_rad(unsigned long long int);	// Radian angle = 1_rad;
	}
}

#endif // !__LIBMATH__ANGLE__RADIAN_H__
