# 退火算法学习
# @`13
# 2017.7.15

# 模拟退火算法实现
# 需求：利用遗传算法求函数f(x)=x﹒sin(10π﹒x)+1.0的最大值,其中x∈[-1,2]。


import math
import random

PI = 3.14

# f(x)=x﹒sin(10π﹒x)+1.0
func = lambda x : x * math.sin(math.radians(10 * PI * x)) + 1.0

# 降温策略
# T(t+1)=k×T(t)  k===0.93



def SimulatedAnnealing(func, start, end, k=0.98, T=1000000000.0, step=0.01):
    """
    退火算法求函数极值
    :param    func: 函数
    :param    start: 下界
    :param    end: 上界
    :param    k: 冷却速率
    :param    T: 温度
    :param    step: 步长
    
    :return 求得func函数的极值点
    """
  
    # 初始化内容
    point = random.uniform(start,end)
  
  
    # 模拟退火
    while T > 0.1:
        
        T = k * T
        # 步进方向 -1 0 1
        direction = random.randint(-1,1)
        # 构造新值 并进行边界判断
        new_point = point + direction * step
        if new_point < start:
            new_point = start
        elif new_point > end:
            new_point = end
            
        # 利用函数进行成本计算
        cost = func(point)
        cost_new = func(point)
        
        # 判断是否更新原解  价值更高 / 算法以一定概率接受较差的值
        if cost_new > cost or random.random() < math.exp(-(cost_new - cost) / T):
            point = new_point
            # print str(point)+"=>"+str(new_point)
            
      
    return point

print func(SimulatedAnnealing(func,-1,2))



















