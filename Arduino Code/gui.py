from math import sqrt
from re import S
from time import sleep
from threading import Thread

from matplotlib.animation import FuncAnimation
from matplotlib.gridspec import GridSpec
import matplotlib.pyplot as plt
from matplotlib import rcParams
import pandas as pd

sleep(1)        

plt.style.use('dark_background')

col_list = open("./data.csv", "r").readline().replace("\n", "").split(",")
rcParams["toolbar"] = "None"
gs = GridSpec(3, 3, hspace=0.4)
fig = plt.figure(figsize=(16, 9))
fig.canvas.manager.set_window_title("Hand Accelerometer Controlled Car Live GUI")
thismanager = plt.get_current_fig_manager()
thismanager.window.wm_iconbitmap("") # Include filename of picture of icon on the GUI

def animate(i):
    try:
        plt.clf()
        data = pd.read_csv("./data.csv", usecols=col_list)
        time_vals = data["time"].astype(float)
        status = "Running"
        direction = data["direction"].tolist()[-1]
        time = round(data["time"].tolist()[-1], 2)
        xAccel = data["aX"].astype(float).tolist()[-1]
        yAccel = data["aY"].astype(float).tolist()[-1]
        zAccel = data["aZ"].astype(float).tolist()[-1]
        speed = data["speed"].astype(float)
        acceleration = round((xAccel**2 + yAccel**2 + zAccel**2)**(1/2) - 400, 2)
        

        gX, gY, gZ = (
            round(data["gX"].tolist()[-1], 2),
            round(data["gY"].tolist()[-1], 2),
            round(data["gZ"].tolist()[-1], 2),
        )

        ax = plt.subplot(gs[0:1, 0])
        ax.set_title("Car Data")
        ax.get_xaxis().set_visible(False)
        ax.get_yaxis().set_visible(False)

        text = f"""
        Status: {status}
        Time: {time}s
        Direction: {direction}
        Speed: {speed.tolist()[-1]}m/s
        Acceleration: {acceleration}m/s^2
        Rotation: ({gX}, {gY}, {gZ})
        """

        ax.annotate(
            text,
            (0.025, 1),
            xycoords="axes fraction",
            va="top",
            fontsize=13,
            linespacing=1.5,
        )

        ax.spines['right'].set_visible(False)
        ax.spines['bottom'].set_visible(False)
        ax.spines['left'].set_visible(False)

        ax = plt.subplot(gs[0, 1:])
        plt.plot(time_vals, data["gX"].astype(float), label="x", color="red")
        plt.plot(time_vals, data["gY"].astype(float), label="y", color="blue")
        plt.plot(time_vals, data["gZ"].astype(float), label="z", color="green")
        ax.set_title("Gyroscope")
        ax.legend(loc="upper left")
        ax = plt.subplot(gs[2, 0:2])
        plt.plot(time_vals, speed, label="Velocity", color="purple")
        ax.set_title("Speed")
        ax.set_ylim([0, 260])
        ax.legend(loc="upper left")

        ax = plt.subplot(gs[1, 2])
        plt.plot(time_vals, data["aX"].astype(float), label="x", color="red")
        plt.plot(time_vals, data["aY"].astype(float), label="y", color="blue")
        plt.plot(time_vals, data["aZ"].astype(float), label="z", color="green")
        ax.set_title("Accelerometer")
        ax.legend(loc="upper left")

        ax = plt.subplot(gs[1, 0:2])
        plt.plot(time_vals, speed, label="Acceleration", color="orange")
        ax.set_title("Acceleration")
        ax.legend(loc="upper left")

    except Exception as e:
        print(e)
        sleep(1)

ani = FuncAnimation(plt.gcf(), animate, interval=250)
plt.tight_layout()
plt.show() 
