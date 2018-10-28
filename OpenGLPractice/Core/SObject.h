#pragma once

namespace AR {

	struct SObject
	{
		virtual void OnStart(){}
		virtual void OnUpdate(){}
		virtual void OnDestroy(){}
	};
}