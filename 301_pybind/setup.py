from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

ext_modules = [
    Pybind11Extension(
        "maths",
        sources=["bindings.cpp"],  # add maths.cpp if needed
        cxx_std=17,
    ),
]

setup(
    name="maths",
    version="0.1.0",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)