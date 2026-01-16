# Практическое задание №8
### вариант 7


```python
import pandas as pd
import matplotlib.pyplot as plt
```


```python
fig, ((ax1, ax2, ax3)) = plt.subplots(1, 3, figsize=(20, 8))

df1 = pd.read_csv('data/test1.csv')
df1.plot(x='t', y='x', style='.-', color='blue', label='RK-2', ylabel='Количество жертв', title='X - жертвы', ax=ax1, alpha=0.3)
df1.plot(x='t', y='y', style='.-', color='blue', label='RK-2',ylabel='Количество хищников', ax=ax2, title='Y - хищники', alpha=0.3)
df2 = pd.read_csv('data/test2.csv')
df2.plot(x='t', y='x', style='.-', color='red', label='RK-4', ax=ax1, alpha=0.3)
df2.plot(x='t', y='y', style='.-', color='red', label='RK-4', ax=ax2, alpha=0.3)
df1.plot(x='x', y='y', kind='scatter', color='blue', label='RK-2', ax=ax3, alpha=0.3, title='Фазовый портрет');
df2.plot(x='x', y='y', kind='scatter', color='red', ax=ax3, label='RK-4', alpha=0.3, xlabel='X - жертвы', ylabel='Y - хищники');
for i in [ax1, ax2, ax3]:
  i.grid(True)
fig.suptitle('Медленная модель - преобладают жертвы X/Y = 2', fontsize=16, y=1.0)
plt.tight_layout()
plt.show()
```


    
![png](output_2_0.png)
    



```python
fig, ((ax1, ax2, ax3)) = plt.subplots(1, 3, figsize=(20, 8))

df1 = pd.read_csv('data/test3.csv')
df1.plot(x='t', y='x', style='.-', color='blue', label='RK-2', ylabel='Количество жертв', title='X - жертвы', ax=ax1, alpha=0.3)
df1.plot(x='t', y='y', style='.-', color='blue', label='RK-2',ylabel='Количество хищников', ax=ax2, title='Y - хищники', alpha=0.3)
df2 = pd.read_csv('data/test4.csv')
df2.plot(x='t', y='x', style='.-', color='red', label='RK-4', ax=ax1, alpha=0.3)
df2.plot(x='t', y='y', style='.-', color='red', label='RK-4', ax=ax2, alpha=0.3)
df1.plot(x='x', y='y', kind='scatter', color='blue', label='RK-2', ax=ax3, alpha=0.3, title='Фазовый портрет');
df2.plot(x='x', y='y', kind='scatter', color='red', ax=ax3, label='RK-4', alpha=0.3, xlabel='X - жертвы', ylabel='Y - хищники');
for i in [ax1, ax2, ax3]:
  i.grid(True)
fig.suptitle('Медленная модель - преобладают хищники Y/X = 2', fontsize=16, y=1.0)
plt.tight_layout()
plt.show()
```


    
![png](output_3_0.png)
    



```python
fig, ((ax1, ax2, ax3)) = plt.subplots(1, 3, figsize=(20, 8))

df1 = pd.read_csv('data/test5.csv')
df1.plot(x='t', y='x', style='.-', color='blue', label='RK-2', ylabel='Количество жертв', title='X - жертвы', ax=ax1, alpha=0.8)
df1.plot(x='t', y='y', style='.-', color='blue', label='RK-2',ylabel='Количество хищников', ax=ax2, title='Y - хищники', alpha=0.8)
df2 = pd.read_csv('data/test6.csv')
df2.plot(x='t', y='x', style='.-', color='red', label='RK-4', ax=ax1, alpha=0.8)
df2.plot(x='t', y='y', style='.-', color='red', label='RK-4', ax=ax2, alpha=0.8)
df1.plot(x='x', y='y', kind='scatter', color='blue', label='RK-2', ax=ax3, alpha=0.8, title='Фазовый портрет');
df2.plot(x='x', y='y', kind='scatter', color='red', ax=ax3, label='RK-4', alpha=0.8, xlabel='X - жертвы', ylabel='Y - хищники');
ax1.set_xlim([0, 5])
ax2.set_xlim([0, 5])
for i in [ax1, ax2, ax3]:
  i.grid(True)
fig.suptitle('Быстрая модель - преобладают жертвы X/Y = 2', fontsize=16, y=1.0)
plt.tight_layout()
plt.show()
```


    
![png](output_4_0.png)
    



```python
fig, ((ax1, ax2, ax3)) = plt.subplots(1, 3, figsize=(20, 8))

df1 = pd.read_csv('data/test7.csv')
df1.plot(x='t', y='x', style='.-', color='blue', label='RK-2', ylabel='Количество жертв', title='X - жертвы', ax=ax1, alpha=0.8)
df1.plot(x='t', y='y', style='.-', color='blue', label='RK-2',ylabel='Количество хищников', ax=ax2, title='Y - хищники', alpha=0.8)
df2 = pd.read_csv('data/test8.csv')
df2.plot(x='t', y='x', style='.-', color='red', label='RK-4', ax=ax1, alpha=0.8)
df2.plot(x='t', y='y', style='.-', color='red', label='RK-4', ax=ax2, alpha=0.8)
df1.plot(x='x', y='y', kind='scatter', color='blue', label='RK-2', ax=ax3, alpha=0.8, title='Фазовый портрет');
df2.plot(x='x', y='y', kind='scatter', color='red', ax=ax3, label='RK-4', alpha=0.8, xlabel='X - жертвы', ylabel='Y - хищники');
ax1.set_xlim([0, 5])
ax2.set_xlim([0, 5])
for i in [ax1, ax2, ax3]:
  i.grid(True)
fig.suptitle('Быстрая модель - преобладают хищники Y/X = 2', fontsize=16, y=1.0)
plt.tight_layout()
plt.show()
```


    
![png](output_5_0.png)
    

