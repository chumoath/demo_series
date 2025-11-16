import _example
print(dir(_example.math))

math_util = _example.math.MathUtils(12.0)
math_util.add(1.0)
print(math_util.getValue())
print(math_util.distance(0, 0, 1, 1))
