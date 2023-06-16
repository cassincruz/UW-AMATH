#%%
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

#%% Problem 1
# Data from the output
data = [
    {"n": 2, "Average time": 69.3333, "FLOPs": 57.6923},
    {"n": 4, "Average time": 111.333, "FLOPs": 71.8563},
    {"n": 8, "Average time": 180.333, "FLOPs": 88.7246},
    {"n": 16, "Average time": 250, "FLOPs": 128},
    {"n": 32, "Average time": 416.667, "FLOPs": 153.6},
    {"n": 64, "Average time": 764, "FLOPs": 167.539},
    {"n": 128, "Average time": 1486, "FLOPs": 172.275},
    {"n": 256, "Average time": 2944.67, "FLOPs": 173.874},
    {"n": 512, "Average time": 5805.67, "FLOPs": 176.379},
    {"n": 1024, "Average time": 11583.3, "FLOPs": 176.806},
]

df = pd.DataFrame(data)

# Plot the data using Seaborn
sns.set(style="whitegrid")
plt.figure(figsize=(10, 6))

# Convert MFLOPs to FLOPs
df["FLOPs"] = df["FLOPs"] * 1e6

# Plot the FLOPs
sns.lineplot(x="n", y="FLOPs", data=df, marker="o", label="FLOPs")

# Customize the plot
plt.xscale("log", base=2)
plt.xlabel("Matrix Size (n)", fontsize=14)
plt.ylabel("Performance (FLOPs)", fontsize=14)
plt.title("daxpy Performance Test (n_trials=3)", fontsize=16)
plt.legend(fontsize=12)

# Save the plot to a file
plt.savefig("Fig1.png", dpi=300)

# Show the plot
plt.show()

#%% Problem 2
import matplotlib.pyplot as plt
import re

