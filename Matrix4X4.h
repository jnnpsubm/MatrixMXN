#pragma once
#include <iostream>
#include <DirectXMath.h>

class Matrix4X4 {
public:
	union {
		struct {
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[4][4];
	};

	Matrix4X4() {}
	Matrix4X4(float _m00, float _m01, float _m02, float _m03,
		      float _m10, float _m11, float _m12, float _m13,
		      float _m20, float _m21, float _m22, float _m23,
		      float _m30, float _m31, float _m32, float _m33)
		: m00(_m00), m01(_m01), m02(_m02), m03(_m03),
		  m10(_m10), m11(_m11), m12(_m12), m13(_m13),
		  m20(_m20), m21(_m21), m22(_m22), m23(_m23),
		  m30(_m30), m31(_m31), m32(_m32), m33(_m33) {}

	float(&operator[](int i))[4]{
		return m[i];
	}
	const float(&operator[](int i) const)[4]{
		return m[i];
	}

	Matrix4X4 operator*(const Matrix4X4& rhs) {
#define dot(r,c) m##r##0*rhs.m0##c+m##r##1*rhs.m1##c+m##r##2*rhs.m2##c+m##r##3*rhs.m3##c
		Matrix4X4 ret(dot(0, 0), dot(0, 1), dot(0, 2), dot(0, 3),
			          dot(1, 0), dot(1, 1), dot(1, 2), dot(1, 3),
			          dot(2, 0), dot(2, 1), dot(2, 2), dot(2, 3),
			          dot(3, 0), dot(3, 1), dot(3, 2), dot(3, 3));
		return ret;
#undef dot
	}

	operator DirectX::XMMATRIX() const {
		return DirectX::XMMatrixSet(m00, m01, m02, m03,
			                        m10, m11, m12, m13,
			                        m20, m21, m22, m23,
			                        m30, m31, m32, m33);
	}
	bool operator==(DirectX::FXMMATRIX rhs) const {
#define row_equal(row) \
    m##row##0==DirectX::XMVectorGetX(rhs.r[##row##])&&m##row##1==DirectX::XMVectorGetY(rhs.r[##row##])&&\
    m##row##2==DirectX::XMVectorGetZ(rhs.r[##row##])&&m##row##3==DirectX::XMVectorGetW(rhs.r[##row##])
		return row_equal(0) && row_equal(1) && row_equal(2) && row_equal(3);
#undef row_equal
	}
	bool nearlyEqual(DirectX::FXMMATRIX rhs) const {
		using std::fabs;
		static const float episilon = 0.00001f;
#define row_nearly_equal(row) \
    fabs(m##row##0 - DirectX::XMVectorGetX(rhs.r[##row##]))<episilon && \
    fabs(m##row##1 - DirectX::XMVectorGetY(rhs.r[##row##]))<episilon && \
    fabs(m##row##2 - DirectX::XMVectorGetZ(rhs.r[##row##]))<episilon && \
    fabs(m##row##3 - DirectX::XMVectorGetW(rhs.r[##row##]))<episilon
		return row_nearly_equal(0) && row_nearly_equal(1) &&
			row_nearly_equal(2) && row_nearly_equal(3);
#undef row_nearly_equal
	}
};

inline
std::ostream& operator<<(std::ostream& os, DirectX::FXMMATRIX m) {
	for (int i = 0; i < 4; ++i) {
		os << DirectX::XMVectorGetX(m.r[i]) << '\t';
		os << DirectX::XMVectorGetY(m.r[i]) << '\t';
		os << DirectX::XMVectorGetZ(m.r[i]) << '\t';
		os << DirectX::XMVectorGetW(m.r[i]) << std::endl;
	}
	return os;
}

inline
std::ostream& operator<<(std::ostream& os, const Matrix4X4& m) {
	for (int i = 0; i < 4; ++i) {
		os << m[i][0] << '\t';
		os << m[i][1] << '\t';
		os << m[i][2] << '\t';
		os << m[i][3] << std::endl;
	}
	return os;
}