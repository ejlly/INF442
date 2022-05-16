import matplotlib.pyplot as plt
import pandas as pd

# For facebook dbscan experiment
df = pd.read_csv("experiments_results/facebook_dbscan.csv", index_col=None)
df.plot(x="M", y="max_cluster_size", marker="o")
plt.xscale("log")
plt.show()

# For ER prob experiment

sizes = [25,100,1000]
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
