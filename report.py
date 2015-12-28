

import matplotlib.pyplot as plt

# helper methods
def write_tab_line(a, out):
    counter = 0
    n = len(a)
    for x in a:
        counter += 1
        out.write('$' + x + '$' + ('&' if counter < n else '\\\\\n'))
    return

def read_form_file(file_name):
    file = open(file_name, 'r')
    arr = []
    index = 0
    for line in file:
        if index % 8 == 0:
            arr.append([[], [], [], []])
        arr[int(index / 8)][int((index % 8) / 2)].append(line)
        index += 1;
    return arr

def formatting(digit, rounding):
    if rounding > 0:
        flag = '%.' + str(rounding) + 'f'
        digit = flag % float(digit)
    return str(digit)

def prepare_array(arr, pointer):
    new_arr = []
    for group in arr:
        new_arr.append(group[pointer])
    return new_arr

def get_delta(arr, rounding = 0):
    deltas = []
    for group in arr:
        deltas.append(formatting(group[0], rounding))
    return deltas

def get_iterations(arr):
    iterations = []
    for group in arr:
        iterations.append(group[1])
    return iterations


# formulagte report files
def epsilon():
    arr = read_form_file('epsilon.in');
    epsilon_helper(arr, 'jacobi', 0)
    epsilon_helper(arr, 'seidel', 1)
    epsilon_helper(arr, 'relaxation', 2)

def epsilon_helper(arr, name, num):
    out = open('./tex/' + name + '_epsilon__gen.tex', 'w')
    n = len(arr)
    header = []
    for i in range(1, 7):
        header.append('10^{-' + str(i) + '}')
    method = prepare_array(arr, num)

    deltas = get_delta(method)
    iterations = get_iterations(method)

    out.write('\\begin{tabular}{|c|' + 'c'*(n) + '|}\n')

    out.write('\hline\n')
    write_tab_line(['\\varepsilon'] + header, out)
    out.write('\hline\n')
    write_tab_line(['\Delta'] + deltas, out)
    out.write('\hline\n')
    write_tab_line(['k'] + iterations, out)
    out.write('\hline\n')

    out.write('\\end{tabular}\n\n')

    str_nodes = []
    for i in range(1, 7):
        str_nodes.append(i)

    # iteration graphic
    iterations_graphic = name + '_epsilon_iterations.png'
    out.write('\\includegraphics{' + iterations_graphic + '}\n')

    grapthic_helper(iterations_graphic, str_nodes, iterations, 'epsilon, 10^-x', 'k, количество шагов')

    # delta graphic
    deltas_graphic = name + '_epsilon_deltas.png'
    out.write('\\includegraphics{' + deltas_graphic + '}\n')

    grapthic_helper(deltas_graphic, str_nodes, deltas, 'epsilon, 10^-x', 'delta')

def dimension():
    arr = read_form_file('dimension.in');
    dimension_helper(arr, 'jacobi', 0)
    dimension_helper(arr, 'seidel', 1)
    dimension_helper(arr, 'relaxation', 2)
    dimension_helper(arr, 'thomas', 3)

def dimension_helper(arr, name, num):
    out = open('./tex/' + name + '_dimension__gen.tex', 'w')
    n = len(arr)
    header = []
    for i in range(10, 110, 10):
        header.append(str(i))
    method = prepare_array(arr, num)

    deltas = get_delta(method, 5)
    iterations = get_iterations(method)

    out.write('\\begin{tabular}{|c|' + 'c'*(n) + '|}\n')

    out.write('\hline\n')
    write_tab_line(['N'] + header, out)
    out.write('\hline\n')
    write_tab_line(['\Delta'] + deltas, out)
    out.write('\hline\n')
    write_tab_line(['k'] + iterations, out)
    out.write('\hline\n')

    out.write('\\end{tabular}\n\n')

    # iteration graphic
    iterations_graphic = name + '_dimension_iterations.png'
    out.write('\\includegraphics{' + iterations_graphic + '}\n')

    grapthic_helper(iterations_graphic, header, iterations, 'N', 'k, количество шагов')

    # delta graphic
    deltas_graphic = name + '_dimension_deltas.png'
    out.write('\\includegraphics{' + deltas_graphic + '}\n')

    grapthic_helper(deltas_graphic, header, deltas, 'N', 'delta')

def omega():
    arr = read_form_file('omega.in');
    omega_helper(arr)

def omega_helper(arr):
    out = open('./tex/omega__gen.tex', 'w')
    n = len(arr)
    header = []
    for i in range(10, 20):
        header.append(str(i / 10))
    method = prepare_array(arr, 2)

    deltas = get_delta(method, 5)
    iterations = get_iterations(method)

    out.write('\\begin{tabular}{|c|' + 'c'*(n) + '|}\n')

    out.write('\hline\n')
    write_tab_line(['\omega'] + header, out)
    out.write('\hline\n')
    write_tab_line(['\Delta'] + deltas, out)
    out.write('\hline\n')
    write_tab_line(['k'] + iterations, out)
    out.write('\hline\n')

    out.write('\\end{tabular}\n\n')

    # iteration graphic
    iterations_graphic = 'omega_iterations.png'
    out.write('\\includegraphics{' + iterations_graphic + '}\n')

    grapthic_helper(iterations_graphic, header, iterations, 'omega', 'k, количество шагов')

    # delta graphic
    deltas_graphic = 'omega_deltas.png'
    out.write('\\includegraphics{' + deltas_graphic + '}\n')

    grapthic_helper(deltas_graphic, header, deltas, 'omega', 'delta')

def grapthic_helper(file_name, str_nodes, str_values, x_label = 'x', y_label = 'y'):
    nodes = []
    for node in str_nodes:
        nodes.append(float(node))

    values = []
    for value in str_values:
        values.append(float(value))

    plt.cla()
    plt.clf()
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.plot(nodes, values, 'b-')
    plt.savefig('./tex/' + file_name)

def create():
    print('Change epsilon...')
    epsilon()
    print('Done')
    print('Change dimension...')
    dimension()
    print('Done')
    print('Change omega...')
    omega()
    print('Done\n==============')
    print('All parts of report done. Please, run `ptflatex main.tex` for get report in pdf format.')
