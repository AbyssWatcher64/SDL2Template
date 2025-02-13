#pragma once
#include "PreCompileHeaders.h"

class Module
{
public:
	Module() : active(false)
	{

	}

	virtual ~Module()
	{

	}

	virtual void Init()
	{
		active = true;
	}

	// Each frame consists of the following steps, which go in order. 
	// Refer to Engine.h to understand what each of them do.
	virtual bool Awake()
	{
		return true;
	}

	virtual bool Start() 
	{
		return true;
	}

	virtual bool PreUpdate()
	{
		return true;
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool Render()
	{
		return true;
	}

	virtual bool PostUpdate()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	// TODO: Maybe disable copying / moving.

public:
	std::string name;
	bool active;

	// TODO: Maybe add configParameters from the xml_node?
};