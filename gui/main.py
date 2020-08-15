#! /usr/bin/python3 

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math
import networkx as nx
import sys
import parser
import class_ant
from usage import usage
from action import action
from set_paths_color import set_paths_colors
from settings import create_settings

def make_graph(farm):
	g = nx.Graph()

	g.add_nodes_from(farm.nodes)
	g.add_edges_from(farm.links)
	return g

def create_data(file):
	data = {}

	data['farm'] = parser.read_file(file)
	data['g'] = make_graph(data['farm'])
	data['pos'] = nx.spring_layout(data['g'])
	return data

def make_squad(data, settings, s_b_n):
	ant_list = []
	for nb in range(1, (int(data['farm'].ants) + 1)):
		ant = class_ant.Ant(nb)
		ant.set_node_path(data['farm'])
		ant.set_location(data['pos'], data['farm'])
		ant.set_journey(data['pos'], s_b_n, data['farm'])
		ant_list.append(ant)
	return ant_list

def main():
	try:
		data = create_data(sys.argv[-1])
		settings = create_settings(sys.argv, data['farm'])
		ant_squad = make_squad(data, settings, settings['steps_between_nodes'])
		set_paths_colors(data['farm'], ant_squad)

		fig = plt.figure(figsize=(settings['window_size']))
		ani = FuncAnimation(
			fig,
			action,
			frames = 10 * data['farm'].moves_nb * settings["steps_between_nodes"],
			fargs = (data, fig, ant_squad, settings),
			interval = settings['interval'],
			repeat = settings['repeat'],
			blit = 0)

		plt.show()
	except:
		usage()
		sys.exit(1)

if __name__ == "__main__":
	main()	