# Read the text
data_txt = """n: 2
Block size: 1, Average time: 930.667 ns, FLOPs: 0.00429799 MFLOPs
Block size: 2, Average time: 625 ns, FLOPs: 0.0064 MFLOPs
Block size: 4, Average time: 597.333 ns, FLOPs: 0.00669643 MFLOPs
Block size: 8, Average time: 583.333 ns, FLOPs: 0.00685714 MFLOPs
Block size: 16, Average time: 583.333 ns, FLOPs: 0.00685714 MFLOPs
Block size: 32, Average time: 597.333 ns, FLOPs: 0.00669643 MFLOPs
Block size: 64, Average time: 583.333 ns, FLOPs: 0.00685714 MFLOPs

n: 4
Block size: 1, Average time: 805.333 ns, FLOPs: 0.00993377 MFLOPs
Block size: 2, Average time: 694.333 ns, FLOPs: 0.0115218 MFLOPs
Block size: 4, Average time: 680.667 ns, FLOPs: 0.0117532 MFLOPs
Block size: 8, Average time: 666.667 ns, FLOPs: 0.012 MFLOPs
Block size: 16, Average time: 666.667 ns, FLOPs: 0.012 MFLOPs
Block size: 32, Average time: 680.667 ns, FLOPs: 0.0117532 MFLOPs
Block size: 64, Average time: 666.667 ns, FLOPs: 0.012 MFLOPs

n: 8
Block size: 1, Average time: 1152.67 ns, FLOPs: 0.0138809 MFLOPs
Block size: 2, Average time: 1139 ns, FLOPs: 0.0140474 MFLOPs
Block size: 4, Average time: 1083.33 ns, FLOPs: 0.0147692 MFLOPs
Block size: 8, Average time: 1027.67 ns, FLOPs: 0.0155693 MFLOPs
Block size: 16, Average time: 6000 ns, FLOPs: 0.00266667 MFLOPs
Block size: 32, Average time: 1027.67 ns, FLOPs: 0.0155693 MFLOPs
Block size: 64, Average time: 1000 ns, FLOPs: 0.016 MFLOPs

n: 16
Block size: 1, Average time: 1708.33 ns, FLOPs: 0.0187317 MFLOPs
Block size: 2, Average time: 1653 ns, FLOPs: 0.0193587 MFLOPs
Block size: 4, Average time: 1652.67 ns, FLOPs: 0.0193626 MFLOPs
Block size: 8, Average time: 1597 ns, FLOPs: 0.0200376 MFLOPs
Block size: 16, Average time: 1555.67 ns, FLOPs: 0.02057 MFLOPs
Block size: 32, Average time: 1625 ns, FLOPs: 0.0196923 MFLOPs
Block size: 64, Average time: 1583.33 ns, FLOPs: 0.0202105 MFLOPs

n: 32
Block size: 1, Average time: 3000 ns, FLOPs: 0.0213333 MFLOPs
Block size: 2, Average time: 2847.33 ns, FLOPs: 0.0224772 MFLOPs
Block size: 4, Average time: 2819.67 ns, FLOPs: 0.0226977 MFLOPs
Block size: 8, Average time: 2722.33 ns, FLOPs: 0.0235092 MFLOPs
Block size: 16, Average time: 2680.67 ns, FLOPs: 0.0238747 MFLOPs
Block size: 32, Average time: 2708.33 ns, FLOPs: 0.0236308 MFLOPs
Block size: 64, Average time: 2680.33 ns, FLOPs: 0.0238776 MFLOPs

n: 64
Block size: 1, Average time: 5041.67 ns, FLOPs: 0.0253884 MFLOPs
Block size: 2, Average time: 5055.67 ns, FLOPs: 0.0253181 MFLOPs
Block size: 4, Average time: 5041.67 ns, FLOPs: 0.0253884 MFLOPs
Block size: 8, Average time: 4916.67 ns, FLOPs: 0.0260339 MFLOPs
Block size: 16, Average time: 4791.67 ns, FLOPs: 0.026713 MFLOPs
Block size: 32, Average time: 4819.67 ns, FLOPs: 0.0265579 MFLOPs
Block size: 64, Average time: 4722 ns, FLOPs: 0.0271072 MFLOPs

n: 128
Block size: 1, Average time: 9430.33 ns, FLOPs: 0.0271464 MFLOPs
Block size: 2, Average time: 9027.67 ns, FLOPs: 0.0283573 MFLOPs
Block size: 4, Average time: 9347.33 ns, FLOPs: 0.0273875 MFLOPs
Block size: 8, Average time: 9180.67 ns, FLOPs: 0.0278847 MFLOPs
Block size: 16, Average time: 8847.33 ns, FLOPs: 0.0289353 MFLOPs
Block size: 32, Average time: 8750 ns, FLOPs: 0.0292571 MFLOPs
Block size: 64, Average time: 8764 ns, FLOPs: 0.0292104 MFLOPs

n: 256
Block size: 1, Average time: 18333.3 ns, FLOPs: 0.0279273 MFLOPs
Block size: 2, Average time: 17569.7 ns, FLOPs: 0.0291411 MFLOPs
Block size: 4, Average time: 18097.3 ns, FLOPs: 0.0282915 MFLOPs
Block size: 8, Average time: 17444.7 ns, FLOPs: 0.0293499 MFLOPs
Block size: 16, Average time: 17139 ns, FLOPs: 0.0298734 MFLOPs
Block size: 32, Average time: 17055.3 ns, FLOPs: 0.0300199 MFLOPs
Block size: 64, Average time: 16916.7 ns, FLOPs: 0.030266 MFLOPs

n: 512
Block size: 1, Average time: 35152.7 ns, FLOPs: 0.0291301 MFLOPs
Block size: 2, Average time: 34680.7 ns, FLOPs: 0.0295265 MFLOPs
Block size: 4, Average time: 54569.3 ns, FLOPs: 0.0187651 MFLOPs
Block size: 8, Average time: 58333.3 ns, FLOPs: 0.0175543 MFLOPs
Block size: 16, Average time: 46958.3 ns, FLOPs: 0.0218066 MFLOPs
Block size: 32, Average time: 46208.3 ns, FLOPs: 0.0221605 MFLOPs
Block size: 64, Average time: 45819.7 ns, FLOPs: 0.0223485 MFLOPs

n: 1024
Block size: 1, Average time: 93708.3 ns, FLOPs: 0.021855 MFLOPs
Block size: 2, Average time: 93153 ns, FLOPs: 0.0219853 MFLOPs
Block size: 4, Average time: 91430.7 ns, FLOPs: 0.0223995 MFLOPs
Block size: 8, Average time: 94944.3 ns, FLOPs: 0.0215705 MFLOPs
Block size: 16, Average time: 73264 ns, FLOPs: 0.0279537 MFLOPs
Block size: 32, Average time: 71763.7 ns, FLOPs: 0.0285381 MFLOPs
Block size: 64, Average time: 71430.7 ns, FLOPs: 0.0286712 MFLOPs
"""

# Extract relevant data
pattern = re.compile(r'n: (\d+)([\s\S]*?)(?=n: |\Z)', re.MULTILINE)
matches = pattern.findall(data_txt)

ns = []
block_sizes = []
flops = []

for match in matches:
    n, block_data = int(match[0]), match[1].strip().split('\n')[1:]
    ns.append(n)
    
    bs = []
    fs = []
    
    for line in block_data:
        line_data = re.findall(r'[-+]?\d*\.\d+|\d+', line)
        block_size, flop = float(line_data[-3]), float(line_data[-1])
        bs.append(block_size)
        fs.append(flop)
    
    block_sizes.append(bs)
    flops.append(fs)

# Transpose flops list
flops_transposed = list(map(list, zip(*flops)))

# Plot data
for i, block_size in enumerate(block_sizes[0]):
    plt.plot(ns, flops_transposed[i], '-o', label=f"Block size: {int(block_size)}")

plt.title('daxpy_unroll FLOPs vs. n')
plt.xlabel('n')
plt.ylabel('MFLOPs')
plt.legend()

plt.savefig("Fig2.png")
plt.show()

