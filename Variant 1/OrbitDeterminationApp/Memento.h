#pragma once
#include "stdafx.h"

namespace Memento
{
	class Memento
	{
	protected:
		QSettings m_mementoSettings;
	public:
		virtual ~Memento();
		//virtual bool operator== (const Memento& other) const = 0;
	};
}

