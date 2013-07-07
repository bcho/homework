#include <Python.h>

#include <stdio.h>

/* complie: gcc xxx.c -o xxx.so -I/usr/incluce/python2.7 -shared -fPIC */

static PyObject *
echo_len(PyObject *self, PyObject *args)
{
    char ping[2 << 10];
    int pong;

    PyArg_ParseTuple(args, "s#", ping, &pong);

    return Py_BuildValue("i", pong);
}

static PyObject *
echo_hello(PyObject *self, PyObject *args)
{
    printf("hello world\n");
    return PyString_FromFormat("Hello, world!");
}

/* TODO METH_KEYWORDS
static PyObject *
echo_42(PyObject *self, PyObject *args, PyObject *kw)
{
    int p1;
    double p2;
    char p3[2 << 10];
    static char *kws[] = {"p1", "p2", "p3", NULL};

    PyArg_ParseTupleAndKeywords(args, kw, "ids", kws,
            &p1, &p2, p3);

    return Py_BuildValue("i", 42);
}
*/

static PyMethodDef hello_methods[] = {
    {"echo_len", echo_len, METH_VARARGS, "echo string size"},
    {"echo_hello", echo_hello, METH_NOARGS, "echo hello world"},
    // {"echo_42", echo_42, METH_KEYWORDS, "echo 42"},
    {NULL, NULL}
};

/* function name should be initmodule_name */
void
inithello()
{
    Py_InitModule("hello", hello_methods);
}
