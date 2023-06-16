#%%
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Set the style of seaborn to have a clean, minimal presentation
sns.set_style("whitegrid")

#%% Create the DataFrame
data = {
    'n': [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384],
    'time': [9.17e-07, 1.47233e-06, 2.73633e-06, 8.639e-06, 7.36133e-06, 1.19307e-05, 2.7611e-05, 5.44303e-05, 0.000143875, 0.000436125, 0.0105014]
}
df = pd.DataFrame(data)

# Convert time to log10 scale
df['log_time'] = np.log10(df['time'])

#%% Plot the data
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x='n', y='log_time', marker='o')

# Set the title and labels
plt.title(r'Average Time for Row and Column Swap Operations ($n_{trials}=3$)', fontsize=14)
plt.xlabel('Matrix Dimension (n)', fontsize=12)
plt.ylabel(r'$\log_{10}$(Time) in Seconds', fontsize=12)

# Setting xticks to display the exact values of n
plt.xscale('log')
plt.xticks(df['n'], labels=df['n'], rotation=45)

plt.show()

# %%
