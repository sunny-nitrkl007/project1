import os
import xml.etree.ElementTree as ET

from conan import ConanFile

from conan.tools.cmake import (
    cmake_layout,
    CMakeToolchain,
    CMake,
    CMakeDeps
)
from os import path


class CPMConan(ConanFile):

    name = "cpm"
    version = "development"

    # default_options = {
    # "cpython/*:with_tkinter": False,
    # "cpython/*:with_curses": False,
    # # "cpython/*:with_gdbm": False,
    # }

    settings = (
        "arch",
        "os",
        "compiler",
        "build_type"
    )

   # generators = "CMakeDeps"
   # generators = "CMakeDeps", "CMakeToolchain" 

    exports_sources = "*"

    # def configure(self):
    #     self.output.warning("Disabling cpython optional packages")
    #     self.options["cpython"].with_tkinter = False
    #     self.options["cpython"].with_curses = False
        # self.options["cpython"].with_gdbm = False

    # def configure(self):
    #     self.output.warning("Disabling cpython tkinter")
    #     self.options["cpython"].with_tkinter = False     

    def requirements(self):
        #pass
        self.requires("boost/1.83.0")
        self.requires("cate_ros2/jazzy-test-4")
        # resolve DDS conflict
        self.requires("zlib/1.3.2")
        self.requires("openssl/3.5.8")
    
    def layout(self):

        build_path = path.join(
            "build",
            self.settings.build_type.value
        )

        cmake_layout(self, build_folder=build_path)

        self.folders.build = build_path

        self.folders.generators = path.join(
            build_path,
            "generators"
        )

    def generate(self):

        deps = CMakeDeps(self)
        deps.generate()

        # cate_dep = self.dependencies["cate_ros2"]
        
        # # Override Conan's visibility graph to treat it as a standard linked library
        # #cate_dep.package_type = "shared-library"
        
        # # Instruct Conan that this dependency MUST visible to the current CMake space
        # # (This forces CMakeDeps to generate the missing -config.cmake file)
        # deps = CMakeDeps(self)
        # deps.set_property("cate_ros2", "cmake_file_name", "cate_ros2")
        # deps.set_property("cate_ros2", "cmake_target_name", "cate_ros2::cate_ros2")
        
        # # Ensure include paths are populated even if the package recipe is thin
        # if not cate_dep.cpp_info.includedirs:
        #     cate_dep.cpp_info.includedirs = ["include"]
            
        # deps.generate()



        tc = CMakeToolchain(self)

        tc.presets_prefix = ""

        tc.generate()


    def build(self):

        self._build_ros2_interfaces()

        cmake = CMake(self)

        cmake.configure()

        cmake.build()

        cmake.install()

    def _resolve_repo_root(self):
        repo_root = path.abspath(path.join(self.source_folder, "..", ".."))

        if not path.isdir(path.join(repo_root, "CPM-Loader-ais")):
            raise Exception("Resolved repo root '{}' has no CPM-Loader-ais.".format(repo_root))

        return repo_root

    def _discover_ros2_interface_packages(self, interfaces_root):
        pkg_names = sorted(
            name for name in os.listdir(interfaces_root)
            if path.isfile(path.join(interfaces_root, name, "package.xml"))
        )
        if not pkg_names:
            raise Exception("No package.xml found under '{}'.".format(interfaces_root))

        depends = {}
        for name in pkg_names:
            root_el = ET.parse(path.join(interfaces_root, name, "package.xml")).getroot()
            local_deps = set()
            for tag in ("depend", "build_depend", "exec_depend"):
                for el in root_el.findall(tag):
                    dep_name = (el.text or "").strip()
                    if dep_name in pkg_names and dep_name != name:
                        local_deps.add(dep_name)
            depends[name] = local_deps

        ordered = []
        remaining = dict(depends)
        while remaining:
            ready = sorted(n for n, deps in remaining.items() if not deps)
            if not ready:
                raise Exception(
                    "Circular dependency among ROS2 interface packages: {}".format(
                        sorted(remaining.keys())
                    )
                )
            for n in ready:
                ordered.append(n)
                del remaining[n]
            for deps in remaining.values():
                deps.difference_update(ready)

        return ordered

    def _build_ros2_interfaces(self):
        repo_root = self._resolve_repo_root()
        ros2_models_dir = path.join(repo_root, "ros2_models")
        interfaces_root = path.abspath(path.join(repo_root, "..", "Ros2_Interfaces", "src"))

        if not path.isdir(interfaces_root):
            raise Exception("Resolved interfaces root '{}' does not exist.".format(interfaces_root))

        interface_packages = self._discover_ros2_interface_packages(interfaces_root)
        self.output.info("ROS2 interface build order: {}".format(interface_packages))

        original_build_folder = self.folders.build

        for pkg in interface_packages:
            self.folders.build = path.join(original_build_folder, "ros2_interfaces", pkg)

            cmake = CMake(self)
            cmake.configure(
                build_script_folder=path.join(interfaces_root, pkg),
                variables={
                    "CMAKE_INSTALL_PREFIX": ros2_models_dir,
                    "CMAKE_PREFIX_PATH": ros2_models_dir,
                },
            )
            cmake.build()
            cmake.install()

        self.folders.build = original_build_folder

    # def package_info(self):
    #     self.runenv_info.prepend_path(
    #         "LD_LIBRARY_PATH",
    #         os.path.join(self.package_folder, "lib")
    #     )    