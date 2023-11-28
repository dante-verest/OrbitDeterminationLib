#pragma once
#include "stdafx.h"

class Components;
enum Commands;

class Mediator
{
public:
	virtual void Notify(Components* sender, Commands event) = 0;
};

