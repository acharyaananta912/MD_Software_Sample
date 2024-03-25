import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("Ntime.csv");

N = df["N"];
time = df["TIME"];

plt.plot(N, time);
plt.xlabel("N")
plt.ylabel("TIME")
plt.title("Time vs N")

plt.savefig("cputime.png")
plt.close()
