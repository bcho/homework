#ifndef EXCEPT_H
#define EXCEPT_H
#include <setjmp.h>

#define T except_t

typedef struct T {
    const char *reason;
} T;

/* exported types */
typedef struct except_frame except_frame;
struct except_frame {
    except_frame *prev;
    jmp_buf env;
    const char *file;
    int line;
    const T *exception;
};

enum {
    except_entered = 0,
    except_raised,
    except_handled,
    except_finalized
};

/* exported variables */
extern except_frame *except_stack;

/* exported functions */
void except_raise(const T *e, const char *file, int line);

/* exported marcos */
#define RAISE(e) except_raise(&(e), __FILE__, __LINE__)
#define RERAISE except_raise(_except_frame.exception, \
                             _except_frame.file, _except_frame.line)
#define RETURN switch(except_stack = except_stack.prev, 0) default: return  /* pop the except frame stack */

#define TRY do { \
    volatile int _except_flag; \
    except_frame _except_frame; \
    _except_frame.prev = except_stack; \
    except_stack = &_except_frame; \
    _except_flag = setjmp(_except_frame.env); \
    if (_except_flag == except_entered) {

#define EXCEPT(e) \
        if (_except_flag == except_entered) \
            except_stack = except_stack->prev; \
    } else if (_except_frame.exception == &(e)) { \
        _except_flag = except_handled;

#define ELSE \
        if (_except_flag == except_entered) \
            except_stack = except_stack->prev; \
    } else { \
        _except_flag = except_handled;

#define FINALLY \
        if (_except_flag == except_entered) \
            except_stack = except_stack->prev; \
    } { \
        if (_except_flag == except_entered) \
            _except_flag = except_finalized;

#define END_TRY \
        if (_except_flag == except_entered) \
            except_stack = except_stack->prev; \
    } if (_except_flag == except_raised) RERAISE; \
} while (0)



#endif
