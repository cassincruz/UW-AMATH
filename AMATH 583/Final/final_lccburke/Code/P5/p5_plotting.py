#%%
import pandas as pd
import matplotlib.pyplot as plt

#%% Define the data
data = {
    'OpenBLAS': {
        16: 0.728653,
        32: 38.0139,
        64: 47.9897,
        128: 41.8579,
        256: 57.474,
        512: 70.9636,
        1024: 76.238,
        2048: 80.439,
        4096: 81.3776,
        8192: 81.8685,
    },
    'CUBLAS': {
        16: 2.72476e-05,
        32: 0.179282,
        64: 1.34888,
        128: 10.5118,
        256: 85.7896,
        512: 210.274,
        1024: 336.138,
        2048: 411.809,
        4096: 544.386,
        8192: 553.653,
    }
}

# Convert the data to a pandas DataFrame
df = pd.DataFrame(data)

#%% Plot the data
plt.figure(figsize=(10, 6))
plt.loglog(df.index, df['OpenBLAS'], marker='o', label='OpenBLAS')
plt.loglog(df.index, df['CUBLAS'], marker='o', label='CUBLAS')
plt.xlabel('Matrix Size (n)')
plt.ylabel('Performance (GFLOPs)')
plt.xticks(df.index, labels=df.index)
plt.title('Performance Comparison of OpenBLAS vs CUBLAS')
plt.legend()
plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.show()

# %%
