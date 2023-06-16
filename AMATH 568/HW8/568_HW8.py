#%% 
import scipy as sp 
import numpy as np 
import matplotlib.pyplot as plt
from numba import njit, cfunc
from numbalsoda import lsoda, lsoda_sig

#%%
def f(t, y, delta=0.01, epsilon=0.01, omega=1):
    return [y[1], -(delta + epsilon * np.cos(omega * t)) * np.sin(y[0])]

@cfunc(lsoda_sig)
def rhs(t, u, du, p): 
    du[0] = u[1]
    du[1] = -(p[0] + p[1] * np.cos(p[2] * t)) * np.sin(u[0])

func = rhs.address # address to ODE function

# %%
def Gamma(delta, epsilon, omega):
    dat=(delta, epsilon, omega)
    t_span = (0, 2 * np.pi / omega)
    
    y1_T = sp.integrate.solve_ivp(f, t_span, y0=[1, 0], args=dat).y[0][-1]

    y2_dt_T = sp.integrate.solve_ivp(f, t_span, y0=[0, 1], args=dat).y[1][-1]

    return y1_T + y2_dt_T

#%% Using Numba
def Gamma_soda(delta, epsilon, omega):
    u0 = [np.array([1.0, 0.0]), np.array([0.0, 1.0])] # Initial conditions
    t_eval = np.linspace(0, 2*np.pi/omega, 1000)
    pars = np.array([delta, epsilon, omega], np.float64)
    u1, _ = lsoda(func, u0[0], t_eval,  data=pars)
    u2, _ = lsoda(func, u0[1], t_eval,  data=pars)

    u1_T = u1[-1,0]
    u2t_T = u2[-1,1]

    return u1_T + u2t_T

# %%
d, e, o = np.linspace(0, 0.1, 50), np.linspace(0, 0.1, 50), np.linspace(0.005, 0.5, 25)
D, E, O = np.meshgrid(d, e, o)

#G2 = np.vectorize(Gamma)(D,E,O)
G_w  = np.vectorize(Gamma_soda)(D, E, O)

# %%
import matplotlib.pyplot as plt
import numpy as np

# Create a grid of subplots with two columns and five rows
fig, axs = plt.subplots(nrows=13, ncols=2, figsize=(10, 40))

# Loop over each subplot and plot the corresponding heat map
for i, ax in enumerate(axs.flatten()):
    if i < 10:
        # Plot the heat map in the current subplot
        im = ax.imshow((G_w[::-1, :, i]), cmap='jet')

        # Add a colorbar to the subplot
        fig.colorbar(im, ax=ax)
        ax.set_xlabel(r'$\delta$')
        ax.set_ylabel(r'$\epsilon$', rotation=0)
        
        # Add a title to the subplot
        ax.set_title(fr'$\omega$ = {o[i]}')
        
    else:
        # Remove the empty subplot
        fig.delaxes(ax)

# Adjust the spacing between subplots
fig.tight_layout()

# Show the plot
#plt.savefig('Gamma.png', dpi=300)


# %%
import plotly.express as px
import ipywidgets as widgets

# Create a heatmap figure using plotly.express
fig = px.imshow(G_w[:, :, 0], zmin=0, zmax=np.max(G_w), color_continuous_scale='viridis')
    
# Define the slider widget for k coordinate
slider_k = widgets.FloatSlider(
    min=o[0],
    max=o[-1],
    step=o[1]-o[0],
    value=o[0],
    description='k:',
    readout_format='.3f',
)

# Define a function for updating the figure when the slider value changes
def update_figure_k(change):
    fig.data[0].z = G_w[:, :, np.argmin(np.abs(o - change.new))]
    fig.update_layout(title_text=f'G_w at k={change.new}')

# Attach the event listener that triggers update_figure_k() when slider value changes
slider_k.observe(update_figure_k, names='value')

# Combine the figure and slider into a single output
output = widgets.VBox([fig.show(), slider_k])
output

# %%
