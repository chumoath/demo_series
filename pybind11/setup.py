from setuptools import setup, Extension
import pybind11

# 定义扩展模块
ext_modules = [
    Extension(
        "math_utils",  # 模块名
        ["src/math_utils.cpp", "src/bind.cpp"],  # 源文件
        include_dirs=[pybind11.get_include(), "inc/"],  # 自动获取 pybind11 头文件路径
        language="c++",
    ),
]

setup(
    name="math_utils",
    ext_modules=ext_modules,
    zip_safe=False,
)