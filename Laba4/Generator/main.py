import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

ser = serial.Serial('COM12', 9600, timeout=0.01)
HIST_BINS = np.linspace(0, 4095, 100)

data = []

def prepare_animation(bar_container):
    def animate(frame_number):
        data.append(int(ser.readline().decode()))

        n, _ = np.histogram(data, HIST_BINS)
        for count, rect in zip(n, bar_container.patches):
            rect.set_height(count)

        return bar_container.patches

    return animate

fig, ax = plt.subplots()

_, _, bar_container = ax.hist(data, HIST_BINS, lw=1, ec="black", fc="red", alpha=0.5)

ax.set_ylim(top=50)

ani = animation.FuncAnimation(fig, prepare_animation(bar_container), 10, repeat=True, blit=True)

plt.show()
