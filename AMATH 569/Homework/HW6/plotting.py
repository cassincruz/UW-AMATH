#%%
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
# %%
x = np.linspace(-1, 1, 1000)
# %%
f = lambda x: (x > 0)*x

f1 = lambda x: 1/4 + x*0
f2 = lambda x: 1/4 + x/2 
f3 = lambda x: 1/4 + x/2 + (5/32) *(3*x**2 - 1)
f4 = lambda x: 1/4 + x/2 + (5/32) *(3*x**2 - 1)

plt.plot(x, f(x), label="$f(x)$")
plt.plot(x, f1(x), label="$f_1(x)$")
plt.plot(x, f2(x), label="$f_2(x)$")
plt.plot(x, f3(x), label="$f_3(x)$")
plt.plot(x, f4(x), label="$f_4(x)$")
plt.legend()
# %%
