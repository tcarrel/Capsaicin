include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Capsaicin"
	architecture "x86_64"
	startproject "Test_App"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "Capsaicin/vendor"
group ""

include "Capsaicin"
include "Test_App"
