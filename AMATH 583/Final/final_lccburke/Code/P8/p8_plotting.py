#%%
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

#%% Data
data = {
    'n': [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]*2,
    'time': [3.0792e-05, 5.0875e-05, 7.7375e-05, 3.525e-05, 0.000158334, 0.000523167, 5.3125e-05, 4.6125e-05, 7.3416e-05, 0.000165917, 0.00221621, 0.00029025, 0.000640417, 0.00133162, 0.00256883, 0.00527467, 0.00745638, 0.00979792, 0.0160654, 0.0340043, 0.238403, 1.89986],
    'operation': ['row swap']*11 + ['col swap']*11
}

# Create DataFrame
df = pd.DataFrame(data)

#%% Plot
plt.figure(figsize=(10, 6))
sns.set(style="whitegrid")
plot = sns.lineplot(x='n', y='time', hue='operation', style='operation', markers=True, dashes=False, data=df)
plot.set(xscale="log", yscale="log")
plt.xticks(ticks=df['n'].unique(), labels=df['n'].unique())
plt.title(r'Row and Column Swap Times for Different Matrix Sizes ($n_{trials}=3$)')
plt.xlabel('Matrix Size (n)')
plt.ylabel(r'$\log_{10}$(Time) (seconds, log scale)')
plt.show()

# %%
