#pragma once

#include "..\Core\TypeDefs.h"

namespace AR {

	class Color4f
	{
	public:
		float r = 0;
		float g = 0;
		float b = 0;
		float a = 0;

		Color4f() {}
		Color4f(float r , float g , float b , float a):r(r),g(g),b(b),a(a){}
		~Color4f() {}
	};

}

