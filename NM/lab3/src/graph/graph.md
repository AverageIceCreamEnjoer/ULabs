# Лабораторная работа №3 численные методы

```python
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
```

## Рассмотрим сплайн аппроксимацию выборки из 1670 элементов нормального распреления при M = 1.04, $\sigma$ = 3.74 и различным параметром сглаживания


```python
df = pd.read_csv("../../spline_p0.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = 0', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_3_1.png)
    



```python
df = pd.read_csv("../../spline_p01.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = 0.1', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_4_1.png)
    



```python
df = pd.read_csv("../../spline_p03.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = 0.3', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_5_1.png)
    



```python
df = pd.read_csv("../../spline_p05.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = 0.5', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_6_1.png)
    



```python
df = pd.read_csv("../../spline_p07.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = 0.7', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_7_1.png)
    



```python
df = pd.read_csv("../../spline_p09.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = 0.9', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_8_1.png)
    



```python
df = pd.read_csv("../../spline_p099.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = 0.99', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_9_1.png)
    



```python
df = pd.read_csv("../../spline_p1.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)'], linestyle='--', linewidth=2, alpha=0.8)
plt.scatter(df['x'], df['f(x)'], marker='.', color='red', s=40)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p ~ 1', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1670 entries, 0 to 1669
    Data columns (total 2 columns):
     #   Column  Non-Null Count  Dtype  
    ---  ------  --------------  -----  
     0   x       1670 non-null   int64  
     1   f(x)    1670 non-null   float64
    dtypes: float64(1), int64(1)
    memory usage: 26.2 KB
    None



    
![png](output_10_1.png)
    


## Так как на большой выборке тяжело разглядеть разницу в конкретных значениях сетки, рассмотрим небольшую выборку из 10 элементов того же распределения с сглаживанием от 0 до 1 и попробуем варьировать веса


```python
df = pd.read_csv("../../splines1.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)0'], marker='o', linestyle='--', color='red', label='p=0', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)0.3'], marker='o', linestyle='--', color='orange', label='p=0.3', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)0.5'], marker='o', linestyle='--', color='green', label='p=0.5', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)0.7'], marker='o', linestyle='--', color='blue', label='p=0.7', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)1'], marker='o', linestyle='--', color='purple', label='p=1', linewidth=2, alpha=0.8)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = [0, 0.3, 0.5, 0.7, 1],', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 10 entries, 0 to 9
    Data columns (total 6 columns):
     #   Column   Non-Null Count  Dtype  
    ---  ------   --------------  -----  
     0   x        10 non-null     int64  
     1   f(x)0    10 non-null     float64
     2   f(x)0.3  10 non-null     float64
     3   f(x)0.5  10 non-null     float64
     4   f(x)0.7  10 non-null     float64
     5   f(x)1    10 non-null     float64
    dtypes: float64(5), int64(1)
    memory usage: 612.0 bytes
    None



    
![png](output_12_1.png)
    


## Как видим, небольшая выборка дала большую ошибку, так как прямая при p~1 далеко от M = 1.04. Попробуем подогнать данные увеличив вес четвертой точки с 1 до 10


```python
df = pd.read_csv("../../splines2.csv", sep=",")
print(df.info())
plt.figure(figsize=(16, 9))
plt.plot(df['x'], df['f(x)0'], marker='o', linestyle='--', color='red', label='p=0', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)0.3'], marker='o', linestyle='--', color='orange', label='p=0.3', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)0.5'], marker='o', linestyle='--', color='green', label='p=0.5', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)0.7'], marker='o', linestyle='--', color='blue', label='p=0.7', linewidth=2, alpha=0.8)
plt.plot(df['x'], df['f(x)1'], marker='o', linestyle='--', color='purple', label='p=1', linewidth=2, alpha=0.8)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True, alpha=0.5)
plt.ylim((-3.74,3.74))
plt.title('Сглаживание p = [0, 0.3, 0.5, 0.7, 1], w[3] = 10', fontsize=16)
plt.show()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 10 entries, 0 to 9
    Data columns (total 6 columns):
     #   Column   Non-Null Count  Dtype  
    ---  ------   --------------  -----  
     0   x        10 non-null     int64  
     1   f(x)0    10 non-null     float64
     2   f(x)0.3  10 non-null     float64
     3   f(x)0.5  10 non-null     float64
     4   f(x)0.7  10 non-null     float64
     5   f(x)1    10 non-null     float64
    dtypes: float64(5), int64(1)
    memory usage: 612.0 bytes
    None



    
![png](output_14_1.png)
    

