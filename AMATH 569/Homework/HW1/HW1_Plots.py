# %%
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

#%% Define the function x(xi, t)
def x_function(xi, t):
    if xi <= 0:
        return xi + t
    elif 0 < xi < 1:
        return xi + t - xi * t
    else:
        return xi
    
def xi(x,t) :
    if x <= t : 
        return x-t
    elif t < x < 1 : 
        return (x-t)/(1-t)
    else: 
        return x 
    
def u(x,t):
    if xi(x,t) <= 0 :
        return 1 
    elif 0 < xi(x,t) < 1:
        return 1-xi(x,t)
    else: 
        return 0


#%% Create a meshgrid for the plot 1
xi_values = np.linspace(-5, 5, 1000)
t_values = np.linspace(0, 1, 1000)
XI, T = np.meshgrid(xi_values, t_values)
X = np.vectorize(x_function)(XI, T)

# Set the seaborn style
sns.set(style="white", context="notebook", font_scale=1.2)

# Create the plot
plt.figure(figsize=(10, 1))
contour_levels = np.linspace(np.min(X), np.max(X), 30)
contour_plot = plt.contour(XI, T, X, contour_levels, colors="black")
plt.xlabel("$\\xi$")
plt.xticks([-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5])
plt.ylabel("t")
plt.title("$x(\\xi, t)$")
plt.tight_layout()

# Show the plot
plt.show()

#%% Create a meshgrid for plot 2
x_values = np.linspace(-5, 5, 1000)
t_values = np.linspace(0, 1, 1000)
X, T = np.meshgrid(x_values, t_values)
U = np.array([[u(x, t) for x in x_values] for t in t_values])

# Set the seaborn style
sns.set(style="white", context="notebook", font_scale=1.2)

# Create the plot
plt.figure(figsize=(10, 1))
contour_levels = np.linspace(np.min(U), np.max(U), 30)
contour_plot = plt.contourf(X, T, U, contour_levels, cmap="Greys")
plt.xlabel("$x$")
plt.xticks([-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5])
plt.ylabel("$t$")
plt.title("$u(x, t)$")

# Add colorbar without labels, showing only min and max values
cbar = plt.colorbar(contour_plot, ticks=[0, 1])
cbar.ax.set_yticklabels([0, 1])

plt.tight_layout()

# Show the plot
plt.show()


# %% Plot 3

def u(x, t):
    if t < 1:
        if x <= t:
            return 1
        elif t < x < 1:
            return 1 - (x - t) / (1 - t)
        else:
            return 0
    else:
        shock_location = 1 + 0.5 * (t - 1)
        if x < shock_location:
            return 1
        else:
            return 0

X = np.linspace(-5, 5, 1000)
T = np.linspace(0, 4, 1000)

U = np.array([[u(x, t) for x in X] for t in T])

fig, ax = plt.subplots(figsize=(10, 4))
c = ax.pcolormesh(X, T, U, cmap='Greys', shading='auto')
cbar = plt.colorbar(c, ticks=[0, 1])
cbar.ax.set_yticklabels([0, 1])
#fig.colorbar(c, ax=ax)

ax.set_title('$u(x,t)$')
ax.set_xlabel('$x$')
ax.set_ylabel('$t$')

plt.show()

 
# %% Figure 4# Create a grid for x and t
import numpy as np
import matplotlib.pyplot as plt

# Create a grid for x and t
t = np.linspace(0, 4, 1000)
x = np.linspace(0, 5, 2000)

# Compute the solution u(x, t) for each point in the grid
X, T = np.meshgrid(x, t)
u = (2 * X * np.exp(T)) / (2 * np.exp(T) - 1)

# Set the valid region bounds for x
valid_region_bounds = 4 * np.exp(t) - 2

# Mask the solution outside the valid region
for i in range(len(t)):
    u[i, x > valid_region_bounds[i]] = np.nan

# Create the contour plot using matplotlib
fig, ax = plt.subplots(figsize=(10, 6))
contour_plot = ax.contourf(X, T, u, cmap='gray_r', levels=20)

# Create the colorbar
cbar = plt.colorbar(contour_plot)
min_value = np.nanmin(u)  # Get the minimum value of u, ignoring NaNs
max_value = np.nanmax(u)  # Get the maximum value of u, ignoring NaNs
cbar.set_ticks([min_value, max_value])  # Set ticks to the actual minimum and maximum values
cbar.ax.set_yticklabels([f"{min_value:.0f}", f"{max_value:.0f}"])  # Format the tick labels

# Plot the valid region boundary
ax.plot(valid_region_bounds, t, linestyle='--', color='black')

# Create a mask for the invalid region
invalid_region_mask = np.zeros_like(X, dtype=bool)
for i in range(len(t)):
    invalid_region_mask[i, x <= valid_region_bounds[i]] = True

# Fill the invalid region with a pattern
ax.contourf(X, T, invalid_region_mask, levels=[-0.5, 0.5], hatches=['xx'], colors='none', alpha=0.5)

# Set x-axis limits
ax.set_xlim(0, 5)

# Set plot labels and title
ax.set_xlabel('$x$')
ax.set_ylabel('$t$')
ax.set_title('$u(x,t)$ over the valid region')

# Show the plot
plt.show()







# %%
