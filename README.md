# Experiments With Connected Components, ER Graphs and DBSCAN

## Results and methodology

See `report.pdf`

## How to run

To run, compile all the `.cpp` files and run the resulting executable with one of the following flags:

- For dbscan experiments: `[-d|-u] filename1 filename2 ...` (use `-u` for undirected graph, if the edges are not already duplicated, and `-d` for directed graph, or if the edges are already duplicated)
- For ER experiments: `-e N NB_TEST NB_PROB MAX_VALUE path`
- For experiments on 2D plane graphs with given M & eps: `-p M EPS NB_TEST INCR_N MAX_N path`
- For experiments on 2D plane graphs with an heuristics to find M & eps: `-h NB_TEST INCR_N MAX_N path`

To create the plots, you need to use Python 3 with pandas and matplotlib. Change the file names inside the `plotter.py` file so that it matches yours, and then run `python plotter.py`
