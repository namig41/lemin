import os

def usage():
	os.system('clear')

	red			= "\x1b[31m"
	orange		= "\x1b[91m"
	blue		= "\x1b[34m"
	green		= "\x1b[32m"
	yellow		= "\x1b[33m"
	purple		= "\x1b[35m"
	pink		= "\x1b[95m"
	cyan		= "\x1b[36m"
	grey		= "\x1b[40m"
	underline	= "\x1b[4m"
	rev			= "\x1b[7m"
	bold		= "\x1b[1m"
	end			= "\x1b[0m"


	print("  {}{}{}compile:{}".format(underline, bold, cyan, end))
	print("\t{}{}make{}".format(bold, blue, end))
	print("  {}{}{}Launch visualizer:{}".format(underline, bold, cyan, end))
	print("\t{}{}python3 main.py [map_file] [-visu_option_1] [-visu_option_2] etc...{}".format(bold, blue, end))
	print("  {}{}{}Visualizer keys:{}".format(underline, bold, cyan, end))

	# Animation speed
	print("\t{}-fast:{} change the step settings from 15 to 5".format(green, end))
	print("\t{}-slow:{} change the step settings from 5 to 30".format(green, end))

	# Themes
	print("\t{}-dark_theme:{} change the theme settings".format(green, end))
	print("\t{}-blue_theme:{} change the theme settings".format(green, end))

	# Help
	print("\t{}-help:{} print all settings".format(green, end))