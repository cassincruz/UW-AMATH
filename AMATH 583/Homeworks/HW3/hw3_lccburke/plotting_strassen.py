#%%
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

#%% Load the data
strassen_default = pd.read_csv('results_strassen.txt', delim_whitespace=True, names=['n', 'time'])

#%% Calculate performance
strassen_default['performance'] = (2 * strassen_default['n']**3 - strassen_default['n']**2) / (strassen_default['time'] * 1e6)  # Convert to MFLOPs

#%% Plot the data
plt.figure(figsize=(10, 6))
sns.lineplot(data=strassen_default, x='n', y='performance')
plt.xscale('log', base=2)
plt.xticks([2**i for i in range(1, 10)], [2**i for i in range(1, 10)]) # specify x-ticks manually
plt.title('Strassen Algorithm Performance (Double)')
plt.xlabel('Matrix Dimension (n)')
plt.ylabel('Performance (MFLOPs)') # add units to y-axis title
plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.show()

# %%
