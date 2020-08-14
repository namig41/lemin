#import networks as nx
import re

class Graph:

	def __init__(self):

		self.ants	= None
		self.start	= None
		self.end	= None
		self.nodes	= []
		self.reg_dict = {}

	def parse_file(self, file):
		
		with open(file, 'r') as f:
			for line in f:
				pass