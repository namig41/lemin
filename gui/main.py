#! /usr/bin/python3 

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math
import numpy as np
import networkx as nx
import pandas as pd
import sys

df = pd.DataFrame({ 'from':['A', 'B', 'C','A'], 'to':['D', 'A', 'E','C'], 'value':[1, 10, 5, 5]})
 
# Build your graph
G=nx.from_pandas_edgelist(df, 'from', 'to', create_using=nx.Graph() )
 
# Custom the nodes:
nx.draw(G, node_color='skyblue', edge_color=df['value'], width=10.0)

plt.show()