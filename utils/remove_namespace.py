import sys, os

if len(sys.argv) != 2:
	print('run the file as:')
	print('python remove_namespace <namespace_to_remove>')
	print('for instance, to remove tools namespace:')
	print('python remove_namespace tools')
	quit()

archives = []
namespace_name = sys.argv[1]

def treat_file(file_name):
	reader = open(file_name, 'r')
	string_list = reader.readlines()
	reader.close()

	new_string_list = []

	brackets = -1
	include_line = True
	removing_namespace = False
	for string in string_list:
		if removing_namespace:
			for c in string:
				if c == '}':
					brackets -= 1
				elif c == '{':
					brackets += 1

			if brackets == 0:
				removing_namespace = False
				include_line = False
				brackets = -1
		else:
			idx1 = string.find('namespace ' + namespace_name + '{')
			idx2 = string.find('namespace ' + namespace_name + ' {')
	
			if idx1 != -1 or idx2 != -1:
				removing_namespace = True
				include_line = False
				brackets = 1

		if include_line:
			new_string_list.append(string)
		include_line = True

	if len(new_string_list) != len(string_list):
		writer = open(file_name, 'w')
		writer.write("".join(new_string_list))
		writer.close()

def recursive_search(base_path):
	for f in os.listdir(base_path):
		abs_path = os.path.join(base_path, f)

		if os.path.isfile(abs_path):
			if f.endswith('.cpp') or f.endswith('.h') or f.endswith('.hpp'):
				archives.append(abs_path)
		elif os.path.isdir(abs_path) and f != 'cmake-build-debug':
			recursive_search(abs_path)

archives = []
recursive_search(os.getcwd())
for archive in archives:
	treat_file(archive)

