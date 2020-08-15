import sys
from usage import usage

def check_args(args, option):
	for arg in args:
		if arg == option:
			return True
	return False

def check_graph_size(farm, settings):
	if (len(farm.nodes)) < 100:
		settings["markersize"] = 20.0
		settings["node_size"] = 500
		settings["window_size"] = (12, 8)
	elif (len(farm.nodes)) < 1000:
		settings["markersize"] = 10.0
		settings["node_size"] = 300
		settings["window_size"] = (16, 12)
	elif (len(farm.nodes)) > 1000:
		settings["markersize"] = 5.0
		settings["node_size"] = 100
		settings["window_size"] = (18, 16)
	return settings

def basic_settings(settings, args, farm):

	settings = check_graph_size(farm, settings)		
	settings["repeat"] = False
	settings["window_size"] = None
	settings["steps_between_nodes"] = 10
	settings["link_color"] = "#101010"
	settings["labels"] = dict([(farm.start, 'Start'), (farm.end, 'End')])
	settings["interval"] = 1
	settings["node_color"] = "#00ffff"

	settings["used"] = ['#F7C59F', '#5A5a86', '#7CEA9C', '#55D6BE', '#2E5EAA', '#00C9FF', '#2A324B', '#F6C0D0', '#B8E1FF', '#808D8E', '#202030']
	settings["text_color"] = "#EEEEEE"
	settings["background_color"] = "#15202b"
	settings["node_color"] = "#282828"
	settings["ant_colors_list"] = ['#15B6B6', '#15B6B6', '#1515B6', '#B615B6', '#6615B6', '#15B6B6', '#15B6B6', '#1515B6', '#B615B6', '#6615B6', '#6615B6']

	if check_args(args, "-blue_theme"):
		settings["link_color"] = "#549EDD"
		settings["used"] = ['#F7C59F', '#5A5a86', '#7CEA9C', '#55D6BE', '#2E5EAA', '#00C9FF', '#2A324B', '#F6C0D0', '#B8E1FF', '#808D8E', '#202030']
		settings["text_color"] = "#094DB9"
		settings["background_color"] = "#013FC1"
		settings["node_color"] = "#AAD1ED"
		settings["ant_colors_list"] = ['#1515B6', '#1515B6', '#1515B6', '#1515B6', '#1515B6', '#1515B6', '#1515B6', '#1515B6', '#1515B6', '#1515B6', '#1515B6']
	return settings

def print_usage(args):
	if check_args(args, "-help"):
		usage()

def set_speed(settings, args):
	if check_args(args, "-fast"):
		settings["steps_between_nodes"] = 5
	if check_args(args, "-slow"):
		settings["steps_between_nodes"] = 15
	return settings

def create_settings(args, farm):
	settings = {}
	settings = basic_settings(settings, args, farm)
	settings = set_speed(settings, args)
	check_graph_size(farm, settings)
	print_usage(args)
	return settings