

import os

def make(app = './main',  epsilon_file = 'epsilon.in', dimension_file = 'dimension.in', omega_file = 'omega.in'):
	epsilon_out = open(epsilon_file, 'w')
	dimension_out = open(dimension_file, 'w')
	omega_out = open(omega_file, 'w')
	epsilon_out.close()
	dimension_out.close()
	omega_out.close()

	change_epsilon(app, epsilon_file)
	change_dimension(app, dimension_file)
	change_omega(app, omega_file)


def change_epsilon(app, file_name):
	for order in range(1, 7):
		os.system(app + ' --epsilon=1e-' + str(order) + ' >> ' + file_name)


def change_dimension(app, file_name):
	for dimension in range(10, 110, 10):
		os.system(app + ' --numbers=' + str(dimension) + ' >> ' + file_name)

def change_omega(app, file_name):
	for omega in range(10, 20):
		os.system(app + ' --omega=' + str(omega / 10) + ' >> ' + file_name)