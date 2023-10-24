import matplotlib.pyplot as plt
import pandas as pd

# Read the CSV file
df = pd.read_csv("output.csv")
roll = df['Roll']
pitch = df[' Pitch']
yaw = df[' Yaw']

# time array with a sample rate of 0.01 seconds
time = [0.01 * i for i in range(len(roll))]

# subplots for roll, pitch, and yaw
fig, (ax1, ax2, ax3) = plt.subplots(3, 1, sharex=1, figsize=(10, 8))

ax1.plot(time, roll, label='Roll')
ax1.set_ylabel('Roll (degrees)')
ax1.set_title('Orientation Data')
#ax1.set_ylim([-5, 20])
ax1.legend()

ax2.plot(time, pitch, label='Pitch', color='orange')
ax2.set_ylabel('Pitch (degrees)')
#ax2.set_ylim([-5, 20])
ax2.legend()

ax3.plot(time, yaw, label='Yaw', color='green')
ax3.set_xlabel('Time (seconds)')
ax3.set_ylabel('Yaw (degrees)')
#ax3.set_ylim([-5, 20])
ax3.legend()

plt.tight_layout()
plt.show()
