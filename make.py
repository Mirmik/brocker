#!/usr/bin/env python3

from licant.cxx_modules import application, doit
from licant.modules import submodule
from licant.libs import include

include("g0")

application("target",
	sources = ["main.cpp"],
	include_paths = [".", "include"],

	include_modules = [
		submodule("g0.base"),

		submodule("gxx"),
		submodule("gxx.print", "cout"),
		submodule("gxx.dprint", "cout"),
	]
)

doit("target")