#coding: utf-8

#import pygtk
#pygtk.require('2.0')
import gtk


def cb_co(slot_object, data=None):
    print slot_object


class HelloWorld(object):

    def cb_hello(self, widget, data=None):
        print widget, data
        print 'Hello World'

    def cb_delete(self, widget, event, data=None):
        print widget, event, data
        print 'delete event occurred'

        return False

    def cb_destory(self, widget, data=None):
        print widget, data
        gtk.main_quit()

    def cb_emit(self, widget, data=None):
        self.emit_button.emit(data or 'destroy')
        print 'emited!'

    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)

        # subscribe to delete event
        self.window.connect('delete_event', self.cb_delete)

        self.window.connect('destroy', self.cb_destory)

        self.window.set_border_width(10)
        self.button = gtk.Button('Hello World')
        self.button.connect('clicked', self.cb_hello, 'test')

        self.button.connect_object('clicked', cb_co, self.button)
        self.button.connect_object('clicked', gtk.Widget.destroy, self.window)

        #: emit a signal
        self.emit_button = gtk.Button('Emit!')
        self.emit_button.connect('clicked', self.cb_emit, 'destroy')

        #self.window.add(self.button)
        self.window.add(self.emit_button)

        #self.button.show()
        self.emit_button.show()
        self.window.show()

    def main(self):
        gtk.main()


if __name__ == '__main__':
    HelloWorld().main()
