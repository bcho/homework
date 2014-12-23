# coding: utf-8

import glob

output_file = 'html.ts'

var_tmpl = 'export var %s = \'%s\''
module_tmpl = 'module %s {\n %s }'


def name_normalize(name):
    return name.split('.')[0].lower()


def build(module_name, output_file, glob_pattern):
    variables = []
    for file_name in glob.glob(glob_pattern):
        var_name = name_normalize(file_name)
        with open(file_name) as f:
            content = f.read().replace('\n', '')
            variables.append(var_tmpl % (var_name, content))

    module = module_tmpl % (module_name, '\n'.join(variables))
    with open(output_file, 'w') as output:
        output.write(module)


if __name__ == '__main__':
    build('html', 'html.ts', '*.html')
    build('sqlQuery', 'sqlQuery.ts', '*.sql')
