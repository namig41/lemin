import matplotlib.pyplot as plt
import networkx as nx 
def draw_node(data, name, color, size):

	node_list = []
	node_list.append(name)

	node = nx.draw_networkx_nodes(
		data['g'],
		data['pos'],
		nodelist=node_list,
		node_color=color,
		node_size=size,
		node_shape='s')

	node.set_edgecolor('#000000')
	return node


def draw_nodes(data, settings):
	for path in data['farm'].used_nodes:	
		for node in path:
			draw_node(data, node, settings['node_color'], settings['node_size'])

	for name in data['farm'].nodes:
		if name == data['farm'].start:
			draw_node(data, name, '#21319c', settings['node_size'] * 2)
		elif name == data['farm'].end:
			draw_node(data, name, '#21319c', settings['node_size'] * 2)
		else:
			draw_node(data, name, settings["node_color"], settings['node_size'])
		
def draw_ant(position, color, settings):
	ant = plt.plot([position[0]], [position[1]],
				   color=color, marker='.', markersize=settings["markersize"])
	return ant


def action(frame, data, fig, ant_squad, settings):
	
	fig.clear()

	nx.draw_networkx_edges(data['g'], data['pos'], edgelist = data['farm'].links, edge_color=settings['link_color'], width=1.0)

	for path in data['farm'].used_links:
		nx.draw_networkx_edges(data['g'], data['pos'], edgelist = path, edge_color=settings['link_color'], width=1.0)

	draw_nodes(data, settings)
	
	# draw all the ants:
	for ant in ant_squad:
		if frame < len(ant.journey):
			draw_ant(ant.journey[frame], ant.color, settings)
	
	nx.draw_networkx_labels(
		data['g'],
		data['pos'],
		font_size = 8,
		labels = settings['labels'],
		font_family = 'sans-serif',
		font_color = settings['text_color'])
	
	# set the background color
	fig.set_facecolor(settings['background_color'])

	# Hide axis
	plt.axis('off')