#%% Problem 3
# Data from the output
data = [
    {"n": 2, "Average time": 0.908, "FLOPs": 8.81057},
    {"n": 4, "Average time": 1.237, "FLOPs": 25.869},
    {"n": 8, "Average time": 2.27, "FLOPs": 56.3877},
    {"n": 16, "Average time": 5.8, "FLOPs": 88.2759},
    {"n": 32, "Average time": 19.087, "FLOPs": 107.298},
    {"n": 64, "Average time": 57.475, "FLOPs": 142.532},
    {"n": 128, "Average time": 268.525, "FLOPs": 122.03},
    {"n": 256, "Average time": 715.329, "FLOPs": 183.233},
    {"n": 512, "Average time": 1776.04, "FLOPs": 295.2},
    {"n": 1024, "Average time": 4456.64, "FLOPs": 470.568},
]

df = pd.DataFrame(data)

# Plot the data using Seaborn
sns.set(style="whitegrid")
plt.figure(figsize=(10, 6))

# Convert MFLOPs to FLOPs
df["FLOPs"] = df["FLOPs"] * 1e6

# Plot the FLOPs
sns.lineplot(x="n", y="FLOPs", data=df, marker="o", label="FLOPs")

# Customize the plot
plt.xscale("log", base=2)
plt.xlabel("Matrix Size (n)", fontsize=14)
plt.ylabel("Performance (FLOPs)", fontsize=14)
plt.title("dgemv Performance Test (n_trials=3)", fontsize=16)
plt.legend(fontsize=12)

# Show the plot
plt.savefig("Fig4.png")
plt.show()

#%% Problem 4
# Data from the output
data = [
    {"n": 2, "Average time": 0.805667, "FLOPs": 19.8593},
    {"n": 4, "Average time": 1.36133, "FLOPs": 94.0255},
    {"n": 8, "Average time": 8.625, "FLOPs": 118.725},
    {"n": 16, "Average time": 60.4163, "FLOPs": 135.592},
    {"n": 32, "Average time": 524.736, "FLOPs": 124.893},
    {"n": 64, "Average time": 3415.69, "FLOPs": 153.494},
    {"n": 128, "Average time": 16370.4, "FLOPs": 256.213},
    {"n": 256, "Average time": 74721.2, "FLOPs": 449.062},
    {"n": 512, "Average time": 590738, "FLOPs": 454.407},
    {"n": 1024, "Average time": 5.75708e+06, "FLOPs": 373.016},
]

df = pd.DataFrame(data)

# Plot the data using Seaborn
sns.set(style="whitegrid")
plt.figure(figsize=(10, 6))

# Convert MFLOPs to FLOPs
df["FLOPs"] = df["FLOPs"] * 1e6

# Plot the FLOPs
sns.lineplot(x="n", y="FLOPs", data=df, marker="o", label="FLOPs")

# Customize the plot
plt.xscale("log", base=2)
plt.xlabel("Matrix Size (n)", fontsize=14)
plt.ylabel("Performance (FLOPs)", fontsize=14)
plt.title("dgemm Performance Test (n_trials=3)", fontsize=16)
plt.legend(fontsize=12)

# Show the plot
plt.savefig("Fig3.png")
plt.show()

#%% Problem 5
data = [
    (2, "axpy", 9.30233e+07),
    (2, "gemv", 8e+06),
    (2, "gemm", 3.2e+06),
    (4, "axpy", 1.05263e+08),
    (4, "gemv", 3.2e+07),
    (4, "gemm", 1.42222e+07),
    (8, "axpy", 8.64865e+07),
    (8, "gemv", 4.26667e+07),
    (8, "gemm", 3.41333e+07),
    (16, "axpy", 1.02894e+08),
    (16, "gemv", 7.31429e+07),
    (16, "gemm", 5.18481e+07),
    (32, "axpy", 1.18299e+08),
    (32, "gemv", 1.07789e+08),
    (32, "gemm", 7.82987e+07),
    (64, "axpy", 1.77285e+08),
    (64, "gemv", 1.41241e+08),
    (64, "gemm", 9.64474e+07),
    (128, "axpy", 1.87408e+08),
    (128, "gemv", 1.48945e+08),
    (128, "gemm", 1.4598e+08),
    (256, "axpy", 3.17618e+08),
    (256, "gemv", 2.75361e+08),
    (256, "gemm", 2.97165e+08),
    (512, "axpy", 5.81488e+08),
    (512, "gemv", 4.72332e+08),
    (512, "gemm", 3.26824e+08),
    (1024, "axpy", 5.71907e+08),
    (1024, "gemv", 4.58895e+08),
    (1024, "gemm", -3.33933e+08),
]

# Convert data to a pandas DataFrame
import pandas as pd

df = pd.DataFrame(data, columns=["n", "function", "FLOPS"])

# Set the seaborn style and context
sns.set_style("whitegrid")
sns.set_context("notebook", font_scale=1.2)

# Create the plot
plt.figure(figsize=(10, 6))
ax = sns.scatterplot(x="n", y="FLOPS", hue="function", data=df, palette="deep", marker="o", s=100)
ax.set(xscale="log", yscale="log")
ax.set_title("FLOPS vs. n for float type")
ax.set_ylabel("FLOPS")
ax.set_xlabel("n")

# Display the plot
plt.savefig("Fig5.png")
plt.show()

# %%
