import matplotlib.pyplot as plt
import numpy as np

# Reading and preparing data
with open('inversionModuloP.txt', 'r') as file:
    data = file.readlines()

function1_speeds = [float(data[i].strip()) for i in range(0, len(data), 2)]
function2_speeds = [float(data[i].strip()) for i in range(1, len(data), 2)]

# Calculate averages
average_function1 = np.mean(function1_speeds)
average_function2 = np.mean(function2_speeds)

# Rolling mean for smoothing
window_size = 100
function1_smooth = np.convolve(function1_speeds, np.ones(window_size) / window_size, mode='valid')
function2_smooth = np.convolve(function2_speeds, np.ones(window_size) / window_size, mode='valid')

# Identify highs and lows for both functions
lowest1, highest1 = min(function1_smooth), max(function1_smooth)
lowest2, highest2 = min(function2_smooth), max(function2_smooth)
lowest1_idx, highest1_idx = np.argmin(function1_smooth), np.argmax(function1_smooth)
lowest2_idx, highest2_idx = np.argmin(function2_smooth), np.argmax(function2_smooth)

# Create subplots
fig, axs = plt.subplots(2, 1, figsize=(14, 14), dpi=100)

# Plot for Total Cycles
axs[0].plot(function1_smooth, color='dodgerblue', label='C Implementation', linewidth=2, linestyle='-')
axs[0].axhline(average_function1, color='dodgerblue', linestyle='dashdot', linewidth=2, label=f'Avg Cycles: {average_function1:.5f}')
axs[0].plot(lowest1_idx, lowest1, 'v', color='green', markersize=10)
axs[0].text(lowest1_idx, lowest1, f'{lowest1:.5f}', color='green', va='top', ha='center')
axs[0].plot(highest1_idx, highest1, '^', color='red', markersize=10)
axs[0].text(highest1_idx, highest1, f'{highest1:.5f}', color='red', va='bottom', ha='center')
axs[0].set_title('inversionModuloP (in C)', fontsize=18, fontweight='bold', color='dodgerblue')
axs[0].set_ylabel('Cycles', fontsize=16, fontweight='bold')
axs[0].legend(loc='upper right', fontsize=12)
axs[0].grid(True, linestyle='--', linewidth=0.5, alpha=0.7)

# Plot for Cycles per Word
axs[1].plot(function2_smooth, color='crimson', label='ARMv8 Implementation', linewidth=2, linestyle='-')
axs[1].axhline(average_function2, color='crimson', linestyle='dashdot', linewidth=2, label=f'Avg Cycles: {average_function2:.5f}')
axs[1].plot(lowest2_idx, lowest2, 'v', color='green', markersize=10,)
axs[1].text(lowest2_idx, lowest2, f'{lowest2:.5f}', color='green', va='top', ha='center')
axs[1].plot(highest2_idx, highest2, '^', color='red', markersize=10)
axs[1].text(highest2_idx, highest2, f'{highest2:.5f}', color='red', va='bottom', ha='center')
axs[1].set_title('inversionModuloP (in ARMv8)', fontsize=18, fontweight='bold', color='crimson')
axs[1].set_xlabel('Run Number', fontsize=16, fontweight='bold')
axs[1].set_ylabel('Cycles', fontsize=16, fontweight='bold')
axs[1].legend(loc='upper right', fontsize=12)
axs[1].grid(True, linestyle='--', linewidth=0.5, alpha=0.7)

# Enhance layout
plt.tight_layout()
fig.patch.set_facecolor('white')
fig.patch.set_edgecolor('lightgrey')

# Show plot
plt.show()
