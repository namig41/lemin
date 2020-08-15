import re

class Graph:

	def __init__(self):

		self.ants   		= None
		self.start  		= None
		self.end    		= None
		self.moves_nb  		= None
		self.nodes  		= []
		self.used_nodes  	= []
		self.pos    		= {}
		self.links  		= []
		self.used_links		= []
		self.moves  		= []

	def __str__(self):
		return ("Ants: {}\tStart: {}\t End: {}\n".format(self.ants, self.start, self.ants) +\
				"Rooms: {}\nlinks{}\n".format(self.nodes, self.links) +\
				"Moves: {}\nMove_nb: {}\n".format(self.moves, self.moves_nb))
