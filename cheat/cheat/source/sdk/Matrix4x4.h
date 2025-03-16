#pragma once
#include "sdk.h"

namespace SDK
{
	struct Matrix4x4
	{
		// Unity uses column-major order
		// First column
		float m00;
		float m10;
		float m20;
		float m30;

		// Second column
		float m01;
		float m11;
		float m21;
		float m31;

		// Third column
		float m02;
		float m12;
		float m22;
		float m32;

		// Fourth column
		float m03;
		float m13;
		float m23;
		float m33;

		// Constructor for identity matrix
		Matrix4x4()
		{
			m00 = 1.0f;
			m10 = 0.0f;
			m20 = 0.0f;
			m30 = 0.0f;
			m01 = 0.0f;
			m11 = 1.0f;
			m21 = 0.0f;
			m31 = 0.0f;
			m02 = 0.0f;
			m12 = 0.0f;
			m22 = 1.0f;
			m32 = 0.0f;
			m03 = 0.0f;
			m13 = 0.0f;
			m23 = 0.0f;
			m33 = 1.0f;
		}

		// Get a zero matrix
		static Matrix4x4 Zero()
		{
			Matrix4x4 mat;
			mat.m00 = 0.0f;
			mat.m10 = 0.0f;
			mat.m20 = 0.0f;
			mat.m30 = 0.0f;
			mat.m01 = 0.0f;
			mat.m11 = 0.0f;
			mat.m21 = 0.0f;
			mat.m31 = 0.0f;
			mat.m02 = 0.0f;
			mat.m12 = 0.0f;
			mat.m22 = 0.0f;
			mat.m32 = 0.0f;
			mat.m03 = 0.0f;
			mat.m13 = 0.0f;
			mat.m23 = 0.0f;
			mat.m33 = 0.0f;
			return mat;
		}

		// Get an identity matrix
		static Matrix4x4 Identity()
		{
			Matrix4x4 mat;
			mat.m00 = 1.0f;
			mat.m10 = 0.0f;
			mat.m20 = 0.0f;
			mat.m30 = 0.0f;
			mat.m01 = 0.0f;
			mat.m11 = 1.0f;
			mat.m21 = 0.0f;
			mat.m31 = 0.0f;
			mat.m02 = 0.0f;
			mat.m12 = 0.0f;
			mat.m22 = 1.0f;
			mat.m32 = 0.0f;
			mat.m03 = 0.0f;
			mat.m13 = 0.0f;
			mat.m23 = 0.0f;
			mat.m33 = 1.0f;
			return mat;
		}

		// Optional: Matrix multiplication
		Matrix4x4 operator*(const Matrix4x4& other) const
		{
			Matrix4x4 result;

			result.m00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
			result.m10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
			result.m20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
			result.m30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;

			result.m01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
			result.m11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
			result.m21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
			result.m31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;

			result.m02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
			result.m12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
			result.m22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
			result.m32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;

			result.m03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;
			result.m13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;
			result.m23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;
			result.m33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

			return result;
		}
	};
}
