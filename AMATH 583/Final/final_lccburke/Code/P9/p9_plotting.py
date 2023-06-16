# %%
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

#%%
data = {'Buffer Size (Bytes)': [8, 16, 32, 64, 128, 256],
        'To GPU (Bytes/µs)': [8/45, 16/4, 32/3, 64/4, 128/4, 256/4],
        'To CPU (Bytes/µs)': [8/14, 16/12, 32/10, 64/9, 128/9, 256/9]}

df = pd.DataFrame(data)

#%%
fig, ax = plt.subplots(figsize=(10,6))

# We'll still use semilogx for the y-axis
ax.semilogx(df['Buffer Size (Bytes)'], 1e6*df['To GPU (Bytes/µs)'], label='To GPU', marker='o')
ax.semilogx(df['Buffer Size (Bytes)'], 1e6*df['To CPU (Bytes/µs)'], label='To CPU', marker='o')

# But now we set the x-axis labels manually
ax.set_xscale('log')
ax.set_yscale('log')

ax.set_xticks(df['Buffer Size (Bytes)'])
ax.set_xticklabels(df['Buffer Size (Bytes)'])

plt.grid(True, which="both", ls="--")

ax.set_xlabel('Buffer Size (Bytes)')
ax.set_ylabel('Bandwidth (Bytes/s)')

plt.title('Bandwidth vs. Buffer Size')
plt.legend()

plt.show()
