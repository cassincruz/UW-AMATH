#%%
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

#%% Load the data
float_default = pd.read_csv('results_float_default.txt', delim_whitespace=True, names=['n', 'kij_time','jki_time'])
float_O3 = pd.read_csv('results_float_O3.txt', delim_whitespace=True, names=['n', 'kij_time','jki_time'])
float_ffast = pd.read_csv('results_float_ffast.txt', delim_whitespace=True, names=['n', 'kij_time','jki_time'])

#%% Calculate performance
for df in [float_default, float_O3, float_ffast]:
    for loop in ['kij', 'jki']:
        df[loop + '_perf'] = (2 * df['n']**3 - df['n']**2) / (df[loop + '_time'] * 1e6)  # Convert to MFLOPs

#%% Combine the data
float_default['optimization'] = 'default'
float_O3['optimization'] = 'O3'
float_ffast['optimization'] = 'ffast-math'

df_float = pd.concat([float_default, float_O3, float_ffast])

#%% "Melt" the data into long format
df_float = df_float.melt(id_vars=['n', 'optimization'], value_vars=['kij_perf', 'jki_perf'], var_name='loop_variant', value_name='performance')

#%% Remove the '_perf' from the loop_variant for cleaner plotting
df_float['loop_variant'] = df_float['loop_variant'].apply(lambda x: x.replace('_perf', ''))

#%% Plot the data
plt.figure(figsize=(10, 6))
sns.lineplot(data=df_float[df_float.loop_variant=='kij'], x='n', y='performance', hue='optimization')
plt.xscale('log', base=2)
plt.xticks([2**i for i in range(1, 10)], [2**i for i in range(1, 10)]) # specify x-ticks manually
plt.title('KIJ Loop Optimizations (Float)')
plt.xlabel('Matrix Dimension (n)')
plt.ylabel('Performance (MFLOPs)') # add units to y-axis title
plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.show()

plt.figure(figsize=(10, 6))
sns.lineplot(data=df_float[df_float.loop_variant=='jki'], x='n', y='performance', hue='optimization')
plt.xscale('log', base=2)
plt.xticks([2**i for i in range(1, 10)], [2**i for i in range(1, 10)]) # specify x-ticks manually
plt.title('JKI Loop Optimizations (Float)')
plt.xlabel('Matrix Dimension (n)')
plt.ylabel('Performance (MFLOPs)') # add units to y-axis title
plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.show()


# %%
