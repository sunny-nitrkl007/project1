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

        cmake = CMake(self)

        cmake.configure()

        cmake.build()

        cmake.install()

    # def package_info(self):
    #     self.runenv_info.prepend_path(
    #         "LD_LIBRARY_PATH",
    #         os.path.join(self.package_folder, "lib")
    #     )    