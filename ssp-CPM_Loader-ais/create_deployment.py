import os
from conan.tools.files import copy

def deploy(graph, output_folder, **kwargs):
    conanfile = graph.root.conanfile
    conanfile.output.warning("######## DEPLOYING DEPENDENCIES (INSTALL ONLY) ########")

    for dep in conanfile.dependencies.host.values():
        pkg = dep.package_folder
        if not pkg:
            continue

        pkg_name = str(dep.ref.name)
        pkg_ver = str(dep.ref.version)

        deploy_dir = os.path.join(output_folder, f"{pkg_name}_{pkg_ver}")
        conanfile.output.info(f"Collecting runtime from {dep.ref} to {deploy_dir}")

        for folder in ["bin", "lib", "share", "include"]:
            src_dir = os.path.join(pkg, folder)
            if os.path.exists(src_dir):
                copy(
                    conanfile,
                    "*",
                    src=src_dir,
                    dst=os.path.join(deploy_dir, folder)
                )
