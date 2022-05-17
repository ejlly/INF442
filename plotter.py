import matplotlib.pyplot as plt
import pandas as pd

# For dbscan experiment

df = pd.read_csv("experiments_results/facebook_dbscan.csv", index_col=None)
df.plot(x="M", y="max_cluster_size", marker="o")
plt.xscale("log")
plt.show()

# For ER prob experiment

sizes = [25, 100, 1000]
file_names = [f"experiments_results/ER_prob_{s}.csv" for s in sizes]

for file_name in file_names:
    df = pd.read_csv(file_name, index_col=None)
    df.plot(
        x="p",
        y=["avg_nb_composantes", "avg_nb_composantes_isolees"],
        label=["number of components", "number of isolated components"],
        marker="o",
        color=["r", "b"],
    )
    plt.yscale("log")
    plt.show()

# For 2D experiment

params = ["4_0.2", "4_0.1", "4_0.05", "8_0.1", "16_0.1", "64_0.1", "heuristics"]
file_names = [f"experiments_results/2D_{p}.csv" for p in params]

for file_name in file_names:
    fig, axes = plt.subplots(nrows=2, sharex="col")
    df = pd.read_csv(file_name, index_col=None)
    df["percent_in_noise"] = df["avg_nb_noise"] / df["n"]
    df.plot(
        x="n",
        y="avg_nb_composantes",
        label="number of components",
        marker="o",
        color="b",
        ax=axes[1],
    )
    df.plot(
        x="n",
        y="percent_in_noise",
        label="fraction of points in noise",
        marker="o",
        color="r",
        ax=axes[0],
    )
    plt.show()
