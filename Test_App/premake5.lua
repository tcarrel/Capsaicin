project "Test_App"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Capsaicin/vendor/spdlog/include",
		"%{wks.location}/Capsaicin/src",
		"%{wks.location}/Capsaicin/vendor"
		--"%{IncludeDir.glm}",
		--"%{IncludeDir.entt}"
	}

	links
	{
		"Capsaicin"
	}

	filter "system:windows"
		systemversion "latest"
        defines "CP_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "CP_DEBUG"
		runtime "Debug"
		symbols "on"
		
		postbuildcommands
		{
			"{COPYDIR} \"%{LibraryDir.VulkanSDK_DebugDLL}\" \"%{cfg.targetdir}\""
		}

	filter "configurations:Release"
		defines "CP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CP_DIST"
		runtime "Release"
		optimize "on"
