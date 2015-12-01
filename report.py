

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
        if index % 6 == 0:
            arr.append([[], [], []])
        arr[int(index / 6)][int((index % 6) / 2)].append(line)
        index += 1;
    return arr

def prepare_array(arr, pointer):
    new_arr = []
    for group in arr:
        new_arr.append(group[pointer])
    return new_arr

def get_delta(arr):
    deltas = []
    for group in arr:
        deltas.append(group[0])
    return deltas

def get_iterations(arr):
    iterations = []
    for group in arr:
        iterations.append(group[1])
    return iterations


# formulagte report files
def epsilon(arr):
    epsilon_helper(arr, 'jacobi', 0)
    epsilon_helper(arr, 'seidel', 1)
    epsilon_helper(arr, 'relaxation', 2)

def epsilon_helper(arr, name, num):
    out = open('./tex/' + name + '_epsilon.tex', 'w')
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

    iterations_graphic = name + '_iterations.png'
    out.write('\\includegraphics{' + iterations_graphic + '}')

    str_nodes = []
    for i in range(1, 7):
        str_nodes.append(i)

    grapthic_helper(iterations_graphic, str_nodes, iterations)

def grapthic_helper(file_name, str_nodes, str_values):
    nodes = []
    for node in str_nodes:
        nodes.append(float(node))

    values = []
    for value in str_values:
        values.append(float(value))

    plt.cla()
    plt.clf()
    plt.plot(nodes, values, 'b-')
    plt.savefig('./tex/' + file_name)


def max_error(a, b, approximate_func, true_fun, out):
    nodes_count = []
    chebyshev = []
    equidistant = []
    for i in range(8):
        nodes_count.append(8 + 2*i)
    for count in nodes_count:
        chebyshev.append(compare.chebyshev_max_error(a, b, approximate_func, true_fun, count))
        equidistant.append(compare.equidistant_max_error(a, b, approximate_func, true_fun, count))
    out.write(', где $n =' + tex_siquence(nodes_count) + '$ и вычилим максимальную погрешность в равностоящих $2n$ узлах\\\\\n')
    out.write('\\begin{tabular}{' + '|r|' + 'c'*len(nodes_count) + '|}\n')
    out.write('\hline\n')
    out.write('Кол-во узлов&')
    write_tab_line(nodes_count, 0, out)
    out.write('\hline\n')

    out.write('равн. узлы&')
    write_tab_line(equidistant, 8, out)
    out.write('Чеб. узлы&')
    write_tab_line(chebyshev, 8, out)
    out.write('\hline\n')
    out.write('\\end{tabular}\n\n')

def errors_in_points(a, b, approximate_func, true_fun, n, out):
    points = nodes.equidistant_nodes(a, b, 2*n)
    out.write('\\quad\n\\noindent Количество узлов интерполяции - ' + str(n) + '. Считаем в равноудаленных ' + str(2*n) + ' узлах.\\\\\n')
    chebyshev = compare.chebyshev_errors(a, b, approximate_func, true_fun, n)
    equidistant = compare.equidistant_errors(a, b, approximate_func, true_fun, n)
    out.write('\\begin{tabular}{|ccc|}\n')
    out.write('\hline\n')
    out.write('$x$&Погрешность(Чеб. узлы)&Погрешность (ровн. узлы)\\\\\n')
    out.write('\hline\n')
    for i in range(2*n + 1):
        arr = [points[i], chebyshev[i], equidistant[i]]
        write_tab_line(arr, 8, out)
    out.write('\hline\n')
    out.write('\\end{tabular}\\\\\n\n')
    graphic_file_name = out.name.split('/')[2].split('.')[0] + str(len(points)) + '.png'
    out.write('\\includegraphics{' + graphic_file_name + '}')
    plt.cla()
    plt.clf()
    plt.plot(points, equidistant, 'r--', points, chebyshev, 'b-')
    plt.savefig('./tex/' + graphic_file_name)

def integral_iterations(n, out):
    eps_arr = []
    iterations = []
    out.write('\\begin{tabular}{|l|' + 'c'*n + '|}\n')
    out.write('\hline\n')
    out.write('Точность&')
    for i in range(n):
        eps_arr.append(1e-2 * 1e-1**i)
    write_tab_line(eps_arr, n+1, out)
    out.write('\hline\n')
    for method in ['left_rectangle', 'center_rectangle', 'trapezoidal', 'simpson', 'gauss']:
        iterations.clear()
        for i in range(n):
            iterations.append(f.integral(2, method, eps_arr[i]))
        out.write(' '.join(method.split('_')) + '&')
        write_tab_line(iterations, 0, out)
    out.write('\hline\n')
    out.write('\\end{tabular}\\\\\n\n')

def lagrange(a, b):
    out_for_errors_in_points = open('./tex/lagrange_errors.tex', 'w')
    out_for_max_error = open('./tex/lagrange_max_error.tex', 'w')
    out_for_max_error.write('Протабулируем $L_n(x)$ на отрезке [' + str(a) + ', ' + str(b) + ']')

    errors_in_points(a, b, f.lagrange, f.taylor, 5, out_for_errors_in_points)
    errors_in_points(a, b, f.lagrange, f.taylor, 10, out_for_errors_in_points)
    max_error(a, b, f.lagrange, f.taylor, out_for_max_error)

def derivative(a, b):
    out_for_errors_in_points = open('./tex/derivative_errors.tex', 'w')
    out_for_max_error = open('./tex/derivative_of_lagrange_max_error.tex', 'w')
    out_for_max_error.write('Протабулируем $L’_n(x)$ на отрезке [' + str(a) + ', ' + str(b) + ']')

    errors_in_points(a, b, f.lagrange_for_derivative, f.derivative, 5, out_for_errors_in_points)
    errors_in_points(a, b, f.lagrange_for_derivative, f.derivative, 10, out_for_errors_in_points)
    max_error(a, b, f.lagrange_for_derivative, f.derivative, out_for_max_error)

def integral(a, b):
    out = open('./tex/integral.tex', 'w')
    integral_iterations(5, out)

def inverse(a, b):
    n = 19
    out = open('./tex/inverse.tex', 'w')
    points = nodes.equidistant_nodes(a, b, n)
    true_erf = nodes.method_for_array(points, f.taylor)
    inverse = nodes.method_for_array(points, f.inverse)
    out.write('\\begin{tabular}{|ccc|}\n')
    out.write('\hline\n')
    out.write('$x$&$erf(x)$&$erf^{-1}(x)$\\\\\n')
    out.write('\hline\n')
    for i in range(n + 1):
        arr = [points[i], true_erf[i], inverse[i]]
        write_tab_line(arr, 8, out)
    out.write('\hline\n')
    out.write('\\end{tabular}\\\\\n\n')
    graphic_file_name = out.name.split('/')[2].split('.')[0] + '.png'
    out.write('\\includegraphics{' + graphic_file_name + '}')
    plt.cla()
    plt.clf()
    plt.plot(points, true_erf, 'r--', points, inverse, 'b-')
    plt.savefig('./tex/' + graphic_file_name)

def create():
    epsilon_arr = read_form_file('epsilon.in');
    print('Change epsilon...')
    epsilon(epsilon_arr)
    print('Done')
    # print('Change dimension...')
    # dimension()
    # print('Done\n==============')
    print('All parts of report done. Please, run `ptflatex main.tex` for get report in pdf format.')
