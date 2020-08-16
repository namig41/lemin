import re
import sys
import networkx as nx
import matplotlib.pyplot as plt
from items import get_start, get_end, get_room, get_link, get_move
import graph
import subprocess

def regex_compile():
	reg_dict = {}

	reg_dict["is_error"]    = re.compile(r"ERROR")
	reg_dict["is_ant_nb"]   = re.compile(r"^\d+$")
	reg_dict["is_comment"]	= re.compile(r"^#")
	reg_dict["is_start"]	= re.compile(r"^#{2}(start)")
	reg_dict["is_end"]		= re.compile(r"^#{2}(end)")
	reg_dict["is_room"]		= re.compile(r"^([\d\w]+) \d+ \d+\n$")
	reg_dict["is_link"]		= re.compile(r"^([\d\w]+)-([\d\w]+)\n$")
	reg_dict["is_move"]		= re.compile(r"L([\d\w]+)-([\d\w]+)")
	return reg_dict

def check_status(g, status, line):
	if (status == None):
		return status
	elif (status == "start"):
		get_start(g, line)
	elif (status == "end"):
		get_end(g, line)
	elif (status == "comment"):
		pass
	status = None
	return status
	

def read_file(file):
	status = None
	g = graph.Graph()
	reg_dict = regex_compile()

	with open(file, 'r') as f:
		for line in f:
			status = check_status(g, status, line)
			if (reg_dict["is_ant_nb"].search(line)):
				g.ants = int(line)
			elif (reg_dict["is_start"].search(line)):
				status = "start"
			elif (reg_dict["is_end"].search(line)):
				status = "end"
			elif (reg_dict["is_room"].search(line)):
				get_room(g, line)
			elif (reg_dict["is_link"].search(line)):
				get_link(g, line)
			elif (reg_dict["is_comment"].search(line)):
				status = "comment"

	with open(file, 'r') as f:
		with subprocess.Popen(['../lem-in'], stdin=f, stdout=subprocess.PIPE) as lemin:

			for line in lemin.stdout:
				line = line.decode()
				status = check_status(g, status, line)

				if (reg_dict["is_move"].search(line)):
					get_move(g, line)
				elif (reg_dict["is_error"].search(line)):
					sys.exit("Error")
				elif (reg_dict["is_comment"].search(line)):
					status = "comment"

	g.moves_nb = len(g.moves)
	return (g)