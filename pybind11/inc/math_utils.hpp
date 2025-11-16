#pragma once

class MathUtils {
public:
    // 构造函数
    MathUtils(double value);

    // 获取初始值
    double getValue() const;

    // 静态方法：计算两点距离
    static double distance(double x1, double y1, double x2, double y2);

    // 实例方法：给初始值加上一个数
    double add(double x);
    
    static void print_hello();
private:
    double startValue_;
};