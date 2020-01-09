/*
 * This file was auto-generated by speedy-antlr-tool
 *  https://github.com/amykyta3/speedy-antlr-tool
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <cstring>

#include "antlr4-runtime.h"
#include "MyGrammarLexer.h"
#include "MyGrammarParser.h"
#include "speedy_antlr.h"

#include "sa_mygrammar_translator.h"

/*
 * Python function prototype:
 *  do_parse(
 *      parser_cls:antlr4.Parser,
 *      stream:antlr4.InputStream,
 *      entry_rule_name:str,
 *      sa_err_listener:SA_ErrorListener
 *  )
 */
PyObject* do_parse(PyObject *self, PyObject *args) {
    PyObject *strdata = NULL;
    PyObject *result = NULL;
    PyObject *token_module = NULL;

    try {
        // Get args
        PyObject *parser_cls = NULL;
        PyObject *stream = NULL;
        const char *entry_rule_name = NULL;
        PyObject *sa_err_listener = NULL;
        if(!PyArg_ParseTuple(args,
            "OOsO:do_parse",
            &parser_cls, &stream, &entry_rule_name, &sa_err_listener
        )) {
            return NULL;
        }

        // Extract input stream's string
        const char *cstrdata;
        Py_ssize_t bufsize;
        strdata = PyObject_GetAttrString(stream, "strdata");
        if(!strdata) throw speedy_antlr::PythonException();
        cstrdata = PyUnicode_AsUTF8AndSize(strdata, &bufsize);
        if(!cstrdata) throw speedy_antlr::PythonException();

        // Create an antlr InputStream object
        antlr4::ANTLRInputStream cpp_stream(cstrdata, bufsize);

        // in case error listener is overridden
        token_module = PyImport_ImportModule("antlr4.Token");
        if(!token_module) throw speedy_antlr::PythonException();
        speedy_antlr::Translator translator(parser_cls, stream);
        speedy_antlr::ErrorTranslatorListener err_listener(&translator, sa_err_listener);

        // Lex
        MyGrammarLexer lexer(&cpp_stream);
        if(sa_err_listener != Py_None){
            lexer.removeErrorListeners();
            lexer.addErrorListener(&err_listener);
        }
        antlr4::CommonTokenStream token_stream(&lexer);
        token_stream.fill();

        // Parse
        MyGrammarParser parser(&token_stream);
        if(sa_err_listener != Py_None){
            parser.removeErrorListeners();
            parser.addErrorListener(&err_listener);
        }
        antlr4::tree::ParseTree *parse_tree;
        if(!strcmp(entry_rule_name, "root")){
            parse_tree = parser.root();

        } else if(!strcmp(entry_rule_name, "expr")){
            parse_tree = parser.expr();

        } else if(!strcmp(entry_rule_name, "literal")){
            parse_tree = parser.literal();

        } else if(!strcmp(entry_rule_name, "number")){
            parse_tree = parser.number();

        } else if(!strcmp(entry_rule_name, "string_literal")){
            parse_tree = parser.string_literal();

        } else {
            PyErr_SetString(PyExc_ValueError, "Invalid entry_rule_name");
            throw speedy_antlr::PythonException();
        }

        // Translate Parse tree to Python
        SA_MyGrammarTranslator visitor(&translator);
        result = visitor.visit(parse_tree);

        // Clean up data
        Py_XDECREF(token_module);
        Py_XDECREF(strdata);

        return result;

    } catch(speedy_antlr::PythonException &e) {
        Py_XDECREF(token_module);
        Py_XDECREF(strdata);
        Py_XDECREF(result);

        // Python exception already has error indicator set
        return NULL;
    } catch(...) {
        Py_XDECREF(token_module);
        Py_XDECREF(strdata);
        Py_XDECREF(result);

        // An internal C++ exception was thrown.
        // Set error indicator to a generic runtime error
        PyErr_SetString(PyExc_RuntimeError, "Internal error");
        return NULL;
    }
}


extern "C" {

    static PyObject* c_do_parse(PyObject *self, PyObject *args) {
        return do_parse(self, args);
    }

    static PyMethodDef methods[] = {
        {
            "do_parse",  c_do_parse, METH_VARARGS,
            "Run parser"
        },
        {NULL, NULL, 0, NULL} /* Sentinel */
    };

    static struct PyModuleDef module = {
        PyModuleDef_HEAD_INIT,
        "sa_mygrammar_cpp_parser",   /* name of module */
        NULL, /* module documentation, may be NULL */
        -1,       /* size of per-interpreter state of the module,
                    or -1 if the module keeps state in global variables. */
        methods
    };
}


PyMODINIT_FUNC
PyInit_sa_mygrammar_cpp_parser(void) {
    PyObject *m = PyModule_Create(&module);
    return m;
}