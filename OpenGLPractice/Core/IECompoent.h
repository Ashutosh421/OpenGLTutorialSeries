#pragma once
#include "SObject.h"

namespace AR {
	struct IEComponent : public AR::SObject
	{
		virtual void OnStart() override {}
		virtual void OnUpdate() override {}
		virtual void OnDestroy() override {}
	};
}

