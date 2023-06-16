#%%
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

#%% Create a DataFrame from your data
data = {
    'n': [16, 32, 64, 128, 256, 512],
    'FFTW_time': [0.000858188, 0.00515331, 0.0579066, 0.79447, 6.62401, 244.819],
    'CUFFT_time': [0.000265693, 0.000725019, 0.00541721, 0.0371251, 0.289094, 39.7252]
}
df = pd.DataFrame(data)

# Compute the operation count for each n
df['ops'] = 2 * 3 * 5 * df['n']**3 * np.log2(df['n']) + df['n']**3

# Convert time measurements to performance
df['FFTW_perf'] = df['ops'] / df['FFTW_time']
df['CUFFT_perf'] = df['ops'] / df['CUFFT_time']

#%%
fig, ax = plt.subplots(figsize=(10,6))

# We'll still use semilogx for the y-axis
ax.semilogx(df['n'], df['FFTW_perf'], marker='o', label='FFTW')
ax.semilogx(df['n'], df['CUFFT_perf'], marker='o', label='CUFFT')

# But now we set the x-axis labels manually
ax.set_xscale('log')
ax.set_yscale('log')

ax.set_xticks(df['n'])
ax.set_xticklabels(df['n'])

#plt.grid(True, which="both", ls="--")

ax.set_xlabel('Dimension of the cubic lattices (n)')
ax.set_ylabel('Performance (FLOPs)')

plt.title('Performance of FFTW vs CUFFT on HYAK')
plt.legend()

plt.show()
# %%
