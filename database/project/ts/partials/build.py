# coding: utf-8

output_file = 'html.ts'

var_tmpl = 'export var %s = \'%s\''
module_tmpl = 'module html {\n %s }'


def name_normalize(name):
    return name.split('.')[0].lower()


if __name__ == '__main__':
    import glob

    variables = []
    for html_file in glob.glob('*.html'):
        var_name = name_normalize(html_file)
        with open(html_file) as html:
            content = html.read().replace('\n', '')
            variables.append(var_tmpl % (var_name, content))

    with open(output_file, 'w') as output:
        module = module_tmpl % ('\n'.join(variables))
        output.write(module)
