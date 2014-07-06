project "system"
    kind "StaticLib"

    files { "**.cc", "**.cpp", "**.c", "**.h" }
    excludes { "Win32/**", "Unix/**", "TinyMT/**" }
    includedirs ".."
    configuration "not vs*"
        buildoptions { "-std=gnu++0x" }
