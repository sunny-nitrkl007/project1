from conan import ConanFile
from conan.tools.files import copy
import os
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
    options = {
        "build_target": ["ros2_model", "nvm", "apps", "tes_apps"]
    }

    default_options = {
        "build_target": "ros2_model"
    }
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
    #jazzy-test-4 1.0.1"  

    def requirements(self):
        #pass
        self.requires("boost/1.83.0")
        self.requires("cate_ros2/1.0.1")
        # resolve DDS conflict
        self.requires("zlib/1.3.2")
        #self.requires("openssl/3.5.8")
        self.requires("openssl/3.5.9", override=True)
    
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

         # Create deployment folder during conan install
        os.makedirs(
            os.path.join(
                self.recipe_folder,
                "dependencies"
            ),
            exist_ok=True
        )

    def generate(self):
        #self._create_deployment()
        self.output.warning(f"BUILD_TARGET = {self.options.build_target}")
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        tc.presets_prefix = ""
        tc.variables["BUILD_TARGET"] = str(self.options.build_target)
        tc.variables["CATE_ROS2_ROOT"] = self.dependencies["cate_ros2"].package_folder
        tc.generate()

        # deploy_root = os.path.join(
        # self.recipe_folder,
        # "deployment"
        # )
        
        # self.output.warning("######## GENERATE CALLED ########")
        # os.makedirs(deploy_root, exist_ok=True)

        # for dep in self.dependencies.host.values():

        #     pkg = dep.package_folder

        #     if not pkg:
        #         continue

        #     pkg_name = str(dep.ref.name)
        #     pkg_ver = str(dep.ref.version)

        #     deploy_dir = os.path.join(
        #     deploy_root,
        #     f"{pkg_name}_{pkg_ver}"
        #     )

        #     os.makedirs(deploy_dir, exist_ok=True)

        #     self.output.info(
        #         f"Collecting runtime from {dep.ref}"
        #     )

        #     copy(
        #         self,
        #         "*",
        #         src=os.path.join(pkg, "bin"),
        #         dst=os.path.join(deploy_dir, "bin")
        #     )

        #     copy(
        #         self,
        #         "*",
        #         src=os.path.join(pkg, "lib"),
        #         dst=os.path.join(deploy_dir, "lib")
        #     )

        #     copy(
        #         self,
        #         "*",
        #         src=os.path.join(pkg, "share"),
        #         dst=os.path.join(deploy_dir, "share")
        #     )

        #     copy(
        #         self,
        #         "*",
        #         src=os.path.join(pkg, "include"),
        #         dst=os.path.join(deploy_dir, "include")
        #     )
        


    def build(self):
        self.output.warning("******** BUILD ********")
        cmake = CMake(self)

        cmake.configure()

        cmake.build()

        cmake.install()

    # def package_info(self):
    #     self.runenv_info.prepend_path(
    #         "LD_LIBRARY_PATH",
    #         os.path.join(self.package_folder, "lib")
    #     )    

   

